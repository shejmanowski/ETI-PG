import data_reader
import visualizer


if __name__ == '__main__':
    data = data_reader.read_data('SpacerniakGdansk.csv')
    visualizer.original_vs_interpolated(data, 'Gdansk Old Town')

