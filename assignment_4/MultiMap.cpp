#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

int MultiMap::hash(TKey k) const {
    return abs(k%capacity);
}
//Theta(1)
MultiMap::MultiMap() {
	capacity=1000;
    elems=new TElems[capacity];
    for (int i = 0; i < capacity; ++i) {
        elems[i]=NULL_TELEMS;
    }
    next=new int [capacity];
    for (int i = 0; i <capacity ; ++i) {
        next[i]=-1;
    }
    firstFree=capacity;
    sizeHash=0;
}
//THeta(capacity)

void MultiMap::add(TKey c, TValue v) {
	int pos= hash(c);
    if (elems[pos].key==-111111)
    {
        elems[pos].key=c;
        elems[pos].capacity=1000;
        elems[pos].values=new TValue[elems[pos].capacity];
        elems[pos].values[0]=v;
        elems[pos].sizeElems=1;
        next[pos]=-1;
    } else{
//        int Free=firstFreeSpace();
//        if (Free==-1)
//            resize();
//        firstFree=firstFreeSpace();
        int current=pos;
        while (next[current]!=-1 && elems[current].key!=c)
            current=next[current];
        if (elems[current].key==c)
        {
            if (elems[current].sizeElems==capacity)
                resizeElems(elems[current]);
            elems[current].values[elems[current].sizeElems]=v;
            elems[current].sizeElems+=1;
        } else{
            int Free=firstFreeSpace();
            if (Free==-1)
                resize();
            firstFree=firstFreeSpace();
            elems[firstFree].key=c;
            elems[firstFree].capacity=1000;
            elems[firstFree].values=new TValue[elems[firstFree].capacity];
            elems[firstFree].sizeElems=1;
            elems[firstFree].values[0]=v;
            next[firstFree]=-1;
            next[current]=firstFree;
        }
    }
    sizeHash+=1;

}
//Best case Theta(1)
//Worst case Theta(resize)=Theta(capacity)
bool MultiMap::remove(TKey c, TValue v) {
	int pos= hash(c);
    if (elems[pos].key==c)
    {
        if (next[pos]==-1) {
            int j;
            for (j = 0; j < elems[pos].sizeElems; ++j) {
                if (elems[pos].values[j]==v)
                    break;
            }
            if (elems[pos].values[j]!=v)
                return false;
            for (int i = j; i <elems[pos].sizeElems-1 ; ++i) {
                elems[pos].values[i]=elems[pos].values[i+1];
            }
            elems[pos].sizeElems-=1;
            sizeHash-=1;
            if (elems[pos].sizeElems==0) {
                delete[] elems[pos].values;
                elems[pos] = NULL_TELEMS;
            }
            return true;
        }

        int j;
        for (j = 0; j < elems[pos].sizeElems; ++j) {
            if (elems[pos].values[j]==v)
                break;
        }
        if (elems[pos].values[j]!=v)
            return false;
        for (int i = j; i <elems[pos].sizeElems-1 ; ++i) {
            elems[pos].values[i]=elems[pos].values[i+1];
        }
        elems[pos].sizeElems-=1;
        sizeHash-=1;
        if (elems[pos].sizeElems==0) {
//            int nextpos;
//            for (nextpos = 0; nextpos < capacity; ++nextpos) {
//                if (next[nextpos]==pos)
//                    break;
//            }
//            next[nextpos]=next[pos];
            delete[] elems[pos].values;
            elems[pos] = NULL_TELEMS;
            int save=next[pos];
            elems[pos]=elems[next[pos]];
            next[pos]=next[next[pos]];
            elems[save]=NULL_TELEMS;
//            rehash();
        }
        return true;
    }
    int current=pos;
    while (next[current]!=-1 && elems[current].key!=c)
    {
        current=next[current];
    }
    if (current==-1)
        return false;
    if (elems[current].key!=c)
        return false;
    if (next[current]==-1) {
        int j;
        for (j = 0; j < elems[current].sizeElems; ++j) {
            if (elems[current].values[j]==v)
                break;
        }
        if (elems[current].values[j]!=v)
            return false;
        for (int i = j; i <elems[current].sizeElems-1 ; ++i) {
            elems[current].values[i]=elems[current].values[i+1];
        }
        elems[current].sizeElems-=1;
        sizeHash-=1;
        if (elems[current].sizeElems==0) {
            int nextpos;
            for (nextpos = 0; nextpos < capacity; ++nextpos) {
                if (next[nextpos]==current)
                    break;
            }
            next[nextpos]=-1;
            delete[] elems[current].values;
            elems[current] = NULL_TELEMS;
        }
        return true;
    }

    int j;
    for (j = 0; j < elems[current].sizeElems; ++j) {
        if (elems[current].values[j]==v)
            break;
    }
    if (elems[current].values[j]!=v)
        return false;
    for (int i = j; i <elems[current].sizeElems-1 ; ++i) {
        elems[current].values[i]=elems[current].values[i+1];
    }
    elems[current].sizeElems-=1;
    sizeHash-=1;
    if (elems[current].sizeElems==0) {
        int nextpos;
        for (nextpos = 0; nextpos < capacity; ++nextpos) {
            if (next[nextpos]==current)
                break;
        }
        next[nextpos]=next[current];
        delete[] elems[current].values;
        elems[current] = NULL_TELEMS;
//        rehash();
    }
    return true;
}
//Best case Theta(1)
//Worst case Theta(capacity)

vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue > found;
    int pos= hash(c);
    if (elems[pos].key==c)
        for (int i = 0; i < elems[pos].sizeElems; ++i) {
            found.push_back(elems[pos].values[i]);
        }
    else{
        int current=pos;
        while (next[current]!=-1 && elems[current].key!=c)
        {
            current=next[current];
        }
        if (elems[current].key!=c)
            return found;
        else{
            for (int i = 0; i < elems[current].sizeElems; ++i) {
                found.push_back(elems[current].values[i]);
            }
        }
    }
	return found;
}
//Best case Theta(1)
//Worst case Theta(nrHash)

int MultiMap::size() const {
    return sizeHash;
}
//Theta(1)

bool MultiMap::isEmpty() const {
    if (sizeHash!=0)
        return false;
	return true;
}
//Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
//Theta(1)

MultiMap::~MultiMap() {
    for (int i = 0; i < capacity; ++i) {
        if (elems[capacity].key!=-111111)
            delete[] elems[i].values;
    }
    delete[] elems;
    delete[] next;
}
//Theta(capacity)
int MultiMap::firstFreeSpace() {
    for (int i = 0; i < capacity; ++i) {
        if (elems[i].key==-111111)
            return i;
    }
    return -1;
}
//Best case Theta(1)
//Worsst case Theta(capacity)
void MultiMap::resize() {
    TElems* newElems=new TElems[capacity*2];
    int* newNext=new int [capacity*2];
    vector<TElem > aux;
    for (int i = 0; i < capacity; ++i) {
        if (elems[i].key!=-111111)
            for (int j = 0; j < elems[i].sizeElems; ++j) {
                aux.emplace_back(elems[i].key,elems[i].values[j]);
            }
    }
    capacity=2*capacity;
    delete[] next;
    delete[] elems;
    for (int i = 0; i <capacity ; ++i) {
        newNext[i]=-1;
    }
    for (int i = 0; i < capacity; ++i) {
        newElems[i]=NULL_TELEMS;
    }
    sizeHash=0;
    elems=newElems;
    next=newNext;
    for (int i = 0; i < aux.size(); ++i) {
        add(aux[i].first,aux[i].second);
    }
}
//Theta(capacity)
void MultiMap::resizeElems(TElems &elem) {
    TValue *newValues=new TValue [elem.capacity*2];
    for (int i = 0; i < elem.sizeElems; ++i) {
        newValues[i]=elem.values[i];
    }
    delete[] elem.values;
    elem.capacity*=2;
    elem.values=newValues;
}
//Theta(sizeElems)
void MultiMap::rehash() {
    TElems* newElems=new TElems[capacity];
    int* newNext=new int [capacity];
    vector<TElem > aux;
    for (int i = 0; i < capacity; ++i) {
        if (elems[i].key!=-111111)
            for (int j = 0; j < elems[i].sizeElems; ++j) {
                aux.emplace_back(elems[i].key,elems[i].values[j]);
            }
    }
    delete[] next;
    delete[] elems;
    for (int i = 0; i <capacity ; ++i) {
        newNext[i]=-1;
    }
    for (int i = 0; i < capacity; ++i) {
        newElems[i]=NULL_TELEMS;
    }
    sizeHash=0;
    elems=newElems;
    next=newNext;
    for (int i = 0; i < aux.size(); ++i) {
        add(aux[i].first,aux[i].second);
    }
}
//Theta(capacity)
int MultiMap::getKeyRange() const {
    int min=111111;
    int max=-111111;
    if (isEmpty())
        return -1;
    for (int i = 0; i < capacity; ++i) {
        if (elems[i].key!=-111111){
            if (elems[i].key<min)
                min=elems[i].key;
            if (elems[i].key>max)
                max=elems[i].key;
        }
    }
    return max-min;
}
//Theta(capacity)