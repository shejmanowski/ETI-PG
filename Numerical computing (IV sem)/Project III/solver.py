from math import sqrt
import numpy as np
import numpy.linalg.linalg

import matrix
# import constants


def diag_vect(diag, vector):
    result = matrix.make_empty_vector(matrix.get_rows_numb(vector))
    for i in range(matrix.get_column_numb(diag)):
        result[i].append(vector[i][0] / diag[i][i])
    return result


def forward_sub(mat_lower, vect):
    result = matrix.make_empty_vector(matrix.get_rows_numb(vect))
    for i in range(matrix.get_rows_numb(vect)):
        row_sum = 0
        for j in range(i):
            row_sum += result[j][0] * mat_lower[i][j]
        result[i].append((vect[i][0] - row_sum) / mat_lower[i][i])
    return result


def backward_sub(mat_upper, vect):  # TODO: refactor with reverse(), just to make it look cleaner
    vect_len = matrix.get_rows_numb(vect)
    result = matrix.make_empty_vector(vect_len)
    for i in range(vect_len):
        row_sum = 0
        for j in range(i):
            row_sum += result[vect_len - j - 1][0] * mat_upper[vect_len - i - 1][vect_len - j - 1]
        result[vect_len - i - 1].append((vect[vect_len - i - 1][0] - row_sum) / mat_upper[vect_len - i - 1][vect_len - i - 1])
    return result


def make_l_and_u(mat):
    mat_size = matrix.get_rows_numb(mat)
    mat_u = matrix.copy_matrix(mat)
    mat_l = matrix.make_i(mat_size)
    for k in range(mat_size - 1):
        for j in range(k + 1, mat_size):
            mat_l[j][k] = mat_u[j][k] / mat_u[k][k]
            for i in range(k, mat_size):
                mat_u[j][i] = mat_u[j][i] - mat_l[j][k] * mat_u[k][i]
    return mat_l, mat_u


# def jacobi(mat_a, vect_b):
#     # x(k+1) = inv(-D)(L + U)x(k) + inv(D)b
#     mat_u = matrix.get_upper_triangular(mat_a)              # U
#     mat_l = matrix.get_lower_triangular(mat_a)              # L
#     mat_d = matrix.get_diag(mat_a)                          # D
#     vect_x = matrix.make_x(matrix.get_rows_numb(vect_b))    # x(0)
#     neg_d = matrix.negate_matrix(mat_d)                     # -D
#     solved_d_b = diag_vect(mat_d, vect_b)                   # inv(D)b
#     sum_l_u = matrix.add_matrices(mat_u, mat_l)             # L + U
#
#     iterations_n = 0
#     while not threshold_passed(mat_a, vect_x, vect_b, constants.threshold):
#         sum_l_u_times_x = matrix.multipy_matrices(sum_l_u, vect_x)                      # (L + U)x(k)
#         vect_x = matrix.add_matrices(diag_vect(neg_d, sum_l_u_times_x), solved_d_b)
#         iterations_n += 1
#
#     return vect_x, iterations_n
#
#
# def jacobi_2(mat_a, vect_b):
#     vect_x = matrix.make_x(matrix.get_rows_numb(mat_a))
#     vect_x_prev = matrix.copy_matrix(vect_x)
#     iterations = 0
#     while not threshold_passed(mat_a, vect_x, vect_b, constants.threshold):
#         for i in range(matrix.get_rows_numb(mat_a)):
#             sum_x = 0
#             for j in range(matrix.get_column_numb(mat_a)):
#                 if i != j:
#                     sum_x -= mat_a[i][j] * vect_x_prev[j][0]
#             sum_x += vect_b[i][0]
#             vect_x[i][0] = sum_x / mat_a[i][i]
#         vect_x_prev = matrix.copy_matrix(vect_x)
#         iterations += 1
#     return vect_x, iterations
#
#
# def gauss_seidel(mat_a, vect_b):
#     # x(k+1) = -inv(D + L)(Ux(k)) + inv(D + L)b
#     mat_u = matrix.get_upper_triangular(mat_a)              # U
#     mat_l = matrix.get_lower_triangular(mat_a)              # L
#     mat_d = matrix.get_diag(mat_a)                          # D
#     vect_x = matrix.make_x(matrix.get_rows_numb(vect_b))    # x(0)
#     sum_d_l = matrix.add_matrices(mat_d, mat_l)             # D + L
#     neg_d_l = matrix.negate_matrix(sum_d_l)                 # -(D + L)
#     solved_dl_b = forward_sub(sum_d_l, vect_b)              # inv(D + L)b
#
#     iterations = 0
#     while not threshold_passed(mat_a, vect_x, vect_b, constants.threshold):
#         product_u_x = matrix.multipy_matrices(mat_u, vect_x)    # Ux(k)
#         solved_dl_ux = forward_sub(neg_d_l, product_u_x)
#         vect_x = matrix.add_matrices(solved_dl_ux, solved_dl_b)
#         iterations += 1
#
#     return vect_x, iterations


def lu(mat_a, vect_b):
    mat_l, mat_u = make_l_and_u(mat_a)
    vect_y = forward_sub(mat_l, vect_b)
    vect_x = backward_sub(mat_u, vect_y)
    norm_res = norm(residuum(mat_a, vect_x, vect_b))
    return vect_x, norm_res


def lu_with_pivot(mat_a, vect_b):  # using numpy, because of pivoting (as it was allowed)
    print(vect_b)
    mat_a_np = np.array(mat_a)
    vect_b_np = np.array(vect_b)

    return numpy.linalg.solve(mat_a_np, vect_b_np)


def residuum(mat_a, vect_x, vect_b):
    res = matrix.multipy_matrices(mat_a, vect_x)
    res = matrix.add_matrices(res, matrix.negate_matrix(vect_b))
    return res


def norm(vect):
    squares_sum = 0
    for i in range(matrix.get_rows_numb(vect)):
        for j in range(matrix.get_column_numb(vect)):
            squares_sum += vect[i][j] ** 2
    return sqrt(squares_sum)


def threshold_passed(mat_a, vect_x, vect_b, threshold):
    if norm(residuum(mat_a, vect_x, vect_b)) < threshold:
        return True
    else:
        return False
