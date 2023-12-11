
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <cassert>
using namespace std;
void testNewFunction(){
    cout << "Test extra functionality"<<endl;
    Matrix m(3,3);
    m.modify(1,0,5);
    m.modify(2,0,5);
    assert(m.numberOfNonZeroElems(0)==2);
    try {
        m.numberOfNonZeroElems(4);
    }
    catch (...) {

    }
    
}

int main() {

//
	testAll();
	testAllExtended();
    testNewFunction();
	cout << "Test End" << endl;
	system("pause");
}