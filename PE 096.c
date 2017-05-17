#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc.h>
#include <time.h>

#define Mc 324

struct Rows
{
	int row[Mc];
	int index, prow, pcolumn, number;
	struct Rows *next;
};

struct Rows *initrows()
{
	struct Rows *rows;
	int i;
	rows = (struct Rows *)malloc(sizeof(struct Rows));
	for (i = 0; i < Mc; i++)
	{
		rows->row[i] = 0;
	}
	rows->index = -1;
	rows->prow = -1;
	rows->pcolumn = -1;
	rows->number = -1;
	rows->next = NULL;
	return(rows);
}

void appendrows(struct Rows *rows, int i, int j, int num)
{
	struct Rows *rowsnode, *newnode;
	int n;
	rowsnode = rows;
	while (rowsnode->next != NULL)
	{
		rowsnode = rowsnode->next;
	}
	newnode = (struct Rows *)malloc(sizeof(struct Rows));
	rowsnode->next = newnode;

	for (n = 0; n < Mc; n++)
	{
		newnode->row[n] = 0;
	}
	//position limit
	newnode->row[9 * i + j] = 1;
	//column limit
	newnode->row[9 * j + num - 1 + 9 * 9] = 1;
	//row limit
	newnode->row[9 * i + num - 1 + 9 * 9 * 2] = 1;
	//area limit
	newnode->row[(i / 3 + j / 3 * 3) * 9 + num - 1 + 9 * 9 * 3] = 1;
	newnode->prow = i;
	newnode->pcolumn = j;
	newnode->number = num;
	newnode->index = rowsnode->index + 1;
	newnode->next = NULL;
}

void deleterows(struct Rows *rows)
{
	struct Rows *rowsnode;
	rowsnode = rows;
	if (rowsnode->next != NULL)
	{
		while (rowsnode->next->next != NULL)
		{
			rowsnode = rowsnode->next;
		}
		free(rowsnode->next->next);
		rowsnode->next = NULL;
	}
}

void freerows(struct Rows *rows)
{
	while (rows->next != NULL)
	{
		deleterows(rows);
	}
	free(rows);
}

struct DancingLinks
{
	struct DancingLinks *L, *R, *U, *D, *C;
	int S, column, row;
};

struct DancingLinks *createnode(int i, int j)
{
	struct DancingLinks *node;
	node = (struct DancingLinks *)malloc(sizeof(struct DancingLinks));
	node->L = node;
	node->R = node;
	node->U = node;
	node->D = node;
	node->C = node;
	node->S = 0;
	node->row = i;
	node->column = j;
	return(node);
}

struct DancingLinks *searchnode(struct DancingLinks *h, int i, int j)
{
	struct DancingLinks *result;
	result = h;
	while (result->column != j)
	{
		result = result->R;
	}
	while (result->row != i)
	{
		result = result->D;
	}
	return(result);
}

struct DancingLinks *initdancinglinks(struct Rows *M, int Mr)
{
	struct DancingLinks *h = createnode(-1, -1);
	h->C = NULL;
	h->U = NULL;
	h->D = NULL;

	int i, j;
	struct DancingLinks *newnode, *tempnode, *tempnodeh, *tempnodev;
	struct Rows *temprows;

	tempnodeh = h;
	for (j = 0; j < Mc; j++)
	{
		newnode = createnode(-1, j);
		tempnodeh->R = newnode;
		newnode->L = tempnodeh;
		tempnodeh = newnode;
		tempnodev = tempnodeh;
		for (i = 0; i < Mr; i++)
		{
			temprows = M;
			while (temprows->index != i)
			{
				temprows = temprows->next;
			}
			if (temprows->row[j] == 1)
			{
				newnode = createnode(i, j);
				tempnodev->D = newnode;
				newnode->U = tempnodev;
				newnode->C = tempnodeh;
				tempnodev = newnode;
			}
		}
		newnode->D = tempnodeh;
		tempnodeh->U = newnode;
	}
	h->L = tempnodeh;
	tempnodeh->R = h;

	for (i = 0; i < Mr; i++)
	{
		temprows = M;
		while (temprows->index != i)
		{
			temprows = temprows->next;
		}
		for (j = 0; j < Mc; j++)
		{
			if (temprows->row[j] == 1)
			{
				break;
			}
		}
		tempnodev = searchnode(h, i, j);
		tempnodeh = tempnodev;
		for (j = j + 1; j < Mc; j++)
		{
			if (temprows->row[j] == 1)
			{
				tempnode = searchnode(h, i, j);
				tempnode->L = tempnodeh;
				tempnodeh->R = tempnode;
				tempnodeh = tempnode;
			}
		}
		tempnodeh->R = tempnodev;
		tempnodev->L = tempnodeh;
	}
	return(h);
}

struct DancingLinks *countones(struct DancingLinks *h)
{
	struct DancingLinks *tempnodeh, *tempnodev;
	int tempS = INT_MAX;
	struct DancingLinks *result = h;
	tempnodeh = h->R;
	while (tempnodeh->column != -1)
	{
		tempnodev = tempnodeh->D;
		while (tempnodev->row != -1)
		{
			tempnodeh->S = tempnodeh->S + 1;
			tempnodev = tempnodev->D;
		}
		if (tempnodeh->S<tempS)
		{
			tempS = tempnodeh->S;
			result = tempnodeh;
		}
		tempnodeh = tempnodeh->R;
	}
	return(result);
}

void coverc(struct DancingLinks *c)
{
	struct DancingLinks *i, *j;
	c->R->L = c->L;
	c->L->R = c->R;
	i = c->D;
	while (i != c)
	{
		j = i->R;
		while (j != i)
		{
			j->D->U = j->U;
			j->U->D = j->D;
			j->C->S = j->C->S - 1;
			j = j->R;
		}
		i = i->D;
	}
}

void uncoverc(struct DancingLinks *c)
{
	struct DancingLinks *i, *j;
	i = c->U;
	while (i != c)
	{
		j = i->L;
		while (j != i)
		{
			j->C->S = j->C->S + 1;
			j->D->U = j;
			j->U->D = j;
			j = j->L;
		}
		i = i->U;
	}
	c->R->L = c;
	c->L->R = c;
}

struct List
{
	int r;
	struct List *next;
};

struct List *initlist()
{
	struct List *list;
	list = (struct List *)malloc(sizeof(struct List));
	list->r = INT_MAX;
	list->next = NULL;
	return(list);
}

void appendlist(struct List *list, int nr)
{
	if (list->r != -1)
	{
		struct List *listnode, *newnode;
		listnode = list;
		while (listnode->next != NULL)
		{
			listnode = listnode->next;
		}
		newnode = (struct List *)malloc(sizeof(struct List));
		listnode->next = newnode;
		newnode->r = nr;
		newnode->next = NULL;
	}
}

void deletelist(struct List *list)
{
	if (list->r != -1)
	{
		struct List *listnode;
		listnode = list;
		if (listnode->next != NULL)
		{
			while (listnode->next->next != NULL)
			{
				listnode = listnode->next;
			}
			free(listnode->next->next);
			listnode->next = NULL;
		}
	}
}

void search(struct DancingLinks *h, struct List *ans)
{
	if (h->R == h)
	{
		ans->r = -1;
		return;
	}
	struct DancingLinks *c, *r, *j;
	c = countones(h);
	coverc(c);
	r = c->D;
	while (r != c)
	{
		appendlist(ans, r->row);
		j = r->R;
		while (j != r)
		{
			coverc(j->C);
			j = j->R;
		}
		search(h, ans);
		deletelist(ans);
		j = r->L;
		while (j != r)
		{
			uncoverc(j->C);
			j = j->L;
		}
		r = r->D;
	}
	uncoverc(c);
}

void freelist(struct List *list)
{
	list->r = INT_MAX;
	while (list->next != NULL)
	{
		deletelist(list);
	}
	free(list);
}

void freedancinglinks(struct DancingLinks *h)
{
	struct DancingLinks *tempnodeh, *tempnodev;
	tempnodeh = h->L;
	while (tempnodeh->column != -1)
	{
		tempnodev = tempnodeh->U;
		while (tempnodev->row != -1)
		{
			tempnodev = tempnodev->U;
			free(tempnodev->D);
		}
		tempnodeh = tempnodeh->L;
		free(tempnodeh->R);
	}
	free(h);
}

int main(void)
{
	clock_t start, finish;
	FILE *stream;
	errno_t err;
	char buffer[11];
	int Mat[9][9];
	int grid = 0, gridi = 0, gridj = 0;
	int Solution = 0;

	start = clock();

	err = fopen_s(&stream, "PE 096.txt", "r");


	while (! feof(stream))
	{
		fgets(buffer, 11, stream);
		if (buffer[0] < 48 || buffer[0]>57)
		{
			grid = grid + 1;
			gridi = 0;
			gridj = 0;
			continue;
		}
		else
		{
			for ( gridj = 0; gridj < 9; gridj++)
			{
				Mat[gridi][gridj] = buffer[gridj] - 48;
			}
		}
		gridi = gridi + 1;
		if (gridi == 9)
		{
			struct DancingLinks *head;
			struct List *answer;
			struct Rows *rows;
			int Mr, i, j, x;
			int solution[9][9];

			rows = initrows();
			Mr = 0;
			//printf("Grid %d\n",grid);
			for (i = 0; i < 9; i++)
			{
				for (j = 0; j < 9; j++)
				{
					//printf("%d ", Mat[i][j]);
					if (Mat[i][j] != 0)
					{
						appendrows(rows, i, j, Mat[i][j]);
						Mr = Mr + 1;
					}
					else
					{
						for (x = 1; x < 10; x++)
						{
							appendrows(rows, i, j, x);
							Mr = Mr + 1;
						}
					}
				}
				//printf("\n");
			}

			head = initdancinglinks(rows, Mr);
			answer = initlist();

			search(head, answer);

			struct Rows *temprows = initrows();
			struct List *templist = answer;
			while (templist->next != NULL)
			{
				templist = templist->next;
				temprows = rows->next;
				while (temprows->index != templist->r)
				{
					temprows = temprows->next;
				}
				solution[temprows->prow][temprows->pcolumn] = temprows->number;
			}
			solution[temprows->prow][temprows->pcolumn] = temprows->number;

			for (j = 0; j < 3; j++)
			{
				Solution = Solution + solution[0][j] * (100 * (j == 0) + 10 * (j == 1) + (j == 2));
			}			

			freerows(rows);
			freelist(answer);
			freedancinglinks(head);
		}
	}

	finish = clock();
	printf("%d\n", Solution);
	printf("Elapsed time is %f seconds\n", (double)(finish - start) / 1000);
	system("pause");
	return 0;
}