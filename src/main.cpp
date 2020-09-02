#include <iostream>
#include "CLI.h"
#include "HuffmanArchiver.h"

int main(int argc, char **argv) {
    command_arguments args;
    try {
        args = CLI::parse_args(argc, argv);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    HuffmanArchiver archiver;
    std::ifstream source(args.source_file, std::ios::binary);
    std::ofstream destination(args.destination_file, std::ios::binary);
    if (args.compress_flag != ARGUMENT_NOT_SET) {
        archiver.compress(source, destination);
    }
    if (args.extract_flag != ARGUMENT_NOT_SET) {
        archiver.extract(source, destination);
    }
    std::cout << archiver.get_size_of_initial_data() << std::endl;
    std::cout << archiver.get_size_of_processed_data() << std::endl;
    std::cout << archiver.get_size_of_ancillary_data() << std::endl;
    return 0;
}
