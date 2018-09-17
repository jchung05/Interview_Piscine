#include "header.h"
#include <string.h>

# define d 256
# define q 53

int		howManyJesus(char *bible, char *jesus)
{
	int		jesusLen = strlen(jesus);
	int		bibleLen = strlen(bible);
	int		i,j = 0;
	int		jhash = 0;
	int		bhash = 0;
	int		h = 1;
	int		count = 0;

	for (i = 0; i < jesusLen - 1; i++)
		h = (h * d) % q;

	for (i = 0; i < jesusLen; i++)
	{
		bhash = (d * bhash + bible[i]) % q;
		jhash = (d * jhash + jesus[i]) % q;
	}

	for (i = 0; i <= bibleLen - jesusLen; i++)
	{
		if (jhash == bhash)
		{
			for (j = 0; j < jesusLen; j++)
				if (bible[i + j] != jesus[j])
					break;

			if (j == jesusLen)
				count++;
		}

		if (i < bibleLen - jesusLen)
		{
			bhash = (d * (bhash - bible[i] * h) + bible[i + jesusLen]) % q;

			if (bhash < 0)
				bhash += q;
		}
	}
	return (count);
}