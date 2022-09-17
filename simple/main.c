#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

FILE *fptr;

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

	int mat1_row, mat1_col, mat2_row, mat2_col;

	matrix1 = next_matrix(&mat1_row, &mat1_col);
	while (true)
	{
		matrix2 = next_matrix(&mat2_row, &mat2_col);
		if (matrix2 == NULL)
			break;
		// printf("mul\n");
		// printf("[%d, %d]\n", mat1_row, mat1_col);
		// printf("[%d, %d]\n", mat2_row, mat2_col);
		matrix_tmp = mul(mat1_row, mat1_col, matrix1, mat2_row, matrix2);
		mat_destroy(matrix1);
		mat_destroy(matrix2);
		matrix1 = matrix_tmp;
		mat1_col = mat2_col;
	}
	printf("Успех!");
	return 0;
}