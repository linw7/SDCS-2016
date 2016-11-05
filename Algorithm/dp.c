/*
 * DP solution
 */

#include <stdio.h>
#include <stdlib.h>

#define ITEM_NUM (10 + 1)
#define BAG_SIZE (20 + 1)
#define W_CTRL 20
#define V_CTRL 10


typedef struct{
	int weight;
	int value;
	int choice;
}object;
object items[ITEM_NUM];
int DP[ITEM_NUM][BAG_SIZE] = {0};

void init();
void pack();
void print_matrix();
void print_item();

int main()
{
	init();
	print_item();
	pack();
	print_matrix();
	return 0;
}

void init()
{
	int i;
	for(i = 1; i < ITEM_NUM; ++i){
		items[i].weight = (rand() % W_CTRL);
		items[i].value = (rand() % V_CTRL);
		items[i].choice = 0;
	}
}

void pack(){
	int i, j;
	for(i = 1; i < ITEM_NUM; ++i){
		for(j = 1; j < BAG_SIZE; ++j){
			if(j < items[i].weight){
				DP[i][j] = DP[i - 1][j];
				continue;
			}
			else if((DP[i - 1][j - items[i].weight] + items[i].value) > DP[i - 1][j])
				DP[i][j] = DP[i -1][j - items[i].weight] + items[i].value;
			else
				DP[i][j] = DP[i -1][j];
		}
	}
}

void print_matrix()
{
	int i, j;
	printf("The DP Matrix :\n");
	for(i = 0; i < ITEM_NUM; ++i){
		for(j = 0; j < BAG_SIZE; ++j)
			printf("%4d  ", DP[i][j]);
		printf("\n");
	}
	printf("\nThe max weight = %d\n", DP[ITEM_NUM - 1][BAG_SIZE - 1]);
}

void print_item()
{
	int i, count = 0;
	printf("Item info :\n");
	for(i = 1; i < ITEM_NUM; ++i)
		printf("Weight = %4d, Value = %4d\n",items[i].weight, items[i].value);
	printf("\n");
}
