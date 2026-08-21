#pragma once

#include "Task.h"
#include "Repo.h"
#include "Service.h"

class Tester
{
public:
	/*
	* Metoda ce testeaza partea de Domain
	*/
	void testTask();

	/*
	* Metoda ce testeaza partea de Repo
	*/
	void testRepo();

	/*
	* Metoda ce testeaza partea de Validator
	*/
	void testValidator();

	/*
	* Metoda ce testeaza partea de Service
	*/
	void testService();
};

