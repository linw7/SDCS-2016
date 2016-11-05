/*
 * DP solution
 * Space - Optimization
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
int DP[BAG_SIZE] = {0};

void init();
int max(int i, int j);
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

int max(int i, int j)
{
	if(DP[j] > (DP[j - items[i].weight] + items[i].value))
		return DP[j];
	else
		return (DP[j - items[i].weight] + items[i].value);

}

void pack(){
	int i, j;
	for(i = 1; i < ITEM_NUM; ++i){
		for(j = BAG_SIZE - 1; j >= items[i].weight; --j){
			DP[j] = max(i, j);
		}
	}
}

void print_matrix()
{
	int i;
	printf("DP array :\n");
	for(i = 0; i < BAG_SIZE; ++i)
		printf("%4d ", DP[i]);
	printf("\nThe max weight = %d\n", DP[BAG_SIZE - 1]);
}

void print_item()
{
	int i, count = 0;
	printf("Item info :\n");
	for(i = 1; i < ITEM_NUM; ++i)
		printf("Weight = %4d, Value = %4d\n",items[i].weight, items[i].value);
	printf("\n");
}
