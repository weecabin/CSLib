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
  delete dataend;
}
void Add(T t)
{
  if (values++==0)
  {
    head = tail = new node<T>;
    head->value=t;
    // add the end node
    dataend = new node<T>();
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
    println("head==tail");
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

  iterator operator--(int) 
  {
    iterator temp = *this;
    nodePtr = nodePtr->prev;
    return temp;
  }

  void Remove()
  {
    nodePtr->prev->next = nodePtr->next;
    nodePtr->next->prev = nodePtr->prev;
    node<T> *temp = nodePtr->next;
    delete nodePtr;
    nodePtr = temp;
  }

  void Insert(T t)
  {
    node<T> *newval = new node<T>();
    newval->value = t;
    node<T> *oldprev = nodePtr->prev;

    oldprev->next = newval;
    newval->prev = oldprev;

    newval->next = nodePtr;
    nodePtr->prev = newval;
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

iterator Find(T t) const
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

private:
node<T> *head;
node<T> *tail;
node<T> *dataend;
int values=0;
node<T> *getnext;
node<T> *getprev;
};

#endif