/*
 * Recall solution
 */

#include <stdio.h>
#include <stdlib.h>

#define ITEM_NUM (10 + 1)
#define BAG_SIZE 20
#define W_CTRL 20
#define V_CTRL 10


typedef struct{
	int weight;
	int value;
	int choice;
}object;
object items[ITEM_NUM];
int current_weight = 0;
int current_value = 0;
int best_value = 0;
int times = 0;

void init();
void print_item();
void pack();
void recall(int i);

int main()
{
	init();
	print_item();
	pack();
	printf("Searched node = %d\n", times);
	printf("Best value = %d\n", best_value);
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

void print_item()
{
	int i, count = 0;
	printf("Item info :\n");
	for(i = 1; i < ITEM_NUM; ++i)
		printf("Weight = %4d, Value = %4d\n",items[i].weight, items[i].value);
	printf("\n");
}

void pack()
{
	recall(1);
}

void recall(int i)
{
	int j;
	times += 1;
	if(i > ITEM_NUM - 1){
		if(current_value > best_value)
			best_value = current_value;
		return;
	}
	if(current_weight + items[i].weight <= BAG_SIZE){
		current_weight += items[i].weight;
		current_value += items[i].value;
		recall(i + 1);
		current_weight -= items[i].weight;
	    current_value -=items[i].value;
	}
	recall(i + 1);
}