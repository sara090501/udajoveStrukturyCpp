#include "utils.h"

sequence::sequence(const char *start, size_t length) :
        start_(start),
        length_(start == nullptr ? 0 : utils::min(length, std::strlen(start))){
}

sequence::sequence(const char *start) :
        start_(start),
        length_(start == nullptr ? 0 : std::strlen(start)) {
}

const char* sequence::get_start() {
    return this->start_;
}

char sequence::at(size_t index) {
    return *(this->start_ + index);
}

size_t sequence::get_length() {
    return this->length_;
}
