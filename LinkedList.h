#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "MyDefines.h"

template<class T> class node
{
  public:
  // set end=true to indicate the end of the list
  node(bool end=false)
  {
    prev=nullptr;
    next=nullptr;
    this->end = end;
  }
  ~node()
  {
    //print("~node ");println(value);
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
  dataend = new node<T>(true);
}
~LinkedList()
{
  Clear();
  //println("delete dataend");
  delete dataend;
}

int ValuesIn()
{
  return values;
}
void Clear()
{
  if (values==0)return;
  while(head!=tail)
  {
    node<T> *temp=tail;
    //println("delete node");
    tail=tail->prev;
    delete temp;
  }
  //println("delete node");
  delete head;
  values=0;
}
// adds a new value after tail
void Add(T t)
{
  if (values++==0)
  {
    //println("first LL");
    head = tail = new node<T>;
    head->value=t;
    // add the end node and hook it into both ends of head
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
void InsertAtNext(T t)
{
  node<T> *newEntry = new node<T>();
  newEntry->value=t;
  node<T> *before = getnext->prev;
  if (before==head)head=newEntry;
  node<T> *after = before->prev;

  after->next = newEntry;
  newEntry->prev = after;

  before->prev = newEntry;
  newEntry->next = before;
  values++;
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
void Print(bool up = true)
{
  if (values!=0)
  {
    print("values=");println(values);
    if (up)
    {
      node<T> *temp=head;
      while(temp!=dataend) // looking for the dummy entry
      {
        println(temp->value);
        temp=temp->next;
      }
    }
    else
    {
      node<T> *temp=tail;
      while(temp!=dataend) // looking for the dummy entry
      {
        println(temp->value);
        temp=temp->prev;
      }
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

void insert(iterator itr,T t)
{
  node<T> *ptr = head;
  while(ptr!=dataend)
  {
    if (itr==iterator(ptr))
    {
      //print("found: ");println(ptr->value);
      node<T> *newval = new node<T>();
      newval->value = t;

      ptr->prev->next = newval;
      newval->prev = ptr->prev;

      newval->next = ptr;
      ptr->prev = newval;
      values++;
      return;
    }
    ptr=ptr->next;
  }
}

void erase(iterator itr)
{
  node<T> *ptr = head;
  while (ptr!=dataend)
  {
    if (itr==iterator(ptr))
    {
      //print("found: ");println(*itr);
      //print("prev: ");println(ptr->prev->value);
      //print("next: ");println(ptr->next->value);
      ptr->prev->next = ptr->next;
      ptr->next->prev = ptr->prev;
      if (ptr==head)
        head = dataend->next;
      else if (ptr==tail)
        tail=dataend->prev;
      //delete ptr;
      values--;
      return;
    }
    ptr=ptr->next;
  }
}

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