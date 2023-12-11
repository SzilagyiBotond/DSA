#include "SetIterator.h"
#include "Set.h"
#include <exception>
SetIterator::SetIterator(const Set& m) : set(m)
{
    currentElement=set.head;

}
//Theta(1)

void SetIterator::first() {
	currentElement=set.head;
}
//Theta(1)


void SetIterator::next() {
//    if (currentElement== set.tail)
//        throw std::exception();
    if (currentElement!= nullptr)
        currentElement=currentElement->next;
    else
        throw std::exception();
}
//Theta(1)

TElem SetIterator::getCurrent()
{
    if (currentElement== nullptr)
        throw std::exception();
	return currentElement->info;
}
//Theta(1)
bool SetIterator::valid() const {
	return currentElement!= nullptr;
}
//Theta(1)
void SetIterator::last() {
    currentElement=set.tail;
}
//Theta(1)


