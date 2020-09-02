#ifndef HUFFMAN_CLI_H
#define HUFFMAN_CLI_H

#include <string>
#include <fstream>

const std::string COMPRESS_COMMAND = "-c";
const std::string EXTRACT_COMMAND = "-u";
const std::string SOURCE_FILE_COMMAND = "-f";
const std::string SOURCE_FILE_FULL_COMMAND = "--file";
const std::string DESTINATION_FILE_COMMAND = "-o";
const std::string DESTINATION_FILE_FULL_COMMAND = "--output";
const std::string ARGUMENT_NOT_SET = "NULL";

struct command_arguments {
    std::string extract_flag = ARGUMENT_NOT_SET;
    std::string compress_flag = ARGUMENT_NOT_SET;
    std::string source_file = ARGUMENT_NOT_SET;
    std::string destination_file = ARGUMENT_NOT_SET;
};

class CLI {
public:
    CLI() = default;
    static command_arguments parse_args(int argc, char** argv);
private:
    static void validate_arguments(command_arguments& command);
};


#endif //HUFFMAN_CLI_H
