import sys
from maze import Maze, path_from

def djikstra(maze):
    start_node = maze.find_node('S')
    start_node.cost = 0
    pq = [start_node]
    while len(pq) > 0:
        pq.sort(key=lambda x: x.cost)
        e = pq.pop(0)
        e.vistited = True

        if e.type == 'E':
            return path_from(e)

        children = maze.get_possible_movements(e)
        for child in children:
            if not child.visited:
                new_cost = e.cost + maze.move_cost(e, child)
                if new_cost < child.cost:
                    child.cost = new_cost
                    child.parent = e
                    pq.append(child)
    return None

maze = Maze.from_file(sys.argv[1])
maze.draw()
maze.path = djikstra(maze)
print()
maze.draw()
print('path length: ', len(maze.path))
for node in maze.path:
    print(f'({node.x}, {node.y})', end=' ')
print()