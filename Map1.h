#ifndef MAP1_H
#define MAP1_H
#include <iostream>

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

template<class A, class B>
class Iterator
{
    using Node2_t = Map1Node<A,B>;
    // constructor that takes in a pointer from the linked list
    public:
    Iterator() noexcept : current_node(nullptr){};
    Iterator(Node2_t *node) noexcept : current_node(node){};

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
        //std::cout<<this->current_node->value<<"\n";
        return this->current_node->value;
    };

    // searches the list from the current position to the end
    // returns the Iterator associated with key
    Iterator operator[](A key)
    { 
      Node2_t *temp = current_node;
      while(temp->next!=nullptr)
      {
        //println(temp->key);
        if (temp->key==key)
          break;
        temp=temp->next;
      }
      return Iterator(temp);
    }

private:
    // was going to use this for delete and insert, but it was messy
    // may visit it again
    //Node2_t *previous_node = nullptr;
    Node2_t *current_node = nullptr;
};

// Map1, implemented as a single linked list
template<class A, class B> class Map1
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
      if (ptr->key==key)
        break;
      prev=ptr;
      ptr=ptr->next;
    }
    if (ptr == first)
    {
      first = ptr->next;
    }
    else if (ptr == last)
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
        if (key < ptr->key)
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
        if (n2->key < n1->key) 
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
    return Iterator<A,B>(first);
  }
  Iterator<A,B> end()
  {
    return Iterator<A,B>(endnode);
  }
  private:
  bool sort=true;
  int size=0;
  Node2_t *first;
  Node2_t *last;
  Node2_t *endnode;
};

#endif