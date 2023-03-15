import sys
import copy


class Minmax:
    def __init__(self, my_token='x'):
        self.my_token = my_token

    def h(self, game):
        token = self.my_token
        rating = 0

        for t in game.center_column():
            if t == token:
                rating += 3
        for window in game.iter_fours():
            if window.count(token) == 3 and window.count('_') == 1:
                rating += 5
            elif window.count(token) == 2 and window.count('_') == 2:
                rating += 2
            elif window.count(token) == 0 and window.count('_') == 1:
                rating -= 4

        return rating


    def minMax(self, game, depth, maximization, alpha, beta):
        if game.game_over is True:
            if game.wins == 'x':
                return None, 10000
            elif game.wins == 'o':
                return None, -10000
            else:
                return None, 0

        elif depth == 0:
            return None, self.h(game)

        elif maximization is True:
            best_score = -sys.maxsize
            best_move = None
            for move in game.possible_drops():
                state_copy = copy.deepcopy(game)
                state_copy.drop_token(move)
                result = self.minMax(state_copy, depth - 1, not maximization, alpha, beta)[1]
                if result > best_score:
                    best_score = result
                    best_move = move
                alpha = max(alpha, best_score)
                if alpha >= beta:
                    break

        else:
            best_score = sys.maxsize
            best_move = None
            for move in game.possible_drops():
                state_copy = copy.deepcopy(game)
                state_copy.drop_token(move)
                result = self.minMax(state_copy, depth - 1, not maximization, alpha, beta)[1]
                if result < best_score:
                    best_score = result
                    best_move = move
                beta = min(beta, best_score)
                if alpha >= beta:
                    break

        return best_move, best_score
