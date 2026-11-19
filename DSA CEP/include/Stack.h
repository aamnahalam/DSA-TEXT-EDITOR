
#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <class T>
class Stack
{
private:
    T* arr;
    int top;
    int capacity;

    void resize()
    {
        int newCapacity = capacity * 2;

        T* newArr = new T[newCapacity];

        for (int i = 0; i <= top; i++)
        {
            newArr[i] = arr[i];
        }

        delete[] arr;

        arr = newArr;
        capacity = newCapacity;
    }

public:

    Stack(int size = 10)
    {
        capacity = (size > 0) ? size : 10;
        arr = new T[capacity];
        top = -1;
    }

    void push(T value)
    {
        if (top == capacity - 1)
        {
            resize();
        }

        top++;
        arr[top] = value;
    }

    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow!" << endl;
            return;
        }

        top--;
    }

    T peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return T();
        }

        return arr[top];
    }

    bool isEmpty()
    {
        return top == -1;
    }

    int getSize()
    {
        return top + 1;
    }

    int getCapacity()
    {
        return capacity;
    }

    
void clear()
{
    top = -1;
}


    ~Stack()
    {
        delete[] arr;
    }
};

#endif
