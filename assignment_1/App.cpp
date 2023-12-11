#include "ExtendedTest.h"
#include "ShortTest.h"
#include <assert.h>
#include "SortedMap.h"


#include <iostream>
using namespace std;
bool relatie2(TKey cheie1, TKey cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}
void test()
{
    SortedMap sortedMap(relatie2);
    sortedMap.add(1,2);
    sortedMap.add(1,3);
    sortedMap.add(3,4);
//    assert(sortedMap.search(1)!=0);
    std::vector<TKey> vec=sortedMap.keySet();
    assert(vec[0]==1);
    assert(vec[1]==3);
    assert(vec.size()==2);
    SortedMap srtm(relatie2);
    std::vector<TKey> v=srtm.keySet();
    assert(v.empty()== true);
    srtm.add(3,4);
    v=srtm.keySet();
    assert(v.empty()!= true);
    assert(v[0]==3);
}
int main() {
	testAll();
	testAllExtended();
	cout << "That's all!" << endl;
    test();
    system("pause");
	return 0;
}


