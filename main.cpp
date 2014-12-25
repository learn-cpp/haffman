#include <iostream>
#include <fstream>
#include "haffman.hpp"

void help() {
    std::cout << std::endl;
    std::cout << "Haffman haffman:" << std::endl;
    std::cout << "huffman -c <source_file> <output_file>" << std::endl;
    std::cout << "huffman -d <compressed_file> <output_file>" << std::endl;
}

int main(const int argc, const char **argv) {
    if (argc < 4) {
        help();
        return 1;
    }

    std::ifstream in(argv[2], std::ios::out | std::ios::binary);
    if (!in) {
        throw std::runtime_error("Couldn't open source file");
    }
    std::ofstream out(argv[3], std::ios::out | std::ios::binary);
    if (!out) {
        throw std::runtime_error("Couldn't open output file");
    }

    haffman compressor;

    std::string act = argv[1];
    if (act.find("-c") != std::string::npos) {
        compressor.compress(in, out);
    } else if (act.find("-d") != std::string::npos) {
        compressor.decompress(in, out);
    } else {
        help();
        return 1;
    }
}