#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char terminals[][10] = {"$","%","(",")","*","+",",","-",".","/","<","<=","<>","=",">",">=","[","]","as","char","declare","do","else","for","foreach","from","id","if","in","letter","num","number","print","put","read","resize","string","then","to"};

char* toUpper(char *word)
{
	int i;
	for (i = 0; i < strlen(word); i++)
		word[i] = toupper(word[i]);

	return word;
}

int tokenToCode(char *token, char type)
{
	int i = 0;

	switch(type)
	{
		case 't':
		case 'i':
					while(i < 39 && strcmp(terminals[i], token))
							i++;

					if (i == 39)
						i = 42;
					break;
		case 'c':
					i = 39;
					break;
		case 's':
					i = 40;
					break;
		case 'n':
					i = 41;
					break;
	}

	// printf("Token:%s|i:%d\n", token, i);
	return i;
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
	if (code == 37 || code == 91 || code == 93 ||
		code == 39 || code == 34 || code == 00 ||
		code == 9  || code == 10 || code == 32 ||
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

						i++;

					break;
		case 'c':
					i++;

					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							line[i] != '\'' &&
							line[i] != EOF)
								if (line[i] == '\\' && (line[i+1] == '\'' || line[i+1] == '\"' || line[i+1] == 't' || line[i+1] == 'n' || line[i+1] == '\\'))
									i+=2;
								else
									i++;
						i++;

					break;
		case 'n':
		case 'i':
					while (	i < size &&
							line[i] != EOF &&
							!isSeparator(line[i]) &&
							isalnum(line[i]))
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
	token = (char**) calloc(strlen(file), sizeof(char*));

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
			token[j] = (char*) calloc(separator+1, sizeof(char));
		} while (token[j] == NULL);

		strncat(token[j], file+i, separator);
		token[j][separator] = '\0';

//		printf("|%s/\n", token[j]);
		j++;
		i += separator;
	}

	*amount = j;
	return token;
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

int* verifyTokens(char** tokens, int amount)
{
	int* codes = (int*) malloc((amount + 1) * sizeof(int));
	int i, index = 0, line = 1, flag = 0;

	for (i = 0; i < amount; i++)
	{
		if (tokens[i][0] == '\'')
		{
			if (validChar(tokens[i], line))
			{
				codes[index] = tokenToCode(tokens[i],'c');
				index++;
			}
			else
				flag = 1;
		}
		else if (tokens[i][0] == '\"')
		{
			if (validString(tokens[i], line))
			{
				codes[index] = tokenToCode(tokens[i],'s');
				index++;
			}
			else
				flag = 1;
		}
		else if (isalpha(tokens[i][0]))
		{
			codes[index] = tokenToCode(tokens[i],'i');
			index++;
		}
		else if (isdigit(tokens[i][0]))
		{
			if (validNumber(tokens[i], line))
			{
				codes[index] = tokenToCode(tokens[i],'n');
				index++;
			}
			else
				flag = 1;
		}
		else if (validSeparator(tokens[i], line))
		{
			if (*tokens[i] != ' ' && *tokens[i] != '\n' && *tokens[i] != '\t' && *tokens[i] != '\'' && *tokens[i] != '\"')
			{
				codes[index] = tokenToCode(tokens[i],'t');
				index++;
			}
		}
		else
			flag = 1;

		if (tokens[i][strlen(tokens[i]) - 1] == '\n')
			line++;
	}

	if (!flag)
		return codes;
	else
		return NULL;
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
		printf("ARQUIVO INVALIDO!\n");
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
		strcpy(name, "../Entradas/sample5.in");
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

		if (text != NULL)
		{
			char **tokens = NULL;
			int tokensAmount = 0;
			tokens = tokenizer(text, &tokensAmount);

			int *codes = NULL;
			codes = verifyTokens(tokens, tokensAmount);

			if (codes != NULL)
				printf("SIM\n");
		}
	}

	return 0;
}