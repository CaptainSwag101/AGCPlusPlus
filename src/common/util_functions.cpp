#include "util_functions.hpp"

word get_sign_bits(const word input) {
    return input >> 14;
}