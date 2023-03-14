import math


def make_a(n, a1, a2, a3):
    matrix = make_empty_vector(n)
    for i in range(n):
        for j in range(n):
            if i == j:
                matrix[i].append(a1)
            elif i == j - 1 or i == j + 1:
                matrix[i].append(a2)
            elif i == j + 2 or i == j - 2:
                matrix[i].append(a3)
            else:
                matrix[i].append(0)
    return matrix


def make_empty_vector(n):
    empty_vec = list()
    for i in range(0, n):
        empty_vec.append(list())
    return empty_vec


def make_b(n):
    vector = make_empty_vector(n)
    for i in range(n):
        vector[i].append(math.sin(i * 5))  # 5 = f + 1, f = 4
    return vector


def make_x(n):
    vector = make_empty_vector(n)
    for i in range(n):
        vector[i].append(1)
    return vector


def make_i(n):
    mat_i = make_empty_vector(n)
    for i in range(n):
        for j in range(n):
            if i == j:
                mat_i[i].append(1)
            else:
                mat_i[i].append(0)
    return mat_i


def get_diag(matrix):
    matrix_diag = make_empty_vector(get_rows_numb(matrix))
    for i in range(get_rows_numb(matrix)):
        for j in range(get_column_numb(matrix)):
            if i == j:
                matrix_diag[i].append(matrix[i][j])
            else:
                matrix_diag[i].append(0)
    return matrix_diag


def get_upper_triangular(matrix):
    mat_upper = make_empty_vector(get_rows_numb(matrix))
    for i in range(get_rows_numb(matrix)):
        for j in range(get_column_numb(matrix)):
            if i < j:
                mat_upper[i].append(matrix[i][j])
            else:
                mat_upper[i].append(0)
    return mat_upper


def get_lower_triangular(matrix):
    mat_lower = make_empty_vector(get_rows_numb(matrix))
    for i in range(get_rows_numb(matrix)):
        for j in range(get_column_numb(matrix)):
            if i > j:
                mat_lower[i].append(matrix[i][j])
            else:
                mat_lower[i].append(0)
    return mat_lower


def get_rows_numb(matrix):
    return len(matrix)


def get_column_numb(matrix):
    return len(matrix[0])


def multipy_matrices(matrix_1, matrix_2):
    if get_column_numb(matrix_1) != get_rows_numb(matrix_2):   # checking if mat_a column numb == mat_b rows numb
        print('Can not multipy matrices - wrong dimensions')
        return

    multiply_result_rows_numb = get_rows_numb(matrix_1)
    multiply_result_columns_numb = get_column_numb(matrix_2)
    common_dimension = get_column_numb(matrix_1)
    multipy_result = make_empty_vector(multiply_result_rows_numb)
    for i in range(multiply_result_rows_numb):
        for j in range(multiply_result_columns_numb):
            sum_i_j = 0
            for k in range(common_dimension):
                sum_i_j += matrix_1[i][k] * matrix_2[k][j]
            multipy_result[i].append(sum_i_j)

    return multipy_result


def add_matrices(matrix_1, matrix_2):
    if get_column_numb(matrix_1) != get_column_numb(matrix_2) or get_rows_numb(matrix_1) != get_rows_numb(matrix_2):
        print('Can not add matrices - different dimensions')
        return

    add_result = make_empty_vector(get_rows_numb(matrix_1))
    for i in range(get_rows_numb(matrix_1)):
        for j in range(get_column_numb(matrix_1)):
            add_result[i].append(matrix_1[i][j] + matrix_2[i][j])
    return add_result


def negate_matrix(matrix):
    negation_result = make_empty_vector(get_rows_numb(matrix))
    for i in range(get_rows_numb(matrix)):
        for j in range(get_column_numb(matrix)):
            negation_result[i].append(-matrix[i][j])
    return negation_result


def matrices_are_equal(matrix_a, matrix_b):
    if get_column_numb(matrix_a) != get_column_numb(matrix_b) or get_rows_numb(matrix_a) != get_rows_numb(matrix_b):
        return False
    for i in range(get_rows_numb(matrix_a)):
        for j in range(get_column_numb(matrix_a)):
            if matrix_a[i][j] != matrix_b[i][j]:
                return False
    return True


def copy_matrix(mat):
    copy = make_empty_vector(get_rows_numb(mat))
    for i in range(get_rows_numb(mat)):
        for j in range(get_column_numb(mat)):
            copy[i].append(mat[i][j])
    return copy


def print_matrix(matrix):
    for i in range(get_rows_numb(matrix)):
        for j in range(get_column_numb(matrix)):
            if matrix[i][j] >= 0:
                print(' ' + str(matrix[i][j]), end=' ')
            else:
                print(str(matrix[i][j]), end=' ')
        print()


