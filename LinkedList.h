#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

#define print(x)(std::cout<<x)
#define println(x)(std::cout<<x<<"\n")

template<class T> class node
{
  public:
  node(bool end=false)
  {
    prev=0;
    next=0;
    this->end = end;
  }
  ~node()
  {
    print("~node ");println(value);
  }
  T value;
  node<T> *prev;
  node<T> *next;
  bool end=false;
};
// A doubly linked list bracked inclusively by head and tail pointers.
// A dataend element marks past the end while iteratung either direction.
template<class T> class LinkedList
{
public:
LinkedList()
{
}
~LinkedList()
{
  if (values==0)return;
  println("~LinkedList");
  while(head!=tail)
  {
    node<T> *temp=tail;
    tail=tail->prev;
    delete temp;
  }
  delete head;
  delete dataend;
}
// adds a new value after tail
void Add(T t)
{
  if (values++==0)
  {
    head = tail = new node<T>;
    head->value=t;
    // add the end node and hook it into both ends of head
    dataend = new node<T>(true);
    head->next = dataend;
    head->prev = dataend;
    dataend->prev=head;
    dataend->next=head;
    return;
  }
  // create new element and insert it before dataend
  node<T> *newEntry = new node<T>();
  newEntry->value=t;
  newEntry->next=dataend;
  dataend->prev = newEntry;
  if (head==tail)
  {
    //println("head==tail");
    head->next=newEntry;
    newEntry->prev=head;
  }
  else
  {
    // tail points to newEntry
    tail->next = newEntry;
    newEntry->prev=tail;
  }
  tail=newEntry;
}
T GetNext(bool reset=false)
{
  if (values==0)throw;
  if (reset)
  {
    getnext=head->next;
    return head->value;
  }
  if (getnext==dataend)throw;
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
    getprev=tail->prev;
    return tail->value;
  }
  if (getprev==dataend)throw;
  node<T> *temp=getprev;
  getprev=getprev->prev;
  return temp->value;
}
void Print()
{
  if (values!=0)
  {
    print("values=");println(values);
    node<T> *temp=head;
    while(temp!=dataend) // looking for the dummy entry
    {
      println(temp->value);
      temp=temp->next;
    }
  }
}
bool EndNext()
{
  return getnext==dataend;
}
bool EndPrev()
{
  return getprev==dataend;
}

// Inner class iterator
// http://www2.lawrence.edu/fast/GREGGJ/CMSC270/linked/iterators.html
class iterator 
{
  friend class LinkedList;
  private:
  // points to the node the iterator is pointing to
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

  // Overload for the comparison operator ==
  bool operator==(const iterator& itr) const 
  {
    return nodePtr == itr.nodePtr;
  } 

  // Overload for the dereference operator *
  T& operator*() const 
  {
    return nodePtr->value;
  }

  // Overload for the preincrement operator ++
  iterator operator++() 
  {
    nodePtr = nodePtr->next;
    return *this;
  }

 // Overload for the predecrement operator ++
  iterator operator--() 
  {
    nodePtr = nodePtr->prev;
    return *this;
  }

  void remove()
  {
    nodePtr->prev->next = nodePtr->next;
    nodePtr->next->prev = nodePtr->prev;
    node<T> *temp = nodePtr->next;
    delete nodePtr;
    nodePtr = temp;
  }

  void insert(T t)
  {
    node<T> *newval = new node<T>();
    newval->value = t;
    node<T> *oldprev = nodePtr->prev;

    oldprev->next = newval;
    newval->prev = oldprev;

    newval->next = nodePtr;
    nodePtr->prev = newval;
  }

  iterator next(int count=1)
  {
    for (int i=0;i<count;i++)
    {
      nodePtr=nodePtr->next;
      if (nodePtr->end)
        break;
    }
    return *this;
  }

  iterator prev(int count=1)
  {
    for (int i=0;i<count;i++)
    {
      nodePtr=nodePtr->prev;
      if (nodePtr->end)
        break;
    }
    return *this;
  }

  iterator findnext(T t)
  {
    node<T> *temp = nodePtr;
    while(!temp->end)
    {
      if (temp->value==t)
        break;
      temp=temp->next;
    }
   nodePtr=temp;
   return *this;
  }

  iterator findprev(T t)
  {
    node<T> *temp = nodePtr;
    if (temp->end)temp=temp->prev;
    while(!temp->end)
    {
      if (temp->value==t)
        break;
      temp=temp->prev;
    }
   nodePtr=temp;
   return *this;
  }
}; // End of inner class iterator

iterator Head() const 
{
  return iterator(head);
}
    
iterator Tail() const 
{
  return iterator(tail);
}

iterator End() const
{
  return iterator(dataend);
}

iterator FindNext(T t) const
{
  node<T> *temp = head;
  while(temp!=dataend)
  {
    if (temp->value == t)
    {
      return iterator(temp);
    }
    temp = temp->next;
  }
  return iterator(dataend);
}

iterator FindPrev(T t) const
{
  node<T> *temp = head;
  while(temp!=dataend)
  {
    if (temp->value == t)
    {
      return iterator(temp);
    }
    temp = temp->prev;
  }
  return iterator(dataend);
}
private:
node<T> *head;
node<T> *tail;
node<T> *dataend;
int values=0;
node<T> *getnext;
node<T> *getprev;
};

#endif