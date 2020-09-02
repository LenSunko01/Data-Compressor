#include "doctest.h"
#include "Huffman.h"

bool check_prefix_code(std::string first, std::string second) {
    if (first.length() < second.length()) {
        swap(first, second);
    }
    return first.find(second) != 0;
}

TEST_CASE("1 testing the Huffman::encode function: different frequency") {
    std::map<char, uint64_t> frequency_table{{'a', 1}, {'b', 5}, {'c', 10}};
    std::map<char, std::string> code_table;
    SUBCASE("different frequency, none coincide") {
        frequency_table['a'] = 1;
        frequency_table['b'] = 5;
        frequency_table['c'] = 10;
        code_table = Huffman::encode(frequency_table);
        CHECK(code_table['a'].length() == 2);
        CHECK(code_table['b'].length() == 2);
        CHECK(code_table['c'].length() == 1);
        CHECK(check_prefix_code(code_table['a'], code_table['b']));
        CHECK(check_prefix_code(code_table['a'], code_table['c']));
        CHECK(check_prefix_code(code_table['b'], code_table['c']));
    }
    SUBCASE("different frequency, some of them are equal, number of symbols is power of two") {
        frequency_table['a'] = 1;
        frequency_table['b'] = 5;
        frequency_table['c'] = 10;
        frequency_table['d'] = 10;
        code_table = Huffman::encode(frequency_table);
        CHECK(code_table['a'].length() == 3);
        CHECK(code_table['b'].length() == 3);
        CHECK(code_table['c'].length() == 2);
        CHECK(code_table['d'].length() == 1);
        CHECK(check_prefix_code(code_table['a'], code_table['b']));
        CHECK(check_prefix_code(code_table['a'], code_table['c']));
        CHECK(check_prefix_code(code_table['a'], code_table['d']));
        CHECK(check_prefix_code(code_table['b'], code_table['c']));
        CHECK(check_prefix_code(code_table['b'], code_table['d']));
        CHECK(check_prefix_code(code_table['c'], code_table['d']));
    }
    SUBCASE("different frequency, some of them are equal, number of symbols is not power of two") {
        frequency_table['a'] = 3;
        frequency_table['b'] = 5;
        frequency_table['c'] = 10;
        frequency_table['d'] = 10;
        frequency_table['e'] = 3;
        code_table = Huffman::encode(frequency_table);
        CHECK(code_table['a'].length() == 3);
        CHECK(code_table['e'].length() == 3);
        CHECK(code_table['b'].length() == 2);
        CHECK(code_table['d'].length() == 2);
        CHECK(code_table['c'].length() == 2);
        CHECK(check_prefix_code(code_table['a'], code_table['b']));
        CHECK(check_prefix_code(code_table['a'], code_table['c']));
        CHECK(check_prefix_code(code_table['a'], code_table['d']));
        CHECK(check_prefix_code(code_table['a'], code_table['e']));
        CHECK(check_prefix_code(code_table['b'], code_table['c']));
        CHECK(check_prefix_code(code_table['b'], code_table['d']));
        CHECK(check_prefix_code(code_table['b'], code_table['e']));
        CHECK(check_prefix_code(code_table['c'], code_table['d']));
        CHECK(check_prefix_code(code_table['c'], code_table['e']));
        CHECK(check_prefix_code(code_table['d'], code_table['e']));
    }
}

TEST_CASE("2 testing the Huffman::encode function: empty frequency_table") {
    std::map<char, uint64_t> frequency_table;
    std::map<char, std::string> code_table;
    code_table = Huffman::encode(frequency_table);
    CHECK(code_table.empty());
}

TEST_CASE("3 testing the Huffman::encode function: equal frequency") {
    std::map<char, uint64_t> frequency_table;
    std::map<char, std::string> code_table;
    SUBCASE("number of symbols is power of two") {
        frequency_table['a'] = 15;
        frequency_table['b'] = 15;
        frequency_table['c'] = 15;
        frequency_table['d'] = 15;
        code_table = Huffman::encode(frequency_table);
        CHECK(code_table['a'].length() == 2);
        CHECK(code_table['b'].length() == 2);
        CHECK(code_table['c'].length() == 2);
        CHECK(code_table['d'].length() == 2);
        CHECK(check_prefix_code(code_table['a'], code_table['b']));
        CHECK(check_prefix_code(code_table['a'], code_table['c']));
        CHECK(check_prefix_code(code_table['a'], code_table['d']));
        CHECK(check_prefix_code(code_table['b'], code_table['c']));
        CHECK(check_prefix_code(code_table['b'], code_table['d']));
        CHECK(check_prefix_code(code_table['c'], code_table['d']));
    }
    SUBCASE("number of symbols is not power of two") {
        frequency_table['a'] = 15;
        frequency_table['b'] = 15;
        frequency_table['c'] = 15;
        code_table = Huffman::encode(frequency_table);
        CHECK(code_table['a'].length() == 2);
        CHECK(code_table['b'].length() == 2);
        CHECK(code_table['c'].length() == 1);
        CHECK(check_prefix_code(code_table['a'], code_table['b']));
        CHECK(check_prefix_code(code_table['a'], code_table['c']));
        CHECK(check_prefix_code(code_table['b'], code_table['c']));
    }
}

TEST_CASE("4 testing the Huffman::encode function: one symbol") {
    std::map<char, uint64_t> frequency_table{{'a', 1}};
    std::map<char, std::string> code_table;
    code_table = Huffman::encode(frequency_table);
    CHECK(code_table['a'].length() == 1);
}

TEST_CASE("testing the Huffman::create_table_code_symbol function") {
    Huffman encoder;
    std::map<char, std::string> code_table_symbol_code{{'a', "100"},{'b', "0"}};
    std::map<std::string, char> code_table = encoder.create_table_code_symbol(code_table_symbol_code);
    CHECK(code_table.size() == 2);
    CHECK(code_table["100"] == 'a');
    CHECK(code_table["0"] == 'b');
}

