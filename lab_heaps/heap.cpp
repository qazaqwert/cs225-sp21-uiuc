
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // Update to return the index you are choosing to be1 your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // Update to return the index of the left child.
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // Update to return the index of the right child.
    return (2 * currentIdx) + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // Update to return whether the given node has a child
    if(2 * currentIdx > _elems.size() )
    return false;

    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t right = rightChild(currentIdx);
    size_t left = leftChild(currentIdx);
    
    if (right >= _elems.size()) return left; //if right is out of scope it cant be bigger than the left

    if (!higherPriority(_elems[left], _elems[right])) return right;

    return left;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.

    if (hasAChild(currentIdx) == false) //If the node has no children then its done
    return;

    size_t kiddo = maxPriorityChild(currentIdx); //Grabs the child of max priority from current index

    //recurse over the kiddies
    if (!higherPriority(_elems[currentIdx], _elems[kiddo])) { //if current index isnt a higher priority than it's max priority child
        std::swap(_elems[currentIdx], _elems[kiddo]); //Swap the current index with its highest prio kid
        heapifyDown(kiddo); //keep going
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    //thank you graham cracker evans very cool //Graham cracker evans bruh my sides
    //do I need to clear this? well since its a constructor i technically dont think so

    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.clear();
    _elems.push_back(T());

    //add daData to daElems
    for (size_t i = 0; i < elems.size(); i++)
        _elems.push_back(elems[i]);

    //go down because thats what cool kids do
    for (size_t j = parent(_elems.size() - 1); j > 0; j--)
      heapifyDown(j);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority

    //if daHeap is empty, just return an empty boy?
    if (empty()) return T();

    //god bless the lab videos
    T toReturn = _elems[root()];
    _elems[root()] = _elems[_elems.size() - 1];
    _elems.pop_back();
    heapifyDown(root());

    return toReturn;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (empty()) return T();

    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    //thank you graham very cool
    if (empty()) return;

    T daTemp = _elems[idx];
    _elems[idx] = elem;

    if(daTemp < elem)
        heapifyDown(idx);
    else
        heapifyUp(idx);
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    //daHeap is not empty
    if (_elems.size() > 1) return false;

    return true;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
