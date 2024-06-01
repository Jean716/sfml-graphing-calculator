#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include <cassert>
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linked_list_functions.h"


template <typename T>
class Stack    // last-in/first-out (LIFO)
    {

    public:
        class Iterator
            {
            public:
                friend class Stack;       //give access to list to access _ptr
                Iterator() : _ptr(nullptr) {}          //default ctor
                Iterator(node<T>* p) : _ptr(p) {}       //Point Iterator to where
                //  p is pointing to
               // Dereference operator
                T& operator*()
                    {
                    assert(_ptr != nullptr && "Attempting to dereference a null iterator.");
                    return _ptr->_item;
                    };

                //member access operator                         
                T* operator->() // 
                    {
                    assert(_ptr != nullptr && "Attempting to access a member of a null iterator.");
                    return &(_ptr->_item);
                    };

                // Check if iterator points to null
                bool is_null() { return _ptr == nullptr; };

                // Inequality operator
                friend bool operator!=(const Iterator &left, const Iterator &right)
                    {
                    return left._ptr != right._ptr;
                    }

                // Equality operator
                friend bool operator==(const Iterator &left, const Iterator &right)
                    {
                    return left._ptr == right._ptr;
                    }

                //prefix operator: ++it
                Iterator &operator++()
                    {
                    assert(_ptr != nullptr && "Attempting to increment a null iterator.");
                    _ptr = _ptr->_next;
                    return *this;
                    };


                //friend operator: it++
                friend Iterator operator++(Iterator &it, int unused)
                    {
                    Iterator hold = it; // make a copy of the original iterator
                    it._ptr = it._ptr->_next;
                    return hold;  //  return the copy of the original iterator
                    };

            private:
                node<T>* _ptr;                          //pointer being encapsulated
            };

        Stack();

        Stack(const Stack<T>& copyMe);
        ~Stack();
        Stack<T>& operator=(const Stack<T>& RHS);

        T top();
        bool empty();
        void push(T item);
        T pop(); // Removes the top element of the stack.

        template<typename TT>
        friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe);

        Iterator begin() const;              //Iterator to the head node
        Iterator end() const;                //Iterator to NULL
        int size() const { return _size; }

    private:
        node<T>* _top;
        int _size;
    };

template<typename T>
Stack<T>::Stack() :_top(nullptr), _size(0)
    {
    }


//ANCHOR - Big Three
/*======================================================= DIVISION =======================================================*/
template<typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
    {
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
    }

/*=============================================*/
template<typename T>
Stack<T>::~Stack()
    {
    _clear_list(_top);
    _size = 0;
    }
/*=============================================*/
template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS)
    {

    if (this != &RHS)// check for self-assignment
        {
        // create a new list
        node<T>* new_top = _copy_list(RHS._top);

        // delte the old list
        _clear_list(_top);

        // update the head and size
        _top = new_top;
        _size = RHS._size;
        }

    return *this;
    }

/*========================================================================================================================*/


template<typename T>
T Stack<T>::top() //  Return the top item
    {
    assert(!empty() && "Stack is empty");
    return _top->_item;
    }

template<typename T>
bool Stack<T>::empty() //  Is the stack empty?
    {
    return _top == nullptr;
    }

template<typename T>
void Stack<T>::push(T item) //  Add an item to the top
    {
    _insert_head(_top, item);
    _size++;
    }

template<typename T>
T Stack<T>::pop() // Remove and return the top item
    {
    assert(!empty() && "Stack is empty");
    T item = _delete_node(_top, _top);
    _size--;
    return item;
    }

template<typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
    {
    return Iterator(_top);
    }

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() const
    {
    return Iterator(nullptr);
    }


template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe)
    {
    outs << "Stack: head->";

    for (typename Stack<TT>::Iterator it = printMe.begin(); it != printMe.end(); ++it)
        {
        outs << "[" << *it << "]-> ";
        }
    outs << "|||";
    return outs;
    }


#endif