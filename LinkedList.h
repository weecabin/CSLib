#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

#define print(x)(std::cout<<x)
#define println(x)(std::cout<<x<<"\n")

template<class T> class ListElement
{
  public:
  ListElement()
  {
    prev=0;
    next=0;
  }
  ~ListElement()
  {
    print("~ListElement ");println(value);
  }
  T value;
  ListElement<T> *prev;
  ListElement<T> *next;
};

template<class T> class LinkedList
{
public:
~LinkedList()
{
  println("~LinkedList");
  while(head!=tail)
  {
    ListElement<T> *temp=tail;
    tail=tail->prev;
    delete temp;
  }
  delete head;
}
void Add(T t)
{
  if (values++==0)
  {
    head = new ListElement<T>;
    head->value=t;
    tail=head;
    return;
  }
  // create new element and point tail->next to it
  tail->next = new ListElement<T>;
  // assign the new tail prev pointer to the old tail
  tail->next->prev=tail;
  // new tail links are all setup
  // set tail to the new tail
  tail=tail->next;
  // assign the value
  tail->value=t;
}
T GetNext(bool reset=false)
{
  if (values==0)throw;
  if (reset)
  {
    getnext=head->next;
    return head->value;
  }
  if (getnext==0)throw;
  ListElement<T> *temp=getnext;
  getnext=getnext->next;
  return temp->value;
}
T GetPrev(bool reset=false)
{
  if (values==0)throw;
  if (reset)
  {
    getprev=tail->prev;
    return tail->value;
  }
  if (getprev==0)throw;
  ListElement<T> *temp=getprev;
  getprev=getprev->prev;
  return temp->value;
}
void Print()
{
  if (values!=0)
  {
    ListElement<T> *temp=head;
    while(temp!=0)
    {
      println(temp->value);
      temp=temp->next;
    }
  }
}
bool EndNext()
{
  return getnext==0;
}
bool EndPrev()
{
  return getprev==0;
}
private:
ListElement<T> *head;
ListElement<T> *tail;
int values=0;
ListElement<T> *getnext;
ListElement<T> *getprev;
};

#endif