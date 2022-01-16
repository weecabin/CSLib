#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

#define print(x)(std::cout<<x)
#define println(x)(std::cout<<x<<"\n")

template<class T> class node
{
  public:
  node()
  {
    prev=0;
    next=0;
  }
  ~node()
  {
    print("~node ");println(value);
  }
  T value;
  node<T> *prev;
  node<T> *next;
};

template<class T> class LinkedList
{
public:
LinkedList()
{
}
~LinkedList()
{
  println("~LinkedList");
  while(head!=tail)
  {
    node<T> *temp=tail;
    tail=tail->prev;
    delete temp;
  }
  delete head;
}
void Add(T t)
{
  if (values++==0)
  {
    head = new node<T>;
    head->value=t;
    // add a dummy node at the end
    tail = new node<T>();
    head->next = tail;
    tail->prev=head;
    return;
  }
  // create new element and insert it before the dummy end node
  node<T> *newentry = new node<T>();
  newentry->value=t;
  node<T> *oldend = tail->prev;
  oldend->next = newentry;
  tail->prev = newentry;
  newentry->prev = oldend;
  newentry->next = tail;
}
T GetNext(bool reset=false)
{
  if (values==0)throw;
  if (reset)
  {
    getnext=head->next;
    return head->value;
  }
  if (getnext==tail)throw;
  node<T> *temp=getnext;
  getnext=getnext->next;
  return temp->value;
}
T GetPrev(bool reset=false)
{
  if (values==0)throw;
  if (reset)
  {
    // last entry is one before the dummy tail entry
    getprev=tail->prev->prev;
    return tail->prev->value;
  }
  if (getprev==0)throw;
  node<T> *temp=getprev;
  getprev=getprev->prev;
  return temp->value;
}
void Print()
{
  if (values!=0)
  {
    node<T> *temp=head;
    while(temp->next!=0) // looking for the dummy entry
    {
      println(temp->value);
      temp=temp->next;
    }
  }
}
bool EndNext()
{
  return getnext->next==0;
}
bool EndPrev()
{
  return getprev==0;
}

// Inner class iterator
// needs to be ported to my list
// http://www2.lawrence.edu/fast/GREGGJ/CMSC270/linked/iterators.html
class iterator 
{
  friend class LinkedList;
  private:
  node<T> *nodePtr;
  // The constructor is private, so only our friends
  // can create instances of iterators.
  iterator(node<T> *newPtr) : nodePtr(newPtr) {}

  public:
  iterator() : nodePtr(nullptr) {} 

  // Overload for the comparison operator !=
  bool operator!=(const iterator& itr) const 
  {
    return nodePtr != itr.nodePtr;
  } 

  // Overload for the dereference operator *
  T& operator*() const 
  {
    return nodePtr->value;
  }

  // Overload for the postincrement operator ++
  iterator operator++(int) 
  {
    iterator temp = *this;
    nodePtr = nodePtr->next;
    return temp;
  }
}; // End of inner class iterator

iterator begin() const 
{
  return iterator(head);
}
    
iterator end() const 
{
  return iterator(tail);
}

private:
node<T> *head;
node<T> *tail;
int values=0;
node<T> *getnext;
node<T> *getprev;
};

#endif