#include <sstream>
#include "doctest.h"

#include "HuffmanArchiver.h"

TEST_CASE("1 test end-to-end algorithm: different symbols") {
    std::stringstream in;
    in << "abccba";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 6);
    CHECK(encoder.get_size_of_processed_data() == 2);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 2);
    CHECK(encoder.get_size_of_processed_data() == 6);
    CHECK(new_out.str() == "abccba");
}

TEST_CASE("2 test end-to-end algorithm: one symbol") {
    std::stringstream in;
    in << "h";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() == encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() == encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    CHECK(new_out.str() == "h");
}

TEST_CASE("3 test end-to-end algorithm: string of equal symbols, length is not divided by 8") {
    std::stringstream in;
    in << "ooooooooo";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 9);
    CHECK(encoder.get_size_of_processed_data() == 2);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 2);
    CHECK(encoder.get_size_of_processed_data() == 9);
    CHECK(new_out.str() == "ooooooooo");
}

TEST_CASE("4 test end-to-end algorithm: string of equal symbols, length is divided by 8") {
    std::stringstream in;
    in << "7777777777777777";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 16);
    CHECK(encoder.get_size_of_processed_data() == 2);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 2);
    CHECK(encoder.get_size_of_processed_data() == 16);
    CHECK(new_out.str() == "7777777777777777");
}

TEST_CASE("5 test end-to-end algorithm: string with spaces") {
    std::stringstream in;
    in << "y43*54 gk fk ";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 13);
    CHECK(encoder.get_size_of_processed_data() == 5);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
    CHECK(encoder.get_size_of_initial_data() == 5);
    CHECK(encoder.get_size_of_processed_data() == 13);
    CHECK(new_out.str() == "y43*54 gk fk ");
}

TEST_CASE("6 test end-to-end algorithm: empty file") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(new_out.str().empty());
}

TEST_CASE("7 test end-to-end algorithm: single space symbol") {
    std::stringstream in;
    in << " ";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    CHECK(new_out.str() == " ");
}

TEST_CASE("8 test end-to-end algorithm: single new-line symbol") {
    std::stringstream in;
    in << "\n";
    std::stringstream out;
    HuffmanArchiver encoder;
    encoder.compress(in, out);
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    std::stringstream new_in;
    std::stringstream new_out;
    new_in << out.str();
    encoder.extract(new_in, new_out);
    CHECK(encoder.get_size_of_initial_data() == 1);
    CHECK(encoder.get_size_of_processed_data() == 1);
    CHECK(new_out.str() == "\n");
}

TEST_CASE("8 test end-to-end algorithm: space and different symbols combinations") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver encoder;
    SUBCASE("space symbol at the beginning") {
        in << " k";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 2);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 2);
        CHECK(new_out.str() == " k");
    }
    SUBCASE("space symbol at the end") {
        in << "o ";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 2);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 2);
        CHECK(new_out.str() == "o ");
    }
    SUBCASE("space symbol at the beginning and at the end") {
        in << " s l ";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 5);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 5);
        CHECK(new_out.str() == " s l ");
    }
    SUBCASE("more than one space symbol") {
        in << "   k   ";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 7);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 7);
        CHECK(new_out.str() == "   k   ");
    }
}

TEST_CASE("9 test end-to-end algorithm: space and new-line symbols combinations") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver encoder;
    SUBCASE("space at the beginning") {
        in << " \n";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 2);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 2);
        CHECK(new_out.str() == " \n");
    }
    SUBCASE("space at the beginning and at the end") {
        in << " \n ";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 3);
        CHECK(encoder.get_size_of_processed_data() == 1);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 1);
        CHECK(encoder.get_size_of_processed_data() == 3);
        CHECK(new_out.str() == " \n ");
    }
    SUBCASE("many space symbols and new-line symbols") {
        in << "\n    \n \n ";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() > encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 9);
        CHECK(encoder.get_size_of_processed_data() == 2);
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() < encoder.get_size_of_processed_data());
        CHECK(encoder.get_size_of_initial_data() == 2);
        CHECK(encoder.get_size_of_processed_data() == 9);
        CHECK(new_out.str() == "\n    \n \n ");
    }
}

TEST_CASE("10 test end-to-end algorithm: size of processed data is less or equal to initial") {
    std::stringstream in;
    std::stringstream out;
    HuffmanArchiver encoder;
    SUBCASE("one symbol") {
        in << "a";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() >= encoder.get_size_of_processed_data());
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() <= encoder.get_size_of_processed_data());
        CHECK(new_out.str() == "a");
    }
    SUBCASE("eight different symbols") {
        in << "abcdefgr";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() >= encoder.get_size_of_processed_data());
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() <= encoder.get_size_of_processed_data());
        CHECK(new_out.str() == "abcdefgr");
    }
    SUBCASE("8 symbols, some are equal") {
        in << "abcdefab";
        encoder.compress(in, out);
        CHECK(encoder.get_size_of_initial_data() >= encoder.get_size_of_processed_data());
        std::stringstream new_in;
        std::stringstream new_out;
        new_in << out.str();
        encoder.extract(new_in, new_out);
        CHECK(encoder.get_size_of_initial_data() <= encoder.get_size_of_processed_data());
        CHECK(new_out.str() == "abcdefab");
    }
}




