#include <iostream>
#include <chrono>
#include <string>
#include <math.h>
#include "needleman_wunsch.h"

int main() {
    needleman_wunsch dp;
    char str_a[] = "GATTACA";
    char str_b[] = "GCATGCG";
    dp.run(sequence(str_a), sequence(str_b));
    dp.print_score_matrix();
    dp.print_solutions();

    return 0;
}
