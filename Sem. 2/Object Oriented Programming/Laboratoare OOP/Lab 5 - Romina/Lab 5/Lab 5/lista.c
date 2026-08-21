#include "lista.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 2

static int forceListAllocFail = 0;
static int forceResizeAllocFail = 0;
static int forceAddElemFail = 0;
static int forceCopyListFail = 0;

void setForceCopyListFail(int value) {
    forceCopyListFail = value;
}

void setForceAddElemFail(int value) {
    forceAddElemFail = value;
}

void setForceListAllocFail(int value) {
    forceListAllocFail = value;
}

void setForceResizeAllocFail(int value) {
    forceResizeAllocFail = value;
}

static int resizeList(List* l) {
    if (forceResizeAllocFail) {
        return 0;
    }

    int newCapacity = l->capacity * 2;
    void** newElems = (void**)malloc(sizeof(void*) * newCapacity);
    if (newElems == NULL) {
        return 0;
    }

    for (int i = 0; i < l->size; i++) {
        newElems[i] = l->elems[i];
    }

    free(l->elems);
    l->elems = newElems;
    l->capacity = newCapacity;
    return 1;
}

List createList(CopyFunction copyElem, DestroyFunction destroyElem) {

    List l;
    l.size = 0;
    l.capacity = 0;
    l.copyElem = copyElem;
    l.destroyElem = destroyElem;
    l.elems = NULL;

    if (forceListAllocFail) {
        return l;
    }

    l.capacity = INITIAL_CAPACITY;
    l.elems = (void**)malloc(sizeof(void*) * l.capacity);

    //if (l.elems == NULL) {
    //    l.capacity = 0;
    //}

    return l;
}

void destroyList(List* l) {
    //if (l == NULL || l->elems == NULL) {
    //    return;
    //}

    for (int i = 0; i < l->size; i++) {
        if (l->elems[i] != NULL) {
            l->destroyElem(l->elems[i]);
        }
    }

    free(l->elems);
    l->elems = NULL;
    l->size = 0;
    l->capacity = 0;
    l->copyElem = NULL;
    l->destroyElem = NULL;
}

List copyList(const List* l) {

    List copy;

    if (l == NULL) {
        copy.elems = NULL;
        copy.size = 0;
        copy.capacity = 0;
        copy.copyElem = NULL;
        copy.destroyElem = NULL;
        return copy;
    }

    if (l != NULL && forceCopyListFail) {
        copy.elems = NULL;
        copy.size = 0;
        copy.capacity = 0;
        copy.copyElem = l->copyElem;
        copy.destroyElem = l->destroyElem;
        return copy;
    }

    copy = createList(l->copyElem, l->destroyElem);
    if (copy.elems == NULL) {
        return copy;
    }

    for (int i = 0; i < l->size; i++) {
        if (!addElem(&copy, l->elems[i])) {
            destroyList(&copy);
            copy.elems = NULL;
            copy.size = 0;
            copy.capacity = 0;
            copy.copyElem = l->copyElem;
            copy.destroyElem = l->destroyElem;
            return copy;
        }
    }

    return copy;
}

int addElem(List* l, void* elem) {
    if (l == NULL || l->elems == NULL || elem == NULL) {
        return 0;
    }

    if (forceAddElemFail) {
        return 0;
    }

    if (l->size == l->capacity) {
        if (!resizeList(l)) {
            return 0;
        }
    }

    void* copy = l->copyElem(elem);
    if (copy == NULL) {
        return 0;
    }

    l->elems[l->size] = copy;
    l->size++;
    return 1;
}

void* getElem(const List* l, int pos) {
    if (l == NULL || pos < 0 || pos >= l->size) {
        return NULL;
    }
    return l->elems[pos];
}

int setElem(List* l, int pos, void* elem) {
    if (l == NULL || l->elems == NULL || elem == NULL) {
        return 0;
    }
    //if (pos < 0 || pos >= l->size) {
    //    return 0;
    //}

    void* copy = l->copyElem(elem);
    if (copy == NULL) {
        return 0;
    }

    l->destroyElem(l->elems[pos]);
    l->elems[pos] = copy;
    return 1;
}

int removeElem(List* l, int pos) {
    //if (l == NULL || l->elems == NULL) {
    //    return 0;
    //}

    if (pos < 0 || pos >= l->size) {
        return 0;
    }

    l->destroyElem(l->elems[pos]);

    for (int i = pos; i < l->size - 1; i++) {
        l->elems[i] = l->elems[i + 1];
    }

    l->size--;
    return 1;
}

int sizeList(const List* l) {
    if (l == NULL) {
        return 0;
    }
    return l->size;
}