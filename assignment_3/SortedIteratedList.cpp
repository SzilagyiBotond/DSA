#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->r=r;
    capacity=CAP;
    sizeOf=0;
    elems= new TComp [capacity];
    next=new int[capacity];
    prev=new int[capacity];
    head=-1;
    tail=-1;
    firstFree=0;
}

//Theta(1)
int SortedIteratedList::size() const {
	return sizeOf;
}
//Theta(1)
bool SortedIteratedList::isEmpty() const {
    if (sizeOf==0)
        return true;
	return false;
}
//Theta(1)
ListIterator SortedIteratedList::first() const {
	return ListIterator(*this);
}
//Theta(1)
TComp SortedIteratedList::getElement(ListIterator poz) const {
    if (poz.current==-1)throw exception();
    return elems[poz.current];
}
//Theta(1)
void SortedIteratedList::freePos(int poz){
    elems[poz]=NULL_TCOMP;
    next[poz]=firstFree;
}
//Theta(1)
TComp SortedIteratedList::remove(ListIterator& poz) {
    if (poz.current==-1)throw exception();
//    if (elems[poz.current]==NULL_TCOMP)throw exception();
    TComp removedElement=elems[poz.current];

    if (poz.current==head) // if the head is to be deleted
    {
        if (next[head]==-1) // if the head is the only element
        {
            head=-1;
            tail=-1;
            sizeOf--;
            poz.next();
//            freePos(poz.current);
            return removedElement;
        } // if the head is not the only element
        prev[head]=-1;
        int i=next[head];
        head=i;
        sizeOf--;
        poz.next();
//        freePos(poz.current);

        return removedElement;

    }
    if (next[poz.current]!=-1) // if not the head is deleted
    {
        prev[next[poz.current]]=prev[poz.current];
        next[prev[poz.current]]=next[poz.current];
    }
    else
    {
        if (next[head]==-1)
        {
            head=-1;
            tail=-1;
        }
        else
        {
            next[prev[tail]]=-1;
            int i=tail;
            tail=prev[i];
        }
    }
    sizeOf--;
    poz.next();
//    freePos(poz.current);

    return removedElement;
}
//Theta(1+next)
ListIterator SortedIteratedList::search(TComp e) const{
	ListIterator it=ListIterator(*this);
    while (it.current!=-1 && elems[it.current]!=e)
    {
        it.current=next[it.current];
    }
	return it;
}

//Worst case(sizeof)
//Best case(1)
void SortedIteratedList::add(TComp e) {
    if (head==-1 && tail==-1)
    {
        head=0;
        tail=0;
        elems[firstFree]=e;
        next[firstFree]=-1;
        prev[firstFree]=-1;
        sizeOf++;
        firstFree++;
        return;
    }
    if (firstFree==capacity)
        resize();
    int index=head;
    while (index!=-1 && r(elems[index],e))
    {
        index=next[index];
    }
    if (index==head) {
        prev[head]=firstFree;
        prev[firstFree]=-1;
        next[firstFree]=head;
        head=firstFree;
        elems[firstFree]=e;
        firstFree++;
        sizeOf++;
        return;
    }
    if (index==-1)
    {
        elems[firstFree]=e;
        next[tail]=firstFree;
        next[firstFree]=-1;
        prev[firstFree]=tail;
        tail=firstFree;
        firstFree++;
        sizeOf++;
        return;
    }
    elems[firstFree]=e;
    next[firstFree]=index;
    prev[firstFree]=prev[index];
    next[prev[index]]=firstFree;
    prev[index]=firstFree;
    sizeOf++;
    firstFree++;
}
//Worst case(sizeof)
//Best case(1)
SortedIteratedList::~SortedIteratedList() {
    delete[] this->elems;
    delete[] this->prev;
    delete[] this->next;
}
//Theta(1)

void SortedIteratedList::resize() {
    TComp *newElems=new TComp [capacity*2];
    int *newNext=new int[capacity*2];
    int *newPrev=new int[capacity*2];
    for (int i = 0; i < this->sizeOf; i++) {
        newElems[i]=elems[i];
        newNext[i]=next[i];
        newPrev[i]=prev[i];
    }
    capacity=capacity*2;
    delete[] elems;
    delete[] next;
    delete[] prev;
    elems=newElems;
    prev=newPrev;
    next=newNext;
}
//Theta(sizeof)
ListIterator SortedIteratedList::lastIndexOf(TComp e) const {
    ListIterator it= search(e);
    while(elems[it.current]==e)
    {
        if(elems[next[it.current]]==e)
            it.next();
        else
            break;
    }
    return it;
}
//Worst case Theta(sizeof+search)
