#ifndef BIOINFORMATICS_NEEDLEMAN_WUNSCH_H
#define BIOINFORMATICS_NEEDLEMAN_WUNSCH_H

#include "utils.h"

class nucleotides :
    public alphabet {
public:
    int to_ordinal_value(char c) const override;
    char to_char(int ordinal_value) const override;
    int size() const override;
    static nucleotides* get_instance();
private:
    nucleotides();
};

class needleman_wunsch {
public:
    needleman_wunsch(const alphabet_matrix<int>& similarity_matrix, const int& gap_penalty);
    needleman_wunsch();
    ~needleman_wunsch();
    void run(const sequence& seq_a, const sequence& seq_b);
    void print_score_matrix();
    void print_solutions();

private:
    void print_solution_backtracking(char* aligned_a, char* aligned_b, ssize_t row, ssize_t column);

private:
    alphabet_matrix<int> similarity_matrix_;
    int gap_penalty_;
    matrix<int>* score_matrix_;
    sequence seq_a_;
    sequence seq_b_;
};


#endif //BIOINFORMATICS_NEEDLEMAN_WUNSCH_H
