#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
  tail->next = new ListElement<T>;
  tail->next->prev=tail;
  tail=tail->next;
  tail->value=t;
}
T Get(bool first=false)
{
  if (first)
  {
    getnext=head->next;
    return head->value;
  }
  if (getnext==0)throw "End Of Data";
  ListElement<T> *temp=getnext;
  getnext=getnext->next;
  return temp->value;
}
void Print()
{
  
}
bool EndOfData()
{
  return getnext==0;
}
private:
ListElement<T> *head;
ListElement<T> *tail;
int values=0;
ListElement<T> *getnext;
};

#endif