import csv


def read_data(file_name):
    with open('data/' + file_name, 'r') as csv_f:
        raw_data = csv.reader(csv_f, delimiter=',')

        data = []
        for row in raw_data:
            data.append((float(row[0]), float(row[1])))
    return data
