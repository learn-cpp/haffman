#include "haffman.hpp"

tree_node *haffman::build_char_tree() {
    std::list<tree_node *> tree;

    for (auto pair : char_map) {
        tree.push_back(new tree_node(pair.second, pair.first));
    }

    while (tree.size() != 1) {
        tree.sort(tree_node::compare);

        tree_node *left = tree.front();
        tree.pop_front();

        tree_node *right = tree.front();
        tree.pop_front();

        tree.push_back(new tree_node(left, right));
    }

    return tree.front();
}

void haffman::build_code_table(tree_node *node) {
    if (node->left != nullptr) {
        code.push_back(0);
        build_code_table(node->left);
    }
    if (node->right != nullptr) {
        code.push_back(1);
        build_code_table(node->right);
    }
    if (node->letter != '\0') {
        code_table[node->letter] = code;
    }

    code.pop_back();
}


void haffman::compress(std::istream &in_stream, std::ostream &out_stream) {
    std::stringstream str_stream;
    str_stream << in_stream.rdbuf();
    std::string input = str_stream.str();

    for (auto ch : input) {
        char_map[ch]++;
    }

    std::cout << "char map " << char_map.size() << ": " << std::endl;
    // dump char map
    out_stream << char_map.size();
    for (auto i: char_map) {
        out_stream << i.first << i.second;
        std::cout << "'" << i.first << "': " << i.second << std::endl;
    }

    auto *tree = build_char_tree();
    build_code_table(tree);

    std::cout << "code table: " << std::endl;
    for (auto i : code_table) {
        std::cout << i.first << ": ";
        for (auto j : i.second) {
            std::cout << j;
        }
        std::cout << std::endl;
    }

    // dump compressed data
    char buf = 0;
    short count = 0;
    for (auto symbol: input) {
        auto code = code_table[symbol];
        size_t size = code.size();
        for (size_t i = 0; i < size; ++i) {
            std::cout << code[i];
            buf |= code[i] << (7 - count);
            count++;
            if (count == 8) {
                out_stream << buf;
                count = 0;
                buf = 0;
            }
        }
    }
    if (count > 0) {
        out_stream << buf;
    }
}

void haffman::decompress(std::istream &in_stream, std::ostream &out_stream) {
    unsigned long char_map_size;
    in_stream >> char_map_size;
    std::cout << "char map size: " << char_map_size << std::endl;
    for (unsigned long i = 0; i < char_map_size; ++i) {
        char symbol;
        size_t count;
        in_stream.get(symbol);
        in_stream >> count;
        char_map[symbol] = count;
        std::cout << symbol << ": " << count << std::endl;
    }

    auto *node = build_char_tree();

    // decode compressed data
    short count = 0;
    auto *it_node = node;
    char byte;
    in_stream.get(byte);

    do {
        bool bit = (bool) (byte & (1 << (7 - count)));
        it_node = bit ? it_node->right : it_node->left;
        if (it_node->left == nullptr && it_node->right == nullptr) {
            out_stream << it_node->letter;
            it_node = node;
        }

        count++;
        if (count == 8) {
            count = 0;
            in_stream.get(byte);
        }
    } while (!in_stream.eof());
}