#pragma once
#include <vector>
#include <cstddef>
#include <string>
#include <ostream>
template<typename K,typename V>

class HashMap{
    using namespace std;
    struct Entry{
        const K key;
        const V value;
    };
    size_t sz;
    vector tab;

    Hashmap():sz(0){tab = new vector(new forward_list(pair<K,V>))}

};