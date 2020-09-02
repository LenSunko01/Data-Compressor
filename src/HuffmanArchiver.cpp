#include "HuffmanArchiver.h"

void HuffmanArchiver::compress(std::istream &in, std::ostream &out) {
    read_frequency_table(in);
    BinaryFileWriter::write_frequency_table(out, frequency_table);
    count_size_of_ancillary_data();
    code_table_symbol_code = Huffman::encode(frequency_table);
    int32_t encoded_string_size = get_size_of_encoded_string();
    BinaryFileWriter::write_int32(out, encoded_string_size);
    size_of_processed_data_bytes = save(in, out);
}

void HuffmanArchiver::read_frequency_table(std::istream& in) {
    Huffman encoder;
    size_of_initial_data_bytes = BinaryFileReader::size_of_istream_bytes(in);
    for (std::size_t i = 0; i < size_of_initial_data_bytes; i++) {
        encoder.add_to_frequency_table(BinaryFileReader::get_byte(in));
    }
    in.seekg(0, std::ios::beg);
    frequency_table = encoder.get_frequency_table();
}

void HuffmanArchiver::count_size_of_ancillary_data() {
    // number of different symbols (4 bytes)
    size_of_ancillary_data_bytes = sizeof(int32_t);
    //<char(1 byte), frequency(4 bytes)>
    size_of_ancillary_data_bytes += frequency_table.size() * 5;
    // encoded_string_size (4 bytes)
    size_of_ancillary_data_bytes += sizeof(int32_t);
}

std::size_t HuffmanArchiver::save(std::istream &in, std::ostream& out) {
    std::string tmp;
    std::size_t size_of_processed_data = 0;
    char compressed_byte;
    for (std::size_t i = 0; i < size_of_initial_data_bytes; i++) {
        compressed_byte = 0;
        unsigned char byte = BinaryFileReader::get_byte(in);
        tmp += code_table_symbol_code[byte];
        while (tmp.length() >= number_of_bits_in_byte) {
            for (std::size_t bit = 0; bit < number_of_bits_in_byte; bit++) {
                compressed_byte = compressed_byte * 2 +
                                  (tmp[bit] - '0');
            }
            BinaryFileWriter::write_byte(out, compressed_byte);
            ++size_of_processed_data;
            std::string str = tmp.substr(number_of_bits_in_byte);
            tmp = str;
        }
    }
    if (!tmp.empty()) {
        compressed_byte = 0;
        for (std::size_t bit = 0; bit < tmp.length(); bit++) {
            compressed_byte = compressed_byte * 2 +
                              (tmp[bit] - '0');
        }
        BinaryFileWriter::write_byte(out, compressed_byte);
        ++size_of_processed_data;
    }
    return size_of_processed_data;
}

void HuffmanArchiver::extract(std::istream &in, std::ostream &out) {
    frequency_table = BinaryFileReader::read_frequency_table(in);
    count_size_of_ancillary_data();
    encoded_data_string_size = BinaryFileReader::read_int32(in);
    size_of_initial_data_bytes = encoded_data_string_size / number_of_bits_in_byte;
    if (encoded_data_string_size % number_of_bits_in_byte) {
        size_of_initial_data_bytes++;
    }
    code_table_symbol_code = Huffman::encode(frequency_table);
    code_table_code_symbol = Huffman::create_table_code_symbol(code_table_symbol_code);
    decode(in, out);
}

static std::string get_symbol(const char byte, int bit) {
    if (byte & (1 << bit)) {
        return "1";
    }
    return "0";
}

void HuffmanArchiver::decode(std::istream& in, std::ostream& out) {
    std::string tmp;
    size_of_processed_data_bytes = 0;
    for (std::size_t byte = 0; byte < encoded_data_string_size/number_of_bits_in_byte; byte++) {
        char compressed_byte = BinaryFileReader::get_byte(in);
        for (int bit = number_of_bits_in_byte - 1; bit >= 0; bit--) {
            tmp += get_symbol(compressed_byte, bit);
        }
        if (code_table_code_symbol.find(tmp) != code_table_code_symbol.end()) {
            BinaryFileWriter::write_byte(out, code_table_code_symbol[tmp]);
            ++size_of_processed_data_bytes;
            tmp = "";
        }
    }
    char current = BinaryFileReader::get_byte(in);
    for (int bit = encoded_data_string_size % number_of_bits_in_byte - 1; bit >= 0; bit--) {
        tmp += get_symbol(current, bit);
        if (code_table_code_symbol.find(tmp) != code_table_code_symbol.end()) {
            BinaryFileWriter::write_byte(out, code_table_code_symbol[tmp]);
            ++size_of_processed_data_bytes;
            tmp = "";
        }
    }
    std::string code;
    for (auto symbol : tmp) {
        code += symbol;
        if (code_table_code_symbol.find(code) != code_table_code_symbol.end()) {
            BinaryFileWriter::write_byte(out, code_table_code_symbol[code]);
            ++size_of_processed_data_bytes;
            code = "";
        }
    }
}

std::size_t HuffmanArchiver::get_size_of_initial_data() const {
    return size_of_initial_data_bytes;
}

std::size_t HuffmanArchiver::get_size_of_processed_data() const {
    return size_of_processed_data_bytes;
}

std::size_t HuffmanArchiver::get_size_of_ancillary_data() const {
    return size_of_ancillary_data_bytes;
}

int32_t HuffmanArchiver::get_size_of_encoded_string() {
    std::size_t size = 0;
    for (auto symbol : frequency_table) {
        size += symbol.second * code_table_symbol_code[symbol.first].length();
    }
    return size;
}

void HuffmanArchiver::set_table_symbol_code(std::map<char, std::string>& new_table) {
    code_table_symbol_code = new_table;
}

void HuffmanArchiver::set_size_of_initial_data(std::size_t new_size) {
    size_of_initial_data_bytes = new_size;
}

void HuffmanArchiver::set_encoded_data_string_size(int32_t new_size) {
    encoded_data_string_size = new_size;
}

void HuffmanArchiver::set_table_code_symbol(std::map<std::string, char>& new_table) {
    code_table_code_symbol = new_table;
}




