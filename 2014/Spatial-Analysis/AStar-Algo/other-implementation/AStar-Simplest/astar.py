# http://stackoverflow.com/questions/4159331/python-speed-up-an-a-star-pathfinding-algorithm

import heapq
import numpy as np

def aStar(self, graph, current, end):
    openSet = set()
    openHeap = []
    closedSet = set()

    def retracePath(c):
        path = [c]
        while c.parent is not None:
            c = c.parent
            path.append(c)
        path.reverse()
        return path

    openSet.add(current)
    openHeap.append((0,current))
    while openSet:
        current = heapq.heappop(openHeap)[1]
        if current == end:
            return retracePath(current) # out ==> 
        openSet.remove(current)
        closedSet.add(current)
        for tile in graph[current]:
            if tile not in closedSet:
                tile.H = (abs(end.x-tile.x)+abs(end.y-tile.y))*10 
                if tile not in openSet:
                    openSet.add(tile)
                    heapq.heappush(openHeap, (tile.H,tile))
                tile.parent = current
    return [] # failed ==>


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
