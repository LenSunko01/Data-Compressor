#include "BinaryFileReader.h"

std::map<char, uint64_t> BinaryFileReader::read_frequency_table(std::istream &in) {
    std::map<char, uint64_t> frequency_table;
    int32_t size_of_frequency_table = read_int32(in);
    char symbol;
    int32_t frequency;
    for (int i = 0; i < size_of_frequency_table; i++) {
        in.read(&symbol, sizeof(char));
        frequency = read_int32(in);
        frequency_table[symbol] = frequency;
    }
    return frequency_table;
}

char BinaryFileReader::get_byte(std::istream &in) {
    char data;
    in.read(&data, sizeof(char));
    return data;
}

std::size_t BinaryFileReader::size_of_istream_bytes(std::istream &in) {
    in.seekg(0, std::ios::end);
    std::size_t size = in.tellg();
    in.seekg(0, std::ios::beg);
    return size;
}

int32_t BinaryFileReader::read_int32(std::istream &in) {
    int32_t data;
    in.read(reinterpret_cast<char*>(&data), sizeof(int32_t));
    return data;
}
