#include "header.h"

struct s_sellers	*closestSellers(struct s_graph *parisPlaces, char *youAreHere)
{
	struct s_node		*start;
	struct s_node		*tmp;
	struct s_queue		*deque;
	struct s_queue		*bars;
	struct s_sellers	*sellers;
	int					dist;
	int					count;

	start = NULL;
	for (int i = 0; parisPlaces->places[i]; i++)
	{
		if (!strcmp(youAreHere, parisPlaces->places[i]->name))
		{
			start = parisPlaces->places[i];
			break;
		}
	}
	if (!start)
		return (NULL);

	dist = 0;
	count = 0;
	deque = queueInit();
	bars = queueInit();
	enqueue(deque, start);//Put your starting item into the deque
	enqueue(deque, NULL);
	while (deque->first)
	{
		while ((tmp = dequeue(deque)))//Pop starting item and all future enqueued items until a match value is found
		{
			tmp->visited = 1;//Mark that location node as traveled
			if (tmp->hasCerealBar)//Place with cereal found, enqueue
			{
				count++;
				enqueue(bars, tmp);
			}
			else
			{
				for (int j = 0; tmp->connectedPlaces[j]; j++)//Cereal not found, loop for a location that hasn't been visited
				{
					if (tmp->connectedPlaces[j]->visited != 1)//New location found, enqueue for next loop through
					{
						tmp->connectedPlaces[j]->visited = 1;
						enqueue(deque, tmp->connectedPlaces[j]);
					}
				}
			}
		}
		enqueue(deque, NULL);//Null queue the deque after finding a place with cereal OR deque is empty
		if (count)//If cereal was found exit the loop
			break;
		dist++;//If cereal was NOT found increase distance to travel and start over
	}

	sellers = malloc(sizeof(struct s_sellers));//Make a sellers list

	if (!sellers)
		return (NULL);

	sellers->distance = dist;
	sellers->placeNames = malloc(sizeof(char *) * count + 1);

	for (int i = 0; i < count; i++)//For each seller in the deque, iterate i and place the seller in next spot in sellers struct
		sellers->placeNames[i] = dequeue(bars)->name;

	sellers->placeNames[count] = NULL;
	return (sellers);
}