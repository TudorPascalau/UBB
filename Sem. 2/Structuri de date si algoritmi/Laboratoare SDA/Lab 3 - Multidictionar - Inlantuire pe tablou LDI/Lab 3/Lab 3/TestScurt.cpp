#include "TestScurt.h"
#include "MD.h"
#include "IteratorMD.h"
#include <assert.h>
#include <vector>
#include<iostream>

void testAll() {
	MD m;
	m.adauga(1, 100);
	m.adauga(2, 200);
	m.adauga(3, 300);
	m.adauga(1, 500);
	m.adauga(2, 600);
	m.adauga(4, 800);

	assert(m.dim() == 6);

	assert(m.sterge(5, 600) == false);
	assert(m.sterge(1, 500) == true);

	assert(m.dim() == 5);

    vector<TValoare> v;
	v=m.cauta(6);
	assert(v.size()==0);

	v=m.cauta(1);
	assert(v.size()==1);

	assert(m.vid() == false);

	IteratorMD im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
		im.element();
		im.urmator();
	}
	assert(im.valid() == false);
	im.prim();
	assert(im.valid() == true);

	MD m2;
	m2.adauga(1, 100);
	m2.adauga(2, 200);
	m2.adauga(3, 300);
	m2.adauga(1, 500);
	m2.adauga(2, 600);
	m2.adauga(4, 800);
	vector<TValoare> rez = m2.stergeValoriPentruCheie(1);
	assert(rez.size() == 2);
	assert(rez[0] == 100);
	assert(rez[1] == 500);
	rez = m2.cauta(1);
	assert(rez.size() == 0);
	rez = m2.cauta(2);
	assert(rez.size() == 2);

}
