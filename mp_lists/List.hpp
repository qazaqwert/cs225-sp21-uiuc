/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List()
{

  // @TODO: graded in MP3.1
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.  
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const
{
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  /// @todo Graded in MP3.1
  ListNode *ptr = head_;     //Sets a pointer to the first listnode
  ListNode *nodeNext = NULL; //Initializes a temp pointer to NULL to clean it out.
  while (ptr != NULL)        //Next points to the next node in the list, and its null when when the next node doesnt exist, so stop when null is reached
  {
    nodeNext = ptr->next; //next gets set equal to the next node in the list before deleting the current node so we can actually get to the next node
    delete ptr;           //the current node is deleted
    ptr = nodeNext;       //the new current node is set to the next node that was assigned earlier
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const &ndata)
{
  /// @todo Graded in MP3.1
  //cout << "Start of insertfront before new" << endl;
  ListNode *newNode = new ListNode(ndata); //newNode is a pointer to a new node with ndata in it
  //ADD: Edge case for when the list is currently empty
  //cout << "Start of insertfront after new" << endl;
  newNode->next = NULL; //clears out next and previous to null, which is the state of the data when its the only node in the list
  newNode->prev = NULL;
  //cout << "Before null case" << endl;
  if (head_ == NULL)
  {                  //When head == null, the list is currently empty
    head_ = newNode; //Sets the head equal to the newNode, since it is the head now
    tail_ = newNode; //Also sets the tail equal to the newNode since it is the tail as well, being the only node
    length_++;       //increments length
    //cout << "one step before null case done" << endl;
    return; //Exits function
  }
  //cout << "before non-null case" << endl;
  //Case when the list has some data already in it
  newNode->next = head_; //sets the next parameter of the new node to head because we are inserting this data in front of the current head
  head_->prev = newNode; //sets the previous of the head, which was null, to our new node so that we keep the list linked together
  head_ = newNode;       //now sets the head to be equal to the newNode, as it is the new head

  length_++; //Increments length
  //cout << "after non-null case" << endl;
  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T &ndata)
{
  /// @todo Graded in MP3.1
  ListNode *newNode = new ListNode(ndata);
  newNode->next = NULL; //clears out next and previous to null, which is the state of the data when its the only node in the list
  newNode->prev = NULL;
  //case when list is currently empty
  if (tail_ == NULL)
  {                  //When head == null, the list is currently empty
    head_ = newNode; //Sets the head equal to the newNode, since it is the head now
    tail_ = newNode; //Also sets the tail equal to the newNode since it is the tail as well, being the only node
    length_++;       //increments length
    return;          //Exits function
  }
  //Case when list is not currently empty

  newNode->prev = tail_;
  tail_->next = newNode;
  tail_ = newNode;

  length_++;
  return;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode *List<T>::split(ListNode *start, int splitPoint)
{
  /// @todo Graded in MP3.1
  ListNode *curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++)
  {
    curr = curr->next;
  }

  if (curr != NULL)
  {
    curr->prev->next = NULL;
    curr->prev = NULL;
  }

  return (curr);
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate()
{
  // @todo Graded in MP3.1
  //cout << "before 1st edge" << endl;
  if (this->head_ == NULL)
  {
    return;
  }
  //cout << "before 2nd edge" << endl;
  if (this->length_ < 3)
  {
    return;
  }
  //cout << "after 2nd edge" << endl;
  int triprotnum = ((length_) / 3); //Number of blocks of 3 to rotate
  //cout << "before outer for loop" << endl;
  for (int i = 0; i < triprotnum; i++)
  {
    //cout << "inside inner for loop" << endl;
    int start = i * 3;       //find the place to start the rotation for each block
    ListNode *temp1 = head_; //Creates a temp node at the head of the list
    if (start != 0)          //In the 0 case, we need to start at head, else we need to start at the start location
    {
      //cout << "start != 0 case" << endl;
      for (int a = 0; a < start; a++) //Need to iterate the first temp node to the correct start location
      {
        ListNode *tempNext = temp1->next;
        temp1 = temp1->next;
      }
    }
    // cout << "before assigning temp nodes" << endl;
    ListNode *temp2 = temp1->next; //Create a temp node for the one after the start
    ListNode *temp3 = temp2->next; //Create a temp node fot the last one in the list
    ListNode *prev1 = temp1->prev; //Stores the previous of the first element for safekeeping
    ListNode *prev2 = temp2->prev; //Stores the previous of the second element for safekeeping
    ListNode *prev3 = temp3->next; //Stores next of third element
    ListNode *prev4 = temp1->next; //I dont think i actually use this ngl but im keeping it here cuz it works

    temp1->prev = temp2->next; //Makes 1st node's prev be the last node of the 3
    temp1->next = prev3;       //Makes 1st node's next be what the last node's next used to be
    temp2->prev = prev1;       //Makes 2nd node's prev be what the 1st node's prev used to be
    temp3->next = prev2;       //Makes 3rd node's next point to the 1st, now 3rd, element

    if (temp1->next == NULL)
    { //If the next of the 1st, (now 3rd) node is null, it is now the tail
      tail_ = temp1;
    }
    else
    {
      temp1->next->prev = prev2; //Makes the outer 4th node's previous equal to new 3rd node if the new 3rd node isnt the last node in the List
    }
    if (temp2->prev == NULL)
    { //If the previous of the 2nd (Now first) node is null, it is now the head
      head_ = temp2;
    }
    if (prev1 != NULL)
    {
      temp2->prev->next = temp2;
    }
    continue;
  }
  // cout << "Before return, traverse through whole list" << endl;
  // cout << "node 1 data: ";
  // cout << head_->data << endl;
  // cout << "node 2 data: ";
  // cout << head_->next->data << endl;
  // cout << "node 3 data: ";
  // cout << head_->next->next->data << endl;
  // cout << "node 3 next: ";
  // cout << head_->next->next->next->data << endl;
  // cout << "node 4 data: ";
  // cout << head_->next->next->next->data << endl;
  // cout << "node 5 data: ";
  // cout << head_->next->next->next->next->data << endl;
  // cout << "node 6 data: ";
  // cout << head_->next->next->next->next->next->data << endl;
  return;
}

//__________________________________________________________________________________________________________________________________________________________________

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *&startPoint, ListNode *&endPoint)
{
  cout << "before edge 1" << endl;
  if (startPoint == NULL)
  {
    return;
  }
  cout << "after edge 1" << endl;
  /// @todo Graded in MP3.2
  ListNode *Omega = endPoint;
  ListNode *Alpha = startPoint;

  ListNode *tempEnd = endPoint->next;
  ListNode *ptr = NULL;

  ListNode *tempPrev = startPoint->prev;
  ListNode *tempNext = endPoint->next;

  ListNode *curr = startPoint;

  while (curr != tempEnd)
  {
    ptr = curr->prev;
    curr->prev = curr->next;
    curr->next = ptr;
    // curr->prev = currNext;
    // curr->next = currPrev;
    curr = curr->prev;
  }

  if (Omega == tail_)
  {
    tail_ = Alpha;
    tail_->next = NULL;
  }
  else
  {
    tempNext->prev = Alpha;
    Alpha->next = tempNext;
  }

  if (Alpha == head_)
  {
    head_ = Omega;
    head_->prev = NULL;
  }
  else
  {
    tempPrev->next = Omega;
    Omega->prev = tempPrev;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  /// @todo Graded in MP3.2
  ListNode *Omega = NULL;  //Omega is the end, start it out as NULL
  ListNode *temp = head_;  //temp saves the head for later
  ListNode *Alpha = head_; //Alpha is the start, start at head

  while (temp != NULL) //Temp is iterated to be the new start, so as long as start isnt null we keep going
  {
    for (int a = 0; temp->next != NULL && a < n - 1; a++)
    {
      temp = temp->next;
    }
    Omega = temp;
    ListNode *n = Omega->next;

    reverse(Alpha, Omega);

    temp = n;
    Alpha = temp;
  }
}
//STOP USING FOR LOOPS RETARD
// for (int a = 0; a < (length_ / n); a++) //Iterates through the list reversing blocks of size n until the remaining block is less than size n
// {
//   cout << "start of for loop" << endl;
//   ListNode *startCalc = NULL;
//   ListNode *endCalc = NULL;
//   cout << "before a==0 case" << endl;
//   if (a == 0)                           //If a==0, ie we havent done a reverse yet, we need to set the endPoint to n-1 past the head.
//   {
//     cout << "in a==0 if" << endl;
//     ListNode *startCalc = head_;       //Initializes a listnode pointer ref to be equal to head
//     ListNode *endCalc = head_;         //Inits endPt to be the head in order to iterate
//     for (int i = 1; i < n; i++)         //Iterates n-1 times
//     {
//       endCalc = endCalc->next;          //next's endcalc n-1 times
//     }
//   }

//   else                                  //if a!= 0, ie we have reversed a block already, we need to set the startPoint to tail_->next and endPoint to n past the tail.
//   {
//     cout << "in else case" << endl;
//     ListNode *startCalc = tail_->next; //Inits startcalc to be the tail->next
//     ListNode *endCalc = tail_;         //Inits endCalc to be the tail
//     cout << "before else case for" << endl;
//     for (int a = 0; a < n && endCalc != NULL; a++)         //Iterates n times
//     {

//       endCalc = endCalc->next;          //next's endcalc n times
//     }
//     cout << "after else case for" << endl;
//   }
//   cout << "before for reverse" << endl;
//   cout << "startCalc data: ";
//   if (startCalc->data != NULL){
//   cout << startCalc->data << endl;
//   }
//   cout << "endCalc data: ";
//   if (endCalc->data != NULL){
//   cout << endCalc->data << endl;
//   }
//   reverse(startCalc, endCalc);          //calls the reverse function with the specified start and endcalcs.
//   cout << "after for reverse" << endl;
// }
// cout << "after for loop" << endl;
// int remaining = (length_ % n);
// if (remaining != 0){        //Reverse the remaining nodes, need start to be tail_->next and end to be tail_->next * remaining.
// cout << "in remaining != 0 if" << endl;
// ListNode * remStart = tail_->next;   //Makes the start of the remaning nodes equal to tail->next
// ListNode * remEnd = tail_;           //Inits end of remaining
// for (int r = 0; r < remaining; r++)
// {
//   cout << "in remaining != 0 for" << endl;
//   remEnd = remEnd->next;              //Next's remEnd remaining number of times
// }
// cout << "before remaining != 0 reverse" << endl;
// reverse(remStart, remEnd);
// }
// cout << "before return" << endl;
// return;
//}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> &otherList)
{
  // set up the current list
  head_ = merge(head_, otherList.head_);
  tail_ = head_;

  // make sure there is a node in the new list
  if (tail_ != NULL)
  {
    while (tail_->next != NULL)
      tail_ = tail_->next;
  }
  length_ = length_ + otherList.length_;

  // empty out the parameter list
  otherList.head_ = NULL;
  otherList.tail_ = NULL;
  otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode *List<T>::merge(ListNode *first, ListNode *second)
{
  /// @todo Graded in MP3.2

  if (first == NULL)
  {
    return second;
  }
  if (second == NULL)
  {
    return first;
  }
  if (first == NULL && second == NULL)
  {
    return NULL;
  }
  ListNode *mergeHead;
  //Okay basic algo, go through and make sure edge cases are satisfied, then traverse through the first list to end, and connect to second list.
  if (first->data < second->data) //making sure that the head of first is less than the head of second
  {
    mergeHead = first; //storing first for later

    while (second != NULL) //Iterator loop, stops when second is iterated to the end
    {
      if (first->data < second->data) //If the second data is bigger than the first data, which it should be
      {
        if (first->next == NULL) //checks if first->next == NULL, which is true when we are at the tail of first
        {
          first->next = second; //Makes first->next (the tail) point to the start of the second list
          second->prev = first; //Makes second->prev (the head) point to the end of the end of the first list
          break;                //Exits the while loop and goes into the main if loop again to iterate over second
        }
        first = first->next; //If first->next isnt NULL, iterate it to the next position
      }
      else //When second data (head of second) is <= to the first data (tail of first)
      {
        ListNode *Adding = second;  //Making a new listnode equal to the second (head of second)
        second = second->next;      //Iterating second to next position
        Adding->prev = first->prev; //Inserting the head of second in the same position of the tail of first
        first->prev->next = Adding; //Making the one before Adding and the tail of first point to Adding
        Adding->next = first;       //Making adding point to the tail of first
        first->prev = Adding;       //Finishes inserting the head of second before the tail of first
      }
      //This while happens, checking to see if the nodes in second should be inserted before or after the last node in first, and stops once we do all of the second nodes.
    }
  }
  //Now for the case in which the first element in second is less than the first element in first
  else
  {
    mergeHead = second;
    while (first != NULL)
    {
      if (second->data < first->data)
      {
        if (second->next == NULL)
        {
          second->next = first;
          first->prev = second;
          break;
        }
        second = second->next; //Iterating second to next position in list
      }
      else
      {
        ListNode *Adding = first; //essentially doing the same stuff as before
        first = first->next;
        Adding->prev = second->prev;
        second->prev->next = Adding;
        Adding->next = second;
        second->prev = Adding;
      }
    }
  }

  return mergeHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode *List<T>::mergesort(ListNode *start, int chainLength)
{
  /// @todo Graded in MP3.2
  //cancer
  if (chainLength == 1) //chain size 1 only need return pointer -> segfault?
  {
    //cout<<"bruh what"<< endl;
    return start;
  }

  if (chainLength <= 0) //Chain length is not valid
  {
    return NULL;
  }

  ListNode *Alpha = start;
  ListNode *ptr = Alpha;
  ListNode *Beta = NULL;

  int halfLength = (chainLength / 2);
  int lengthOne = halfLength; //split up list, side lengths dont have to match
  int lengthTwo = chainLength - lengthOne;

  for (int i = 0; i < lengthOne - 1; i++) //Test more? -1 makes segfault no more?
  {
    ptr = ptr->next;
  }
  ListNode *newPtr = ptr;
  Beta = newPtr->next;
  ptr->next = NULL;
  Beta->prev = NULL;

  return merge(mergesort(Alpha, lengthOne), mergesort(Beta, lengthTwo)); //call merge recursively on now sorted alpha and beta
}
