#pragma once

template <class T>
class Vector {
   public:
    int getCapacity() const;
    int getLen() const;
    const T& getContent() const;

    Vector();
    Vector(const Vector<T>& other);
    ~Vector();

    void pushBack(const T& newEl);
    void popBack();
    bool deleteElement(int i);
    void empty();

    T& operator[](int i);
    const T& operator[](int i) const;

   protected:
    int capacity, len;
    T* content;

    static const int START_CAPACITY = 2;

    void reAlloc(int newCapacity);
};

template <class T>
int Vector<T>::getCapacity() const {
    return capacity;
}

template <class T>
int Vector<T>::getLen() const {
    return len;
}

template <class T>
const T& Vector<T>::getContent() const {
    return content;
}

template <class T>
Vector<T>::Vector() {
    capacity = START_CAPACITY;
    content = new T[capacity];
    len = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
    len = 0;
    capacity = 0;

    reAlloc(other.getCapacity());
    len = other.getLen();

    for (int i = 0; i < len; i++) {
        content[i] = other[i];
    }
}

template <class T>
Vector<T>::~Vector() {
    if (content) {
        delete[] content;
    }
}

template <class T>
void Vector<T>::reAlloc(int newCapacity) {
    int minLen = (newCapacity > len ? len : newCapacity);

    T* newContent = new T[newCapacity];

    for (int i = 0; i < minLen; i++) {
        newContent[i] = content[i];
    }

    capacity = newCapacity;

    delete[] content;
    content = newContent;
}

template <class T>
void Vector<T>::pushBack(const T& newEl) {
    if (capacity > len) {
        content[len++] = newEl;
    } else {
        reAlloc(len * 2);
        content[len++] = newEl;
    }
}

template <class T>
void Vector<T>::popBack() {
    if (len > 0) {
        len--;
    }
}

template <class T>
bool Vector<T>::deleteElement(int i) {
    if (i >= 0 && i < len) {
        for (int j = i + 1; j < len; j++) {
            content[j - 1] = content[j];
        }

        len--;
        return true;
    } else {
        return false;
    }
}

template <class T>
void Vector<T>::empty() {
    len = 0;
}

template <class T>
T& Vector<T>::operator[](int i) {
    return content[i];
}

template <class T>
const T& Vector<T>::operator[](int i) const {
    return content[i];
}
