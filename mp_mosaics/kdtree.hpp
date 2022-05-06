/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> &first, const Point<Dim> &second, int curDim) const
{
  /**
     * @todo Implement this function!
     */
  if (first[curDim] < second[curDim])
  {
    return true;
  }
  if (first[curDim] == second[curDim])
  {
    return (first < second);
  }
  return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> &target,
                                const Point<Dim> &currentBest, //what the fuck?
                                const Point<Dim> &potential) const
{
  /**
     * @todo Implement this function!
     */
  double currentBestDist = 0;
  double potentialDist = 0;
  for (int i = 0; i < Dim; i++)
  {
    potentialDist = (potentialDist + ((potential[i] - target[i]) * (potential[i] - target[i])));
    currentBestDist = (currentBestDist + ((currentBest[i] - target[i]) * (currentBest[i] - target[i])));
  }
  if (potentialDist < currentBestDist)
  {
    return true;
  }
  if (potentialDist == currentBestDist)
  {
    return (potentialDist < currentBestDist);
  }
  return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>> &newPoints)
{
  /**
  * @todo Implement this function!
  */

  root = NULL; //Empty out tree to begin
  size = 0;

  //test cases are sus
  if (newPoints.empty())
  {
    return;
  }

  vector<Point<Dim>> tempPoints = newPoints;

  root = treeRecurse(tempPoints, 0, tempPoints.size() - 1, 0); //Recurses and makes the tree
}
//First Helper Function for constructor
template <int Dim>
typename KDTree<Dim>::KDTreeNode *KDTree<Dim>::treeRecurse(vector<Point<Dim>> &newPoints, int left, int right, int delta)
{

  KDTreeNode *sub = NULL;

  if (right < left) //If right side smaller, we're done
  {
    return NULL;
  }

  int middle = ((right + left) / 2);

  sub = new KDTreeNode(quickSel(newPoints, left, right, delta % Dim, middle));

  size = size + 1; //After each recursive step, iterate size and dimension delta
  delta = delta + 1;

  sub->left = treeRecurse(newPoints, left, middle - 1, delta); //recursion over the left then right trees
  sub->right = treeRecurse(newPoints, middle + 1, right, delta);

  return sub;
}

//Second Helper Function for constructor, quickselect
template <int Dim>
Point<Dim> &KDTree<Dim>::quickSel(vector<Point<Dim>> &newPoints, int left, int right, int delta, int i)
{

  if (right == left) //if the right and left are the same we stop
  {
    return newPoints[right];
  }

  int pivot = partition(newPoints, left, right, delta, i); //use pivot helper func around index i to find new pivot point

  if (i < pivot == true)
  {
    return quickSel(newPoints, left, pivot - 1, delta, i);
  }
  if (i > pivot == true)
  {
    return quickSel(newPoints, pivot + 1, right, delta, i);
  }

  return newPoints[i]; //situation when i equals the pivot
}

//Third Helper Function for constructor, partition
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &newPoints, int left, int right, int delta, int i)
{
  int index = left;
  Point<Dim> old = newPoints[i];

  std::swap(newPoints[right], newPoints[i]);

  for (int a = left; a < right; a++) //go until the left and right are the same, while going along, if the value is smaller, swap it and keep going
  {
    if (smallerDimVal(newPoints[a], old, delta) == true)
    {
      std::swap(newPoints[a], newPoints[index]);
      index = index + 1;
    }
  }

  std::swap(newPoints[right], newPoints[index]); //swap around the original left and the current right and return

  return index;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim> &other) //copy constructor
{
  /**
   * @todo Implement this function!
   */
  //gotta do it recursively?
  //helper function time part 2
  root = copyRecurse(other.root, root); //start with root of original kdtree, and the root of the new kdtree other you wanna copy to
  size = other.size;
}
//Helper function for copy constructor
template <int Dim>
typename KDTree<Dim>::KDTreeNode *KDTree<Dim>::copyRecurse(KDTreeNode *other, KDTreeNode *sub)
{
  if (other == NULL) //If the other kdtree has a NULL root, stop.
  {
    return NULL;
  }

  sub = new KDTreeNode();
  sub->point = other->point;

  sub->left = copyRecurse(other->left, sub->left);
  sub->right = copyRecurse(other->right, sub->right);

  return sub;
}

template <int Dim>
const KDTree<Dim> &KDTree<Dim>::operator=(const KDTree<Dim> &rhs) //assignment operator
{
  /**
   * @todo Implement this function!
   */
  //copy but the thing already exists?
  if (this != NULL) //Get rid of the old data if it is in this
  {
    KDTDestroy(root);
  }

  copyRecurse(rhs->root, root); //Copy over the new data into the old root
  size = rhs.size;              //Update the size of the new KDTree
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() //destructor
{
  /**
   * @todo Implement this function!
   */
  KDTDestroy(root);
}

template <int Dim>
void KDTree<Dim>::KDTDestroy(KDTreeNode *&sub)
{
  if (sub == NULL)
  {
    return;
  }

  KDTDestroy(sub->right);
  KDTDestroy(sub->left);

  delete sub;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query) const
{
  /**
     * @todo Implement this function!
     */

  Point<Dim> temp = query;           //prevents fuckups
  Point<Dim> currBest = root->point; //Initializes the current best to the root, in recursive helper it keeps track of the current closest point to query
  NNRecurse(currBest, root, temp, 0);

  return currBest;
}

//Nearest Neighbor Helper
template <int Dim>
void KDTree<Dim>::NNRecurse(Point<Dim> &currBest, KDTreeNode *currNode, Point<Dim> &query, int delta) const
{
  KDTreeNode *alt = NULL;
  KDTreeNode *next = NULL;

  if (currNode == NULL) //if the node we are on is NULL, we skrrt
  {
    return;
  }

  if (smallerDimVal(currNode->point, query, delta) == false) //Checks to see if the currentNode's point val in dimension delta is smaller than the query point
  {
    alt = currNode->right; //If the currentNode we are looking at's point is larger than the query's point we make the alternative node be the right
    next = currNode->left; //And the next node to look at be the left, because the left should have a smaller point size
  }

  else
  {
    alt = currNode->left;   //If the currentNode we are looking at's point is smaller than the query's point, we make the alternative node be the left
    next = currNode->right; //And the next node to look at be the right, because the right should have a larger point size.
  }

  NNRecurse(currBest, next, query, (delta + 1) % Dim); //We then call NNRecurse again except this time the node we are comparing query to is the next node we found before
                                                       //We also iterate the dimension to the next level based on the overall Dim

  if (shouldReplace(query, currBest, currNode->point) == true) //If the current node point is closer to the query than the currBest, it is the currbest.
  {
    currBest = currNode->point;
  }

  float rad = 0; //Init radius to 0

  float dist = std::pow(currNode->point[delta] - query[delta], 2); //distance is the squared distance between the node's point val we are currently testing and the querys

  for (int a = 0; a < Dim; a++) //from a = 0 to dimension
  {
    rad = rad + std::pow(query[a] - currBest[a], 2); //Radius is equal to the radius, plus the squared dim-distance between the current best and the query
  }

  if (dist <= rad) //If the distance is less than the radius we need to go through again
  {
    NNRecurse(currBest, alt, query, (delta + 1) % Dim);
  }
}