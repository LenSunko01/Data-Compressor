#include "BinaryFileWriter.h"

void BinaryFileWriter::write_frequency_table(std::ostream &out,
                                             const std::map<char, uint64_t> &frequency_table) {
    int32_t number_of_different_symbols = frequency_table.size();
    write_int32(out, number_of_different_symbols);
    //<char(1 byte), frequency(4 bytes)>
    for (auto item : frequency_table) {
        out.write(&item.first, sizeof(char));
        write_int32(out, item.second);
    }
}

void BinaryFileWriter::write_byte(std::ostream &out, char byte) {
    out.write(&byte, sizeof(char));
}

void BinaryFileWriter::write_int32(std::ostream &out, int32_t data) {
    out.write(reinterpret_cast<char*>(&data), sizeof(int32_t));
}
