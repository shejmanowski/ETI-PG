import sys
from maze import Maze, path_from

def gbfs(maze):
    start_node = maze.find_node('S')
    end_node = maze.find_node('E')
    pq = [start_node]
    start_node.cost = 0
    while len(pq) > 0:
        pq.sort(key=lambda x: x.cost)
        node = pq.pop(0)  # FIFO
        node.visited = True
        if node.type == 'E':
            return path_from(node)

        children = maze.get_possible_movements(node)
        for child in children:
            if not child.visited:
                child.parent = node
                child.cost = abs(end_node.x - child.x) + abs(end_node.y - child.y)
                pq.append(child)

    return None

maze = Maze.from_file(sys.argv[1])
maze.draw()
maze.path = gbfs(maze)
print()
maze.draw()
print('path length: ', len(maze.path))
for node in maze.path:
    print(f'({node.x}, {node.y})', end=' ')
print()