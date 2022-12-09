#include <gtest/gtest.h>
#include "s21_matrix_oop.h"

TEST(constructor_test, empty_constructor) {
    S21Matrix Matrix;
    ASSERT_EQ(Matrix.getRows(), 1);
    ASSERT_EQ(Matrix.getCols(), 1);
    ASSERT_EQ(Matrix(0, 0), 0);
}

TEST(constructor_test, param_constructor) {
    S21Matrix Matrix(3, 3);
    Matrix.setElem(0, 2 , 3.14);
    ASSERT_EQ(Matrix.getRows(), 3);
    ASSERT_EQ(Matrix.getCols(), 3);
    ASSERT_EQ(Matrix.getElem(0, 2), 3.14);
}

TEST(constructor_test, copy_constructor) {
    S21Matrix Matrix1(3, 3);
    Matrix1.setElem(0, 2 , 3.14);
    S21Matrix Matrix2(Matrix1);

    ASSERT_EQ(Matrix2.getRows(), 3);
    ASSERT_EQ(Matrix2.getCols(), 3);
    ASSERT_EQ(Matrix1.getElem(0, 2), 3.14);
}

TEST(constructor_test, move_constructor) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
        S21Matrix Matrix1(3, 3);
        Matrix1.fill_matrix_from_vector(vec);

    S21Matrix Matrix2(std::move(Matrix1));

    S21Matrix Matrix3(3, 3);
    Matrix3.fill_matrix_from_vector(vec);

    ASSERT_TRUE(Matrix2 == Matrix3);
}

TEST(equel_test, is_Equal) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec);

    ASSERT_TRUE(Matrix1.eq_matrix(Matrix2));
}

TEST(equel_test, is_not_Equal) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec);
    Matrix2.setElem(2, 2, 3.14);

    ASSERT_TRUE(Matrix1.eq_matrix(Matrix2) == false);
}

TEST(sum_test, test1) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    vector<double> vec2{4, 32, 3,
                        4, -2, 6.3,
                        7.0, 8, 1.03 };
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);

    Matrix1.sum_matrix(Matrix2);

    vector<double> result_v{5, 34, 6,
                            8, 3, 12.3,
                            14, 16, 10.03};
    S21Matrix result_matrix(3, 3);
    result_matrix.fill_matrix_from_vector(result_v);

    ASSERT_TRUE(Matrix1.eq_matrix(result_matrix));
}


TEST(mul_number, test1) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    double num = 2.5;
    Matrix1 *= num;

    vector<double> result{2.5, 5, 7.5,
                        10, 12.5, 15,
                        17.5, 20, 22.5};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(result);

    ASSERT_TRUE(Matrix1.eq_matrix(Result_matrix));
}

TEST(mul_number, test2) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    double num = 0;
    Matrix1.mul_number(num);

    vector<double> result{0, 0, 0,
                        0, 0, 0,
                        0, 0, 0};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(result);

    ASSERT_TRUE(Matrix1.eq_matrix(Result_matrix));
}

TEST(mult_test, test1) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9 };
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    vector<double> vec2{1, 4, 7,
                        2, 5, 8,
                        3, 6, 9 };
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);

    Matrix1.mul_matrix(Matrix2);

    vector<double> result{14, 32, 50,
                        32, 77, 122,
                        50, 122, 194};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(result);

    ASSERT_TRUE(Matrix1.eq_matrix(Result_matrix));
}

TEST(transpose_test, test1) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    S21Matrix Matrix2 = Matrix1.transpose();

    vector<double> result{1, 4, 7,
                        2, 5, 8,
                        3, 6, 9};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(result);

    ASSERT_TRUE(Matrix2.eq_matrix(Result_matrix));
}

TEST(determinant_test, test1) {
    vector<double> vec{9.9, 2, 3,
                        4, 5, 6,
                        7, 8, 9};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    ASSERT_DOUBLE_EQ(Matrix1.determinant(), -26.7);
}

TEST(determinant_test, test2) {
    S21Matrix Matrix1(1, 1);
    Matrix1.setElem(0, 0, 13);
    ASSERT_DOUBLE_EQ(Matrix1.determinant(), 13);
}

TEST(calc_complements_test, test1) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vect1);

    vector<double> vec2 = {-88.48099, 5096.7295,  -44.439691,
                            -2.646,    -5095.9185, -37.569,
                            -61.63149, 2705.60775, 33.818111};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    Matrix1 = Matrix1.calc_complements();
    ASSERT_TRUE(Matrix1.eq_matrix(Result_matrix));
}

TEST(inverse_matrix_test, test1) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vect1);

    S21Matrix Matrix2(3, 3);
    Matrix2 = Matrix1.inverse_matrix();

    vector<double> vec2 = {1.0, 0,   0,
                            0,   1.0, 0,
                            0,   0,   1.0};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    ASSERT_TRUE(Matrix1 * Matrix2 == Result_matrix);
}

TEST(setCols_test, test1) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vect1);
    Matrix1.setCols(4);
    Matrix1.setElem(2, 3, 3.14);

    vector<double> vec2 = {12.345, -0.42,  56.1,  0,
                            51.1,   1.0009, 13.05, 0,
                            72.99,  0.56,   -81.1, 3.14};
    S21Matrix Result_matrix(3, 4);
    Result_matrix.fill_matrix_from_vector(vec2);

    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(setCols_test, test2) {
    vector<double> vect1 = {12.345, -0.42,  56.1,  0,
                        51.1,   1.0009, 13.05, 0,
                        72.99,  0.56,   -81.1, 3.14};
    S21Matrix Matrix1(3, 4);
    Matrix1.fill_matrix_from_vector(vect1);
    Matrix1.setCols(3);

    vector<double> vec2 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(setRows_test, test1) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vect1);
    Matrix1.setRows(4);
    Matrix1.setElem(3, 2, 3.14);

    vector<double> vec2 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1,
                            0,        0,   3.14};
    S21Matrix Result_matrix(4, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(setRows_test, test2) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                        51.1,   1.0009, 13.05,
                        72.99,  0.56,   -81.1,
                        0,        0,   3.14};
    S21Matrix Matrix1(4, 3);
    Matrix1.fill_matrix_from_vector(vect1);
    Matrix1.setRows(3);

    vector<double> vec2 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(test_operator_mul, test1) {
    vector<double> vec1 = {12.345, -0.42,  56.1,
                              51.1,   1.0009, 13.05,
                              72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);

    S21Matrix Result_matrix(Matrix1);
    Result_matrix.mul_matrix(Matrix1);
    Matrix1 *= Matrix1;
    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(test_operator_mul, test2) {
    vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109,  13.05,
                              2.99, 3.56, -1.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Result_matrix(Matrix1);
    Result_matrix.mul_matrix(Matrix1);
    Matrix1 = Matrix1 * Matrix1;
    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(test_operator_mul, test3) {
    double num = 34.1;
    vector<double> vec1 = {2.5,  -0.2, 6.1,
                            5.1,  109,  13.05,
                            2.99, 3.56, -1.1};
    vector<double> vec2 = {2.5 * num,  -0.2 * num, 6.1 * num,
                            5.1 * num,  109. * num, 13.05 * num,
                            2.99 * num, 3.56 * num, -1.1 * num};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);

    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);

    S21Matrix Matrix3;
    Matrix3 = num * Matrix1;
    Matrix1 = Matrix1 * num;
    ASSERT_TRUE(Matrix1 == Matrix2);
    ASSERT_TRUE(Matrix3 == Matrix2);
}

TEST(test_operator_eq, test1) {
    vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109,  13.05,
                              2.99, 3.56, -1.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Result_matrix;
    Result_matrix = Matrix1;
    ASSERT_TRUE(Matrix1 == Result_matrix);
}

TEST(test_operator_eq, test2) {
    vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109,  13.05,
                              2.99, 3.56, -1.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    Matrix1 = Matrix1;

    ASSERT_TRUE(Matrix1 == Matrix1);
}

TEST(test_operator_eq, test3) {
    vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109,  13.05,
                              2.99, 3.56, -1.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Matrix2(4, 3);
    
    ASSERT_FALSE(Matrix1 == Matrix2);
}


TEST(test_operator_sum, test1) {
     vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109., 13.05,
                              2.99, 3.56, -1.1};
     vector<double> vec2 = {5.0,      -0.4,     12.2,
                              10.2,     218.,     26.1,
                              2.99 * 2, 3.56 * 2, -1.1 * 2};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);
    S21Matrix Matrix3;
    Matrix3 = Matrix1 + Matrix1;
    ASSERT_TRUE(Matrix3 == Matrix2);
}

TEST(test_operator_sum, test2) {
     vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109., 13.05,
                              2.99, 3.56, -1.1};
     vector<double> vec2 = {5.0,      -0.4,     12.2,
                              10.2,     218.,     26.1,
                              2.99 * 2, 3.56 * 2, -1.1 * 2};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);
    S21Matrix Matrix3(Matrix1);
    Matrix3 += Matrix1;
    ASSERT_TRUE(Matrix3 == Matrix2);
}

TEST(test_operator_sub, test1) {
     vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109., 13.05,
                              2.99, 3.56, -1.1};
     vector<double> vec2 = {5.0,      -0.4,     12.2,
                              10.2,     218.,     26.1,
                              2.99 * 2, 3.56 * 2, -1.1 * 2};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);
    S21Matrix Matrix3;
    Matrix3 = Matrix2 - Matrix1;
    ASSERT_TRUE(Matrix3 == Matrix1);
}

TEST(test_operator_sub, test2) {
     vector<double> vec1 = {2.5,  -0.2, 6.1,
                              5.1,  109., 13.05,
                              2.99, 3.56, -1.1};
     vector<double> vec2 = {5.0,      -0.4,     12.2,
                              10.2,     218.,     26.1,
                              2.99 * 2, 3.56 * 2, -1.1 * 2};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec1);
    S21Matrix Matrix2(3, 3);
    Matrix2.fill_matrix_from_vector(vec2);
    S21Matrix Matrix3(Matrix2);
    Matrix3 -= Matrix1;
    ASSERT_TRUE(Matrix3 == Matrix1);
}

TEST(test_throw, test1) {
    ASSERT_ANY_THROW(S21Matrix Matrix1(-2, 1));
}

TEST(test_throw, test2) {
    ASSERT_ANY_THROW(S21Matrix Matrix1(5, -4));
}

TEST(test_throw, test3) {
    ASSERT_ANY_THROW(S21Matrix Matrix1(-2, -2));
}

TEST(test_throw, test4) {
    S21Matrix Matrix1(10, 14);
    ASSERT_ANY_THROW(Matrix1.setCols(-1));
    ASSERT_ANY_THROW(Matrix1.setRows(-13));
}

TEST(test_throw, test5) {
    S21Matrix Matrix1(5, 3);
    S21Matrix Matrix2(3, 5);
    ASSERT_ANY_THROW(Matrix1 + Matrix2);
}

TEST(test_throw, test6) {
    S21Matrix Matrix1(1, 1);
    S21Matrix Matrix2(2, 2);
    ASSERT_ANY_THROW(Matrix1 + Matrix2);
}

TEST(test_throw, test7) {
    S21Matrix Matrix1(21, 11);
    S21Matrix Matrix2(21, 21);
    ASSERT_ANY_THROW(Matrix1 + Matrix2);
}

TEST(test_throw, test8) {
    S21Matrix Matrix1(5, 3);
    S21Matrix Matrix2(3, 5);
    ASSERT_ANY_THROW(Matrix1 - Matrix2);
}

TEST(test_throw, test9) {
    S21Matrix Matrix1(1, 1);
    S21Matrix Matrix2(2, 2);
    ASSERT_ANY_THROW(Matrix1 - Matrix2);
}

TEST(test_throw, test10) {
    S21Matrix Matrix1(21, 11);
    S21Matrix Matrix2(21, 21);
    ASSERT_ANY_THROW(Matrix1 - Matrix2);
}

TEST(test_throw, test11) {
    S21Matrix Matrix1(3, 3);
    S21Matrix Matrix2(4, 3);
    ASSERT_ANY_THROW(Matrix1 * Matrix2);
}

TEST(test_throw, test12) {
    S21Matrix Matrix1(3, 3);
    ASSERT_ANY_THROW(Matrix1.setElem(33, 0, 3));
}

TEST(test_throw, test13) {
    vector<double> vect1 = {12.345, -0.42,  56.1,
                            51.1,   1.0009, 13.05,
                            72.99,  0.56,   -81.1};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vect1);

    vector<double> vec2 = {-88.48099, 5096.7295,  -44.439691,
                            -2.646,    -5095.9185, -37.569,
                            -61.63149, 2705.60775, 33.818111};
    S21Matrix Result_matrix(3, 3);
    Result_matrix.fill_matrix_from_vector(vec2);

    Matrix1 = Matrix1.calc_complements();
    ASSERT_TRUE(Matrix1.eq_matrix(Result_matrix));
}

TEST(test_throw, test14) {
    S21Matrix Matrix1(3, 3);
    ASSERT_ANY_THROW(Matrix1(33, 3));
}

TEST(test_throw, test15) {
    vector<double> vec{1, 2, 3,
                        4, 5, 6,
                        7, 8, 9};
    S21Matrix Matrix1(3, 3);
    Matrix1.fill_matrix_from_vector(vec);

    ASSERT_ANY_THROW(Matrix1.inverse_matrix());
}

TEST(test_throw, test16) {
    S21Matrix Matrix1(3, 2);
    ASSERT_ANY_THROW(Matrix1.determinant());
}

TEST(test_throw, test17) {
    S21Matrix Matrix1(3, 2);
    ASSERT_ANY_THROW(Matrix1.calc_complements());
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
