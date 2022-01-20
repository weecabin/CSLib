#ifndef MAP_H
#define MAP_H
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

template<class A, class B> class Map
{
  public:
  ~Map()
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
  void AddSorted(A key, B value)
  {
    if (ll.ValuesIn()==0)
    {
      //println("first map");
      Add(key,value);
      return;
    }
    MapNode<A,B> *node = ll.GetNext(true);
    while(!ll.EndNext())
    { 
      //println("inwhile");
      if (key < node->Key())
      {
        //print("inserting at ");println(node->Key());
        ll.InsertAtNext(new MapNode<A,B>(key,value));
        return;
      }
      node = ll.GetNext();
    }
    ll.InsertAtNext(new MapNode<A,B>(key,value));
  }
  void Add(A key, B value)
  {
    ll.Add(new MapNode<A,B>(key,value));
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
  void Print()
  {
    MapNode<A,B> *node = ll.GetNext(true);
    std::cout<<"key: "<<node->Key()<<"  value: "<<node->Value()<<"\n";
    while(!ll.EndNext())
    { 
      node = ll.GetNext();
      std::cout<<"key: "<<node->Key()<<"  value: "<<node->Value()<<"\n";
    }
  }
  private:
  LinkedList<MapNode<A,B>*> ll;
};

#endif