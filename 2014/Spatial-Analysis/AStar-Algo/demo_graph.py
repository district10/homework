# http://scriptogr.am/jdp/post/pathfinding-with-python-graphs-and-a-star
from astar_graph import AStarGraph AStarGraphNode

# def make_graph(mapinfo):
def make_graph(width, height):
#    nodes = [[AStarGridNode(x, y) for y in range(mapinfo.height)] for x in range(mapinfo.width)]
    nodes = [[AStarGridNode(x, y) for y in range(height)] for x in range(width)]
    graph = {}
    for x, y in product(range(width), range(height)):
        node = nodes[x][y]
        graph[node] = []
        for i, j in product([-1, 0, 1], [-1, 0, 1]):
            if not (0 <= x + i < width): continue
            if not (0 <= y + j < height): continue
            graph[nodes[x][y]].append(nodes[x+i][y+j])
    return graph, nodes

def demo():     
    graph, nodes = make_graph(8, 8)
    paths = AStarGrid(graph)
    start, end = nodes[1][1], nodes[5][7]
    path = paths.search(start, end)
    if path is None:
        print "No path found"
    else:
        print "Path found:", path



# main work

def tmp():
    with open(fpath) as f:
        lines = [line.strip() for line in f] 
        print lines[0]
        print lines[0][5]



def load_graph():
    fpath = "data-smp.txt"
    data = np.genfromtxt(fpath, delimiter=",")
    print "load_graph"
    print data[0]
    print data[1]
    print data[0][3]
    print data[0][5]
    print data[0][6]

def main():
    load_graph();

if __name__ == '__main__': 
    print "ok"
    main()
    print "done"
