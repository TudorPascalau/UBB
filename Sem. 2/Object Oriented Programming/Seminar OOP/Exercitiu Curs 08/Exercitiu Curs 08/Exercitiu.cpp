#include "Clase.h"

#include <iostream>
using std::cout;

#include <vector>
using std::vector;

vector<ClassB*> buildList() {
	vector<ClassB*> list;
	list.push_back(new ClassB{ 8 });
	list.push_back(new ClassD{ 5, "d5"});
	list.push_back(new ClassB{ -3 });
	list.push_back(new ClassD{ 9, "d9" });

	return list;
}

void printList(vector<ClassB*>& list) {
	for (auto& elem : list) {
		elem->Afisare();
	}
}

int main() {

	vector<ClassB*> list = buildList();
	printList(list);
	
	return 0;
}