from astar import AStar, AStarNode
from math import sqrt

def get_loc(dict, id):
    return dict[id][0], dict[id][1]; # return location by id

def dist_from_to(id_from, id_to):
    x1, y1 = get_loc(id_from)
    x2, y2 = get_loc(id_to)
    return sqrt((x1 - x2)**2 + (y1 - y2)**2)


class AStarGraph(AStar):
    def heuristic(self, node, start, end):
        return sqrt((end.x - node.x)**2 + (end.y - node.y)**2)

class AStarGraphNode(AStarNode):
    def __init__(self, id, x, y,):
        self.id = id
        self.x, self.y = x, y
        super(AStarGraphNode, self).__init__()

    def move_cost(self, other):
        distance = dist_from_to(self.id, other.id)
        return distance
