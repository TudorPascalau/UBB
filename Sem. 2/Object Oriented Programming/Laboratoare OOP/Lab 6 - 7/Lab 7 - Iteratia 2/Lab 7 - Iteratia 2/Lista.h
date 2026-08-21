#pragma once

template<typename T>
class IteratorLista;

template<typename T>
class Lista
{
private:
	T* elems;
	int lg;
	int capacity;

	/*
	* Verifica daca lista are capacitate suficienta pentru a adauga un element nou
	* pre: -
	* post: daca lista nu are capacitate suficienta, se dubleaza capacitatea
	*/
	void ensureCapacity() {
		if (lg < capacity) {
			return;
		}

		int newCapacity = capacity * 2;
		T* newElems = new T[newCapacity];

		for (int i = 0; i < lg; i++) {
			newElems[i] = elems[i];
		}

		delete[] elems;
		elems = newElems;
		capacity = newCapacity;
	}

public:

	friend class IteratorLista<T>;

	/*
	* Constructor implicit
	* pre: -
	* post: se creeaza o lista vida, cu capacitate initiala 1
	*/
	Lista() : elems{ new T[1] }, lg{ 0 }, capacity{ 1 } {
	}

	/*
	* Constructor de copiere
	* pre: ot este o lista valida
	* post: se creeaza o copie a listei ot
	*/
	Lista(const Lista& ot) : elems{ new T[ot.capacity] }, lg{ ot.lg }, capacity{ ot.capacity } {
		for (int i = 0; i < lg; i++) {
			elems[i] = ot.elems[i];
		}
	}

	/*
	* Operator de atribuire
	* pre: ot este o lista valida
	* post: lista curenta devine copie a listei ot
	*/
	Lista& operator=(const Lista& ot) {
		if (this == &ot) {
			return *this;
		}

		T* newElems = new T[ot.capacity];
		for (int i = 0; i < ot.lg; i++) {
			newElems[i] = ot.elems[i];
		}

		delete[] elems;
		elems = newElems;
		lg = ot.lg;
		capacity = ot.capacity;

		return *this;
	}

	/*
	* Destructor
	* pre: -
	* post: se elibereaza memoria alocata dinamic
	*/
	~Lista() {
		delete[] elems;
	}

	/*
	* Adauga un element la finalul listei
	* @param e: elementul de adaugat
	* pre: e este de tip T
	* post: elementul este adaugat la finalul listei
	*/
	void add(const T& e) {
		ensureCapacity();
		elems[lg] = e;
		lg++;
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
		for (int i = poz; i < lg - 1; i++) {
			elems[i] = elems[i + 1];
		}
		lg--;
	}

	/*
	* Returneaza numarul de elemente din lista
	* pre: -
	* post: lista nu se modifica
	* @return: numarul de elemente
	*/
	int size() const noexcept {
		return lg;
	}

	/*
	* Returneaza referinta la elementul de pe o pozitie
	* @param poz: pozitia cautata
	* pre: poz este valida
	* post: lista nu se modifica
	* @return: referinta la elementul de pe pozitie
	*/
	T& get(int poz) {
		return elems[poz];
	}

	/*
	* Returneaza referinta const la elementul de pe o pozitie
	* @param poz: pozitia cautata
	* pre: poz este valida
	* post: lista nu se modifica
	* @return: referinta const la elementul de pe pozitie
	*/
	const T& get(int poz) const {
		return elems[poz];
	}

	/*
	* Alias pentru compatibilitate cu codul existent
	*/
	T& getElem(int poz) {
		return get(poz);
	}

	/*
	* Alias pentru compatibilitate cu codul existent
	*/
	const T& getElem(int poz) const {
		return get(poz);
	}

	/*
	* Operator de egalitate
	* @param ot: lista cu care se compara
	* pre: ot este o lista valida
	* post: listele nu se modifica
	* @return: true daca listele sunt egale, false altfel
	*/
	bool operator==(const Lista& ot) const {
		if (lg != ot.lg) {
			return false;
		}

		for (int i = 0; i < lg; i++) {
			if (!(elems[i] == ot.elems[i])) {
				return false;
			}
		}
		return true;
	}

	/*
	* Returneaza un iterator pentru inceputul listei
	* pre: -
	* post: lista nu se modifica
	* @return: un iterator pentru inceputul listei
	*/
	IteratorLista<T> begin() const {
		return IteratorLista<T>(*this);
	}

	/*
	* Returneaza un iterator pentru sfarsitul listei
	* pre: -
	* post: lista nu se modifica
	* @return: un iterator pentru sfarsitul listei
	*/
	IteratorLista<T> end() const {
		return IteratorLista<T>(*this, lg);
	}
};

template<typename T>
class IteratorLista {
private:

	const Lista<T>& lista;
	int poz;

public:

	/*
	* Constructor
	* @param l: lista pe care se itereaza
	* pre: l este o lista valida
	* post: se creeaza un iterator pentru lista l, pozitia initiala este 0
	*/
	IteratorLista(const Lista<T>& l) noexcept : lista{ l }, poz{ 0 } {}

	/*
	* Constructor cu pozitie
	* @param l: lista pe care se itereaza, poz: pozitia initiala
	* pre: l este o lista valida, poz este o pozitie valida sau egala cu lungimea listei
	* post: se creeaza un iterator pentru lista l, pozitia initiala este poz
	*/
	IteratorLista(const Lista<T>& l, int poz) noexcept : lista{ l }, poz{ poz } {}

	/*
	* Verifica daca iteratorul este valid (nu a ajuns la finalul listei)
	* pre: -
	* post: lista nu se modifica
	* @return: true daca iteratorul este valid, false daca a ajuns la finalul listei
	*/
	bool valid() const noexcept {
		return poz < lista.lg;
	}

	/*
	* Returneaza referinta la elementul curent
	* pre: iteratorul este valid
	* post: lista nu se modifica
	* @return: referinta la elementul curent
	*/
	T& element() const noexcept {
		return lista.elems[poz];
	}

	/*
	* Inainteaza iteratorul la urmatorul element
	* pre: iteratorul este valid
	* post: iteratorul avanseaza la urmatorul element
	*/
	void next() noexcept {
		poz++;
	}

	/*
	* Supraincarca operatorul de dereferentiere pentru a returna elementul curent
	* pre: iteratorul este valid
	* post: lista nu se modifica
	* @return: referinta la elementul curent
	*/
	T& operator*() {
		return element();
	}

	/*
	* Supraincarca operatorul de incrementare prefixat pentru a avansa iteratorul
	* pre: iteratorul este valid
	* post: iteratorul avanseaza la urmatorul element
	* @return: referinta la iteratorul curent dupa avansare
	*/
	IteratorLista& operator++() {
		next();
		return *this;
	}

	/*
	* Supraincarca operatorul de egalitate pentru a compara doi iteratori
	* @param ot: iteratorul cu care se compara
	* pre: ot este un iterator valid, iteratorul este valid
	* post: lista nu se modifica
	* @return: true daca iteratorii sunt egali (pozitiile sunt egale), false altfel
	*/
	bool operator==(const IteratorLista& ot) const noexcept {
		return poz == ot.poz;
	}

	/*
	* Supraincarca operatorul de inegalitate pentru a compara doi iteratori
	* @param ot: iteratorul cu care se compara
	* pre: ot este un iterator valid, iteratorul este valid
	* post: lista nu se modifica
	* @return: true daca iteratorii sunt diferiti (pozitiile sunt diferite), false altfel
	*/
	bool operator!=(const IteratorLista& ot) const noexcept {
		return !(*this == ot);
	}
};