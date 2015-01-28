#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>

template<typename Key, typename Value>
class BinaryTree
{
public:
    typedef Key KeyType;
    typedef Value ValueType;

    BinaryTree();
    ~BinaryTree();

    Value& operator [](const Key& key);
    bool remove(const Key& key);

    template<typename K, typename V>
    friend std::ostream& operator <<(std::ostream& os, const BinaryTree<K, V>& tree);

private:
    BinaryTree(const BinaryTree&); // delete

    struct Node
    {
        Key key;
        Value value;

        typedef Node* Child;
        Child left, right;

        Node(const Key& k, const Value& v = Value());
        ~Node();

        void print(std::ostream& os, size_t level = 0);

    private:
        Node(const Node&); // delete
    };

    Node* root;
};

// --- IMPLEMENTATION ---------------------------------------------------------

template<typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree()
    : root(0)
{
}

template<typename Key, typename Value>
BinaryTree<Key, Value>::~BinaryTree()
{
    if (root) delete root;
}

template<typename Key, typename Value>
Value& BinaryTree<Key, Value>::operator [](const Key& key)
{
    Node** link = &root;
    while (*link)
    {
        if ((**link).key == key) return (**link).value;
        link = &((key < (**link).key) ? (**link).left : (**link).right);
    }

    *link = new Node(key);
    return (**link).value;
}

template<typename Key, typename Value>
bool BinaryTree<Key, Value>::remove(const Key& key)
{
    Node** link = &root;
    while (*link)
    {
        if ((**link).key == key)
        {
            // FIXME: save children
            Node* node = *link;
            if (!node->left && !node->right) *link = 0; else
            if (node->left && !node->right) *link = node->left; else
            if (!node->left && node->right) *link = node->right; else
            {
                Node* last = node->left;
                while (last->right) last = last->right;

                last->right = node->right;
                *link = last;
            }

            node->left = 0;
            node->right = 0;
            delete node;
            return true;
        }

        link = &((key < (**link).key) ? (**link).left : (**link).right);
    }

    return false; // nothing to remove
}

template<typename Key, typename Value>
std::ostream& operator <<(std::ostream& os, const BinaryTree<Key, Value>& tree)
{
    tree.root->print(os);
    return os;
}

template<typename Key, typename Value>
BinaryTree<Key, Value>::Node::Node(const Key& k, const Value& v)
    : key(k), value(v)
    , left(0), right(0)
{
}

template<typename Key, typename Value>
BinaryTree<Key, Value>::Node::~Node()
{
    if (left) delete left;
    if (right) delete right;
}

template<typename Key, typename Value>
void BinaryTree<Key, Value>::Node::print(std::ostream& os, size_t level)
{
    // identation
    if (level) os << "+-";
    for (int i = 1; i < level; i++) os << "--";

    // empty or [key]=value
    if (!this)
    {
        os << "empty" << std::endl;
        return;
    }
    os << "[" << key << "]=" << value << std::endl;

    // children
    if (left || right)
    {
        left->print(os, level + 1);
        right->print(os, level + 1);
    }
}

#endif // BINARY_TREE_HPP
