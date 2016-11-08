/*
 * Branch-Bound solution
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE (10 + 1)
#define W_CTRL 5
#define V_CTRL 15
#define BAG_SIZE 10

typedef struct{
	int weight;
	int value;
	int divide;
}object;

typedef struct{
	int c_weight;
	int c_value;
	int lb;
	int ub;
	int level;
}node;

typedef struct{
	node active[SIZE];
	int front;
	int rear;
}node_queue;
node_queue queue;
int best_value = 0;

object items[SIZE];

void init();
void print();
void insert_sort();
void init_queue();
int LB();
int UB();
void pack();
void check(int level);
void enqueue(node new);
void update(node left, node right);
void dequeue();
int empty();
void print();


int main()
{
	init();
	print();
	insert_sort();
	init_queue();
	pack();
	print();
	return 0;
}

void init()
{
	int i;
	items[0].weight = 0;
	items[0].value = 0;
	items[0].divide = 0;
	for(i = 1; i < SIZE; ++i){
		items[i].weight = (rand() % W_CTRL) + 1;
		items[i].value = (rand() % V_CTRL);
		items[i].divide = (int)(items[i].value / items[i].weight);
	}
	insert_sort();
}

void shift(int i, int j)
{
	int move = i - 1;
	int start = j;
	object temp;
	temp.weight = items[i].weight;
	temp.value = items[i].value;
	temp.divide = items[i].divide;
	for(move; move >= start; --move){
		items[move + 1].weight = items[move].weight;
		items[move + 1].value = items[move].value;
		items[move + 1].divide = items[move].divide;
 	}
 	items[start].weight = temp.weight;
 	items[start].value = temp.value;
 	items[start].divide = temp.divide;
}

void insert_sort()
{
	int i, j;
	for(i = 2; i < SIZE; ++i){
		for(j = 1; j < i; ++j){
			if(items[i].divide > items[j].divide)
				shift(i, j);
		}
	}
}

int LB(int c_weight, int c_value, int level)
{
	int i;
	int current_weight = c_weight;
	int current_value = c_value;
	for(i = level + 1; i < SIZE; ++i){
		if((current_weight + items[i].weight) < BAG_SIZE){
			current_weight = current_weight + items[i].weight;
			current_value = current_value + items[i].value;
		}
	}
	return current_value;
}

int UB(int c_weight, int c_value, int level)
{
	int i;
	float k;
	int current_weight = c_weight;
	int current_value = c_value;
	if(current_weight > BAG_SIZE)
		return current_value;
	for(i = level + 1; i < SIZE; ++i){
		if((current_weight + items[i].weight) < BAG_SIZE)
			k = 1;
		else 
			k = (float)((BAG_SIZE - current_weight)*1.0 / items[i].weight);
		current_weight = current_weight + k * items[i].weight;
		current_value = current_value + k * items[i].value;
	}
	return current_value;
}

void init_queue()
{
	queue.front = 1;
	queue.rear = 1;
	queue.active[queue.rear].c_weight = 0;
	queue.active[queue.rear].c_value = 0;
	queue.active[queue.rear].level = 1;
	queue.active[queue.rear].lb = LB(0, 0, 0);
	queue.active[queue.rear].ub = UB(0, 0, 0);
        printf("%d   %d\n", queue.active[queue.rear].lb, queue.active[queue.rear].ub);
	++queue.rear;
}

void enqueue(node new)
{
	queue.active[queue.rear].c_weight = new.c_weight;
	queue.active[queue.rear].c_value = new.c_value;
	queue.active[queue.rear].lb = new.lb;
	queue.active[queue.rear].ub = new.ub;
	queue.active[queue.rear].level = new.level;
	++queue.rear;
}

void update(node left, node right)
{
	if((left.c_weight > BAG_SIZE) || (left.ub < best_value))
		;
	else if(left.ub == left.lb)
		best_value = left.ub;
	else 
		enqueue(left);

	if((right.c_weight > BAG_SIZE) || (right.ub < best_value))
		;
	else if(right.ub == right.lb)
		best_value = right.ub;
	else 
		enqueue(right);
}

void check(int level)
{
	node left, right;
	left.c_weight = queue.active[queue.front].c_weight + items[level].weight;
	left.c_value = queue.active[queue.front].c_value + items[level].value;
	left.lb = LB(left.c_weight, left.c_value, level);
	left.ub = UB(left.c_weight, left.c_value, level);
	left.level = level + 1;
	right.c_weight = queue.active[queue.front].c_weight;
	right.c_value = queue.active[queue.front].c_value;
	right.lb = LB(right.c_weight, right.c_value, level);
	right.ub = UB(right.c_weight, right.c_value, level);
	right.level = level + 1;
    update(left, right);
	printf("left: c_weight = %d, c_value = %d, lb = %d, ub = %d, level = %d\n", left.c_weight, left.c_value, left.lb, left.ub, left.level);
	printf("right: c_weight = %d, c_value = %d, lb = %d, ub = %d, level = %d\n", right.c_weight, right.c_value, right.lb, right.ub, right.level);
}

void dequeue()
{
	check(queue.active[queue.front].level);
	if(queue.active[queue.rear].level == SIZE){
		if(queue.active[queue.rear].c_value > best_value)  
			best_value = queue.active[queue.rear].c_value;
	}
	++queue.front;
}

int empty()
{
	if(queue.front == queue.rear)
		return 1;
	else 
		return 0;
}

void pack()
{	
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	dequeue();
	
}

void print()
{
	int i, count = 0;
	// printf("\nThe solution :");
	// printf("Total weight = %4d, Total value = %4d\n\n", items[0].weight, items[0].value);
	// printf("Chosen item info :\n");
	for(i = 0; i < SIZE; ++i){
		/*
		if(items[i].choice == 1){
			++count;
			printf("Weight = %4d, Value = %4d\n",items[i].weight, items[i].value);
		}
		*/
		printf("Weight = %4d, Value = %4d, Divide = %4d\n",items[i].weight, items[i].value, items[i].divide);
	}
	printf("%d\n", best_value);
	// printf("\nCount item = %4d\n\n", count);
}
