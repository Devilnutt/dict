#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

class DictionaryList
{
public:
    class Node
    {
    public:
        std::string word;
        Node* next;

        Node(const std::string& word) : word(word), next(nullptr) {}
    };

    Node* _head;

    DictionaryList() : _head(nullptr) {}

    Node* begin() const {
        return _head;
    }
    
    void insert(const std::string& word)
    {
        Node* newNode = new Node(word);

        if (_head == nullptr || word < _head->word)
        {
            newNode->next = _head;
            _head = newNode;
        }
        else
        {
            Node* current = _head;
            while (current->next != nullptr && current->next->word < word)
            {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    bool search(const std::string& word)
    {
        Node* current = _head;
        while (current != nullptr)
        {
            if (current->word == word)
                return true;
            current = current->next;
        }
        return false;
    }

    void remove(const std::string& word)
    {
        if (_head == nullptr)
            return;

        if (_head->word == word)
        {
            Node* temp = _head;
            _head = _head->next;
            delete temp;
            return;
        }

        Node* current = _head;
        while (current->next != nullptr && current->next->word != word)
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
            if (!search(current->word))
                insert(current->word);
            current = current->next;
        }
        list._head = nullptr;
    }

    void deleteWords(DictionaryList& list)
    {
        Node* current = list._head;
        while (current != nullptr)
        {
            remove(current->word);
            current = current->next;
        }
    }

    friend DictionaryList getIntersection(DictionaryList& dict1, DictionaryList& dict2)
    {
        DictionaryList result;
        Node* current = dict1._head;
        while (current != nullptr)
        {
            if (dict2.search(current->word))
                result.insert(current->word);
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

int main() {
    setlocale(LC_ALL, "Russian");
    
    DictionaryList dict1, dict2;

    dict1.insert("apple");
    dict1.insert("banana");
    dict1.insert("cherry");

    dict2.insert("banana");
    dict2.insert("grape");
    dict2.insert("orange");

    std::cout << "Словарь 1: ";
    DictionaryList::Node* current1 = dict1.begin(); 
    while (current1 != nullptr) {
        std::cout << current1->word << " ";
        current1 = current1->next;
    }
    std::cout << std::endl;

    std::cout << "Есть ли слово «banana» в словаре 1? ";
    std::cout << (dict1.search("banana") ? "Да" : "Нет") << std::endl;

    dict1.remove("banana");

    std::cout << "Словарь 1 после удаления слова «banana»: ";
    DictionaryList::Node* current2 = dict1.begin();
    while (current2 != nullptr) {
        std::cout << current2->word << " ";
        current2 = current2->next;
    }
    std::cout << std::endl;

    dict1.merge(dict2);

    std::cout << "Словарь 1 после объединения со Словарем 2: ";
    DictionaryList::Node* current3 = dict1.begin();
    while (current3 != nullptr) {
        std::cout << current3->word << " ";
        current3 = current3->next;
    }
    std::cout << std::endl;

    dict1.deleteWords(dict2);

    std::cout << "Словарь 1 после удаления слов из в Словаря 2: ";
    DictionaryList::Node* current4 = dict1.begin();
    while (current4 != nullptr) {
        std::cout << current4->word << " ";
        current4 = current4->next;
    }
    std::cout << std::endl;

    DictionaryList intersection = getIntersection(dict1, dict2);

    std::cout << "Пересечение Словаря 1 и Словаря 2: ";
    DictionaryList::Node* current5 = intersection.begin();
    while (current5 != nullptr) {
        std::cout << current5->word << " ";
        current5 = current5->next;
    }
    std::cout << std::endl;

    return 0;
}
