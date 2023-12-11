#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    if (col.sizeHash==0) {
        currentKey = -1;
        return;
    }
    for (int i = 0; i < col.capacity; ++i) {
        if (col.elems[i].key!=-111111) {
            currentKey = i;
            currentValue=0;
            break;
        }
    }
}
//Best case Theta(1)
//Worst case Theta(capacity)
TElem MultiMapIterator::getCurrent() const{
    if (!valid())
        throw exception();
	return TElem {col.elems[currentKey].key,col.elems[currentKey].values[currentValue]};
}
//Theta (valid)
bool MultiMapIterator::valid() const {
    if (currentKey==-1)
        return false;
//    else{
//        if (col.elems[currentKey].sizeElems==currentValue)
//            return false;
//    }
	return true;
}
//theta(1)
void MultiMapIterator::next() {
    if (!valid())
        throw exception();
    if (currentValue+1==col.elems[currentKey].sizeElems) {
        int i;
        for (i = currentKey + 1; i <= col.capacity; ++i) {
            if (col.elems[i].key != -111111) {
                currentKey = i;
                currentValue = 0;
                break;
            }
        }
        if (i==col.capacity){
            currentKey=-1;
        }
    }
    else{
        currentValue+=1;
    }
}
//Best case Theta(1)
//Worst case Theta(capacity)
void MultiMapIterator::first() {
    if (col.sizeHash==0) {
        currentKey = -1;
        return;
    }
    for (int i = 0; i < col.capacity; ++i) {
        if (col.elems[i].key!=-111111) {
            currentKey = i;
            currentValue=0;
            break;
        }
    }
}
//Best case Theta(1)
//Worst case Theta(capacity)
