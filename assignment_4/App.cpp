#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"
#include <cassert>
using namespace std;
void testNewFunction(){
    cout << "Testing new functionality"<<endl;
    MultiMap m;
//    m.add(-1,-1);
//    m.add(-2,-2);
    m.add(1, 100);
    m.add(2, 200);
    m.add(3, 300);
    m.add(1, 500);
    m.add(2, 600);
    m.add(4, 800);

    assert(m.size() == 6);
    assert(m.getKeyRange()==3);
    m.remove(4,800);
    assert(m.getKeyRange()==2);
    m.remove(1,100);
    m.remove(2,200);
    m.remove(3,300);
    m.remove(1,500);
    m.remove(2,600);
    assert(m.size()==0);
    assert(m.getKeyRange()==-1);
}

int main() {


	testAll();
	testAllExtended();
    testNewFunction();
	cout << "End" << endl;
	system("pause");

}
