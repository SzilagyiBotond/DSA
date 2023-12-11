#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
    this->current= this->list.head;
}
//Theta(1)
void ListIterator::first(){
	current=list.head;
}
//Theta(1)
void ListIterator::next(){
    if (current==-1)throw exception();
    current=list.next[current];
}
//THeta(1)
bool ListIterator::valid() const{
	return current!=-1;
}
//Theta(1)
TComp ListIterator::getCurrent() const{
    if (current==-1)throw exception();
	return list.elems[current];
}
//Theta(1)

