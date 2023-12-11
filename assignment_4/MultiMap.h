#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;
struct TElems{
    TKey key;
    TValue* values;
    int sizeElems;
    int capacity;
};
#define NULL_TELEMS TElems{-111111,nullptr,0,0};
class MultiMap
{
	friend class MultiMapIterator;

private:
	TElems* elems;
    int* next;
    int hash(TKey k) const;
    int firstFree;
    int capacity;
    int sizeHash;
public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();
    int firstFreeSpace();
    void resize();
    void resizeElems(TElems& elem);
    void rehash();
    int getKeyRange() const;
};

