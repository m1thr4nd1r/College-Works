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

int validSeparator(int code1, int code2)
{
	if (isSeparator(code1) &&
		(code1 != '<' || (code2 != '>' && code2 != '=' )) &&
		(code1 != '>' || code2 != '='))
			return 1;
	return 0;
}

int nextSeparator(char *line, char type)
{
	int i = 0, size = (int) strlen(line);

	switch (type)
	{
		case 's':
					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							(line[i] != '\"' || line[i-1] == '\\') &&
							line[i] != EOF)
						i++;

					break;
		case 'c':
					while (	i < size &&
							line[i] != '\n' &&
							line[i] != '\t' &&
							line[i] != 0 &&
							(line[i] != '\'' || line[i-1] == '\\') &&
							line[i] != EOF)
						i++;

					break;
		case 'n':
		case 'i':
					while (	i < size &&
							line[i] != EOF &&
							(!isSeparator(line[i]) ||
							(line[i] == '<' && (line[i+1] == '>' || line[i+1] == '=')) ||
							(line[i] == '>' && line[i+1] == '=') ||
							(line[i-1] == '<' && (line[i] == '>' || line[i] == '=')) ||
							(line[i-1] == '>' && line[i] == '=')))
						i++;
					break;
	}

	return i;
}

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

void readFile(FILE *file)
{
	char *lines;

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	lines = malloc(sizeof(char) * size);
	fread(lines, 1, size+1, file);
	fclose(file);

	int i = 0;
	while (i < size && (isPrintable(lines[i]) || lines[i] == 9 || lines[i] == 10))
		i++;
	lines[size+1] = EOF;

	if (i == size)
		processLine(lines);
	else
		printf("ARQUIVO INVÁLIDO!\n");
}

int main(int argc, char** argv)
{
	FILE *file = NULL;
	char *name = NULL;

	if (argc == 1)
	{
		name = malloc(sizeof(char) * 58);
		strcpy(name, "D:/Dropbox/Superior/Codigos/Compiladores/separators.in"); // Windows
		//strcpy(name, "./simpletest.in"); // Linux
	}
	else
//		Caso seja passado como ./a.exe < test.in, entao o indice abaixo troca de 1 para 2
		name = argv[1];

	file = fopen(name , "rt");

	if (file == NULL)
		printf("Problemas na abertura do arquivo\n");
	else
		readFile(file);

	return 0;
}
