#include <vector>
#include <string>

/**
 * This class is an adaptation of iain's answer at
 * https://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
 *
 *
 * @author iain
 * @date_copied 07/15/2017
 */
class input_parser {
private:
    std::vector <std::string> tokens;

public:
    input_parser(int &argc, char const **argv);

    const std::string& get_cmd_option(const std::string &option) const;
    bool cmd_option_exists(const std::string &option) const;
};