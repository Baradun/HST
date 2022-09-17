#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>


FILE *fptr;
int SIZE = 10000000;

struct m
{
	int row;
	int col;
	int **matrix;
};


int **mat_init(int n_rows, int n_cols)
{
	int **m;
	int i;
	m = (int **)malloc(n_rows * sizeof(int *));
	m[0] = (int *)calloc(n_rows * n_cols, sizeof(int));
	for (i = 1; i < n_rows; ++i)
		m[i] = m[i - 1] + n_cols;
	return m;
}

void mat_destroy(int **m)
{
	free(m[0]);
	free(m);
}

int **mul(int n_a_rows, int n_a_cols, int *const *a, int n_b_cols, int *const *b)
{
	int i, j, k;
	int **m;
	m = mat_init(n_a_rows, n_b_cols);
	for (i = 0; i < n_a_rows; ++i)
	{
		for (j = 0; j < n_b_cols; ++j)
		{
			int t = 0;
			for (k = 0; k < n_a_cols; ++k)
				t += a[i][k] * b[k][j];
			m[i][j] = t;
		}
	}
	return m;
}

int **next_matrix(int *row, int *col)
{
	int m, n, k;
	if (fscanf(fptr, "%d", &m) == EOF)
		return NULL;
	fscanf(fptr, "%d", &n);
	*row = m;
	*col = n;
	int **matrix = mat_init(m, n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (fscanf(fptr, "%d", &k) == EOF)
				return NULL;
			matrix[i][j] = k;
		}
	}
	return matrix;
}

int main()
{

	fptr = fopen("data.txt", "r");
	int **matrix1;
	int **matrix2;
	int **matrix_tmp;
	
	// struct m matrix_list[SIZE];
	struct m* matrix_list = malloc(SIZE * sizeof(struct m));

	int mat1_row, mat1_col, mat2_row, mat2_col;
	int i;
	for(i = 0; i < SIZE; ++i)
	{
		matrix_tmp = next_matrix(&mat1_row, &mat1_col);
		if (matrix1 == NULL)
			break;
		matrix_list[i].row = mat1_row;
		matrix_list[i].col = mat1_col;
		matrix_list[i].matrix = matrix_tmp;
	}

	// start timer 
	struct timeval t1, t2;
	double elapsedTime;
	gettimeofday(&t1, NULL);
	//

	for(i = 0; i < SIZE; ++i){
		if(i == 0){
			mat1_row = matrix_list[i].row;
			mat1_col = matrix_list[i].col;
			matrix1 = matrix_list[i].matrix;
			continue;
		}
		mat2_row = matrix_list[i].row;
		mat2_col = matrix_list[i].col;
		matrix2 = matrix_list[i].matrix;

		matrix_tmp = mul(mat1_row, mat1_col, matrix1, mat2_row, matrix2);
		matrix1 = matrix_tmp;
		mat1_col = mat2_col;
	}
	// end timer
	gettimeofday(&t2, NULL);
	//
	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("t: %f \n", elapsedTime);

	return 0;
}