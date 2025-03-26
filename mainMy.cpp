//
// Created by sgeratova on 5. 3. 2025.
//
#include "trie.h"

int char_to_ord(char c) {
    switch (c) {
        case 'A': return 0;
        case 'T': return 1;
        case 'C': return 2;
        case 'G': return 3;
    }
    return -1;
}

int ord_to_char(int ord) {
    static char alphabet[] = {'A', 'T', 'G', 'C'};
    return alphabet[ord];
}

int main() {
    trie<4>  dict(char_to_ord, ord_to_char);
    dict.insert("ATTTAAAC", 100);
    dict.insert("ATAAAAC", 100);
    dict.insert("ACT", 100);
    dict.insert("CAGTTT", 100);
    dict.insert("ACT", 100);
    dict.insert("CAG", 100);

    dict.print();

    std::cout << dict.contains("ATAAAAC", 100) << std::endl;
    std::cout << dict.contains("CAG", 100) << std::endl;
    std::cout << dict.contains("CAGC", 100) << std::endl;
    std::cout << dict.contains("", 100) << std::endl;
}
