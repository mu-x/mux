#!/usr/bin/python

class Node:
    def __init__(self, value, next=None):
        self.value, self.next = value, next

    def __getitem__(self, num):
        while num < 0:
            num = num + len(self)
        while num:
            self, num = self.next, num - 1
        return self

    def __len__(self):
        count = 0
        while self != None:
            self, count = self.next, count + 1
        return count

    def __repr__(self):
        out = []
        while self != None:
            out.append(str(self.value))
            self = self.next
        out.append('None')
        return ' -> '.join(out)

def del_this(node):
    if not node.next:
        raise Exception('This is a last node!')
    node.value = node.next.value
    node.next = node.next.next

def mk_list(fin):
    node = None
    for it in xrange(fin, 0, -1):
        node = Node(it, node)
    return node

def loop_detect(node):
    a, b = node.next, node.next.next
    while a != b:
        a, b = a.next, b.next.next
    a = node
    while a != b:
        a, b = a.next, b.next
    return a.value

def test():
    nl = mk_list(5)
    print nl
    print 'len: %i' % len(nl)
    del_this(nl[3])
    print nl

    nl = mk_list(10)
    print nl, '->', nl[7].value
    nl[-1].next = nl[7]
    print loop_detect(nl)

if __name__ == '__main__':
    test()
