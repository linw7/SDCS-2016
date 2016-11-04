/* 
 * Weight-priority solution
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE (100 + 1)
#define W_CTRL 100
#define V_CTRL 100
#define BAG_SIZE 1000 
#define L_CHILD(i) (2 * i)
#define R_CHILD(i) (2 * i + 1)

typedef struct{
	int weight;
	int value;
	int choice;
}object;
object items[SIZE];

void init();
void swap(int i, int max);
void heap_modify(int cur, int length);
void heap_create();
void remodify(int pos);
void pack();
void print();

int main()
{
	init();
	heap_create();
	pack();
	print();
	return 0;
}

void init()
{
	int i;
	items[0].weight = 0;
	items[0].value = 0;
	items[0].choice = 0;
	for(i = 1; i < SIZE; ++i){
		items[i].weight = (rand() % W_CTRL);
		items[i].value = (rand() % V_CTRL);
		items[i].choice = 0;
	}
}

void swap(int i, int max)
{
	object temp;
	temp.weight = items[i].weight;
	temp.value = items[i].value;
	temp.choice = items[i].choice;
	items[i].weight = items[max].weight;
	items[i].value = items[max].value;
	items[i].choice = items[max].choice;
	items[max].weight = temp.weight;
	items[max].value = temp.value;
	items[max].choice = temp.choice;
}

void heap_modify(int cur, int length)
{
	int max = cur;
	int leftchild = L_CHILD(cur);
	int rightchild = R_CHILD(cur);
	if((rightchild < length) && (items[leftchild].weight >= items[rightchild].weight))
		max = leftchild;
	else if((leftchild < length) && (items[rightchild].weight >= items[leftchild].weight))
		max = rightchild;
	if(rightchild == length)
		max = leftchild;

	if(max != cur){
		if(items[max].weight > items[cur].weight){
			swap(cur, max);
			heap_modify(max, length);
		}
	}
}

void heap_create()
{
	int i;
	for(i = SIZE / 2; i >= 1; --i)
		heap_modify(i, SIZE);
}

void remodify(int pos)
{
	swap(1, pos);
	heap_modify(1, pos);
}

void pack()
{
	int pos = SIZE;
	while((items[0].weight + items[1].weight) <= BAG_SIZE){
		items[0].weight += items[1].weight;
		items[0].value += items[1].value;
		items[1].choice = 1;
		pos = pos - 1;
		remodify(pos);
	}
}

void print()
{
	int i, count = 0;
	printf("\nThe solution :");
	printf("Total weight = %4d, Total value = %4d\n\n", items[0].weight, items[0].value);
	printf("Chosen item info :\n");
	for(i = 0; i < SIZE; ++i){
		if(items[i].choice == 1){
			++count;
			printf("Weight = %4d, Value = %4d\n",items[i].weight, items[i].value);
		}
	}
	printf("\nCount item = %4d\n\n", count);
}