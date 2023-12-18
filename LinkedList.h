#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T> *next;
    Node(T data)
    {
        this->data = data;
        next = NULL;
    }
    Node()
    {
        next = NULL;
    }
};

template <typename T>
class LinkedList
{
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }
    void push_back(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void push_front(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    void pop_back()
    {
        if (head == NULL)
            return;
        if (head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        else
        {
            Node<T> *temp = head;
            while (temp->next != tail)
            {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = NULL;
        }
        size--;
    }
    void pop_front()
    {
        if (head == NULL)
            return;
        if (head == tail)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
        else
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size--;
    }
    T front()
    {
        if (head == NULL)
            return -1;
        return head->data;
    }
    T back()
    {
        if (tail == NULL)
            return -1;
        return tail->data;
    }
    int getSize()
    {
        return size;
    }
    bool empty()
    {
        return size == 0;
    }
    T operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            exit(1);
        }
        Node<T> *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
    void reverse()
    {
        // 1 -> 2 -> 3 -> 4 -> 5
        // 5 -> 4 -> 3 -> 2 -> 1
        Node<T> *prev = NULL;
        Node<T> *curr = head;
        Node<T> *next = NULL;
        while (curr != NULL)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
};