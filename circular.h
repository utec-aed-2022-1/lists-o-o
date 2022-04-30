#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"


template <typename T>
class CircularList : public List<T> {  
    private:
        Node<T>* head;//sentinel
        int nodes;
public:
    CircularList() : List<T>() {
        head = new Node<T>();
        nodes = 0;
    }

    ~CircularList() {
        if(head) {
            if (head->prev)
                head->prev->next = nullptr;
        }
        if(head) {
            head->killSelf();
        }
        head = nullptr;
        nodes = 0;
    }

    T front() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        return head->next->data;
    }

    T back() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        return head->prev->data;
    }

    void push_front(T data) {
        Node<T>* node = new Node<T>(data);

        if(is_empty()) {
            head->next = node;
            head->prev = node;
            node->next = head;
            node->prev = head;
        } else {
            node->next = head->next;
            node->next->prev = node;
            head->next = node;
            head->next->prev = node;
        }

        nodes++;
    }

    void push_back(T data) {
        Node<T>* node = new Node<T>(data);

        if(is_empty()) {
            push_front(data);
        } else {
            node->prev = head->prev;
            node->prev->next = node;
            node->next = head;
            head->prev = node;
        }

        nodes++;
    }

    T pop_front() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        T data = head->next->data;

        if(size() == 1) {
            delete head->next;
            head->next = nullptr;
            head->prev = nullptr;
            nodes--;
            return data;
        }

        Node<T> *tmp = head->next;
        head->next = head->next->next;
        head->next->prev = head;
        delete tmp;
        nodes--;
        return data;
    }

    T pop_back() {
        if(is_empty())
            throw std::invalid_argument("It's empty");

        T data = head->prev->data;

        if(size() == 1) {
            delete head->next;
            head->next = nullptr;
            head->prev = nullptr;
            nodes--;
            return data;
        }

        Node<T> *tmp = head->prev;
        head->prev = head->prev->prev;
        head->prev->next = head;
        delete tmp;
        nodes--;
        return data;
    }

    T insert(T data, int pos) {
        if(pos < 0 || pos > size()-1)
            throw std::invalid_argument("Invalid position");

        if(pos == 0)
            push_front(data);
        else if(pos == size()-1)
            push_back(data);
        else {
            Node<T> *node = new Node<T>(data);
            Node<T> *tmp = head;

            for(size_t i=0; i<pos; ++i)
                tmp = tmp->next;
            node->next = tmp->next;
            node->next->prev = node;
            tmp->next = node;
            tmp->next->prev = tmp;
            nodes++;
        }

        return data;
    }

    bool remove(int pos) {
        if(pos < 0 || pos > size()-1) {
            return false;
            throw std::invalid_argument("Invalid position");
        }

        if(pos == 0)
            pop_front();
        else if(pos == size() - 1)
            pop_back();
        else {
            Node<T> *tmp = head;

            for(size_t i=0; i<pos; ++i)
                tmp = tmp->next;

            Node<T> *node = tmp->next;
            tmp->next = node->next;
            tmp->next->prev = tmp;
            delete node;
            nodes--;
        }

        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos > size() - 1)
            throw std::invalid_argument("Invalid position");

        Node<T> *tmp = head;
        for (int i=0; i<(pos+1); i++)
            tmp = tmp->next;
        return tmp->data;
    }

    bool is_empty() {
        return nodes == 0;
    }

    int size() {
        return nodes;
    }

    void clear() {
        if(head) {
            if (head->prev)
                head->prev->next = nullptr;
        }
        if(head) {
            head->killSelf();
        }
        head = nullptr;
        nodes = 0;
    }

    void sort() {
        if(is_empty()) return;

        for (int i = 0; i < nodes - 1; i++) { // bubble sort
            Node<T>* temp = head->next;

            for (int j = 0; j < nodes - i - 1; j++) {
                if (temp->data > temp->next->data) {
                    T temp_data = temp->data;
                    temp->data = temp->next->data;
                    temp->next->data = temp_data;
                }
                temp = temp->next;
            }
        }
    }

    bool is_sorted() {
        if(is_empty()) return true;

        Node<T>* tmp = head->next;
        for(int i = 0; i < nodes - 1; i++) {
            if(tmp->data > tmp->next->data)
                return false;
            tmp = tmp->next;
        }
        return true;
    }

    void reverse() {
        Node<T>* tmp = head;
        for(int i = 0; i < (nodes+1);i++){
            auto temporal = tmp->next;
            tmp->next = tmp->prev;
            tmp->prev = temporal;

            tmp = tmp->prev;
        }
    }

    std::string name() {
        Node<T>* tmp = head->next;
        std::string result;
        for(int i = 0; i < nodes; i++) {
            result += std::to_string(tmp->data) + " ";
            tmp = tmp->next;
        }
        return result;
    }

};

#endif
