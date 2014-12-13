#!/usr/bin/python
''' Binary Tree
'''

class Node(object):
    '''Binary Node
    '''
    def __init__(self, value, left = None, right = None):
        self.value = value
        self.left = left
        self.right = right
    
    def __str__(self):
        strs = (str(self.value), str(self.left), str(self.right))
        return "%s ( %s , %s )" % strs

def height(node):
    return 1 + max(height(node.left), height(node.right)) if node else 0

def diametr(node):
    if not node: return 0
    d = height(node.left) + 1 + height(node.right)
    return max(d, diametr(node.left), diametr(node.right))


class Tree(object):
    '''Binary Tree
    '''
    def __init__(self, root=None):
        self.root = root

    def __str__(self):
        return 'Tree( %s )' % str(self.root or 'Empty')

    def height(self): return height(self.root)
    def diametr(self): return diametr(self.root)


if __name__ == '__main__':
    import unittest
    class BinTreeTest(unittest.TestCase):

	def test_str(self):
	    def check(n, s): self.assertEqual(str(n), s)
	    check(Tree(), 'Tree( Empty )')
	    check(Tree(Node(1, Node(2))), 'Tree( 1 ( 2 ( None , None ) , None ) )')
	    check(Node(1, Node(2), Node(7, Node(5), Node(6))),
                  '1 ( 2 ( None , None ) , 7 ( 5 ( None , None ) , 6 ( None , None ) ) )')

	def test_operators(self):
	    def check(n, h, d):
		t = Tree(n)
		self.assertEqual(t.height(), h)
		self.assertEqual(t.diametr(), d)
	    check(None, 0, 0)
	    check(Node(1, Node(1.1)), 2, 2)
	    check(Node(1, Node(1.1), Node(1.2)), 2, 3)

    unittest.main()
