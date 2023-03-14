

def lagrange(data, x):
    yp = 0.0
    for point_1 in data:
        p = point_1[1]
        for point_2 in data:
            if point_1 != point_2:
                p = p * (x - point_2[0]) / (point_1[0] - point_2[0])
        yp = yp + p
    return x, yp


def lagrange_for_array(data, step):
    data_subset = data[::step]
    data_subset.append((data[-1]))
    interpolated_data = []
    for x in data:
        interpolated_data.append(lagrange(data_subset, x[0]))
    return interpolated_data, data_subset
