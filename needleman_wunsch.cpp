#include "needleman_wunsch.h"
#include <iostream>
#include <iomanip>

int nucleotides::to_ordinal_value(char c) const {
    switch (c) {
        case 'A':
            return 0;
        case 'T':
            return 1;
        case 'G':
            return 2;
        case 'C':
            return 3;
    }
    return -1;
}

char nucleotides::to_char(int ordinal_value) const {
    static char chars[] = {'A', 'T', 'G', 'C'};
    return chars[ordinal_value];
}

int nucleotides::size() const {
    return 4;
}

nucleotides *nucleotides::get_instance() {
    static nucleotides alpha;
    return &alpha;
}

nucleotides::nucleotides() {
}

needleman_wunsch::needleman_wunsch(const alphabet_matrix<int>& similarity_matrix, const int& gap_penalty) :
        similarity_matrix_(similarity_matrix),
        gap_penalty_(gap_penalty),
        score_matrix_(nullptr),
        seq_a_(std::move(sequence(nullptr))),
        seq_b_(std::move(sequence(nullptr))) {

}

needleman_wunsch::needleman_wunsch() :
        needleman_wunsch(alphabet_matrix<int>(nucleotides::get_instance()), -1)
{
    const alphabet* alpha = similarity_matrix_.get_alphabet();
    for (int i = 0; i < alpha->size(); ++i) {
        for (int j = 0; j < alpha->size(); ++j) {
            if (i == j) {
                similarity_matrix_.access(alpha->to_char(i), alpha->to_char(j)) = 1;
            }
            else {
                similarity_matrix_.access(alpha->to_char(i), alpha->to_char(j)) = -1;
            }
        }
    }
}

needleman_wunsch::~needleman_wunsch() {
    if (this->score_matrix_ != nullptr) {
        delete this->score_matrix_;
        this->score_matrix_ = nullptr;
    }
}

void needleman_wunsch::run(const sequence& seq_a, const sequence& seq_b) {
	//TODO needleman_wunsch::run
}

void needleman_wunsch::print_score_matrix() {
    if (this->score_matrix_ == nullptr) {
        std::cerr << "needleman_wunsch::print_score_matrix: No score matrix has been computed. Run method needleman_wunsch::run first." << std::endl;
        return;
    }

    const int space_count = 4;
    std::cout << std::setw(space_count - 1) << ' ' << '|';
    std::cout << std::setw(space_count) << ' ';
    const char* letter_j = this->seq_b_.get_start();
    for (ssize_t j = 0; j < this->score_matrix_->column_limit(); ++j) {
        std::cout << std::setw(space_count) << *letter_j;
        ++letter_j;
    }
    std::cout << std::endl;
    for (ssize_t j = -1; j < this->score_matrix_->column_limit() + 1; ++j) {
        for (int s = 0; s < space_count; ++s) {
            std::cout << "–";
        }
    }
    std::cout << std::endl;

    std::cout << std::setw(space_count) << " |";
    for (ssize_t j = -1; j < this->score_matrix_->column_limit(); ++j) {
        std::cout << std::setw(space_count) << this->score_matrix_->access(-1, j);
    }
    std::cout << std::endl;

    const char* letter_i = this->seq_a_.get_start();
    for (ssize_t i = 0; i < this->score_matrix_->row_limit(); ++i) {
        std::cout << std::setw(space_count - 1) << *letter_i << '|';
        for (ssize_t j = -1; j < this->score_matrix_->column_limit(); ++j) {
            std::cout << std::setw(space_count) << this->score_matrix_->access(i, j);
        }
        std::cout << std::endl;
        ++letter_i;
    }
}

void needleman_wunsch::print_solutions() {
    if (this->score_matrix_ == nullptr) {
        std::cerr << "needleman_wunsch::print_solutions: No score matrix has been computed. Run method needleman_wunsch::run first." << std::endl;
        return;
    }

    size_t aligned_length = this->seq_a_.get_length() + this->seq_b_.get_length();
    ssize_t last_row = this->score_matrix_->row_limit() - 1;
    ssize_t last_column = this->score_matrix_->column_limit() - 1;
    char* aligned_a = (char*)std::calloc(aligned_length + 1, sizeof(char));
    char* aligned_b = (char*)std::calloc(aligned_length + 1, sizeof(char));

    this->print_solution_backtracking(aligned_a + aligned_length, aligned_b + aligned_length,last_row, last_column);

    std::free(aligned_a);
    std::free(aligned_b);
}

void needleman_wunsch::print_solution_backtracking(char *aligned_a, char *aligned_b, ssize_t row, ssize_t column) {
	//TODO needleman_wunsch::print_solution_backtracking
}
