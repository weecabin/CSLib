#ifndef MAP2_H
#define MAP2_H
#include "LinkedList.h"
#include "MyDefines.h"

template<class A, class B> class MapNode
{
  public:
  MapNode(A key, B value)
  {
    this->key=key;
    this->value=value;
  }
  A Key()
  {
    return key;
  }
  B Value() 
  {
    return value;
  }
  private:
  A key;
  B value;
};

// double linked map class
template<class A, class B> class Map2
{
  public:
  Map2(int maxsize=0)
  {
    this->maxsize=maxsize;
  }
  ~Map2()
  {
    if (ll.ValuesIn()==0)return;
    MapNode<A,B> *node = ll.GetNext(true);
    while(!ll.EndNext())
    { 
      //print("delete key: ");println(node->Key());
      delete node;
      node = ll.GetNext();
    }
    //print("delete key: ");println(node->Key());
    delete node;
  }
  int Size()
  {
    return ll.ValuesIn();
  }
  void Clear()
  {
    MapNode<A,B> *node = ll.GetNext(true);
    while(!ll.EndNext())
    { 
      //print("delete key: ");println(node->Key());
      delete node;
      node = ll.GetNext();
    }
    //print("delete key: ");println(node->Key());
    delete node;
    ll.Clear();
  }
  void CheckSize()
  {
    if (maxsize!=0 && ll.ValuesIn()>maxsize)
    {
      auto itr = ll.Tail();
      ll.erase(itr);
    }
  }
  void AddSorted(A key, B value)
  {
    if (ll.ValuesIn()==0)
    {
      //println("first map");
      Add(key,value);
      return;
    }
    MapNode<A,B> *node = ll.GetNext(true);
    if (key < node->Key())
      {
        //print("inserting at ");println(node->Key());
        ll.InsertAtNext(new MapNode<A,B>(key,value));
        CheckSize();
        return;
      }
    while(!ll.EndNext())
    { 
      //println("inwhile");      
      node = ll.GetNext();
      if (key < node->Key())
      {
        //print("inserting at ");println(node->Key());
        ll.InsertAtNext(new MapNode<A,B>(key,value));
        CheckSize();
        return;
      } 
    }
    Add(key,value);
  }
  void Add(A key, B value)
  {
    ll.Add(new MapNode<A,B>(key,value));
    CheckSize();
  }
  B operator[](A key)
  {
    return Value(key);
  }
  B Value(A key)
  {
    MapNode<A,B> *node = ll.GetNext(true);
    while(!ll.EndNext())
    {
      if (node->Key()==key)
        return node->Value();
      node = ll.GetNext();
    }
    return node->Value();
  }
  B GetValue(int index)
  {
    if (index>=ll.ValuesIn())throw;
    int i=0;
    MapNode<A,B> *node = ll.GetNext(true);
    //println(node->Value());
    if (i++==index)
      return node->Value();
    while(!ll.EndNext())
    { 
      node = ll.GetNext();
      //println(node->Value());
      if (i++==index)
        break;
    }
    return node->Value();
  }
  void List(void (*callback)(A,B),int count=-1)
  {
    //println("in List");
    if (count>0)
    {
      std::cout<<count<<" of "<<ll.ValuesIn()<<"\n";
    }
    MapNode<A,B> *node = ll.GetNext(true);
    callback(node->Key(),node->Value());
    if (--count==0)return;
    while(!ll.EndNext())
    { 
      node = ll.GetNext();
      callback(node->Key(),node->Value());
      if (--count==0)return;
    }
  }
  void Print()
  {
    std::cout<<"LL ValuesIn: "<<ll.ValuesIn()<<"\n";
    MapNode<A,B> *node = ll.GetNext(true);
    std::cout<<"key: "<<node->Key()<<"  value: "<<node->Value()<<"\n";
    while(!ll.EndNext())
    { 
      node = ll.GetNext();
      std::cout<<"key: "<<node->Key()<<"  value: "<<node->Value()<<"\n";
    }
  }
  private:
  int maxsize=0; // 0 = no limit
  LinkedList<MapNode<A,B>*> ll;
};

#endif