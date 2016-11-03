#include <stdio.h>
#include <string.h>
#include <math.h>

#define pi 3.14

int matrix[8][8] = {0};
float dct_matrix[8][8] = {0};
float quan_matrix[8][8] = {16, 11, 10, 16, 24, 40, 51, 61,
                           12, 12, 14, 19, 26, 58, 60, 55,
                           14, 13, 16, 24, 40, 57, 69, 56,
                           14, 17, 22, 29, 51, 87, 80, 62,
                           18, 22, 37, 56, 68, 109, 103, 77,
                           24, 35, 55, 64, 81, 104, 113, 92,
                           49, 64, 78, 87, 103, 121, 120, 101,
                           72, 92, 95, 98, 112, 100, 103, 99};
float sq_matrix[8][8] = {0};
float rsq_matrix[8][8] = {0};
float rdct_matrix[8][8] = {0};

void read();
float do_cos(int a, int b);
float dct(int u, int v);
void do_dct();
float sq(int u, int v);
void do_sq();
void do_rsq();
void set_round();
float rdct(int i, int j);
void do_rdct();

void printf_matrix_i();
void printf_matrix_d();
void printf_matrix_q();
void printf_matrix_sq();
void printf_matrix_rsq();
void printf_matrix_rdct();


int main()
{
	read();
 
	printf_matrix_i();

	do_dct();
	printf_matrix_d();

	printf_matrix_q();

    do_sq();
    set_round();
    printf_matrix_sq();

    do_rsq();
    printf_matrix_rsq();

    do_rdct();
    printf_matrix_rdct();

	return 0;
}

void read()
{
	char c;
	char str_num[10] = {'\0'};
	int i = 0, j = 0, k = 0;
	int u = 0, v = 0;
	FILE *fp;
	fp = fopen("file", "rb+");

	while((c = getc(fp)) != EOF){
		if((c == ' ') || (c == '\n')){
			k = 0;
			continue;
		}
		else{
			str_num[k++] = c;
			if(k == 3){
				str_num[3] = '\0';
				matrix[i][j++] = (atoi(str_num) - 128);
			}
			if(j == 8){
				++i;
				j = 0;
			}
		}
	}
}

float do_cos(int a, int b)
{
	return cos(((2 * a + 1) * b * pi) / 16);
}

float dct(int u, int v)
{
	float c_u, c_v;
	float sum = 0;
	float value;
	int i, j;
	
	if(u == 0)
		c_v = (float)(1.0 / sqrt(2.0));
	else 
		c_v = (float)1.0;

	if(v == 0)
		c_u = (float)(1.0 / sqrt(2.0));
	else 
		c_u = (float)(1.0);

	value = 0.25 * c_u * c_v;

	for(i = 0; i < 8; ++i)
		for(j = 0; j < 8; ++j)
			sum = sum + (matrix[i][j] * do_cos(i, u) * do_cos(j, v)); 

    return value * sum;  
}

void do_dct()
{
	int u, v;
	for(u = 0 ; u < 8; ++u){
		for(v = 0; v < 8; ++v){
			dct_matrix[u][v] = dct(u, v);
		}
	}
}

float sq(int u, int v)
{
	float value = dct_matrix[u][v] / quan_matrix[u][v];
	if((value > -0.49) && (value < 0.49))
		return 0.0;
	else 
		return value;
}

void do_sq()
{
	int u, v;
	for(u = 0; u < 8; ++u){
		for(v = 0; v < 8; ++v)
			sq_matrix[u][v] = sq(u, v);
	}
}

void do_rsq()
{
	int i, j;
	for(i = 0; i < 8; ++i){
		for(j = 0; j < 8; ++j){
			rsq_matrix[i][j] = quan_matrix[i][j] * sq_matrix[i][j];
		}
	}
}

void set_round()
{    
	float value;
    int i, j;
    for(i = 0; i < 8; ++i){
    	for(j = 0; j < 8; ++j){
    		if(sq_matrix[i][j] > 0){
    			value = ceil(sq_matrix[i][j]);
    			if(value - sq_matrix[i][j] >= 0.5)
    				sq_matrix[i][j] = value - 1;
    			else 
    				sq_matrix[i][j] = value;
    		}
    		else{
    		    value = floor(sq_matrix[i][j]);
    		    if(sq_matrix[i][j] - value >= 0.5)
    		    	sq_matrix[i][j] = value + 1;
    		    else
    		    	sq_matrix[i][j] = value;
    		}
    	}
    }
}

float rdct(int i, int j)
{
	float c_u, c_v;
	float value = 0;
	int u, v;
	
	for(u = 0; u < 8; ++u){
		for(v = 0; v < 8; ++v){
		    if(v == 0)
		        c_v = (float)(1.0 / sqrt(2.0));
	        else 
		        c_v = (float)1.0;

	        if(u == 0)
		        c_u = (float)(1.0 / sqrt(2.0));
	        else 
		        c_u = (float)(1.0);

			value = value + c_u * c_v * rsq_matrix[u][v] * do_cos(i, u) * do_cos(j, v);
		}
	}
	return 0.25 * value;
}

void do_rdct()
{
	int i, j;
	for(i = 0; i < 8; ++i)
		for(j = 0; j < 8; ++j){
			rdct_matrix[i][j] = rdct(i, j) + 128;
		}
}


void printf_matrix_i()
{
	printf("                      ");
	printf("******   Initial Matrix   ******\n");
	int i, j;
	for(i = 0; i < 8 ; ++i){
	    for(j = 0; j < 8; ++j)
			printf("%7d  ", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printf_matrix_d()
{
	printf("                        ");
	printf("******   DCT Matrix   ******\n");

	int i, j;
	for(i = 0; i< 8 ; ++i){
		for(j = 0; j < 8; ++j)
			printf("%7.1f  ", dct_matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printf_matrix_q()
{
	printf("                        ");
	printf("******   QUAN Matrix   ******\n");

	int i, j;
	for(i = 0; i< 8 ; ++i){
		for(j = 0; j < 8; ++j)
			printf("%7.0f  ", quan_matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printf_matrix_sq()
{
	printf("                        ");
	printf("******   SQUAN Matrix   ******\n");

	int i, j;
	for(i = 0; i< 8 ; ++i){
		for(j = 0; j < 8; ++j)
			printf("%7.0f  ", sq_matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printf_matrix_rsq()
{
	printf("                        ");
	printf("******   RSQUAN Matrix   ******\n");

	int i, j;
	for(i = 0; i< 8 ; ++i){
		for(j = 0; j < 8; ++j)
			printf("%7.0f  ", rsq_matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void printf_matrix_rdct()
{
	printf("                         ");
	printf("******   RDCT Matrix   ******\n");

	int i, j;
	for(i = 0; i< 8 ; ++i){
		for(j = 0; j < 8; ++j)
			printf("%7.0f  ", rdct_matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}