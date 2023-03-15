import random
import sys

from exceptions import AgentException
from minmax import Minmax


class RandomAgent:
    def __init__(self, my_token='o'):
        self.my_token = my_token
        self.alghMinMax = Minmax()

    def decide(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException('not my round')
        return random.choice(connect4.possible_drops())

    def decideMinmax(self, connect4):
        if connect4.who_moves != self.my_token:
            raise AgentException('not my round')
        return self.alghMinMax.minMax(connect4, 7, True, -sys.maxsize, sys.maxsize)[0]
