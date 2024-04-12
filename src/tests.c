#include <check.h>

#include "s21_matrix.h"

//-------------s21_create_matrix-------------------

// + все значения квадратной матрицы 0 (0 = 0)
START_TEST(test_s21_create_matrix_1) {
  matrix_t value1;
  int rows = 4, columns = 4;
  s21_create_matrix(rows, columns, &value1);

  ck_assert_int_eq(value1.rows, rows);
  ck_assert_int_eq(value1.columns, columns);

  for (int m = 0; m < rows; m++) {
    for (int n = 0; n < columns; n++) {
      ck_assert_double_eq(value1.matrix[m][n], 0.000000);
    }
  }
  s21_remove_matrix(&value1);
}
END_TEST;

// - отрицательное количество столбцов
START_TEST(test_s21_create_matrix_2) {
  matrix_t value2;
  int rows = 4, columns = -1;
  ck_assert_int_eq(s21_create_matrix(rows, columns, &value2), INVALID_MATRIX);
}
END_TEST;

// + все значения матрицы 0 (0 = 0)
START_TEST(test_s21_create_matrix_3) {
  matrix_t value3;
  int rows = 2, columns = 5;
  s21_create_matrix(rows, columns, &value3);

  ck_assert_int_eq(value3.rows, rows);
  ck_assert_int_eq(value3.columns, columns);

  for (int m = 0; m < rows; m++) {
    for (int n = 0; n < columns; n++) {
      ck_assert_double_eq(value3.matrix[m][n], 0.000000);
    }
  }
  s21_remove_matrix(&value3);
}
END_TEST;

// - указатель на NULL (указатель на структуру)
START_TEST(test_s21_create_matrix_4) {
  ck_assert_int_eq(s21_create_matrix(4, 3, NULL), INVALID_MATRIX);
}
END_TEST;

Suite *s21_create_matrix_test() {
  Suite *result;
  TCase *tc_create_matrix;

  result = suite_create("s21_create_matrix");
  tc_create_matrix = tcase_create("s21_create_matrix");

  tcase_add_test(tc_create_matrix, test_s21_create_matrix_1);
  tcase_add_test(tc_create_matrix, test_s21_create_matrix_2);
  tcase_add_test(tc_create_matrix, test_s21_create_matrix_3);
  tcase_add_test(tc_create_matrix, test_s21_create_matrix_4);

  suite_add_tcase(result, tc_create_matrix);

  return result;
}

//-------------s21_eq_matrix-------------------

// - разное количество столбцов
START_TEST(test_s21_eq_matrix_1) {
  matrix_t value1, value2;
  int rows1 = 3, columns1 = 1, rows2 = 3, columns2 = 2;
  s21_create_matrix(rows1, columns1, &value1);
  s21_create_matrix(rows2, columns2, &value2);

  ck_assert_int_eq(s21_eq_matrix(&value1, &value2), FAILURE);
  s21_remove_matrix(&value1);
  s21_remove_matrix(&value2);
}
END_TEST;

// + одинаковые матрицы, зануленные изначально
START_TEST(test_s21_eq_matrix_2) {
  matrix_t value3, value4;
  int rows3 = 4, columns3 = 2, rows4 = 4, columns4 = 2;
  s21_create_matrix(rows3, columns3, &value3);
  s21_create_matrix(rows4, columns4, &value4);

  ck_assert_int_eq(s21_eq_matrix(&value3, &value4), SUCCESS);
  s21_remove_matrix(&value3);
  s21_remove_matrix(&value4);
}
END_TEST;

// + одинаковые матрицы, заполненные не нулями
START_TEST(test_s21_eq_matrix_3) {
  matrix_t value5, value6;
  int rows5 = 2, columns5 = 2, rows6 = 2, columns6 = 2;
  s21_create_matrix(rows5, columns5, &value5);
  s21_create_matrix(rows6, columns6, &value6);

  sequent_filling(&value5, 3, 1);
  sequent_filling(&value6, 3, 1);

  ck_assert_int_eq(s21_eq_matrix(&value5, &value6), SUCCESS);
  s21_remove_matrix(&value5);
  s21_remove_matrix(&value6);
}
END_TEST;

// - неодинаковые матрицы, заполненные разными значениями
START_TEST(test_s21_eq_matrix_4) {
  matrix_t value7, value8;
  int rows7 = 2, columns7 = 2, rows8 = 2, columns8 = 2;
  s21_create_matrix(rows7, columns7, &value7);
  s21_create_matrix(rows8, columns8, &value8);

  sequent_filling(&value7, 3, 1);
  sequent_filling(&value8, 5, 1);

  ck_assert_int_eq(s21_eq_matrix(&value7, &value8), FAILURE);
  s21_remove_matrix(&value7);
  s21_remove_matrix(&value8);
}
END_TEST;

// - неодинаковые матрицы, заполненные разными маленькими значениями
START_TEST(test_s21_eq_matrix_5) {
  matrix_t value7, value8;
  int rows7 = 2, columns7 = 2, rows8 = 2, columns8 = 2;
  s21_create_matrix(rows7, columns7, &value7);
  s21_create_matrix(rows8, columns8, &value8);

  sequent_filling(&value7, 1.555556, 1);
  sequent_filling(&value8, 1.555555, 1);

  ck_assert_int_eq(s21_eq_matrix(&value7, &value8), FAILURE);
  s21_remove_matrix(&value7);
  s21_remove_matrix(&value8);
}
END_TEST;

Suite *s21_eq_matrix_test() {
  Suite *result;
  TCase *tc_eq_matrix;

  result = suite_create("s21_eq_matrix");
  tc_eq_matrix = tcase_create("s21_eq_matrix");

  tcase_add_test(tc_eq_matrix, test_s21_eq_matrix_1);
  tcase_add_test(tc_eq_matrix, test_s21_eq_matrix_2);
  tcase_add_test(tc_eq_matrix, test_s21_eq_matrix_3);
  tcase_add_test(tc_eq_matrix, test_s21_eq_matrix_4);
  tcase_add_test(tc_eq_matrix, test_s21_eq_matrix_5);

  suite_add_tcase(result, tc_eq_matrix);

  return result;
}

//-------------s21_sum_matrix-------------------

// + матрицы норм и равны
START_TEST(test_s21_sum_matrix_1) {
  matrix_t valueA, valueB, result, check;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4, rows_check = 2,
      columns_check = 4;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);
  s21_create_matrix(rows_check, columns_check, &check);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&valueB, 3, 1);
  s21_sum_matrix(&valueA, &valueB, &result);
  sequent_filling(&check, 5, 2);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// - есть бесконечное число в начальной матрице
START_TEST(test_s21_sum_matrix_2) {
  matrix_t valueA, valueB, result;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  valueA.matrix[0][0] = +INFINITY;

  ck_assert_int_eq(s21_sum_matrix(&valueA, &valueB, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

// - нулевой указатель на result
START_TEST(test_s21_sum_matrix_3) {
  matrix_t valueA, valueB;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  ck_assert_int_eq(s21_sum_matrix(&valueA, &valueB, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

Suite *s21_sum_matrix_test() {
  Suite *result;
  TCase *tc_sum_matrix;

  result = suite_create("s21_sum_matrix");
  tc_sum_matrix = tcase_create("s21_sum_matrix");

  tcase_add_test(tc_sum_matrix, test_s21_sum_matrix_1);
  tcase_add_test(tc_sum_matrix, test_s21_sum_matrix_2);
  tcase_add_test(tc_sum_matrix, test_s21_sum_matrix_3);

  suite_add_tcase(result, tc_sum_matrix);

  return result;
}

//-------------s21_sub_matrix-------------------

// + матрицы норм и равны
START_TEST(test_s21_sub_matrix_1) {
  matrix_t valueA, valueB, result, check;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4, rows_check = 2,
      columns_check = 4;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);
  s21_create_matrix(rows_check, columns_check, &check);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&valueB, 3, 1);
  s21_sub_matrix(&valueA, &valueB, &result);

  for (int m = 0; m < check.rows; m++) {
    for (int n = 0; n < check.columns; n++) {
      check.matrix[m][n] = -1;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// - есть бесконечное число в начальной матрице
START_TEST(test_s21_sub_matrix_2) {
  matrix_t valueA, valueB, result;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  valueA.matrix[0][0] = +INFINITY;

  ck_assert_int_eq(s21_sub_matrix(&valueA, &valueB, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

// - нулевой указатель на result
START_TEST(test_s21_sub_matrix_3) {
  matrix_t valueA, valueB;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 4, rowsB = 2, columnsB = 4;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  ck_assert_int_eq(s21_sub_matrix(&valueA, &valueB, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

Suite *s21_sub_matrix_test() {
  Suite *result;
  TCase *tc_sub_matrix;

  result = suite_create("s21_sub_matrix");
  tc_sub_matrix = tcase_create("s21_sub_matrix");

  tcase_add_test(tc_sub_matrix, test_s21_sub_matrix_1);
  tcase_add_test(tc_sub_matrix, test_s21_sub_matrix_2);
  tcase_add_test(tc_sub_matrix, test_s21_sub_matrix_3);

  suite_add_tcase(result, tc_sub_matrix);

  return result;
}

//-------------s21_mult_number-------------------

// + матрицы норм и равны
START_TEST(test_s21_mult_number_1) {
  matrix_t valueA, result, check;
  int rowsA = 2, columnsA = 4, rows_check = 2, columns_check = 4;
  double number = 2;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&check, 4, 2);
  s21_mult_number(&valueA, number, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// - есть бесконечное число в начальной матрице
START_TEST(test_s21_mult_number_2) {
  matrix_t valueA, result;
  int rowsA = 2, columnsA = 4;
  double number = 2;
  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = +INFINITY;

  ck_assert_int_eq(s21_mult_number(&valueA, number, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
}
END_TEST;

// - нулевой указатель на number
START_TEST(test_s21_mult_number_3) {
  matrix_t valueA;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 4;
  double number = 2;
  s21_create_matrix(rowsA, columnsA, &valueA);

  ck_assert_int_eq(s21_mult_number(&valueA, number, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
}
END_TEST;

Suite *s21_mult_number_test() {
  Suite *result;
  TCase *tc_mult_number;

  result = suite_create("s21_mult_number");
  tc_mult_number = tcase_create("s21_mult_number");

  tcase_add_test(tc_mult_number, test_s21_mult_number_1);
  tcase_add_test(tc_mult_number, test_s21_mult_number_2);
  tcase_add_test(tc_mult_number, test_s21_mult_number_3);

  suite_add_tcase(result, tc_mult_number);

  return result;
}

//-------------s21_mult_matrix-------------------

// + матрицы норм и равны
START_TEST(test_s21_mult_matrix_1) {
  matrix_t valueA, valueB, result, check;
  int rowsA = 2, columnsA = 4, rowsB = 4, columnsB = 2, rows_check = 2,
      columns_check = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);
  s21_create_matrix(rows_check, columns_check, &check);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&valueB, 2, 1);

  check.matrix[0][0] = 80;
  check.matrix[0][1] = 94;
  check.matrix[1][0] = 160;
  check.matrix[1][1] = 190;

  s21_mult_matrix(&valueA, &valueB, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// - есть бесконечное число в начальной матрице
START_TEST(test_s21_mult_matrix_2) {
  matrix_t valueA, valueB, result;
  int rowsA = 2, columnsA = 4;
  int rowsB = 4, columnsB = 2;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  valueA.matrix[0][0] = +INFINITY;

  ck_assert_int_eq(s21_mult_matrix(&valueA, &valueB, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

// - матрицы не подходят под условия для умножения
START_TEST(test_s21_mult_matrix_3) {
  matrix_t valueA, valueB, result;
  int rowsA = 2, columnsA = 4, rowsB = 3, columnsB = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&valueB, 2, 1);

  ck_assert_int_eq(s21_mult_matrix(&valueA, &valueB, &result),
                   CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

// нулевой указатель
START_TEST(test_s21_mult_matrix_4) {
  matrix_t valueA, valueB;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 4, rowsB = 3, columnsB = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rowsB, columnsB, &valueB);

  sequent_filling(&valueA, 2, 1);
  sequent_filling(&valueB, 2, 1);

  ck_assert_int_eq(s21_mult_matrix(&valueA, &valueB, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&valueB);
}
END_TEST;

Suite *s21_mult_matrix_test() {
  Suite *result;
  TCase *tc_mult_matrix;

  result = suite_create("s21_mult_matrix");
  tc_mult_matrix = tcase_create("s21_mult_matrix");

  tcase_add_test(tc_mult_matrix, test_s21_mult_matrix_1);
  tcase_add_test(tc_mult_matrix, test_s21_mult_matrix_2);
  tcase_add_test(tc_mult_matrix, test_s21_mult_matrix_3);
  tcase_add_test(tc_mult_matrix, test_s21_mult_matrix_4);

  suite_add_tcase(result, tc_mult_matrix);

  return result;
}

//-------------s21_transpose-------------------

// + матрицы норм и равны
START_TEST(test_s21_transpose_1) {
  matrix_t valueA, result, check;
  int rowsA = 2, columnsA = 4, rows_check = 4, columns_check = 2;
  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  sequent_filling(&valueA, 2, 1);

  check.matrix[0][0] = 2;
  check.matrix[0][1] = 6;
  check.matrix[1][0] = 3;
  check.matrix[1][1] = 7;
  check.matrix[2][0] = 4;
  check.matrix[2][1] = 8;
  check.matrix[3][0] = 5;
  check.matrix[3][1] = 9;

  s21_transpose(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// нулевой указатель на result
START_TEST(test_s21_transpose_2) {
  matrix_t valueA;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 4;
  s21_create_matrix(rowsA, columnsA, &valueA);
  sequent_filling(&valueA, 2, 1);

  ck_assert_int_eq(s21_transpose(&valueA, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
}
END_TEST;

Suite *s21_transpose_test() {
  Suite *result;
  TCase *tc_transpose;

  result = suite_create("s21_transpose");
  tc_transpose = tcase_create("s21_transpose");

  tcase_add_test(tc_transpose, test_s21_transpose_1);
  tcase_add_test(tc_transpose, test_s21_transpose_2);

  suite_add_tcase(result, tc_transpose);

  return result;
}

//-------------s21_determinant-------------------

// + матрицы без 0 элемента, дет = 0
START_TEST(test_s21_determinant_1) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double result = 0, check = 0;

  s21_create_matrix(rowsA, columnsA, &valueA);

  sequent_filling(&valueA, 1, 1);

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица без возможности поменять строчки, весь 1 столбец нулевой
START_TEST(test_s21_determinant_2) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double result = 0, check = 0;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][1] = 1;
  valueA.matrix[0][2] = 2;
  valueA.matrix[1][1] = 3;
  valueA.matrix[1][2] = 4;
  valueA.matrix[2][1] = 5;
  valueA.matrix[2][2] = 6;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица меняет строчки, есть 0 на главной диагонали, строчки меняются, дет =
// -32
START_TEST(test_s21_determinant_3) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double result = 0, check = -32;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 2;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 6;

  valueA.matrix[1][0] = 7;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 9;

  valueA.matrix[2][0] = 0;
  valueA.matrix[2][1] = 1;
  valueA.matrix[2][2] = 2;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица 2*2, дет = -18
START_TEST(test_s21_determinant_4) {
  matrix_t valueA;
  int rowsA = 2, columnsA = 2;
  double result = 0, check = -18;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 2;
  valueA.matrix[0][1] = 4;

  valueA.matrix[1][0] = 7;
  valueA.matrix[1][1] = 5;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица 1*1, дет = 1
START_TEST(test_s21_determinant_5) {
  matrix_t valueA;
  int rowsA = 1, columnsA = 1;
  double result = 0, check = 1;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 1;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// указатель result на 0
START_TEST(test_s21_determinant_6) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double *result = NULL;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 2;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 6;

  valueA.matrix[1][0] = 7;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 9;

  valueA.matrix[2][0] = 0;
  valueA.matrix[2][1] = 1;
  valueA.matrix[2][2] = 2;

  ck_assert_int_eq(s21_determinant(&valueA, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
}
END_TEST;

// количество столбцов не равно строкам
START_TEST(test_s21_determinant_7) {
  matrix_t valueA;
  int rowsA = 2, columnsA = 3;
  double result = 0;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 2;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 6;

  valueA.matrix[1][0] = 7;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 9;

  ck_assert_int_eq(s21_determinant(&valueA, &result), CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица меняет строчки, есть 0 - [0][0] на главной диагонали, строчки
// меняются, дет = 130
START_TEST(test_s21_determinant_8) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double result = 0, check = 130;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 0;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 6;

  valueA.matrix[1][0] = 7;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 9;

  valueA.matrix[2][0] = 4;
  valueA.matrix[2][1] = 1;
  valueA.matrix[2][2] = 2;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

// не может поменять строчки м/у собой => дет 0
START_TEST(test_s21_determinant_9) {
  matrix_t valueA;
  int rowsA = 3, columnsA = 3;
  double result = 0, check = 0;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 1;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 3;

  valueA.matrix[1][0] = 0;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 3;

  valueA.matrix[2][0] = 0;
  valueA.matrix[2][1] = 0;
  valueA.matrix[2][2] = 2;

  s21_determinant(&valueA, &result);

  ck_assert_double_eq(result, check);
  s21_remove_matrix(&valueA);
}
END_TEST;

Suite *s21_determinant_test() {
  Suite *result;
  TCase *tc_determinant;

  result = suite_create("s21_determinant");
  tc_determinant = tcase_create("s21_determinant");

  tcase_add_test(tc_determinant, test_s21_determinant_1);
  tcase_add_test(tc_determinant, test_s21_determinant_2);
  tcase_add_test(tc_determinant, test_s21_determinant_3);
  tcase_add_test(tc_determinant, test_s21_determinant_4);
  tcase_add_test(tc_determinant, test_s21_determinant_5);
  tcase_add_test(tc_determinant, test_s21_determinant_6);
  tcase_add_test(tc_determinant, test_s21_determinant_7);
  tcase_add_test(tc_determinant, test_s21_determinant_8);
  tcase_add_test(tc_determinant, test_s21_determinant_9);

  suite_add_tcase(result, tc_determinant);

  return result;
}

//-------------calc_complements-------------------

// матрица 2*2
START_TEST(test_s21_calc_complements_1) {
  matrix_t valueA, result, check;
  int rowsA = 2, columnsA = 2, rows_check = 2, columns_check = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 1;
  valueA.matrix[0][1] = 2;
  valueA.matrix[1][0] = 3;
  valueA.matrix[1][1] = 4;

  check.matrix[0][0] = 4;
  check.matrix[0][1] = -3;
  check.matrix[1][0] = -2;
  check.matrix[1][1] = 1;

  s21_calc_complements(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// матрица 3*3
START_TEST(test_s21_calc_complements_2) {
  matrix_t valueA, result, check;
  int rowsA = 3, columnsA = 3, rows_check = 3, columns_check = 3;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 1;
  valueA.matrix[0][1] = 2;
  valueA.matrix[0][2] = 3;

  valueA.matrix[1][0] = 4;
  valueA.matrix[1][1] = 5;
  valueA.matrix[1][2] = 6;

  valueA.matrix[2][0] = 7;
  valueA.matrix[2][1] = 8;
  valueA.matrix[2][2] = 9;

  check.matrix[0][0] = -3;
  check.matrix[0][1] = 6;
  check.matrix[0][2] = -3;

  check.matrix[1][0] = 6;
  check.matrix[1][1] = -12;
  check.matrix[1][2] = 6;

  check.matrix[2][0] = -3;
  check.matrix[2][1] = 6;
  check.matrix[2][2] = -3;

  s21_calc_complements(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// матрица 1*1
START_TEST(test_s21_calc_complements_3) {
  matrix_t valueA, result, check;
  int rowsA = 1, columnsA = 1, rows_check = 1, columns_check = 1;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 5;

  check.matrix[0][0] = 1;

  s21_calc_complements(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// не квадратная матрица
START_TEST(test_s21_calc_complements_4) {
  matrix_t valueA, result;
  int rowsA = 1, columnsA = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 5;
  valueA.matrix[0][1] = 4;

  ck_assert_int_eq(s21_calc_complements(&valueA, &result), CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
}
END_TEST;

// нулевой указатель
START_TEST(test_s21_calc_complements_5) {
  matrix_t valueA;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 5;
  valueA.matrix[0][1] = 4;

  valueA.matrix[1][0] = 3;
  valueA.matrix[1][1] = 2;

  ck_assert_int_eq(s21_calc_complements(&valueA, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
}
END_TEST;

Suite *s21_calc_complements_test() {
  Suite *result;
  TCase *tc_calc_complements;

  result = suite_create("s21_calc_complements");
  tc_calc_complements = tcase_create("s21_calc_complements");

  tcase_add_test(tc_calc_complements, test_s21_calc_complements_1);
  tcase_add_test(tc_calc_complements, test_s21_calc_complements_2);
  tcase_add_test(tc_calc_complements, test_s21_calc_complements_3);
  tcase_add_test(tc_calc_complements, test_s21_calc_complements_4);
  tcase_add_test(tc_calc_complements, test_s21_calc_complements_5);

  suite_add_tcase(result, tc_calc_complements);

  return result;
}

//-------------inverse_matrix-------------------

// матрица 3*3
START_TEST(test_s21_inverse_matrix_1) {
  matrix_t valueA, result, check;
  int rowsA = 3, columnsA = 3, rows_check = 3, columns_check = 3;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 2;
  valueA.matrix[0][1] = 5;
  valueA.matrix[0][2] = 7;

  valueA.matrix[1][0] = 6;
  valueA.matrix[1][1] = 3;
  valueA.matrix[1][2] = 4;

  valueA.matrix[2][0] = 5;
  valueA.matrix[2][1] = -2;
  valueA.matrix[2][2] = -3;

  check.matrix[0][0] = 1;
  check.matrix[0][1] = -1;
  check.matrix[0][2] = 1;

  check.matrix[1][0] = -38;
  check.matrix[1][1] = 41;
  check.matrix[1][2] = -34;

  check.matrix[2][0] = 27;
  check.matrix[2][1] = -29;
  check.matrix[2][2] = 24;

  s21_inverse_matrix(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// матрица 2*2
START_TEST(test_s21_inverse_matrix_2) {
  matrix_t valueA, result, check;
  int rowsA = 2, columnsA = 2, rows_check = 2, columns_check = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 5;
  valueA.matrix[0][1] = 4;

  valueA.matrix[1][0] = 3;
  valueA.matrix[1][1] = 2;

  check.matrix[0][0] = -1;
  check.matrix[0][1] = 2;

  check.matrix[1][0] = 1.5;
  check.matrix[1][1] = -2.5;

  s21_inverse_matrix(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

// детерминант = 0 => нет обратной матрицы
START_TEST(test_s21_inverse_matrix_3) {
  matrix_t valueA, result;
  int rowsA = 3, columnsA = 3;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 1;
  valueA.matrix[0][1] = 4;
  valueA.matrix[0][2] = 3;

  valueA.matrix[1][0] = 0;
  valueA.matrix[1][1] = 0;
  valueA.matrix[1][2] = 3;

  valueA.matrix[2][0] = 0;
  valueA.matrix[2][1] = 0;
  valueA.matrix[2][2] = 2;

  ck_assert_int_eq(s21_inverse_matrix(&valueA, &result), CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
}
END_TEST;

// не квадратная матрица
START_TEST(test_s21_inverse_matrix_4) {
  matrix_t valueA, result;
  int rowsA = 1, columnsA = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 5;
  valueA.matrix[0][1] = 4;

  ck_assert_int_eq(s21_inverse_matrix(&valueA, &result), CALCULATION_ERROR);
  s21_remove_matrix(&valueA);
}
END_TEST;

// нулевой указатель
START_TEST(test_s21_inverse_matrix_5) {
  matrix_t valueA;
  matrix_t *result = NULL;
  int rowsA = 2, columnsA = 2;

  s21_create_matrix(rowsA, columnsA, &valueA);

  valueA.matrix[0][0] = 5;
  valueA.matrix[0][1] = 4;

  valueA.matrix[1][0] = 3;
  valueA.matrix[1][1] = 2;

  ck_assert_int_eq(s21_inverse_matrix(&valueA, result), INVALID_MATRIX);
  s21_remove_matrix(&valueA);
}
END_TEST;

// матрица 1*1
START_TEST(test_s21_inverse_matrix_6) {
  matrix_t valueA, result, check;
  int rowsA = 1, columnsA = 1, rows_check = 1, columns_check = 1;

  s21_create_matrix(rowsA, columnsA, &valueA);
  s21_create_matrix(rows_check, columns_check, &check);

  valueA.matrix[0][0] = 5;

  check.matrix[0][0] = 0.2;

  s21_inverse_matrix(&valueA, &result);

  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&valueA);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST;

Suite *s21_inverse_matrix_test() {
  Suite *result;
  TCase *tc_inverse_matrix;

  result = suite_create("s21_inverse_matrix");
  tc_inverse_matrix = tcase_create("s21_inverse_matrix");

  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_1);
  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_2);
  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_3);
  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_4);
  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_5);
  tcase_add_test(tc_inverse_matrix, test_s21_inverse_matrix_6);

  suite_add_tcase(result, tc_inverse_matrix);

  return result;
}

//--------------------------------------------

int main() {
  Suite *result;
  int failed = 0;
  SRunner *runner;

  result = s21_create_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_eq_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_sum_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_sub_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_mult_number_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_mult_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_transpose_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_determinant_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_calc_complements_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  result = s21_inverse_matrix_test();
  runner = srunner_create(result);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : CK_FAILURE;
}