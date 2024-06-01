#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cassert>
using namespace std;

const int MINIMUM_CAPACITY = 3;

template <class T>
T *allocate(int capacity = MINIMUM_CAPACITY);
template <class T>
T *reallocate(T *a, int size, int capacity);

template <class T>
void print_array(T *a, int size, int capacity = 0, ostream &outs = cout);
template <class T>
void print(T *a, unsigned int how_many, ostream &outs = cout);

template <class T>
T *search_entry(T *a, int size, const T &find_me);
template <class T>
int search(T *a, int size, const T &find_me);

template <class T>
void shift_left(T *a, int &size, int shift_here);
template <class T>
void shift_left(T *a, int &size, T *shift_here);

template <class T>
void shift_right(T *a, int &size, int shift_here);
template <class T>
void shift_right(T *a, int &size, T *shift_here);

template <class T>
void copy_array(T *dest, const T *src, int many_to_copy);
template <class T>
T *copy_array(const T *src, int size);

template <class T>
string array_string(const T *a, int size);

// function definitions
template <class T>
T *allocate(int capacity)
    {
    T *s = new T[capacity]();
    return s;
    }

// print array
template <class T>
void print(T *a, unsigned int how_many, ostream &outs)
    {
    for (int i = 0; i < how_many; i++)
        {
        outs << setw(5) << *a;
        a++;
        }
    }

// 1.print "[size/capacity]"
// 2.print array by call print()function
template <class T>
void print_array(T *a, int size, int capacity, ostream &outs)
    {
    if (capacity == 0)
        {
        outs << "(" << setw(2) << size << ") [";
        }
    else
        {
        outs << "(" << setw(2) << size << "/" << setw(2) << capacity << ") [";
        }
    print(a, size, outs); // call print()function
    outs << " ]" << endl;
    outs << endl;
    }

// search for an element by using for loop and if statement
// search from right to left
template <class T>
T *search_entry(T *a, int size, const T &find_me)
    {
    for (T *walker = a + size - 1; walker >= a; walker--)
        if (*walker == find_me)
            {
            return walker; // here pointer a point to the element find_me
            }
    return nullptr;
    }

// search an designed element and return to index
// search from left to right
template <class T>
int search(T *a, int size, const T &find_me)
    {
    T *end = a + size - 1; // define a pointer to the last element of the array
    for (T *start = a; start <= end; ++start)
        { // travers the array
        if (*start == find_me)
            {                     // if a matching element is found
            return start - a; // return to i
            }
        }
    return -1; // if no matching element, return -1;
    }

// static array
template <class T>
void copy_array(T *dest, const T *src, int many_to_copy)
    {
    for (int i = 0; i < many_to_copy; i++)
        {
        *dest = *src;
        src++;
        dest++;
        }
    }

// return an array that have completed the copy
// dynamic array
template <class T>
T *copy_array(const T *src, int size)
    {
    T *dynamic_arr = allocate<T>(size);
    copy_array(dynamic_arr, src, size);
    return dynamic_arr;
    }

template <class T>
void shift_right(T *a, int &size, T *shift_here)
    {
    size++;
    for (T *walker = a + size - 1; walker > shift_here; walker--)
        {
        *walker = *(walker - 1);
        }
    }

template <class T>
void shift_right(T *a, int &size, int shift_here)
    {
    T *walker = a + shift_here;
    shift_right(a, size, walker);
    }

template <class T>
T *reallocate(T *a, int size, int capacity)
    {
    T *newArray = allocate<T>(capacity);
    copy_array(newArray, a, size);
    delete[] a;
    return newArray;
    }

template <class T>
void shift_left(T *a, int &size, T *shift_here)
    {
    for (T *walker = shift_here; walker < a + size - 1; ++walker)
        {
        *walker = *(walker + 1);
        }
    size--;
    }

template <class T>
void shift_left(T *a, int &size, int shift_here)
    {
    T *walker1 = a + shift_here;
    shift_left(a, size, walker1);
    }

template <class T>
string array_string(const T *a, int size)
    {
    ostringstream outs; // create an output string stream object
    outs << "[";
    for (int i = 0; i < size; i++, a++)
        {

        outs << *a << " ";
        }
    outs << "][" << size << "]";
    return outs.str();
    }

#endif
