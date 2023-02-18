#include <string>
#include "compare_int_string.h"

// helper function to compare list of int strings
bool compare_int_string(const std::string& str1, const std::string& str2) {
    return std::stoi(str1) < std::stoi(str2);
}
