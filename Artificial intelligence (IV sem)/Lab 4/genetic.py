import numpy as np
import random
from utils import fitness


class Genetic:
    def __init__(self, coords, population_size=100, elite_size=10, mutation_rate=0.01):
        self.coords = coords
        self.population_size = population_size
        self.elite_size = elite_size
        self.mutation_rate = mutation_rate

    def population_fitness(self, population):
        population_fitness = {}
        for i, individual in enumerate(population):
            # 1/fitness -> change to maximization problem
            population_fitness[i] = 1/fitness(self.coords, individual)

        return {k: v for k, v in sorted(population_fitness.items(), key=lambda item: item[1], reverse=True)}

    def best_solution(self, population):
        population_fitness = list(self.population_fitness(population))
        best_ind = population_fitness[0]
        return population[best_ind]

    def initial_population(self):
        population = []
        # Create initial population
        for i in range(self.population_size):
            solution = np.random.permutation(len(self.coords))
            population.append(solution)

        return population

    def selection(self, population):
        pop_fitness = self.population_fitness(population)
        sum_fitness = sum(pop_fitness)
        probab_prev = 0
        probab = {}
        selection = []
        for key, value in pop_fitness:
            probab[key] = probab_prev + (value / sum_fitness)

            probab_prev = probab[key]
        for i in range(1, len(population)):
            rand = random.random()
            for key, value in probab:
                if rand <= value:
                    selection.append(population[key])
                    break

        return selection

    def crossover_population(self, population):
        children = []
        for i in range(100):
            parent1 = random.choice(population)
            parent2 = random.choice(population)

            slice_start = random.randint(0, 24)
            slice_stop = random.randint(slice_start, 24)
            slicee = parent1[slice_start:slice_stop]

            for i in slicee:
                if i in parent2:
                    parent2.remove(i)

            parent2.insert(slicee, slice_start, slicee)
            children.append(parent2)
        return population

    def mutate_population(self, population):
        # TODO: implement mutation
        return population

    def next_generation(self, population):
        selection = self.selection(population)
        children = self.crossover_population(selection)
        next_generation = self.mutate_population(children)
        return next_generation
