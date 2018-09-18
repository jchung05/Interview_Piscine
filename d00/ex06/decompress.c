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
	size_t		addLen = strlen(add);
	printf("Fuck me\n");

	if (s->length + addLen > s->capacity)
		return (0);
	printf("Fuck you\n");
	strcat(s->content, add);
	s->length += addLen;
	printf("Fuck everybody\n");
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
	printf("%s\n", header);

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
	printf("Fuck\n");
	struct s_string		*decompressed = stringInit();

	printf("Fuck1\n");

	//Return the list of tokens in an array
	char				**headerTok = splitHeader(cBook);
	if (!headerTok)
		return (NULL);

	printf("Fuck2\n");
	//Move the pointer past the header information
	char				*rbracket = strchr(cBook, '>');
	cBook += (rbracket - cBook);
	printf("Fuck3\n");

	//Search for @ symbol and append to those points -1
	char				*atSym = strchr(cBook, '@');
	char				*tmpContent;
	char				*toWrite;
	size_t				size;
	int					compressedChar;

	while (atSym)
	{
		printf("Fucka\n");
		size = atSym - cBook + 1;
		//Take out 1 for the @ symbol
		toWrite = (char *)malloc(sizeof(char) * size);
		printf("Fuckb\n");
		strncpy(toWrite, cBook, size - 1);
		printf("FUCK\n");
		toWrite[size - 1] = 0;
		//toWrite[size - 1] = 0;
		printf("Fuckc\n");
		printf("%d\n", size);
		printf("%s\n", toWrite);

		//Append non compressed words to decompressed object, resize if it fails
		while (!stringAppend(decompressed, toWrite))
		{
			printf("Fucking\n");
			tmpContent = decompressed->content;
			decompressed->content = realloc(decompressed->content, decompressed->capacity * 2);
			strncpy(decompressed->content, tmpContent, decompressed->length);
			free(tmpContent);
			decompressed->capacity *= 2;
		}
		printf("Fuckd\n");

		cBook += size;

		//Decipher compressed char
		compressedChar = cBook[0];
		while(!stringAppend(decompressed, headerTok[compressedChar - 1]))
		{
			tmpContent = decompressed->content;
			decompressed->content = realloc(decompressed->content, decompressed->capacity * 2);
			strncpy(decompressed->content, tmpContent, decompressed->length);
			free(tmpContent);
			decompressed->capacity *= 2;
		}
		printf("Fucke\n");

		cBook++;

		atSym = strchr(cBook, '@');
		free(toWrite);
	}

	return (decompressed->content);
}