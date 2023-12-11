#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedIteratedList.h"
#include "ListIterator.h"
#include <cassert>
bool relation3(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}
void testNew()
{
    SortedIteratedList list = SortedIteratedList(relation3);
    list.add(1);
    list.add(2);
    list.add(2);
    list.add(2);
    list.add(3);
    ListIterator it=list.lastIndexOf(2);
    assert(list.getElement(it)==2);
    it.next();
    assert(list.getElement(it)==3);
    it.next();
    assert(!it.valid());
    ListIterator its=list.lastIndexOf(3);
    assert(list.remove(its)==3);
    assert(list.size()==4);
    ListIterator nogood=list.lastIndexOf(4);
    assert(!nogood.valid());
}
int main(){
    testAll();
    testAllExtended();
    testNew();
    std::cout<<"Finished IL Tests!"<<std::endl;
	system("pause");
}