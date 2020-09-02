.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -O3 -Wall -Wextra
all: archiver test_hw_03

bin:
	mkdir -p bin

archiver: src/main.cpp bin/Huffman.o bin/BinaryFileReader.o  bin/BinaryFileWriter.o  bin/CLI.o  bin/HuffmanArchiver.o  bin/HuffmanNode.o  bin/HuffmanTree.o bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

test_hw_03: test/TestMain.cpp bin/Huffman.o bin/BinaryFileReader.o bin/BinaryFileWriter.o bin/CLI.o bin/HuffmanArchiver.o bin/HuffmanNode.o bin/HuffmanTree.o test/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin archiver test_hw_03
