import time
import constants
import matrix
import solver
import time_service as ts
import matplotlib.pyplot as plt


def exercise_b():
    mat_a = matrix.make_a(constants.n, constants.a1, constants.a2, constants.a3)
    vect_b = matrix.make_b(constants.n)

    start = time.time()
    result_j, iterations_j = solver.jacobi(mat_a, vect_b)
    end = time.time()
    print()
    print('Jacobi results:')
    print('Time: ', end='')
    ts.print_time(end - start)
    print('Iterations number: ' + str(iterations_j))

    start = time.time()
    result_gs, iterations_gs = solver.gauss_seidel(mat_a, vect_b)
    end = time.time()
    print()
    print('Gauss-Seidel results:')
    print('Time: ', end='')
    ts.print_time(end - start)
    print('Iterations number: ' + str(iterations_gs))


def exercise_c():
    mat_a = matrix.make_a(constants.n, 3, constants.a2, constants.a3)
    vect_b = matrix.make_b(constants.n)

    start = time.time()
    result_j, iterations_j = solver.jacobi(mat_a, vect_b)
    end = time.time()
    print()
    print('Jacobi results:')
    print('Time: ', end='')
    ts.print_time(end - start)
    print('Iterations number: ' + str(iterations_j))

    start = time.time()
    result_gs, iterations_gs = solver.gauss_seidel(mat_a, vect_b)
    end = time.time()
    print()
    print('Gauss-Seidel results:')
    print('Time: ', end='')
    ts.print_time(end - start)
    print('Iterations number: ' + str(iterations_gs))


def exercise_d():
    mat_a = matrix.make_a(constants.n, 3, constants.a2, constants.a3)
    vect_b = matrix.make_b(constants.n)
    start = time.time()
    result_lu, res_norm = solver.lu(mat_a, vect_b)
    end = time.time()
    print('LU factorization results:')
    print('Norm(residuum): ' + str(res_norm))


def exercise_e():
    n = [100, 500, 1000, 2000, 3000]
    exec_time_jacobi = []
    exec_time_gauss_seidel = []
    exec_time_lu = []

    for i in range(len(n)):
        mat_a = matrix.make_a(n[i], constants.a1, constants.a2, constants.a3)
        vect_b = matrix.make_b(n[i])

        start = time.time()
        solver.jacobi(mat_a, vect_b)
        end = time.time()
        exec_time_jacobi.append(end - start)

        start = time.time()
        solver.gauss_seidel(mat_a, vect_b)
        end = time.time()
        exec_time_gauss_seidel.append(end - start)

        start = time.time()
        solver.lu(mat_a, vect_b)
        end = time.time()
        exec_time_lu.append(end - start)

    plt.figure(figsize=(12, 8), dpi=80)
    plt.plot(n, exec_time_jacobi, 'r',
             n, exec_time_gauss_seidel, 'b',
             n, exec_time_lu, 'g')
    plt.yscale('log')
    plt.ylabel('Time [s]', fontsize=15)
    plt.xlabel('Number of unknowns', fontsize=15)
    plt.legend(['Jacobi', 'Gauss-Seidel', 'LU'], fontsize=15)
    plt.title('Time of execution for different number of unknowns', fontsize=15)
    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.show()
