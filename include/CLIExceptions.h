#ifndef HUFFMAN_CLIEXCEPTIONS_H
#define HUFFMAN_CLIEXCEPTIONS_H

#include <exception>

class cli_exception : public std::exception {
protected:
    const char* message = "Unexpected parsing error";
public:
    virtual const char* what() const noexcept {
        return message;
    };
};

class bad_arguments_number_exception : public cli_exception {
public:
    bad_arguments_number_exception() { message = "Error: not enough arguments"; };
};

class double_compress_flag_exception : public cli_exception {
public:
    double_compress_flag_exception() { message = "Error: flag -c has been given twice"; };
};

class double_extract_flag_exception : public cli_exception {
public:
    double_extract_flag_exception() { message = "Error: flag -u has been given twice"; };
};

class double_source_file_exception : public cli_exception {
public:
    double_source_file_exception() { message = "Error: source file has been given twice"; };
};

class double_destination_file_exception : public cli_exception {
public:
    double_destination_file_exception() {
        message = "Error: destination file has been given twice";
    };
};

class unrecognised_flag_exception : public cli_exception {
public:
    unrecognised_flag_exception() { message = "Error: unrecognised flag"; };
};

class equal_destination_source_files_exception : public cli_exception {
public:
    equal_destination_source_files_exception() {
        message = "Error: source and destination files are the same";
    };
};

class source_file_not_given_exception : public cli_exception {
public:
    source_file_not_given_exception() { message = "Error: source file after -f is expected"; };
};

class destination_file_not_given_exception : public cli_exception {
public:
    destination_file_not_given_exception() {
        message = "Error: destination file after -u is expected";
    };
};

class source_file_not_opened_exception : public cli_exception {
public:
    source_file_not_opened_exception() { message = "Error: unable to open source file"; };
};
#endif //HUFFMAN_CLIEXCEPTIONS_H
