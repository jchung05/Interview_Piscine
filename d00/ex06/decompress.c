#include "header.h"
#include <stdio.h>

//success: return new allocated pointer, fail: return NULL
struct s_string		*stringInit(void)
{
	struct s_string		*newstruct;

	newstruct = (struct s_string *)malloc(sizeof(struct s_string));
	if (!newstruct)
		return (NULL);
	newstruct->content = (char *)malloc(sizeof(char));
	if (!newstruct->content)
	{
		free(newstruct);
		return (NULL);
	}
	newstruct->content[0] = 0;
	newstruct->length = 0;
	newstruct->capacity = 1;
	return (newstruct);
}

//return 0 = FAIL, 1 = SUCCESS
int					stringAppend(struct s_string *s, char *add)
{
	printf("xy\n");
	//printf("%s\n", add);
	size_t		addLen = strlen(add);

	if (s->length + addLen > s->capacity)
		return (0);
	strcat(s->content, add);
	s->length += addLen;
	return (1);
}

char				**splitHeader(char *cBook)
{
	if (cBook[0] != '<')
		return (NULL);

	char			*rbracket = strchr(cBook, '>');
	char			*header = (char *)malloc(sizeof(char) * (rbracket - cBook) + 1);

	if (!header || cBook + 1 >= rbracket - 1)
		return (NULL);
	strncpy(header, cBook + 1, rbracket - cBook - 1);
	header[rbracket - cBook - 1] = 0;

	char			*tok = strtok(header, ",");

	if (!tok)
		return (NULL);

	char			**tokens = (char **)malloc(sizeof(char *) * 255);
	int				dictIdx = 0;

	while (tok)
	{
		printf("%d - %s\n", dictIdx, tok);
		tokens[dictIdx++] = tok;
		tok = strtok(NULL, ",");
	}
	tokens[dictIdx] = 0;
	free(header);

	return (tokens);
}

char				*decompress(char *cBook)
{
	struct s_string		*decompressed = stringInit();

	//Return the list of tokens in an array
	char				**headerTok = splitHeader(cBook);
	if (!headerTok)
		return (NULL);

	//Move the pointer past the header information
	char				*rbracket = strchr(cBook, '>');
	cBook += (rbracket - cBook);

	//Search for @ symbol and append to those points -1
	char				*atSym = strchr(cBook, '@');
	char				*tmpContent;
	char				*toWrite;
	size_t				size;
	int					compressedChar;
	int					addLen;

	while (atSym)
	{
		size = atSym - cBook + 1;
		//Take out 1 for the @ symbol
		toWrite = (char *)malloc(sizeof(char) * size);
		strncpy(toWrite, cBook, size - 1);
		toWrite[size - 1] = 0;
		printf("%lu\n", size);

		//Append non compressed words to decompressed object, resize if it fails
		while (!stringAppend(decompressed, toWrite))
		{
			printf("x\n");
			addLen = strlen(toWrite);
			printf("%d\t%d\t%d/%d\n", strlen(decompressed->content), addLen, decompressed->length, decompressed->capacity);
			printf("x\n");

			while (decompressed->capacity < decompressed->length + addLen)
				decompressed->capacity *= 2;
			printf("x\n");
			tmpContent = decompressed->content;
			decompressed->content = (char *)realloc(decompressed->content, decompressed->capacity);
			printf("x\n");
			strncpy(decompressed->content, tmpContent, decompressed->length);
			printf("x\n");
		}
		printf("%d\t%d/%d\n", strlen(decompressed->content), decompressed->length, decompressed->capacity);
		cBook += size;

		//Decipher compressed char
		compressedChar = cBook[0];
		printf("%d\n", compressedChar);
		while(!stringAppend(decompressed, headerTok[compressedChar - 1]))
		{
			printf("y\n");
			addLen = strlen(headerTok[compressedChar - 1]);

			while (decompressed->capacity < decompressed->length + addLen)
				decompressed->capacity *= 2;
			tmpContent = decompressed->content;
			decompressed->content = realloc(decompressed->content, decompressed->capacity);
			strncpy(decompressed->content, tmpContent, decompressed->length);
		}

		cBook++;

		atSym = strchr(cBook, '@');
		free(toWrite);
		printf("%d/%d\n", decompressed->length, decompressed->capacity);
	}

	return (decompressed->content);
}