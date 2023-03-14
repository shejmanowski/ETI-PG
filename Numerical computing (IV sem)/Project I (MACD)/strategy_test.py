import MACD
from termcolor import colored as col
import matplotlib.pyplot as plt
import numpy as np



def test_strategy(prices, data_size, budget, signals):
    stock_balance = 0
    profitOverTime = []
    for i in range(data_size):
        stock_balance *= prices[i] / prices[i - 1]

        profitOverTime.append(stock_balance + budget - 1000)
        if i in signals:
            trade_price = signals[i]
            if signals[i] > 0 and trade_price > budget:  # if not enough money to buy
                trade_price = budget
            elif signals[i] < 0 and -trade_price > stock_balance:  # if not enough balance to sell
                trade_price = -stock_balance

            if signals[i] > 0:
                print(col('Buying for: -', 'red'), end='')
                print(round(trade_price, 2), end='')
                print("$ ", end='')
                print("(at: ", end='')
                print(round(prices[i], 2), end='')
                print("$)")
            elif signals[i] < 0:
                print(col('Selling for: +', 'green'), end='')
                print(round(-trade_price, 2), end='')
                print("$ ", end='')
                print("(at: ", end='')
                print(round(prices[i], 2), end='')
                print("$)")
            budget -= trade_price
            stock_balance += trade_price
            print("Budget after trade: ", end='')
            print(round(budget, 2))
            print("Stock balance after trade: ", end='')
            print(round(stock_balance, 2))
    budget += stock_balance  # selling all the stocks
    return budget, profitOverTime


def drawPlot(tab):
    fig = plt.figure()
    plt.figure(figsize=(8, 4), dpi=80)
    ax = plt.axes()
    ax.set_ylabel('Profit [%]')
    ax.set_xlabel('Stop loss [$]')
    ax.set_title('Profit depending on the stop loss (150 vs 500 vs 1000 days)')
    x = np.linspace(0, len(tab) - 1, len(tab))
    budgetLine, = plt.plot(x * 50, tab, linewidth=1, color='red', label='macd')
    plt.show()


def test_macd(data, data_size, budget):
    macd = MACD.macd(data, data_size)
    signal = MACD.signal(macd)
    signals = MACD.find_intersection_points(data, macd, signal, data_size)
    test_strategy_result = test_strategy(data, data_size, budget, signals)
    profit = test_strategy_result[0] - budget
    drawPlot(test_strategy_result[1])
    return profit

def test_macd_with_sl(data, data_size, budget, sl):
    macd = MACD.macd(data, data_size)
    signal = MACD.signal(macd)
    signals = MACD.find_intersection_points_with_sl(data, low, macd, signal, data_size, sl)
    test_strategy_result = test_strategy(data, data_size, budget, signals)
    profit = test_strategy_result[0] - budget
    drawPlot(test_strategy_result[1])
    return profit


def test_longterm(data, data_size, budget):
    signals = {}
    signals[0] = 10000
    signals[data_size - 1] = -10000
    profit = test_strategy(data, data_size, budget, signals)[0] - budget
    return profit


def test_macd_mod(data, data_size, budget):
    macd = MACD.macd(data, data_size)
    signals = MACD.macd_exp_buy_and_sell(macd, data_size)
    test_strategy_result = test_strategy(data, data_size, budget, signals)
    profit = test_strategy_result[0] - budget
    #drawPlot(test_strategy_result[1])
    return profit

data_size = 150 #  input("Period of time to test (in days): ")
file_name = "BTC-USD.csv"
stop_ls = 1000
prices = MACD.read_data(file_name, data_size, 'Close')
low = MACD.read_data(file_name, data_size, 'Low')

profit = round(test_macd_with_sl(prices, data_size, 1000, stop_ls), 2)


print("Profit: ", end='')
if profit >= 0:
    print(col("+", 'green'), end='')
    print(col(profit, 'green'), end='')
    print(col("$", 'green'))
else:
    print(col(profit, 'red'), end='')
    print(col("$", 'red'))
