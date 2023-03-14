import math


def format_time(time_in_sec):
    h = time_in_sec // (60 * 60)
    min = (time_in_sec - h * 60 * 60) // 60
    sec = math.floor(time_in_sec - h * 60 * 60 - min * 60)
    ms = round((time_in_sec - h * 60 * 60 - min * 60 - sec) * 1000)
    return h, min, sec, ms


def print_time(time_in_sec):
    h, min, sec, ms = format_time(time_in_sec)
    if h > 0:
        print(str(h) + ' hrs ' + str(min) + ' min ' + str(sec) + ' sec ' + str(ms) + ' ms')
    elif min > 0:
        print(str(min) + ' min ' + str(sec) + ' sec ' + str(ms) + ' ms')
    elif sec > 0:
        print(str(sec) + ' sec ' + str(ms) + ' ms')
    else:
        print(str(ms) + ' milisec')
