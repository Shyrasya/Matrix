#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

enum operation_return_codes { OK, INVALID_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int is_matr_str_null(matrix_t *value);
void sequent_filling(matrix_t *value, double fill_start, double step);
int is_number_inf_or_nan(matrix_t value);
int is_rows_columns_posit(matrix_t value);
int is_rows_columns_2_matr_eq(matrix_t A, matrix_t B);
int copy_matrix(matrix_t *A, matrix_t *copy_matrix);
void triang_matrix(matrix_t *copy_A, double *result);
int finf_diag_null_elem(int g, matrix_t *copy_A);
void create_mini_matrix(matrix_t *A, matrix_t *mini_matrix, int c, int r);
// void print_matrix(matrix_t value);

#endif