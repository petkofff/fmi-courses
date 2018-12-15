#pragma once

#include <ostream>

template <class T>
class DLL {
   private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *first;
    Node *last;

   public:
    DLL();
    DLL(const T &firstElement);
    DLL(const DLL<T> &other);
    ~DLL();

    class Iterator;

    bool isEmpty() const;
    void print(std::ostream &o) const;

    const T &front() const;
    const T &back() const;

    T &front() { return first->data; }
    T &back() { return last->data; }

    bool append(const T &element);
    void append(DLL &other);
    void append(Iterator &iter);

    bool removeLast();
    bool removeFirst();

    void empty();

    operator bool() const;

    DLL &operator=(DLL &other);

    class Iterator {
       public:
        Iterator(Node *first, Node *last, DLL *iterated)
            : first(first), current(first), last(last), iterated(iterated) {}

        Iterator(const Iterator &other)
            : first(other.first),
              current(other.first),
              last(other.last),
              iterated(other.iterated) {}

        bool atLast() const { return (current == last); }

        bool atFirst() const { return (current == first); }

        bool isDone() const { return !current; }

        void setToFirst() { this->current = this->first; }

        void setToLast() { this->current = this->last; }

        bool removeElement() {
            if (!this->current) {
                return false;
            }

            if (atFirst()) {
                iterated->removeFirst();
            } else if (atLast()) {
                iterated->removeLast();
            } else {
                Node *prev = this->current->prev;
                Node *next = this->current->next;

                prev->next = next;
                next->prev = prev;

                delete this->current;
            }

            return true;
        }

        operator bool() const { return this->current; }

        const Iterator operator++(int) {
            const Iterator tmp(*this);
            ++this;
            return tmp;
        }

        Iterator &operator++() {
            if (this->current) {
                this->current = this->current->next;
            }
            return *this;
        }

        const Iterator operator--(int) {
            const Iterator tmp(*this);
            --this;
            return tmp;
        }

        Iterator &operator--() {
            if (this->current) {
                this->current = this->current->prev;
            }
            return *this;
        }

        T &operator*() { return this->current->data; }

       private:
        Node *first;
        Node *current;
        Node *last;
        DLL *iterated;
    };

    Iterator intoIter() {
        Iterator iter(first, last, this);
        return iter;
    }
};

template <class T>
DLL<T>::DLL() {
    first = nullptr;
    last = nullptr;
}

template <class T>
DLL<T>::DLL(const T &firstElement) {
    Node *firstNode = new (std::nothrow) Node;
    firstNode->data = firstElement;
    firstNode->next = nullptr;
    firstNode->prev = nullptr;

    first = firstNode;
    last = firstNode;
}

template <class T>
DLL<T>::~DLL() {
    this->empty();
}

template <class T>
bool DLL<T>::isEmpty() const {
    return !first && !last;
}

template <class T>
bool DLL<T>::append(const T &element) {
    Node *newNode = new (std::nothrow) Node;

    if (!newNode) {
        return false;
    }

    newNode->data = element;
    newNode->next = nullptr;

    if (!first || !last) {
        newNode->prev = nullptr;
        first = newNode;
        last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = newNode;
    }

    return true;
}

template <class T>
bool DLL<T>::removeLast() {
    if (last) {
        Node *lastNode = last;
        last = last->prev;
        delete lastNode;
        return true;
    } else {
        return false;
    }
}

template <class T>
bool DLL<T>::removeFirst() {
    if (first) {
        Node *firstNode = first;
        first = first->next;
        delete firstNode;
        return true;
    } else {
        return false;
    }
}

template <class T>
const T &DLL<T>::front() const {
    return first->data;
}

template <class T>
const T &DLL<T>::back() const {
    return last->data;
}

template <class T>
void DLL<T>::print(std::ostream &o) const {
    if (!this->first || !this->last) {
        return;
    }

    Iterator iter = this->intoIter();

    while (!iter.atLast()) {
        o << *iter << " - ";
        ++iter;
    }

    o << *iter;
}

template <class T>
void DLL<T>::append(DLL &other) {
    this->last->next = other.first;
    other.first->prev = this->first;
    this->last = other.last;

    other.first = nullptr;
    other.last = nullptr;
}

template <class T>
void DLL<T>::append(Iterator &iter) {
    while (iter) {
        append(*iter);
        ++iter;
    }
}

template <class T>
DLL<T>::operator bool() const {
    return first && last;
}

template <class T>
DLL<T> &DLL<T>::operator=(DLL &other) {
    this->empty();

    this->first = other.first;
    this->last = other.last;

    other.first = nullptr;
    other.last = nullptr;

    return *this;
}

template <class T>
void DLL<T>::empty() {
    Node *toDelete = this->first;

    while (toDelete) {
        this->first = this->first->next;
        delete toDelete;
        toDelete = this->first;
    }
}
