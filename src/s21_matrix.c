#include "s21_matrix.h"

/**
 * @brief Создалась ли матрица?   0 - да,  1 - некорректная матрица
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (is_matr_str_null(result) || (rows <= 0 || columns <= 0))
    return INVALID_MATRIX;
  result->matrix = (double **)calloc((size_t)rows, sizeof(double *));

  int index = 0;
  while (rows > index) {
    result->matrix[index] = (double *)calloc((size_t)columns, sizeof(double));
    index++;
  }

  result->rows = rows;
  result->columns = columns;
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (!is_matr_str_null(A) && is_rows_columns_posit(*A)) {
    for (int m = 0; m < A->rows; m++) {
      if (A->matrix[m] != NULL) free(A->matrix[m]);
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
}

// void print_matrix(matrix_t value) {
//   for (int m = 0; m < value.rows; m++) {
//     for (int n = 0; n < value.columns; n++) {
//       printf("%f ", value.matrix[m][n]);
//     }
//     printf("\n");
//   }
// }

/**
 * @brief Заполняет пошагово (step) матрицу числами от введенного старта и далее
 * числа +1
 */
void sequent_filling(matrix_t *value, double fill_start, double step) {
  for (int m = 0; m < value->rows; m++) {
    for (int n = 0; n < value->columns; n++) {
      value->matrix[m][n] = fill_start;
      fill_start += step;
    }
  }
}

/**
 * @brief Матричная структура указывает на NULL?   1 - да,  0 - нет
 */
int is_matr_str_null(matrix_t *value) {
  int code = FAILURE;
  if (value == NULL) code = SUCCESS;
  return code;
}

/**
 * @brief Есть ли в матрице число, равное бесконечности или NaN?   1 - да,  0 -
 * нет
 */
int is_number_inf_or_nan(matrix_t value) {
  int code = FAILURE;
  for (int m = 0; m < value.rows && code != SUCCESS; m++) {
    for (int n = 0; n < value.columns && code != SUCCESS; n++) {
      if (value.matrix[m][n] == +INFINITY || value.matrix[m][n] == -INFINITY ||
          value.matrix[m][n] == NAN) {
        code = SUCCESS;
      }
    }
  }
  return code;
}

/**
 * @brief Положительное ли число строчек и столбцов?   1 - да,  0 - нет
 */
int is_rows_columns_posit(matrix_t value) {
  int code = SUCCESS;
  if (value.rows <= 0 || value.columns <= 0) code = FAILURE;
  return code;
}

/**
 * @brief Равно ли количество строчек и столбцов у двух подаваемых матриц?   1 -
 * да,  0 - нет
 */
int is_rows_columns_2_matr_eq(matrix_t A, matrix_t B) {
  int code = SUCCESS;
  if (A.rows != B.rows || A.columns != B.columns) code = FAILURE;
  return code;
}

/**
 * @brief Матрицы равны?    1 - да,  0 - нет
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if ((is_matr_str_null(A) || is_matr_str_null(B)) ||
      !is_rows_columns_2_matr_eq(*A, *B))
    return FAILURE;

  int code = SUCCESS;
  for (int m = 0; m < A->rows && code != FAILURE; m++) {
    for (int n = 0; n < A->columns && code != FAILURE; n++) {
      if (fabs(A->matrix[m][n] - B->matrix[m][n]) > 1e-7) {
        code = FAILURE;
      }
    }
  }
  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((is_matr_str_null(A) || is_matr_str_null(B) ||
       is_matr_str_null(result)) ||
      !is_rows_columns_posit(*A) || !is_rows_columns_posit(*B))
    return INVALID_MATRIX;
  if ((is_number_inf_or_nan(*A) || is_number_inf_or_nan(*B)) ||
      !is_rows_columns_2_matr_eq(*A, *B))
    return CALCULATION_ERROR;
  int code = OK;
  s21_create_matrix(A->rows, A->columns, result);
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      result->matrix[m][n] = A->matrix[m][n] + B->matrix[m][n];
    }
  }
  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((is_matr_str_null(A) || is_matr_str_null(B) ||
       is_matr_str_null(result)) ||
      !is_rows_columns_posit(*A) || !is_rows_columns_posit(*B))
    return INVALID_MATRIX;
  if ((is_number_inf_or_nan(*A) || is_number_inf_or_nan(*B)) ||
      !is_rows_columns_2_matr_eq(*A, *B))
    return CALCULATION_ERROR;
  int code = OK;
  s21_create_matrix(A->rows, A->columns, result);
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      result->matrix[m][n] = A->matrix[m][n] - B->matrix[m][n];
    }
  }
  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (is_matr_str_null(A) || is_matr_str_null(result) ||
      !is_rows_columns_posit(*A))
    return INVALID_MATRIX;
  if ((number == INFINITY) || (number == NAN) || is_number_inf_or_nan(*A))
    return CALCULATION_ERROR;
  int code = OK;
  s21_create_matrix(A->rows, A->columns, result);
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      result->matrix[m][n] = A->matrix[m][n] * number;
    }
  }
  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (is_matr_str_null(A) || is_matr_str_null(B) || is_matr_str_null(result) ||
      !is_rows_columns_posit(*A) || !is_rows_columns_posit(*B))
    return INVALID_MATRIX;
  if (is_number_inf_or_nan(*A) || is_number_inf_or_nan(*B) ||
      (A->columns != B->rows) || (A->rows != B->columns))
    return CALCULATION_ERROR;
  int code = OK;
  s21_create_matrix(A->rows, B->columns, result);
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < B->columns; n++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[m][n] += A->matrix[m][k] * B->matrix[k][n];
      }
    }
  }
  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (is_matr_str_null(A) || is_matr_str_null(result) ||
      !is_rows_columns_posit(*A))
    return INVALID_MATRIX;

  int code = OK;
  s21_create_matrix(A->columns, A->rows, result);
  for (int m = 0; m < result->rows; m++) {
    for (int n = 0; n < result->columns; n++) {
      result->matrix[m][n] = A->matrix[n][m];
    }
  }
  return code;
}

int copy_matrix(matrix_t *A, matrix_t *copy_matrix) {
  if (is_matr_str_null(A) || is_matr_str_null(copy_matrix) ||
      !is_rows_columns_posit(*A))
    return INVALID_MATRIX;
  int code = OK;
  s21_create_matrix(A->rows, A->columns, copy_matrix);
  for (int m = 0; m < copy_matrix->rows; m++) {
    for (int n = 0; n < copy_matrix->columns; n++) {
      copy_matrix->matrix[m][n] = A->matrix[m][n];
    }
  }
  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  if (is_matr_str_null(A) || result == NULL || !is_rows_columns_posit(*A))
    return INVALID_MATRIX;
  if (is_number_inf_or_nan(*A) || (A->columns != A->rows))
    return CALCULATION_ERROR;
  int code = OK, is_nul_det = 1;
  matrix_t copy_A;

  for (int m = 0; m < A->rows && is_nul_det == 1; m++) {
    if (A->matrix[m][0] != 0) is_nul_det = 0;
  }
  if (!is_nul_det && A->rows > 2) {
    *result = 1;
    copy_matrix(A, &copy_A);
    triang_matrix(&copy_A, result);
    if (*result != 0) {
      for (int mult = 0; mult < copy_A.rows; mult++) {
        *result *= copy_A.matrix[mult][mult];
      }
    }
    s21_remove_matrix(&copy_A);
  } else if (!is_nul_det && A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else if (!is_nul_det && A->rows == 1) {
    *result = A->matrix[0][0];
  } else
    *result = 0;
  if (*result == 0) *result = fabs(*result);
  return code;
}

/**
 * @brief Зануляет нижнюю левую половину от главной диагонали
 *
 */
void triang_matrix(matrix_t *copy_A, double *result) {
  for (int g = 0; g < (copy_A->rows - 1) && *result != 0; g++) {
    if (!finf_diag_null_elem(g, copy_A)) {
      for (int r = g + 1; r < copy_A->rows; r++) {
        double k = copy_A->matrix[r][g] / copy_A->matrix[g][g];
        if (k != 0) {
          for (int c = g; c < copy_A->columns; c++) {
            copy_A->matrix[r][c] -= copy_A->matrix[g][c] * k;
          }
        }
      }
    } else
      *result = 0;
  }
}

/**
 * @brief Ищет нулевой элемент на главной диагонали.
 * Если нашел, то пытается поменять строчку на строку,
 * где нет нулевого элемента со сменой знака.
 *
 * 0 - ОК (если не было 0 на главной диагонали или замена прошла успешно).
 * 1 - не нашли строку ненулевую, не с чем поменять местами
 */
int finf_diag_null_elem(int g, matrix_t *copy_A) {
  int code = OK;
  if (copy_A->matrix[g][g] == 0) {
    int flag = 1;
    for (int r = g + 1; r < copy_A->rows; r++) {
      if (copy_A->matrix[r][g] != 0) {
        flag = 0;
        matrix_t temp_m;
        copy_matrix(copy_A, &temp_m);
        for (int c = 0; c < copy_A->columns; c++) {
          temp_m.matrix[g][c] = (-1) * copy_A->matrix[r][c];
          copy_A->matrix[r][c] = copy_A->matrix[g][c];
          copy_A->matrix[g][c] = temp_m.matrix[g][c];
        }
        s21_remove_matrix(&temp_m);
      }
    }
    if (flag) code = 1;
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (is_matr_str_null(A) || is_matr_str_null(result) ||
      !is_rows_columns_posit(*A))
    return INVALID_MATRIX;
  if ((A->columns != A->rows) || is_number_inf_or_nan(*A))
    return CALCULATION_ERROR;

  int code = OK;
  s21_create_matrix(A->rows, A->columns, result);
  if (A->rows > 1) {
    matrix_t mini_matrix;
    s21_create_matrix(A->rows - 1, A->columns - 1, &mini_matrix);
    for (int r = 0; r < result->rows; r++) {
      for (int c = 0; c < result->columns; c++) {
        create_mini_matrix(A, &mini_matrix, c, r);
        s21_determinant(&mini_matrix, &(result->matrix[r][c]));
        result->matrix[r][c] *= pow(-1, r + c);
      }
    }
    s21_remove_matrix(&mini_matrix);
  } else if (A->rows == 1)
    result->matrix[0][0] = 1;

  return code;
}

void create_mini_matrix(matrix_t *A, matrix_t *mini_matrix, int c, int r) {
  int min_r = -1, min_c = -1;
  for (int rowA = 0; rowA < A->rows; rowA++) {
    if (rowA != r) {
      min_r++;
      for (int columnA = 0; columnA < A->columns; columnA++) {
        if (columnA != c) {
          min_c++;
          mini_matrix->matrix[min_r][min_c] = A->matrix[rowA][columnA];
        }
      }
      min_c = -1;
    }
  }
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (is_matr_str_null(A) || is_matr_str_null(result) ||
      !is_rows_columns_posit(*A))
    return INVALID_MATRIX;
  if ((A->columns != A->rows) || is_number_inf_or_nan(*A))
    return CALCULATION_ERROR;
  int code = OK, flag_nul_invers = 0;
  double det_A = 0;
  s21_determinant(A, &det_A);
  if (det_A == 0) flag_nul_invers = 1, code = CALCULATION_ERROR;
  if (!flag_nul_invers) {
    if (A->rows > 1) {
      matrix_t calc_comp_A, trans_A;
      s21_calc_complements(A, &calc_comp_A);
      s21_transpose(&calc_comp_A, &trans_A);
      s21_mult_number(&trans_A, 1 / det_A, result);
      s21_remove_matrix(&calc_comp_A);
      s21_remove_matrix(&trans_A);
    } else if (A->rows == 1) {
      s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
    }
  }
  return code;
}
