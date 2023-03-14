import solver


def calculate_coefficients(data):
    n = len(data) - 1
    coefficients_n = 4
    equations_n = n * coefficients_n

    left_side = [[0 for _ in range(equations_n)] for _ in range(equations_n)]
    right_side = [0 for _ in range(equations_n)]

    for j in range(n):
        h = data[j+1][0] - data[j][0]

        left_side[coefficients_n * j][coefficients_n * j] = 1
        right_side[coefficients_n * j] = data[j][1]

        for i in range(coefficients_n):
            left_side[coefficients_n * j + 1][coefficients_n * j + i] = h ** i
            right_side[coefficients_n * j + 1] = data[j + 1][1]

        if j > 0:
            for i in range(coefficients_n):
                if i == 0:
                    left_side[coefficients_n * (j - 1) + 2][i + coefficients_n * (j - 1)] = i
                else:
                    left_side[coefficients_n * (j - 1) + 2][i + coefficients_n * (j - 1)] = i * h ** (i - 1)
            left_side[coefficients_n * (j - 1) + 2][1 + coefficients_n * j] = -1

        if j > 0:
            left_side[coefficients_n * (j - 1) + 3][coefficients_n * (j - 1) + 2] = 2
            left_side[coefficients_n * (j - 1) + 3][coefficients_n * (j - 1) + 3] = 6 * h
            left_side[coefficients_n * (j - 1) + 3][coefficients_n * j + 2] = -2

        if j == n - 2:
            left_side[equations_n - 2][2] = 2
        if j == n - 1:
            left_side[equations_n - 1][-2] = 2
            left_side[equations_n - 1][-1] = 6 * h

    coefficients = solver.lu_with_pivot(left_side, right_side)
    return coefficients


def spline_calc(point, coefficients_n, coefficients, data):
    for i in range(len(data)-1):
        result = 0
        if data[i][0] <= point[0] <= data[i+1][0]:
            for j in range(coefficients_n):
                h = point[0] - data[i][0]
                result += coefficients[4 * i + j] * h**j
            break
    return result


def spline_interpolation(data, step):
    data_subset = data[::step]
    data_subset.append((data[-1]))
    result = []
    coefficients = calculate_coefficients(data_subset)
    for x in data:
        height = spline_calc(x, 4, coefficients, data_subset)
        result.append((data[0], height))
    return result, data_subset
