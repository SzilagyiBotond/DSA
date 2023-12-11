#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;
bool conditon(TElem e)
{
    if(e>0)
        return true;
    return false;
}
void testOption()
{
    Set s;
    assert(s.isEmpty() == true);
    assert(s.size() == 0);
    assert(s.add(5)==true);
    assert(s.add(1)==true);
    assert(s.add(10)==true);
    assert(s.add(7)==true);
    assert(s.add(-3)==true);
    s.filter(conditon);
    assert(s.size()==4);
    assert(s.search(-3)== false);
}



int main() {

	testAll();
	testAllExtended();
    testOption();
	cout << "That's all!" << endl;
	system("pause");

}



