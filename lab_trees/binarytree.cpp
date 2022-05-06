/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node *subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node *subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}

//helper function to aid with the recursion
template <typename T>
void BinaryTree<T>::mirror(Node *n)
{
    if (n == NULL)
        return;

    Node *temp = n->left;
    n->left = n->right;
    n->right = temp;

    mirror(n->left);
    mirror(n->right);
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    std::stack<T> s;
    int value;
    InorderTraversal<int> traversal(this->getRoot());
    //place data from traversal into our stack
    for (TreeTraversal<int>::Iterator it = traversal.begin(); it != traversal.end(); ++it) {
        s.push((*it)->elem);
    }
    //if stack isn't empty, store top value from it as initial largest value
    if (!s.empty()){ 
        value = s.top();
        s.pop();
    }
    //if value is not largest, break. Else, continue iterating
    while (!s.empty())
    {
        if (value < s.top())
        {
            return false;
        }
        value = s.top();
        s.pop();
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* n) const
{
    bool lOrdered = false, rOrdered = false;
    int rMost = 0, lMost = 0;

    if (n == NULL) return true;

    if (n->left != NULL) {
        lOrdered = isOrderedRecursive(n->left);
        rMost = rightMost(n->left);
    }
    else {
        lOrdered = true;
        rMost = n->elem;
    }
    if (n->right != NULL) {
        rOrdered = isOrderedRecursive(n->right);
        lMost = leftMost(n->right);
    }
    else {   
        rOrdered = true;
        lMost = n->elem;
    }
    if (lOrdered && rOrdered && (lMost>=n->elem) && (rMost<=n->elem))
        return true;
        
    return false;
}

//helper function to identify leftmost node of tree
template <typename T>
T BinaryTree<T>::leftMost(Node* n) const {
    if (n->left == NULL)
        return n->elem;
    return leftMost(n->left);
}

//helper function to identify leftmost node of tree
template <typename T>
T BinaryTree<T>::rightMost(Node* n) const {
    if (n->right == NULL)
        return n->elem;
    return rightMost(n->right);
}
