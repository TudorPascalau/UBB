#pragma once

#include <string>
#include <iostream>
using std::string;
using std::cout;

class Carte
{
private:
	int id;
	string titlu;
	string autor;
	string gen;
	int an;

public:

	/*
	* Constructorul implicit pentru clasa Carte
	*/
	Carte() = default;
	
	/*
	* Constructor pentru clasa carte
	* @param id: id-ul cartii
	* @param titlu: titlul cartii
	* @param autor: autorul cartii
	* @param gen: genul cartii
	* @param an: anul aparitiei
	* pre: -
	* post: este creat un obiect de tip Carte
	*/
	Carte(int id, const string& titlu, const string& autor, const string& gen, int an) 
		:id{ id }, titlu{ titlu }, autor{ autor }, gen{ gen }, an{ an } {
	}

	/*
	* Getter pentru id-ul cartii
	* pre: -
	* post: cartea nu se modifica
	* @return: id-ul cartii
	*/
	int getId() const noexcept;

	/*
	* Getter pentru titlul cartii
	* pre: -
	* post: cartea nu se modifica
	* @return: titlul cartii
	*/
	const string& getTitlu() const noexcept;

	/*
	* Getter pentru autorul cartii
	* pre: -
	* post: cartea nu se modifica
	* @return: autorul cartii
	*/
	const string& getAutor() const noexcept;

	/*
	* Getter pentru genul cartii
	* pre: -
	* post: cartea nu se modifica
	* @return: genul cartii
	*/
	const string& getGen() const noexcept;

	/*
	* Getter pentru anul aparitei cartii
	* pre: -
	* post: cartea
	* @return: anul aparitiei cartii
	*/
	int getAn() const noexcept;

	/*
	* Setter pentru titlul cartii
	* @param newTitlu: titlul de modificat
	* pre: -
	* post: se modifica titlul lui c
	*/
	void setTitlu(const string& newTitlu) noexcept;

	/*
	* Setter pentru autorul cartii
	* @param newAutor: autorul de modificat
	* pre: -
	* post: se modifica autorul lui c
	*/
	void setAutor(const string& newAutor) noexcept;

	/*
	* Setter pentru genul cartii
	* @param newGen: genul de modificat
	* pre: -
	* post: se modifica genul lui c
	*/
	void setGen(const string& newGen) noexcept;

	/*
	* Setter pentru anul aparitiei cartii
	* @param newAn: anul de modificat
	* pre: -
	* post: se modifica anul aparitiei lui c
	*/
	void setAn(int newAn) noexcept;

	/*
	* Suprascriere operator ==
	* @param ot: obiect de tip carte pentru care comparam egalitate
	* pre: ot este de tip Carte
	* post: nu se modifica niciun obiect
	* @return: true, daca cele doua carti au campuri identice;
	*		   false, altfel
	*/
	bool operator==(const Carte& ot) const;


	/*
	* Copy constructor pentru clasa carte
	* @param ot: cealalta carte de copiat
	* pre: ot este de tip Carte
	* post: este creat un obiect de tip Carte
	*/
	Carte(const Carte& ot) : id{ ot.id }, titlu{ ot.titlu }, autor{ ot.autor }, gen{ ot.gen }, an{ ot.an } {
		cout << "Copy constructor apelat\n";
	}

	/*
	* Destructor pentru clasa Carte
	* pre: -
	* post: este distrus un obiect de tip Carte
	*/
	~Carte() = default;
};

