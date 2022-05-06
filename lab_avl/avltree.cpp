/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* right = t->right;
    Node* tempLeft = right->left;

    t->right = tempLeft;
    right->left = t;
    t = right;

    t->left->height = 1 + std::max(heightOrNeg1(t->left->right), heightOrNeg1(t->left->left));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* left = t->left;
    Node* tempRight = left->right;

    t->left= tempRight;
    left->right = t;
    t = left;

    t->right->height = 1 + std::max(heightOrNeg1(t->right->right), heightOrNeg1(t->right->left));
    t->height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    if (subtree == NULL) return;

    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) < -1) {
        if (heightOrNeg1(subtree -> right -> left) - heightOrNeg1(subtree -> right -> right) > 0)
            rotateRightLeft(subtree);

        else rotateLeft(subtree);    
    }

    if (heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right) > 1) {
        if (heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) < 0)
            rotateLeftRight(subtree);

        else rotateRight(subtree);
    }

    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
        subtree = new Node(key, value);

    else if (key < subtree->key)
        insert(subtree -> left, key, value);

    else if (key > subtree->key)
        insert(subtree->right, key, value);

    else
        subtree->value = value;
    
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (key < subtree->key) {
        remove(subtree->left, key);
        rebalance(subtree);
        // your code here
    } else if (key > subtree->key) {
        remove(subtree->right, key);
        rebalance(subtree);
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            delete subtree;
            //it breaks when I don't include this line, I thought binding to null was
            //only good practice? idk maybe it has to do with the shit memory stored there
            subtree = NULL;
            rebalance(subtree);
            return;
            /* no-child remove */
            // your code here
        } else if (subtree->left != NULL && subtree->right != NULL) {
            Node * leftTree = subtree->left;
            while(leftTree->right != NULL)
            {
              leftTree = leftTree->right;
            }
            swap(leftTree, subtree);
            remove(subtree->left, leftTree->key);
            rebalance(subtree);
            /* two-child remove */
            // your code here
        } else {
            Node * temp = NULL;

            if(subtree->right == NULL)
                temp = subtree->left;

            else
                temp = subtree->right;

            delete subtree;
            subtree = temp;
            rebalance(subtree);
            /* one-child remove */
            // your code here
        }
        // your code here
        subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
    }
}
