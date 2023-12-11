#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    this->relation=r;
    this->nrPairs=0;
    this->capacity=100;
    this->elements=new TElem[capacity];
}
void SortedMap::resize() {
    TElem *newElems=new TElem[2* this->capacity];
    for (int i = 0; i < this->nrPairs; i++) {
        newElems[i]= this->elements[i];
    }
    this->capacity= this->capacity*2;
    delete[] this->elements;
    this->elements=newElems;
}
//Theta(nrPairs)
TValue SortedMap::add(TKey k, TValue v) {
	int index=0;
    while(index< this->nrPairs)
    {
        if(this->elements[index].first==k) {
            int to_return = this->elements[index].second;
            this->elements[index].second = v;
            return to_return;
        }
        index++;
    }
    index=0;
    if (this->nrPairs== this->capacity)
        this->resize();
    while(index<this->nrPairs)
    {
        if(this->relation(k, this->elements[index].first))
        {
            for (int i =this->nrPairs; i >index ; i--) {
                this->elements[i].first= this->elements[i-1].first;
                this->elements[i].second= this->elements[i-1].second;
            }
            this->elements[index].first=k;
            this->elements[index].second=v;
            this->nrPairs++;
            return NULL_TVALUE;
        }
        index++;
    }
    this->elements[this->nrPairs].first=k;
    this->elements[this->nrPairs].second=v;
    this->nrPairs++;
	return NULL_TVALUE;
}
//Best case - Theta(1)
//Worst case - Theta(nrPairs^2)
TValue SortedMap::search(TKey k) const {
	int index=0;
    while(index< this->nrPairs)
    {
        if(this->elements[index].first==k)
            return this->elements[index].second;
        index++;
    }
	return NULL_TVALUE;
}
//Best case - Theta(1)
//Worst case - Theta(nrPairs)
TValue SortedMap::remove(TKey k) {
	int index=0;
    bool found= false;
    int value;
    while(index<this->nrPairs && !found)
    {
        if(this->elements[index].first==k)
        {
            found= true;
            value= this->elements[index].second;
        }
        else
            index++;
    }
    if (!found)
        return NULL_TVALUE;
    else {
        for (int i = index; i < nrPairs - 1; i++) {
            this->elements[i].first = this->elements[i + 1].first;
            this->elements[i].second = this->elements[i + 1].second;
        }
        this->nrPairs--;
        return value;
    }
}
//Best case - Theta(1)
//Worst case - Theta(nrPairs)
int SortedMap::size() const {
	return this->nrPairs;
}
//Theta(1)
bool SortedMap::isEmpty() const {
	if(this->nrPairs==0)
        return true;
	return false;
}
//Theta(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//Theta(1)
SortedMap::~SortedMap() {
	delete[] this->elements;
}
//Theta(1)
std::vector<TKey> SortedMap::keySet() const {
    std::vector<TKey> vector1;
    for (int i = 0; i < nrPairs; i++) {
        vector1.push_back(this->elements[i].first);
    }
    return vector1;
}
//Theta(nrPairs)