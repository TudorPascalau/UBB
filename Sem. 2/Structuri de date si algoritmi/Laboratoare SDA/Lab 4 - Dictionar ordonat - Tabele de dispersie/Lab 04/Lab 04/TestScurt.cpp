#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
    dictOrd.adauga(1,2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1)!=NULL_TVALOARE);
    TValoare v =dictOrd.adauga(1,3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()){
    	TElem e = it.element();
    	assert(e.second != NULL_TVALOARE);
    	it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());

    DO dict = DO(relatie1);
    TValoare valFrecMax = dict.ceaMaiFrecventaValoare();
    assert(valFrecMax == NULL_TVALOARE);
	dict.adauga(1, 2);
	dict.adauga(2, 3);
	dict.adauga(3, 2);
	valFrecMax = dict.ceaMaiFrecventaValoare();
    assert(valFrecMax == 2);
	dict.adauga(4, 3);
    valFrecMax = dict.ceaMaiFrecventaValoare();
	assert(valFrecMax == 2 || valFrecMax == 3);
}


