#ifndef LinkedList_H
#define LinkedList_H

#include "lab_2/Errors.h"
#include "lab_2/IEnumerator.h"

template <typename T>
class LinkedList {
public:
    LinkedList() {
        top = nullptr;
        low = nullptr;
        list_length = 0;
    }

    LinkedList(T *items, long length) : LinkedList() {
        if (items == nullptr) { throw NullPointerError(); }
        if (length < 0) { throw IndexOutOfRange(); }

        for (long items_index = 0; items_index < length; items_index ++) {
            Append(items[items_index]);
        }
    }

    LinkedList(const LinkedList<T> &other) : LinkedList() {
        Enumerator<T> enumerator = other.Get_enumerator();
        while (enumerator.Move_next()) {
            Append(enumerator.Get_current());
        }
    }

    ~LinkedList() {
        Node *current_element;
        for (long counter = 0; counter < list_length; counter ++) {
            current_element = top;
            top = current_element -> next;
            delete current_element;
        }
    }
    
    void Append(T item) {
        Node *new_node = new Node();
        new_node -> data = item;
        new_node -> next = nullptr;
        new_node -> prev = low;

        if (list_length == 0) {
            top = new_node;
            low = new_node;
        }
        else {
            low -> next = new_node;
            low = new_node;
        }
        list_length ++;
    }
    
    void Prepend(T item) {
        Node *new_node = new Node();
        new_node -> data = item;
        new_node -> next = top;
        new_node -> prev = nullptr;

        if (list_length == 0) {
            top = new_node;
            low = new_node;
        }
        else {
            top -> prev = new_node;
            top = new_node;
        }
        list_length ++;
    }

    T Pop_first() {
        if (list_length == 0) { throw EmptyCollection(); }

        Node *to_delete = top;
        T value = to_delete -> data;

        if (list_length == 1) {
            top = nullptr;
            low = nullptr;
        }
        else {
            top = to_delete -> next;
            top -> prev = nullptr;
        }
        delete to_delete;
        list_length --;
        return value;
    }

    T Pop() {
        if (list_length == 0) { throw EmptyCollection(); }

        Node *to_delete = low;
        T value = to_delete -> data;

        if (list_length == 1) {
            top = nullptr;
            low = nullptr;
        }
        else {
            low = to_delete -> prev;
            low -> next = nullptr;
        }
        delete to_delete;
        list_length --;
        return value;
    }

    T Get_first() const {
        if (list_length == 0) { throw EmptyCollection(); }
        return top -> data;
    }

    T Get_last() const {
        if (list_length == 0) { throw EmptyCollection(); }
        return low -> data;
    }

    long Get_length() const { return list_length; }

    T Get_list_index(long list_index) const {
        if ((list_index < 0) || (list_index >= list_length)) { throw IndexOutOfRange(); }

        Node *current_element = Find_node_by_index(list_index);
        return current_element -> data;
    }

    T& operator[](long list_index) {
        if ((list_index < 0) || (list_index >= list_length)) { throw IndexOutOfRange(); }

        Node *current_element = Find_node_by_index(list_index);
        return current_element -> data;
    }

    const T& operator[](long list_index) const {
        if ((list_index < 0) || (list_index >= list_length)) { throw IndexOutOfRange(); }
        
        Node *current_element = Find_node_by_index(list_index);
        return current_element -> data;
    }

    LinkedList<T> Get_sub_list(long start_index, long end_index) {
        if ((start_index < 0) || (end_index >= list_length)) { throw IndexOutOfRange(); }
        if (start_index > end_index) { throw IndexesTranslated(); }

        LinkedList<T> sub_list;
        Node *current_element = Find_node_by_index(start_index);
        for (long counter = start_index; counter <= end_index; counter ++) {
            sub_list.Append(current_element -> data);
            current_element = current_element -> next;
        }
        return sub_list;
    }

    void Insert_at(T item, long list_index) {
        if ((list_index < 0) || (list_index > list_length)) { throw IndexOutOfRange(); }

        if (list_index == 0) { Prepend(item); }
        else if (list_index == list_length) { Append(item); }
        else {
            Node *current_element = Find_node_by_index(list_index - 1);

            Node *new_node = new Node();
            new_node -> data = item;
            new_node -> prev = current_element;
            new_node -> next = current_element -> next;
            current_element -> next -> prev = new_node;
            current_element -> next = new_node;
            list_length ++;
        }
    }

    LinkedList<T> Concat(const LinkedList<T> &other_list) const {
        LinkedList<T> result_list(*this);
        Enumerator<T> enumerator = other_list.Get_enumerator();
        while (enumerator.Move_next()) {
            result_list.Append(enumerator.Get_current());
        }
        return result_list;
    }

    LinkedList<T>& operator=(const LinkedList<T> &other) {
        if (this != &other) {
            Node *current_element;
            for (long counter = 0; counter < list_length; counter ++) {
                current_element = top;
                top = top -> next;
                delete current_element;
            }
            low = nullptr;
            list_length = 0;

            Enumerator<T> enumerator = other.Get_enumerator();
            while (enumerator.Move_next()) {
                Append(enumerator.Get_current());
            }
        }
        return *this;
    }

    Enumerator<T> Get_enumerator() const {
        class LinkedListEnumerator : public IEnumerator<T> {
        private:
            const LinkedList<T> *list;
            Node *current_node;
            
        public:
            LinkedListEnumerator(const LinkedList<T> *list2) {
                list = list2;
                current_node = nullptr;
            }
            
            bool Move_next() override {
                if (current_node == nullptr) {
                    current_node = list -> top;
                    return current_node != nullptr;
                }
                current_node = current_node -> next;
                return current_node != nullptr;
            }
            
            T Get_current() override { return current_node -> data; }
            
            void Reset() override { current_node = nullptr; }
        };
        return Enumerator<T>(new LinkedListEnumerator(this));
    }

private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *top;
    Node *low;
    long list_length;

    Node* Find_node_by_index(long list_index) const {
        Node *current_element;
        if (list_index < (list_length / 2)) {
            current_element = top;
            for (long counter = 0; counter < list_index; counter ++) {
                current_element = current_element -> next;
            }
        }
        else {
            current_element = low;
            for (long counter = (list_length - 1); counter > list_index; counter --) {
                current_element = current_element -> prev;
            }
        }
        return current_element;
    }
};
#endif //LinkedList_H
