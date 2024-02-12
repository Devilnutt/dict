#include <iostream>
#include <fstream>
#include <cctype>

class DictionaryList
{
    class Node
    {
    public:
        int value;
        Node* next;

        Node(int value) : value(value), next(nullptr) {}
    };

    Node* _head;

public:
    DictionaryList() : _head(nullptr) {}

    void insert(int value)
    {
        Node* newNode = new Node(value);

        if (_head == nullptr || value < _head->value)
        {
            newNode->next = _head;
            _head = newNode;
        }
        else
        {
            Node* current = _head;
            while (current->next != nullptr && current->next->value < value)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    bool search(int value)
    {
        Node* current = _head;
        while (current != nullptr)
        {
            if (current->value == value)
                return true;
            current = current->next;
        }
        return false;
    }

    void remove(int value)
    {
        if (_head == nullptr)
            return;

        if (_head->value == value)
        {
            Node* temp = _head;
            _head = _head->next;
            delete temp;
            return;
        }

        Node* current = _head;
        while (current->next != nullptr && current->next->value != value)
        {
            current = current->next;
        }

        if (current->next == nullptr)
            return;

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    void merge(DictionaryList& list)
    {
        Node* current = list._head;
        while (current != nullptr)
        {
            if (!search(current->value))
                insert(current->value);
            current = current->next;
        }
        list._head = nullptr; 
    }

    void deleteWords(DictionaryList& list)
    {
        Node* current = list._head;
        while (current != nullptr)
        {
            remove(current->value);
            current = current->next;
        }
    }

    friend DictionaryList getIntersection(DictionaryList& dict1, DictionaryList& dict2)
    {
        DictionaryList result;
        Node* current = dict1._head;
        while (current != nullptr)
        {
            if (dict2.search(current->value))
                result.insert(current->value);
            current = current->next;
        }
        return result;
    }

    ~DictionaryList()
    {
        while (_head != nullptr)
        {
            Node* temp = _head;
            _head = _head->next;
            delete temp;
        }
    }
};
