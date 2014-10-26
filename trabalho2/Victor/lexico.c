#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* toUpper(char *word)
{
	int i;
	for (i = 0; i < strlen(word); i++)
		word[i] = toupper(word[i]);

	return word;
}

void printError(char *content, int line)
{
	printf("LINHA %d: %s\n", line, content);
}

int isPrintable(int code)
{
	if (code >= 32 && code <= 126)
		return 1;
	return 0;
}

int isSeparator(int code)
{
	if (code == 32 || code == 37 || code == 91 || code == 93 ||
		code == 39 || code == 34 || code == 00 ||
		code == 9  || code == 10 ||
		(code > 59 && code < 63) ||
		(code > 38 && code < 48))
		return 1;
	return 0;
}

int nextSeparator(char *line, char type)
{
	int i = 0, size = (int) strlen(line);

	switch (type)
	{
		case 's':
					i++;

					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							line[i] != '\"' &&
							line[i] != EOF)
								if (line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == 't' || line[i+1] == 'n' || line[i+1] == '\\'))
									i+=2;
								else
									i++;

//					if (line[i] == '\"')
						i++;

					break;
		case 'c':
					i++;

					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							line[i] != '\'' &&
//							(line[i] != '\'' || line[i-1] == '\\') &&
							line[i] != EOF)
								if (line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == 't' || line[i+1] == 'n' || line[i+1] == '\\'))
									i+=2;
								else
									i++;

//					if (line[i] == '\'')
						i++;

					break;
		case 'n':
		case 'i':
					while (	i < size &&
							line[i] != EOF &&
							!isSeparator(line[i]) &&
							isalnum(line[i]))
//							(!isSeparator(line[i]) ||
//							(line[i] == '<' && (line[i+1] == '>' || line[i+1] == '=')) ||
//							(line[i] == '>' && line[i+1] == '=') ||
//							(line[i-1] == '<' && (line[i] == '>' || line[i] == '=')) ||
//							(line[i-1] == '>' && line[i] == '=')))
						i++;
					break;
		case 't':
					if ((line[i] == '<' && (line[i+1] == '>' || line[i+1] == '=')) ||
					    (line[i] == '>' && line[i+1] == '='))
							i = 2;
					else
							i = 1;
	}

	return i;
}

char** tokenizer(char *file, int *amount)
{
	int i = 0, j = 0;
	char **token = NULL;
	token = (char**) calloc(strlen(file), sizeof(int));
//	char *token[strlen(file)];
//	char *tokens[strlen(file)];

	while (file[i] > 0 && i < strlen(file))
	{
		token[j] = NULL;

		int separator = -1;

		if (file[i] == '\'')
			separator = nextSeparator(file+i,'c');
		else if (file[i] == '\"')
			separator = nextSeparator(file+i,'s');
		else if (isalpha(file[i]))
			separator = nextSeparator(file+i,'i');
		else if (isdigit(file[i]))
			separator = nextSeparator(file+i,'n');
		else
			separator = nextSeparator(file+i,'t');

		do
		{
			//*tokens[j] = malloc(sizeof(char) * separator);
			//token[j] = malloc(sizeof(char) * separator);
			token[j] = (char*) calloc(separator+1, sizeof(char));
		} while (token[j] == NULL);

		//memset(token[j], 0, separator);
		//strncpy(token[j], file+i, separator);
//		memmove(token[j], file + i, separator);
		//memset(token[j], ' ', separator);
		strncat(token[j], file+i, separator);
		//strncpy(token[j], file+i, separator);
		token[j][separator] = '\0';

		//printf("|%s/\n", token[j]);
		j++;
		i += separator;
	}

	*amount = j;
	return token;
}

int validId(char *s)
{
	int j = 1;
	while (isalnum(s[j]))
		j++;

	return 1;

//	if (isSeparator(s[j]))
//		i = (s[j] == 34 || s[j] == 39 || s[j] == 10 || s[j] == 9)? j : j+1;
//	else
//		i = j;
}

int validNumber(char *s, int line)
{
	int j = 1;

	while (isdigit(s[j]) && j < 10)
		j++;

	if (j == strlen(s))
		return 1;
	else
	{
		printError(s, line);
		return 0;
	}
}

int validChar(char* s, int line)
{
	int j = 1, size = strlen(s), count = 0;

	if (s[size-1] == '\'')
	{
		while (isPrintable(s[j]) && j < size - 1)
		{
			if ( s[j] == '\\' &&
				 (s[j+1] == '\"' || s[j+1] == '\\' || s[j+1] == 't' || s[j+1] == 'n'  || s[j+1] == '\''))
				j++;
			else if (s[j] == '\\' || s[j] == '\"')
				break;
			j++;
			count++;
		}

		if (j == size - 1 && count == 1)
			return 1;
		else
		{
			printError(s, line);
			return 0;
		}
	}
	else
	{
		if (s[size-1] == '\t' || s[size-1] == '\n')
		{
			char temp = s[size-1];
			s[size-1] = '\0';
			printError(s, line);
			s[size-1] = temp;
		}
		else
			printError(s, line);

		return 0;
	}
}

int validString(char* s, int line)
{
	int j = 1, size = strlen(s), count = 0;

	if (s[size-1] == '\"')
	{
		while (isPrintable(s[j]) && j < size - 1)
		{
			if ( s[j] == '\\' &&
				 (s[j+1] == '\"' || s[j+1] == '\\' || s[j+1] == 't' || s[j+1] == 'n'  || s[j+1] == '\''))
				j++;
			else if (s[j] == '\\' || s[j] == '\'')
				break;
			j++;
			count++;
		}

		if (j == size - 1 && count <= 256)
			return 1;
		else
		{
			printError(s, line);
			return 0;
		}
	}
	else
	{
		if (s[size-1] == '\t' || s[size-1] == '\n')
		{
			char temp = s[size-1];
			s[size-1] = '\0';
			printError(s, line);
			s[size-1] = temp;
		}
		else
			printError(s, line);

		return 0;
	}
}

int validSeparator(char* s, int line)
{
	if ((isSeparator(s[0]) && strlen(s) == 1) ||
		(strlen(s) == 2 && ((s[0] == '>' && s[1] == '=') ||
							(s[0] == '<' && (s[1] == '>' || s[1] == '=')))))
		return 1;
	else
	{
		printError(s, line);
		return 0;
	}
}

void verifyTokens(char** tokens, int amount)
// ------------------Testar--------------------
{
	int codes[amount];
	int i, index = 0, line = 1;

	for (i = 0; i < amount; i++)
	{
		if (tokens[i][0] == '\'')
		{
			if (validChar(tokens[i], line))
			{
				codes[index] = 1;
				index++;
			}
		}
		else if (tokens[i][0] == '\"')
		{
			if (validString(tokens[i], line))
			{
				codes[index] = 1;
				index++;
			}
		}
		else if (isalpha(tokens[i][0])) // && validId(tokens[i], line))
		{
			codes[index] = 1;
			index++;
		}
		else if (isdigit(tokens[i][0]))
		{
			if (validNumber(tokens[i], line))
			{
				codes[index] = 1;
				index++;
			}
		}
		else if (validSeparator(tokens[i], line))
		{
			codes[index] = 1;
			index++;
		}

		if (tokens[i][strlen(tokens[i]) - 1] == '\n')
			line++;
	}

	if (index == amount)
		printf("SIM");
}
// ------------------Testar--------------------

void processLine(char *line)
{
	int i = 0, j, currentLine = 1;

	while (line[i] > 0)
	{
		j = i;

		if (isalpha(line[j]))
		{
			j++;
			int separator = nextSeparator(line+i, 'i');
			separator = (separator < 0)? -1: separator + i;

			while (isalnum(line[j]))
				j++;

			if (isSeparator(line[j]))
				i = (line[j] == 34 || line[j] == 39 || line[j] == 10 || line[j] == 9)? j : j+1;
			else
				i = j;
		}
		else if (isdigit(line[j]))
		{
			j++;
			int separator = nextSeparator(line+i, 'n');
			separator = (separator < 0)? -1: separator + i;

			while (isdigit(line[j]) && (j-i) < 10)
				j++;

			if (isSeparator(line[j]))
				i = (line[j] == 34 || line[j] == 39 || line[j] == 10 || line[j] == 9)? j : j+1;
			else if (isalnum(line[j]))
			{
				char error[separator - i];
				memset(error, 0, separator - i);
				strncat(error, line+i, separator - i);
				printError(error, currentLine);
				i = (line[separator] == '\n') ? separator : separator+1;
			}
			else
			{
				char error[1];
				memset(error, 0, 1);
				strncat(error, line+j, 1);
				printError(error, currentLine);
				i = (line[j] == '\n') ? j : j + 1;
			}
		}
		else if (line[j] == '\'')
		{
			j++;
			int separator = nextSeparator(line+j, 'c');
			separator = (separator == 0)? j: separator + j;

			if (isPrintable(line[j]) && j < separator)
			{
				if (line[j] == '\\' &&
					(line[j+1] == '\"' || line[j+1] == '\\' || line[j+1] == 't' || line[j+1] == 'n'  || line[j+1] == '\''))
					j+=2;
				else if (line[j] != '\\' && line[j] != '\"')
					j++;
			}

			if (line[j] == '\'' && j-i > 1)
				i = j + 1;
			else
			{
				int flag = 1 ;

				// Se o separador é valido, preciso imprimir ele no erro
				if (line[separator] == '\'')
				{
					separator++;
					flag = 0;
				}

				char error[separator-i];
				memset(error, 0, separator-i);
				strncat(error, line+i, separator-i);
				printError(error, currentLine);
				i = (line[separator] == '\n') ? separator : separator + flag;
			}
		}
		else if (line[j] == '"')
		{
			j++;
			int separator = nextSeparator(line+j, 's');
			separator = (separator == 0)? j: separator + j;
			int count = 0;

			while (isPrintable(line[j]) && count < 256 && j < separator)
			{
				if (line[j] == '\\' &&
					(line[j+1] == '\"' || line[j+1] == '\\' || line[j+1] == 't' || line[j+1] == 'n'  || line[j+1] == '\''))
					j++;
				else if (line[j] == '\\' || line[j] == '\'')
					break;
				j++;
				count++;
			}

			if (line[j] == '"')
				i = j + 1;
			else
			{
				int flag = 1 ;
				// Se o separador é valido, preciso imprimir ele no erro
				if (line[separator] == '\"')
				{
					separator++;
					flag = 0;
				}

				char error[separator-i];
				memset(error, 0, separator-i);
				strncat(error, line+i, separator-i);
				printError(error, currentLine);
				i = (line[separator] == '\n') ? separator : separator + flag;
			}
		}
		else if (line[j] == '\n')
		{
			i++;
			currentLine++;
		}
		else if (isSeparator(line[j]))
			i++;
		else
		{
			int size = 1;
			if (line[j] == '<' || line[j] == '>')
				size++;
			char error[size];
			memset(error, 0, size);
			strncat(error, line+j, size);
			printError(error, currentLine);
			i = j + size;
		}
	}
}

char* readFile(FILE *file)
{
	char *text = NULL;

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	text = (char*) malloc(sizeof(char) * (size + 1));
	fread(text, 1, size+1, file);
	fclose(file);

	int i = 0;
	while (i < size && (isPrintable(text[i]) || text[i] == 9 || text[i] == 10))
		i++;
	text[size+1] = EOF;

	if (i == size)
		return text;
	else
	{
		printf("ARQUIVO INVÁLIDO!\n");
		return NULL;
	}
}

int main(int argc, char** argv)
{
	FILE *file = NULL;
	char *name = NULL;

	if (argc == 1)
	{
		name = malloc(sizeof(char) * 58);
		//strcpy(name, "D:/Dropbox/Superior/Codigos/compiladores/sample2.in"); // Windows
		strcpy(name, "../Entradas/numbers.in"); // Windows
		//strcpy(name, "./simpletest.in"); // Linux
	}
	else
//		Caso seja passado como ./a.exe < test.in, entao o indice abaixo troca de 1 para 2
		name = argv[1];

	file = fopen(name , "rt");
	if (argc == 1) free(name);

	if (file == NULL)
		printf("Problemas na abertura do arquivo\n");
	else
	{
		char *text = readFile(file);
		//free(file);

		if (text != NULL)
		{
			char **tokens = NULL;
			int tokensAmount = 0;
//			tokens = malloc(sizeof(char) * strlen(text));
			tokens = tokenizer(text, &tokensAmount);
			verifyTokens(tokens, tokensAmount);
		}
	}

	return 0;
}
