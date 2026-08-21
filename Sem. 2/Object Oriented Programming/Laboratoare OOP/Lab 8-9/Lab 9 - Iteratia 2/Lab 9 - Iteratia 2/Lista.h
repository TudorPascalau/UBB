#pragma once

#include <vector>

template<typename T>
class Lista {
private:
	std::vector<T> elems;

public:
	using iterator = typename std::vector<T>::iterator;
	using const_iterator = typename std::vector<T>::const_iterator;

	/*
	* Constructor implicit
	* pre: -
	* post: se creeaza o lista vida
	*/
	Lista() = default;


	/*
	* Constructor de copiere
	* pre: ot este o lista valida
	* post: se creeaza o copie a listei ot
	*/
	Lista(const Lista& ot) = default;

	/*
	* Operator de atribuire
	* pre: ot este o lista valida
	* post: lista curenta devine copie a listei ot
	*/
	Lista& operator=(const Lista& ot) = default;

	/*
	* Destructor
	*/
	~Lista() = default;

	/*
	* Adauga un element la finalul listei
	* @param e: elementul de adaugat
	* pre: e este de tip T
	* post: elementul este adaugat la finalul listei
	*/
	void add(const T& e) {
		elems.push_back(e);
	}

	/*
	* Modifica elementul de pe o pozitie data
	* @param poz: pozitia elementului
	* @param e: noua valoare
	* pre: poz este valida
	* post: elementul de pe pozitie devine e
	*/
	void set(int poz, const T& e) {
		elems[poz] = e;
	}

	/*
	* Sterge elementul de pe o pozitie data
	* @param poz: pozitia elementului de sters
	* pre: poz este valida
	* post: elementul este eliminat din lista
	*/
	void remove(int poz) {
		elems.erase(elems.begin() + poz);
	}

	/*
	* Returneaza numarul de elemente din lista
	* pre: -
	* post: lista nu se modifica
	* @return: numarul de elemente
	*/
	int size() const noexcept {
		return static_cast<int>(elems.size());
	}

	/*
	* Returneaza referinta la elementul de pe o pozitie
	* @param poz: pozitia cautata
	* pre: poz este valida
	* post: lista nu se modifica
	* @return: referinta la elementul de pe pozitie
	*/
	T& get(int poz) noexcept{
		return elems[poz];
	}

	/*
	* Returneaza referinta const la elementul de pe o pozitie
	* @param poz: pozitia cautata
	* pre: poz este valida
	* post: lista nu se modifica
	* @return: referinta const la elementul de pe pozitie
	*/
	const T& get(int poz) const noexcept{
		return elems[poz];
	}


	/*
	* Goleste lista
	* pre: -
	* post: lista devine vida
	*/
	void clear() noexcept {
		elems.clear();
	}

	/*
	* Elimina elementele din intervalul [first, last)
	* @param first: iterator la primul element de sters
	* @param last: iterator la elementul dupa ultimul de sters
	* pre: first si last sunt iteratori validi
	* post: elementele din interval sunt eliminate
	*/
	void erase(iterator first, iterator last) {
		elems.erase(first, last);
	}

	/*
	* Operator de egalitate
	* @param ot: lista cu care se compara
	* pre: ot este o lista valida
	* post: listele nu se modifica
	* @return: true daca listele sunt egale, false altfel
	*/
	bool operator==(const Lista& ot) const {
		return elems == ot.elems;
	}

	/*
	* Iterator pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator la inceputul listei
	*/
	iterator begin() noexcept {
		return elems.begin();
	}

	/*
	* Iterator pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator la sfarsitul listei
	*/
	iterator end() noexcept {
		return elems.end();
	}

	/*
	* Iterator const pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator const la inceputul listei
	*/
	const_iterator begin() const noexcept {
		return elems.begin();
	}

	/*
	* Iterator const pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator const la sfarsitul listei
	*/
	const_iterator end() const noexcept {
		return elems.end();
	}

	/*
	* Iterator const pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator const la inceputul listei
	*/
	const_iterator cbegin() const noexcept {
		return elems.cbegin();
	}

	/*
	* Iterator const pentru parcurgerea listei
	* pre: -
	* post: lista nu se modifica
	* @return: iterator const la sfarsitul listei
	*/
	const_iterator cend() const noexcept {
		return elems.cend();
	}
};