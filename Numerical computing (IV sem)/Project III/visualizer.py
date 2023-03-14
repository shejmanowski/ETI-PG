import matplotlib.pyplot as plt
import lagrange
import spline


def original_vs_interpolated(original, data_name):

    x = [x[0] for x in original]
    y_original = [x[1] for x in original]

    nodes_n = [16, 32, 64]

    fig, axis = plt.subplots(3, sharex=True)
    fig.suptitle('Lagrange interpolation for ' + data_name)

    # Plotting Lagrange results
    for it, node_n in enumerate(nodes_n):
        interpolated, nodes = lagrange.lagrange_for_array(original, node_n)
        y_interpolated = [x[1] for x in interpolated]

        x_nodes = [x[0] for x in nodes]
        y_nodes = [x[1] for x in nodes]

        axis[it].plot(x, y_original, x, y_interpolated)
        axis[it].plot(x_nodes, y_nodes, 'go', markersize=2)
        axis[it].set(ylabel='Altitude[m]')
        axis[it].set_title(f'Nodes number = {int(512 / node_n)}')

    axis[2].set(xlabel='Distance[m]')
    plt.tight_layout()
    fig, axis = plt.subplots(3, sharex=True)
    fig.suptitle('Spline interpolation for ' + data_name)

    # Plotting Splines results
    for it, node_n in enumerate(nodes_n):
        interpolated, nodes = spline.spline_interpolation(original, node_n)
        y_interpolated = [x[1] for x in interpolated]

        x_nodes = [x[0] for x in nodes]
        y_nodes = [x[1] for x in nodes]

        axis[it].plot(x, y_original, x, y_interpolated)
        axis[it].plot(x_nodes, y_nodes, 'go', markersize=2)
        axis[it].set(ylabel='Altitude[m]')
        axis[it].set_title(f'Nodes number = {int(512 / node_n)}')

    axis[2].set(xlabel='Distance[m]')

    plt.tight_layout()
    plt.show()
