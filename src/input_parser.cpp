#include <algorithm>

#include "./input_parser.hpp"

input_parser::input_parser(int &argc, char const **argv) {
    for (int i=1; i < argc; ++i)
        this->tokens.push_back(std::string(argv[i]));
}

const std::string& input_parser::get_cmd_option(const std::string &option) const {
    std::vector<std::string>::const_iterator itr = std::find(this->tokens.begin(), this->tokens.end(), option);

    if (itr != this->tokens.end() && ++itr != this->tokens.end()){
        return *itr;
    }

    static const std::string empty_string("");
    return empty_string;
}

bool input_parser::cmd_option_exists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}