#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
	int front, rear, size;
	int *dices;
}DicesCB;

void CBinit (DicesCB *cb, int size)
{
	cb->size = size + 1;
	cb->front = 0;
	cb->rear = 0;
	cb->dices = (int *)malloc(sizeof(int) * (cb->size));
}

bool CBisempty (DicesCB *cb)
{
	if (cb->front == cb->rear)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CBisfull (DicesCB *cb)
{
	if ((cb->rear + 1) % (cb->size) == cb->front)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CBinsert (DicesCB *cb, int Diceone, int Dicetwo)
{
	if (CBisfull(cb))
	{
		cb->front = (cb->front + 2) % (cb->size);
	}
	if (Diceone <= Dicetwo)
	{
		cb->dices[cb->rear] = Diceone;
		cb->rear = (cb->rear + 1) % (cb->size);
		cb->dices[cb->rear] = Dicetwo;
		cb->rear = (cb->rear + 1) % (cb->size);
	}
	else
	{
		cb->dices[cb->rear] = Dicetwo;
		cb->rear = (cb->rear + 1) % (cb->size);
		cb->dices[cb->rear] = Diceone;
		cb->rear = (cb->rear + 1) % (cb->size);
	}
}

bool CBisidentical(DicesCB *cb)
{
	if (CBisfull(cb))
	{
		if (cb->dices[cb->front] == cb->dices[(cb->front + 2) % (cb->size)] && cb->dices[cb->front] == cb->dices[(cb->front + 4) % (cb->size)])
		{
			if (cb->dices[(cb->front + 1) % (cb->size)] == cb->dices[(cb->front + 3) % (cb->size)] && cb->dices[(cb->front + 1) % (cb->size)] == cb->dices[(cb->front + 5) % (cb->size)] )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void CBprint(DicesCB *cb)
{
	int i = cb->front;
	while (i != cb->rear)
	{
		printf("%d\t", cb->dices[i]);
		i = (i + 1) % (cb->size);
	}
	printf("\n");
}


int rollem (int Sides)
{
	return (1 + rand() % Sides);
}


int main (void)
{
	clock_t start, finish;
	int i,n,N = 1000000;
	int size = 6;
	int sides = 4;
	int diceone, dicetwo, position;
	DicesCB dicescb;
	int monopoly[40] = { 0 };
	int chest[16] = { 0 };
	int chance[16] = { 0 };
	int indexcc = 0;
	int indexch = 0;
	int index = 0;
	int result = 0;

	start = clock();

	CBinit(&dicescb, size);
	chest[0] = 1;
	chest[1] = 2;
	for (n = 0; n < 9; n++)
	{
		chance[n] = n + 1;
	}
	position = 0;
	for (n = 0; n < N; n++)
	{
		diceone = rollem(sides);
		dicetwo = rollem(sides);
		CBinsert(&dicescb, diceone, dicetwo);
		position = (position + diceone + dicetwo) % 40;

		if (CBisidentical(&dicescb) || position ==30)
		{
			position = 10;
			monopoly[position]++;
			continue;
		}

		if (position == 2 || position == 17 || position == 33)
		{
			switch (chest[indexcc])
			{
			case 1: position = 0;
				break;
			case 2: position = 10;
				break;
			default:
				break;
			}
			monopoly[position]++;
			indexcc = (indexcc + 1) % 16;
			continue;
		}

		if (position == 7 || position== 22 || position== 36)
		{
			switch (chance[indexch])
			{
			case 1: position = 0;
				break;
			case 2: position = 10;
				break;
			case 3: position = 11;
				break;
			case 4: position = 24;
				break;
			case 5: position = 39;
				break;
			case 6: position = 5;
				break;
			case 7: position = (((position + 5) / 10) * 10 + 5) % 40;
				break;
			case 8: position = (((position + 5) / 10) * 10 + 5) % 40;
				break;
			case 9: position = (position == 22) ? 28 : 12;
				break;
			case 10: position = position - 3;
				if (position == 33)
				{
					switch (chest[indexcc])
					{
					case 1: position = 0;
						break;
					case 2: position = 10;
						break;
					default:
						break;
					}
					indexcc = (indexcc + 1) % 16;
				}
				break;
			default:
				break;
			}
			monopoly[position]++;
			indexch = (indexch + 1) % 16;
			continue;
		}
		
		monopoly[position]++;
	}

	for (i = 0; i < 3; i++)
	{
		for (n = 0; n < 40; n++)
		{
			if (monopoly[n]>monopoly[index])
			{
				index = n;
			}
		}
		switch (i)
		{
		case 0: result = result + index * 10000;
			break;
		case 1: result = result + index * 100;
			break;
		case 2: result = result + index;
		default:
			break;
		}
		monopoly[index] = 0;
		index = 0;
	}

	printf("%d\n", result);

	finish = clock();
	printf("Elapsed time is %f seconds\n",(double)(finish - start) / 1000);
	system("pause");
}