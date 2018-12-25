#pragma once

#include <functional>
#include <list>

using std::list;

template <class KEY, class VALUE>
class HashTable {
   public:
    HashTable() : size(defaultSize), nodesAdded(0), hash(defaultHash) {
        buffer = new list<Node>[size];
    }

    HashTable(size_t (*hash)(const KEY& key))
        : size(defaultSize), nodesAdded(0), hash(hash) {
        buffer = new list<Node>[size];
    }

    HashTable(size_t size) : size(size), nodesAdded(0), hash(defaultHash) {
        buffer = new list<Node>[size];
    }

    HashTable(size_t size, size_t (*hash)(const KEY& key))
        : size(size), nodesAdded(0), hash(hash) {
        buffer = new list<Node>[size];
    }

    HashTable(const HashTable& hashTable) = delete;

    ~HashTable() { delete[] buffer; }

    void add(const KEY& key, const VALUE& value);
    bool contain(const KEY& key) const;
    bool contain(const KEY& key, const VALUE& value) const;
    bool search(const KEY& key, VALUE& value) const;
    bool deleteElement(const KEY& key);
    VALUE* operator[](const KEY& key);

   private:
    struct Node {
        KEY key;
        VALUE value;
    };

    size_t size;
    size_t nodesAdded;
    list<Node>* buffer;

    size_t (*hash)(const KEY& key) = 0;

    size_t index(const KEY& key) const {
        size_t hashed = hash(key);
        return hashed % size;
    }

    static const size_t defaultSize = (1 << 20);
    static size_t defaultHash(const KEY& key) { return std::hash<KEY>()(key); }
};

template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::add(const KEY& key, const VALUE& value) {
    size_t index = this->index(key);
    Node node = {key, value};
    buffer[index].push_front(node);
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::contain(const KEY& key) const {
    size_t index = this->index(key);
    return !buffer[index].empty();
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::contain(const KEY& key, const VALUE& value) const {
    size_t index = this->index(key);

    for (auto iter = buffer[index].cbegin(); iter != buffer[index].cend();
         ++iter) {
        if ((*iter).key == key && (*iter).value == value) {
            return true;
        }
    }

    return false;
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::search(const KEY& key, VALUE& value) const {
    size_t index = this->index(key);

    for (auto iter = buffer[index].cbegin(); iter != buffer[index].cend();
         ++iter) {
        if ((*iter).key == key) {
            value = (*iter).value;
            return true;
        }
    }

    return false;
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::deleteElement(const KEY& key) {
    size_t index = this->index(key);

    for (auto iter = buffer[index].begin(); iter != buffer[index].end();
         ++iter) {
        if ((*iter).key == key) {
            buffer[index].erase(iter);
            return true;
        }
    }

    return false;
}

template <class KEY, class VALUE>
VALUE* HashTable<KEY, VALUE>::operator[](const KEY& key) {
    size_t index = this->index(key);

    for (auto iter = buffer[index].begin(); iter != buffer[index].end();
         ++iter) {
        if ((*iter).key == key) {
            return &(*iter).value;
        }
    }

    return nullptr;
}
