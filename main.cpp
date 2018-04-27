#include <iostream>
#include <cassert>
#include <cstring>
#include "Hash.h"

size_t clean();

void hash(char *, int (*f)(char *), size_t size);

char *OpenFile(char *buffer);

void add_elem(char *buffer, Head *hash_arr, int hash_num);

int hash_w0(char *);

int hash_lenw(char *);

int hash_h1(char *);

int hash_sumw(char *word);

int main() {
    size_t size = clean();
    char *buffer = nullptr;
    buffer = OpenFile(buffer);

    hash(buffer, hash_sumw, size);
    return 0;

}

//ready function

void hash(char *buffer, int(*func)(char *), size_t size) {
    int prev = 0;
    char *next = buffer;
    int hash_sum = 0;
    auto *hash_array = (Head *) calloc(256, sizeof(Head));

    for (int i = 0; i < size; i++) {
        if (buffer[i] == ' ') {
            buffer[i] = '\0';
            next = buffer + prev;
            hash_sum = func(next);
            add_elem(next, hash_array, hash_sum);
            prev = i + 1;
        }
    }


    for (int i = 0; i < 256; i++) {
        std::cout << hash_array[i].amount << " : " << i << std::endl;
    }


}

void add_elem(char *buffer, Head *hash_arr, int hash_num) {

    hash_arr[hash_num].amount++;

    if (hash_arr[hash_num].new_el == nullptr) {
        hash_arr[hash_num].new_el = new Elem(buffer, nullptr);
    } else {
        Elem *new_elem = hash_arr[hash_num].new_el;
        while (new_elem->next_elem != nullptr) {
            new_elem = new_elem->next_elem;
        }
        new_elem->next_elem = new Elem(buffer, nullptr);
    }
}

int hash_w0(char *word) {
    return word[0] - 'a';
}

int hash_lenw(char *word) {
    return (unsigned) strlen(word);
}

int hash_h1(char */*word*/) {
    return 1;
}

int hash_sumw(char *word) {
    int sum = 0;
    int i = 0;
    while (word[i] != '\0') {
        sum += word[i++];
    }
    return sum % 256;
}

size_t clean() {
    FILE *f = fopen("R_J.txt", "r");
    FILE *newF = fopen("new_RJ.txt", "w+");
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    auto *buffer = (char *) calloc(sizeof(char), size);
    fread(buffer, size, 1, f);
    for (int i = 0; i < size; i++) {
        if (isupper(buffer[i])) {
            buffer[i] += 'a' - 'A';
        };
    }
    for (int i = 0; i < size; i++) {
        if (ispunct(buffer[i])) {
            buffer[i] = ' ';
        };
    }
    bool cheker = 0;
    for (int i = 0; i < size; i++) {
        switch (buffer[i]) {
            case (' '): {
                if (!isalpha(buffer[i + 1]))
                    continue;
                if (!cheker)
                    fprintf(newF, "%c", buffer[i]);

                continue;
            }
            case ('\n'): {
                if (!cheker) {
                    buffer[i] = ' ';
                    fprintf(newF, "%c", buffer[i]);
                }
                cheker = true;
                continue;
            }
            case ('\t'): {
                if (!cheker) {
                    buffer[i] = ' ';
                    fprintf(newF, "%c", buffer[i]);
                }
                cheker = true;
                continue;
            }
            case ('\r'): {
                if (!cheker) {
                    buffer[i] = ' ';
                    fprintf(newF, "%c", buffer[i]);
                }
                cheker = true;
                continue;
            }
            case (','): {
                i++;
                cheker = false;
                continue;
            }
            default:
                cheker = false;
                fprintf(newF, "%c", buffer[i]);
        }
    }
    return size;
}

char *OpenFile(char *buffer) {
    FILE *f = fopen("new_RJ.txt", "r");
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = (char *) calloc(sizeof(char), size);
    fread(buffer, size, 1, f);
    return buffer;
}