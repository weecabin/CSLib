#ifndef MAP1_H
#define MAP1_H
#include <iostream>
#include <cstring>

template <class A>
class Equal
{
  public:
  bool operator()(A a, A b)
  {
    return a==b;
  }
};

// Specialized version of the above template
template <>
class Equal <const char*>
{
  public:
  bool operator()(const char *str1, const char *str2)
  {
    //print("in template<>Equal\n");
    if (strlen(str1)!=strlen(str2))
      return false;
    for (int i=0;i<strlen(str1)&&i<strlen(str2);i++)
    {
      if (str2[i]!=str1[i])
        return false;
    }
    return true;
  }
};

template<class A>
class Less
{
  public:
  bool operator()(A a,A b)
  {
    #ifdef DEBUG
    std::cout<<"In template<class A> Less";
    #endif 
    return a<b;
  }
};

// Specialized version of the above template
template<>
class Less <const char *>
{
  public:
  bool operator()(const char *str1, const char *str2)
  {
    #ifdef DEBUG
    std::cout<<"In template<>Less\n";
    #endif
    for (int i=0;i<strlen(str1)&&i<strlen(str2);i++)
    {
      if (str2[i]<str1[i])
        return false;
    }
    return true;
  }
};

//template<class A, class Lt = Less<A>, class Eq = Equal<A>>
// Node for the single (1) linked list Map1
template<class A, class B> class Map1Node
{
  public:
  Map1Node(){};
  Map1Node(A key, B value)
  {
    this->key=key;
    this->value=value;
  }
  A key;
  B value;
  Map1Node<A,B> *next=nullptr;
};

template<class A, class B, class Lt = Less<A>, class Eq = Equal<A>>
class Iterator
{
    using Node2_t = Map1Node<A,B>;
    // constructor that takes in a pointer from the linked list
    public:
    Iterator() noexcept : current_node(nullptr){};
    Iterator(Node2_t *node) noexcept : current_node(node)
    {
      //print("Iterator() creating: ");println(node->key);
    };

    // incrementing means going through the list
    Iterator &operator++() noexcept
    {
        if (current_node != nullptr)
        {
            //previous_node = current_node;
            current_node = current_node->next;
        }
        return *this;
    };

    // post fixing is bad in general but it has it's usages
    Iterator operator++(int) noexcept
    {
        Iterator tempIter = *this;// we make a copy of the iterator
        ++*this;                   // we increment and updata previous_node in the process
        return tempIter;           // we return the copy before increment
    };

    // we need to be able to compare nodes
    bool operator!=(const Iterator &other) const noexcept
    {
        return this->current_node != other.current_node;
    };

    // debug dump value 
    void Print()
    {
      std::cout<<"key: "<<current_node->key<<" Value: "<<current_node->value<<"\n";
    };

    // return the data from the node (dereference operator)
    B operator*() noexcept
    {
        #ifdef DEBUG
        std::cout<<this->current_node->value<<"\n";
        #endif
        return this->current_node->value;
    };

    // searches the list from the current position to the end
    // returns the Iterator associated with key
    // If no match is found, it returns a pointer to the end node
    Iterator operator[](A key)
    { 
      //print("find: ");println(key);
      Node2_t *temp = current_node;
      while(temp->next!=nullptr)
      {
        //print("checking: ");println(temp->key);
        if (eq(temp->key,key))
          break;
        temp=temp->next;
      }
      #ifdef DEBUG
      print("operator[] found: ");println(temp->key);
      #endif
      return Iterator(temp);
    }

    private:
    Eq eq;
    Lt lt;
    Node2_t *current_node = nullptr;
};


// Map1, implemented as a single linked list
template<class A, class B, class Lt = Less<A>, class Eq = Equal<A> > class Map1
{
  using Node2_t = Map1Node<A,B>;
  public:

  Map1(bool sort)
  {
    this->sort=sort;
    endnode=new Node2_t; // empty end node
  }

  Map1()
  {
    this->sort=true;
    endnode=new Node2_t;
  }

  ~Map1()
  {
    Node2_t *temp=first;
    while(temp!=endnode)
    {
      temp=temp->next;
      delete first;
      first = temp;
    }
    delete endnode;
  }

  void Delete(A key)
  {
    Node2_t *prev;
    Node2_t *ptr=first;
    while(ptr != endnode)
    {
      if (eq(ptr->key,key))
        break;
      prev=ptr;
      ptr=ptr->next;
    }
    if (eq(ptr,first))
    {
      first = ptr->next;
    }
    else if (eq(ptr,last))
    {
      prev->next = endnode;
    }
    else
    {
      prev->next = ptr->next;
    }
    delete ptr;
  }

  void Print()
  {
    Node2_t* temp=first;
    while(temp!=endnode)
    {
      std::cout<<"key:"<<temp->key<<" value:"<<temp->value<<"\n";
      temp=temp->next;
    }
  }
  void Insert(A key, B value)
  {
    Node2_t* newnode = new Node2_t(key,value);
    if (size++==0)
    {
      first = last = newnode;
      first->next = endnode;
      return;
    }
    if (sort)
    {
      Node2_t *ptr=first;
      Node2_t *prev=nullptr;
      while (ptr != endnode)
      {
        if (lt(key,ptr->key))
          break;
        prev=ptr;
        ptr=ptr->next;
      }
      if (ptr==first)
      {
        newnode->next = ptr;
        first=newnode;
        return;
      }
      else if (ptr==endnode)
      {
        last->next = newnode;
        last = newnode;
        newnode->next = endnode;
        return;
      }
      // ptr is not first or end
      prev->next=newnode;
      newnode->next=ptr;
      return;
    }
    else
    {
      last->next = newnode;
      last = newnode;
      newnode->next = endnode;
    }
  }
  void Sort()
  {
    Node2_t *n1 = first;
    Node2_t *n2;
    int count=0;
    while(n1->next!=endnode)
    {
      n2=n1->next;
      while(n2!=endnode)
      {
        if (lt(n2->key,n1->key)) 
        {
          Node2_t temp(n1->key,n1->value);
          n1->key=n2->key;
          n1->value=n2->value;
          n2->key=temp.key;
          n2->value=temp.value;
        }
        n2=n2->next;
      }
      n1=n1->next;
    }
  }

  Iterator<A,B> begin()
  {
    return Iterator<A,B,Lt,Eq>(first);
  }
  Iterator<A,B> end()
  {
    return Iterator<A,B,Lt,Eq>(endnode);
  }
  private:
  bool sort=true;
  int size=0;
  Node2_t *first;
  Node2_t *last;
  Node2_t *endnode;
  Eq eq;
  Lt lt;
};

#endif