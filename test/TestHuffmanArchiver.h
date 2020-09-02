#include <sstream>
#include "doctest.h"
#include "HuffmanArchiver.h"

static unsigned char set(std::string byte) {
    unsigned char compressed_byte = 0;
    for (int i = 7; i >= 0; i--) {
        if (byte[i] == '1') {
            compressed_byte |= 1 << i;
            continue;
        }
        compressed_byte &= ~(1 << i);
    }
    return compressed_byte;
}

TEST_CASE("testing the HuffmanArchiver::compress function") {
    std::stringstream in;
    std::string str;
    std::stringstream out;
    std::string new_str;
    HuffmanArchiver encoder;
    SUBCASE("single-byte file") {
        str.push_back(set("01101010"));
        in << str;
        encoder.compress(in, out);
        CHECK(out.str().size() == 14);
        CHECK(static_cast<int>(out.str().at(0)) == 1);
        CHECK(static_cast<int>(out.str().at(1)) == 0);
        CHECK(static_cast<int>(out.str().at(2)) == 0);
        CHECK(static_cast<int>(out.str().at(3)) == 0);
        CHECK(static_cast<int>(out.str().at(4)) == 86);
        CHECK(static_cast<int>(out.str().at(5)) == 1);
        CHECK(static_cast<int>(out.str().at(6)) == 0);
        CHECK(static_cast<int>(out.str().at(7)) == 0);
        CHECK(static_cast<int>(out.str().at(8)) == 0);
        CHECK(static_cast<int>(out.str().at(9)) == 1);
        CHECK(static_cast<int>(out.str().at(10)) == 0);
        CHECK(static_cast<int>(out.str().at(11)) == 0);
        CHECK(static_cast<int>(out.str().at(12)) == 0);
        CHECK(static_cast<int>(out.str().at(13)) == 0);
    }
    SUBCASE("empty file") {
        encoder.compress(in, out);
        out >> new_str;
        CHECK(new_str.size() == 8);
        for (int i = 0; i < 8; i++) {
            CHECK(static_cast<int>(out.str().at(0)) == 0);
        }
    }
    SUBCASE("different bytes") {
        str.push_back(set("01101010"));
        str.push_back(set("11011111"));
        str.push_back(set("10001011"));
        in << str;
        encoder.compress(in, out);
        CHECK(out.str().size() == 24);
        CHECK(static_cast<int>(out.str().at(0)) == 3);
        CHECK(static_cast<int>(out.str().at(1)) == 0);
        CHECK(static_cast<int>(out.str().at(2)) == 0);
        CHECK(static_cast<int>(out.str().at(3)) == 0);
        CHECK(static_cast<int>(out.str().at(4)) == -47);
        CHECK(static_cast<int>(out.str().at(5)) == 1);
        CHECK(static_cast<int>(out.str().at(6)) == 0);
        CHECK(static_cast<int>(out.str().at(7)) == 0);
        CHECK(static_cast<int>(out.str().at(8)) == 0);
        CHECK(static_cast<int>(out.str().at(9)) == -5);
        CHECK(static_cast<int>(out.str().at(10)) == 1);
        CHECK(static_cast<int>(out.str().at(11)) == 0);
        CHECK(static_cast<int>(out.str().at(12)) == 0);
        CHECK(static_cast<int>(out.str().at(13)) == 0);
        CHECK(static_cast<int>(out.str().at(14)) == 86);
        CHECK(static_cast<int>(out.str().at(15)) == 1);
        CHECK(static_cast<int>(out.str().at(16)) == 0);
        CHECK(static_cast<int>(out.str().at(17)) == 0);
        CHECK(static_cast<int>(out.str().at(18)) == 0);
        CHECK(static_cast<int>(out.str().at(19)) == 5);
        CHECK(static_cast<int>(out.str().at(20)) == 0);
        CHECK(static_cast<int>(out.str().at(21)) == 0);
        CHECK(static_cast<int>(out.str().at(22)) == 0);
        CHECK(static_cast<int>(out.str().at(23)) == 14);
    }
}

TEST_CASE("testing the HuffmanArchiver::save function") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver encoder;
    std::map<char, std::string> code_table;
    SUBCASE("different symbols") {
        in << "abcc";
        code_table['a'] = "1";
        code_table['b'] = "01";
        code_table['c'] = "00";
        encoder.set_table_symbol_code(code_table);
        encoder.set_size_of_initial_data(4);
        encoder.save(in, out);
        CHECK(out.str() == "P");
    }
}

TEST_CASE("testing the HuffmanArchiver::extract function") {
    std::stringstream in;
    std::stringstream out;
    std::stringstream new_out;
    HuffmanArchiver encoder;
    SUBCASE("different symbols") {
        in << "fhdgrtydhfgtr";
        encoder.compress(in, out);
        encoder.extract(out, new_out);
        CHECK(new_out.str() == "fhdgrtydhfgtr");
    }
    SUBCASE("single symbol") {
        in << "u";
        encoder.compress(in, out);
        encoder.extract(out, new_out);
        CHECK(new_out.str() == "u");
    }
    SUBCASE("string of equal symbols") {
        in << "iiiiiiiii";
        encoder.compress(in, out);
        encoder.extract(out, new_out);
        CHECK(new_out.str() == "iiiiiiiii");
    }
}

TEST_CASE("testing the HuffmanArchiver::decode function") {
    HuffmanArchiver decoder;
    std::stringstream in;
    std::stringstream out;
    std::string tmp;
    std::map<std::string, char> code_table;
    SUBCASE("different symbols") {
        code_table["1"] = 'a';
        code_table["01"] = 'b';
        code_table["00"] = 'c';
        decoder.set_encoded_data_string_size(8);
        tmp.push_back(set("11100000"));
        in << tmp;
        decoder.set_table_code_symbol(code_table);
        decoder.decode(in, out);
        CHECK(out.str() == "ccbaa");
    }
    SUBCASE("single symbol") {
        code_table["1"] = 'a';
        decoder.set_encoded_data_string_size(1);
        tmp.push_back('1');
        in << tmp;
        decoder.set_table_code_symbol(code_table);
        decoder.decode(in, out);
        CHECK(out.str() == "a");
    }
    SUBCASE("string of equal symbols") {
        code_table["1"] = 'w';
        decoder.set_encoded_data_string_size(9);
        tmp.push_back(set("11111111"));
        tmp += "1";
        in << tmp;
        decoder.set_table_code_symbol(code_table);
        decoder.decode(in, out);
        CHECK(out.str() == "wwwwwwwww");
    }
}
