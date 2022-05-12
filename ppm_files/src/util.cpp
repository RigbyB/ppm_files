#include "util.h"
#include <sstream>

std::vector<std::string> util::splitString(std::string input) {
    std::stringstream stream(input);
    std::string word;
    std::vector<std::string> output;

    while (std::getline(stream, word, ' '))
        output.push_back(word);

    return output;
}
