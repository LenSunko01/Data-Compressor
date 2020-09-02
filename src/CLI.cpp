#include "CLI.h"
#include "CLIExceptions.h"

inline bool able_to_open(const std::string& file_name) {
    std::ifstream file;
    file.open(file_name, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.close();
    return true;
}

command_arguments CLI::parse_args(int argc, char **argv) {
    command_arguments command;
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == COMPRESS_COMMAND) {
            if (command.compress_flag == ARGUMENT_NOT_SET) {
                command.compress_flag = COMPRESS_COMMAND;
                continue;
            } else {
                throw double_compress_flag_exception();
            }
        }
        if (argv[i] == EXTRACT_COMMAND) {
            if (command.extract_flag == ARGUMENT_NOT_SET) {
                command.extract_flag = EXTRACT_COMMAND;
                continue;
            } else {
                throw double_extract_flag_exception();
            }
        }
        if (argv[i] == SOURCE_FILE_COMMAND ||
            argv[i] == SOURCE_FILE_FULL_COMMAND) {
            if (i == argc - 1) {
                throw source_file_not_given_exception();
            }
            if (command.source_file == ARGUMENT_NOT_SET) {
                command.source_file = argv[++i];
                continue;
            } else {
                throw double_source_file_exception();
            }
        }
        if (argv[i] == DESTINATION_FILE_COMMAND ||
            argv[i] == DESTINATION_FILE_FULL_COMMAND) {
            if (i == argc - 1) {
                throw destination_file_not_given_exception();
            }
            if (command.destination_file == ARGUMENT_NOT_SET) {
                command.destination_file = argv[++i];
                continue;
            } else {
                throw double_destination_file_exception();
            }
        }
        throw unrecognised_flag_exception();
    }
    validate_arguments(command);
    return command;
}

void CLI::validate_arguments(command_arguments &command) {
    if (command.compress_flag == ARGUMENT_NOT_SET &&
        command.extract_flag == ARGUMENT_NOT_SET) {
        throw bad_arguments_number_exception();
    }
    if (command.source_file == ARGUMENT_NOT_SET ||
        command.destination_file == ARGUMENT_NOT_SET) {
        throw bad_arguments_number_exception();
    }
    if (!able_to_open(command.source_file)) {
        throw source_file_not_opened_exception();
    }
    if (command.source_file == command.destination_file) {
        throw equal_destination_source_files_exception();
    }
}
