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
  void Add(A key, B value)
  {
    ll.Add(new MapNode<A,B>(key,value));
  }
  ~Map()
  {
    MapNode<A,B> *node = ll.GetNext(true);
    while(!ll.EndNext())
    { 
      print("delete key: ");println(node->Key());
      delete node;
      node = ll.GetNext();
    }
    print("delete key: ");println(node->Key());
    delete node;
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
  private:
  LinkedList<MapNode<A,B>*> ll;
};

#endif