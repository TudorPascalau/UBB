#pragma once

#include <iostream>
using std::cout;

#include "TestAll.h"


void TestAll::test_all() const {
	test_all_domain();
	cout << "test_all_domain() a rulat cu succes!\n";

	test_all_validator();
	cout << "test_all_validator() a rulat cu succes!\n";

	test_all_list();
	cout << "test_all_list() a rulat cu succes!\n";
	
	test_all_repo();
	cout << "test_all_repo() a rulat cu succes!\n";

	test_all_service();
	cout << "test_all_service() a rulat cu succes!\n";
}