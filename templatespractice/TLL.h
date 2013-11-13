#include<iostream>
using namespace std;

template <class T>
class Node
{
private:
   T data;
   Node* _next;  //you can also place Node<T>* next;
protected:
public:
   Node(T a, Node* n=nullptr) //we will also take a Node pointer. So you actually have 2 constructors:
                              //One is that you get only a value and not Node* pointer and TWO: both
   {
      data = a;
      next = n;
   }

   ~Node() {}

   Node*& next() //Node Reference, so if I do next = something.. it will directly change next
   {
      return _next;
   }

   T& data() { return data; }

};


//IF you want to place char instead of other type of variables, you must modify your constructor and destructor
// so you have to build your specialization!!!

template <> //it will ONLY use this one if you have CHAR
Node<char*>::Node(char* a, Node<char*>* t)
{
   if(a)
   {
      data = new char[strlen(a)+1];
      strcpy(data, a);
   }
   else
   {
      data=NULL;
   }
   next=t;

}

template <>
Node<char*>::~Node()
{
   if(data)
      delete [] data;
}

template <class T>
class LinkedList
{
private:
   Node<T>* front;
   //we will use only external iterator
   unsigned int size;

protected:
   //function to find the back:
   bool findBack(Node<T>*& ref)
   {
      if(front)
      {
         if(front->next)
         {
            auto a = front;
            while(a->next()->next())
            {
               a = a->next();
            ref = a;
            return true;
            }
         }
         else
         {
            ref = front;
            return false;
         }
      }
      return nullptr;
   }

public:
   LinkedList() : front(nullptr), size(0) {}
  //4 functions: void push_front(T a), void push_back(T a), void pop_front(), void pop_back()
   void push_front(T a)
   {
      //Create a new Node:
     // auto n = new Node<T>(a, front); //we are setting values to the new Node and setting our NEXT pointer to FRONT
      //but when we set front to the new Node, we have to do only:
      front = new Node<T>(a,front);
      //increase the size
      size++;
   }
   void push_back(T a)
   {
      Node<T>* r = nullptr; 
      bool isBeforeBack = findBack();
      auto n = new Node<T>(a); //the first parameter is NULL
      size++;
      if(r)
      {
        if(!isBeforeBack)
        {
           front->next() =n;
        }
        else //we have one before the back
        {
           r->next()->next() = n;
        }
      }
      else
      {
         front = n;
      }


   }
  
   void pop_front()
   { //STEPS: create a temporary variable pointing FRONT ("a"), deallocate front, point front to temp,
      auto a = front;
      front = a->next();
      delete a;
      //decrease size
      size--;

   }
   
   void pop_back()
   {
      Node<T>* ref; 
      auto isBeforeBack=findBack(ref);
      if(ref)
      {
         size--;
         if(!isBeforeBack)
         {
            delete front;
            front = null;
         }
         else //something that it's not at the front
         {
            delete a->next(); //the next value is pointing to null
            a->next() = nullptr;
         }
      }
   }

   ~LinkedList(){}


};