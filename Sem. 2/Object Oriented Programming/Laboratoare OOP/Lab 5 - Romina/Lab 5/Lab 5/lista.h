#ifndef LISTA_H_
#define LISTA_H_

typedef void* (*CopyFunction)(void* elem);
typedef void (*DestroyFunction)(void* elem);

typedef struct {
    void** elems;
    int size;
    int capacity;
    CopyFunction copyElem;
    DestroyFunction destroyElem;
} List;

/*
* Creeaza o lista dinamica vida.
* param copyElem: functia folosita pentru copierea unui element
* param destroyElem: functia folosita pentru distrugerea unui element
* preconditii: copyElem != NULL, destroyElem != NULL
* postconditii: se creeaza o lista vida, cu memorie alocata pentru elemente si cu functiile
*               de copiere si distrugere memorate in structura
* return: lista creata; daca alocarea esueaza, campul elems va fi NULL
*/
List createList(CopyFunction copyElem, DestroyFunction destroyElem);

/*
* Distruge lista si toate elementele continute in ea.
* param l: lista de distrus
* preconditii: -
* postconditii: toate elementele din lista sunt distruse folosind functia destroyElem,
*               memoria vectorului intern este eliberata, iar campurile listei sunt resetate;
*               daca l == NULL, functia nu produce niciun efect
*/
void destroyList(List* l);

/*
* Creeaza o copie profunda a unei liste.
* param l: lista care se copiaza
* preconditii: l.copyElem != NULL, l.destroyElem != NULL
* postconditii: se creeaza o noua lista independenta, continand copii ale tuturor elementelor
*               din lista sursa
* return: copia listei; daca alocarea/copierea esueaza, rezultatul poate avea elems == NULL
*         sau poate fi o lista vida, in functie de implementare
*/
List copyList(const List* l);

/*
* Adauga un element in lista.
* param l: lista in care se adauga
* param elem: elementul de adaugat
* preconditii: l != NULL, l->elems != NULL, elem != NULL
* postconditii: daca operatia reuseste, in lista se adauga o copie a elementului, iar dimensiunea
*               listei creste cu 1; daca operatia esueaza, lista ramane neschimbata
* return: 1 daca elementul a fost adaugat cu succes, 0 altfel
*/
int addElem(List* l, void* elem);

/*
* Returneaza elementul de pe o anumita pozitie.
* param l: lista din care se citeste
* param pos: pozitia elementului
* preconditii: l != NULL
* postconditii: daca pozitia este valida, se returneaza elementul de pe acea pozitie;
*               altfel se returneaza NULL
* return: pointer la elementul de pe pozitia ceruta, sau NULL daca pozitia este invalida
*/
void* getElem(const List* l, int pos);

/*
* Inlocuieste elementul de pe o anumita pozitie.
* param l: lista in care se face inlocuirea
* param pos: pozitia elementului de inlocuit
* param elem: noul element
* preconditii: l != NULL, l->elems != NULL, elem != NULL, 0 <= pos < l->size
* postconditii: daca operatia reuseste, vechiul element este distrus, pe pozitia pos este
*               memorata o copie a noului element, iar dimensiunea listei ramane neschimbata;
*               daca operatia esueaza, lista ramane neschimbata
* return: 1 daca inlocuirea s-a realizat cu succes, 0 altfel
*/
int setElem(List* l, int pos, void* elem);

/*
* Sterge elementul de pe o anumita pozitie.
* param l: lista din care se sterge
* param pos: pozitia elementului de sters
* preconditii: l != NULL, l->elems != NULL, 0 <= pos < l->size
* postconditii: daca pozitia este valida, elementul este distrus, elementele din dreapta sunt
*               mutate cu o pozitie la stanga, iar dimensiunea listei scade cu 1;
*               daca pozitia este invalida, lista ramane neschimbata
* return: 1 daca stergerea s-a realizat cu succes, 0 altfel
*/
int removeElem(List* l, int pos);

/*
* Returneaza numarul de elemente din lista.
* param l: lista pentru care se cere dimensiunea
* preconditii: -
* postconditii: se returneaza numarul de elemente din lista; daca l == NULL, se returneaza 0
* return: dimensiunea listei
*/
int sizeList(const List* l);

/*
* Functii folosite doar in teste pentru a forta esecul alocarii.
*/
void setForceListAllocFail(int value);
void setForceResizeAllocFail(int value);
void setForceCopyListFail(int value);
void setForceAddElemFail(int value);

#endif