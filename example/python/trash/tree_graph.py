#!/usr/bin/python

class Vertex:
    everything = []

    def __init__(self, ways=[]):
        self.ways = ways
        Vertex.everything.append(self)

    def has_way(self, vertex):
        for v in Vertex.everything:
            v.visited = False
        def sub_way(ways):
            if vertex in ways:
                return True
            for v in ways:
                if v.visited:
                    return False
                v.visited = True
                if sub_way(v.ways):
                    return True
            return False
        v.visited = True
        return sub_way(v.ways)

def is_connected(a, b):
    return a.has_way(b) or b.has_way(a)

def testVertex():
    a = Vertex()
    b = Vertex([a])
    c = Vertex([a])
    d = Vertex([c])

    assert is_connected(a, b)
    assert is_connected(a, c)
    assert is_connected(a, d)
    assert not is_connected(b, d)


class BNode:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def __repr__(self, level=0):
        return '%i ( %s, %s )' % (
            self.value, repr(self.left), repr(self.right))

    def add(self, value):
        if self.value > value:
            if self.left:
                self.left.add(value)
            else:
                self.left = BNode(value)
        else:
            if self.right:
                self.right.add(value)
            else:
                self.right = BNode(value)

class BTree:
    def __init__(self, numbers=[]):
        self.root = None
        for n in numbers:
            self.add(n)

    def __repr__(self):
        return repr(self.root)

    def add(self, n):
        if self.root:
            self.root.add(n)
        else:
            self.root = BNode(n)

    def find_path(self, summ):
        result = []
        if not self.root:
            return result
        def check_path(path):
            total = 0
            for i in xrange(1, len(path)):
                total += path[-i]
                if total == summ:
                    result.append(path[-i:])
        def iterate(current, path):
            path += (current.value, )
            check_path(path)
            if current.left:
                iterate(current.left, path)
            if current.right:
                iterate(current.right, path)
        iterate(self.root, tuple())
        return tuple(result)

def testBTree():
    tree = BTree([0, 2, 1, 1, -1, -1, -1])
    assert tree.find_path(3) == ((2, 1), )
    assert tree.find_path(-2) == ((-1, -1), (-1, -1))


def main():
    testVertex()
    testBTree()
    print 'Done'

if __name__ == '__main__':
    main()
