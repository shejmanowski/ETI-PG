import math
import pandas as pd


def ema(data, period):
    ema = []
    alpha = 2 / (period + 1)
    base = 1 - alpha
    for i in range(len(data)):
        numerator = 0
        denominator = 0
        for j in range(period + 1):
            if i - j >= 0:
                numerator += data[i - j] * math.pow(base, j)
                denominator += math.pow(base, j)
            else:
                break
        ema.append(numerator / denominator)
    return ema


def signal(macd):
    return ema(macd, 9)


def macd(data, data_size):
    ema12 = ema(data, 12)
    ema26 = ema(data, 26)
    macd = []
    for i in range(data_size):
        macd.append(ema12[i] - ema26[i])
    return macd


def read_data(file_name, data_size, collumn):
    df = pd.read_csv(file_name)
    df = df.tail(data_size)

    data_list = []
    df.reset_index()

    for index, row in df.iterrows():
        data_list.append(row[collumn])
    print(len(data_list))
    return data_list


def find_intersection_points(price, macd, signal, data_size):
    intersection_points = {}
    for i in range(1, data_size):
        macd_was_top = macd[i - 1] - signal[i - 1] > 0  # True means macd was above signal yesterday
        macd_is_top = macd[i] - signal[i] > 0  # True means macd is above signal
        if macd_was_top != macd_is_top:  # if the lines intersect
            if macd_is_top:  # buy crypto
                intersection_points[i] = price[i]
            else:  # sell crypto
                intersection_points[i] = -price[i]
    return intersection_points


def find_intersection_points_with_sl(price, low, macd, signal, data_size, stop_loss):
    intersection_points = {}
    curr_stop_loss = 0
    sold_on_st = False
    for i in range(1, data_size):
        macd_was_top = macd[i - 1] - signal[i - 1] > 0  # True means macd was above signal yesterday
        macd_is_top = macd[i] - signal[i] > 0  # True means macd is above signal
        if macd_was_top != macd_is_top:  # if the lines intersect
            if macd_is_top:  # buy crypto
                curr_stop_loss = price[i] - stop_loss
                intersection_points[i] = price[i]
            else:  # sell crypto
                if sold_on_st:
                    sold_on_st = False
                else:  # buy crypto
                    curr_stop_loss = 0
                    intersection_points[i] = -price[i]
        elif price[i] < curr_stop_loss or low[i] < curr_stop_loss:  # stop loss sell
            sold_on_st = True
            intersection_points[i] = -price[i] + stop_loss
            curr_stop_loss = 0

    return intersection_points


def macd_exp_buy_and_sell(macd, data_size):
    buy_sell_points = {}
    streak = 0
    prev_buy = False
    prev_macd = macd[0]
    for i in range(1, data_size):
        if prev_macd <= macd[i]:
            if not prev_buy:
                streak = 0
                prev_buy = True
            streak += 1
            buy_sell_points[i] = streak / 30  # TO-DO: set it as parameter of the function + test different values
        elif prev_macd >= macd[i]:
            if prev_buy:
                streak = 0
                prev_buy = False
            streak += 1
            buy_sell_points[i] = -streak / 30
        prev_macd = macd[i]
    return buy_sell_points


def main():
    data_size = 1000

    closePrices = read_data("ETH-USD.csv", data_size, 'Close')
    lowPrices = read_data("ETH-USD.csv", data_size, 'Low')
    macd1 = macd(closePrices, data_size)

    dict = {'macd': macd1}

    df = pd.DataFrame(dict)
    df.to_csv('MACD_OUT.csv')

    signal1 = signal(macd1)
    dict2 = {'signal': signal1}

    df = pd.DataFrame(dict2)
    df.to_csv('SIGNAL_OUT.csv')


if __name__ == "__main__":
    main()