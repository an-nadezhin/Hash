//
// Created by andrew on 16.04.18.
//

#ifndef HASH_HASH_H
#define HASH_HASH_H

class Elem {
public:
    char *word;
    Elem *next_elem;
    int amount;

    Elem(char *, Elem *);
};

Elem::Elem(char *new_el, Elem *prev_elem) {
    word = new_el;
    amount = 0;
    if (prev_elem) {
        prev_elem->next_elem = this;
    } else {
        next_elem = nullptr;
    }
}

class Head {
public:
    int amount;
    Elem * new_el;
    Head (Elem*);
};

Head::Head(Elem * elem) : amount(0), new_el(elem) {}

#endif //HASH_HASH_H
