#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

#include <iostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>

struct tree_node {
    size_t count;
    char letter;
    tree_node *left, *right;

    tree_node(tree_node *left, tree_node *right) : left(left), right(right) {
        count = left->count + right->count;
        letter = '\0';
    }

    tree_node(size_t count, char letter) : count(count), letter(letter) {
        left = right = nullptr;
    }

    ~tree_node() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }

    friend bool operator<(const tree_node &left, const tree_node &right) {
        if (left.count == right.count) {
            return left.letter < right.letter;
        }
        return left.count < right.count;
    }

    static bool compare(const tree_node *a, const tree_node *b) {
        return (*a) < (*b);
    }
};

class haffman {
protected:
    typedef std::unordered_map<char, size_t> char_map_t;
    typedef std::vector<bool> code_t;
    typedef std::unordered_map<char, code_t> code_table_t;
private:
    std::stringstream input;
    char_map_t char_map;
    code_t code;
    code_table_t code_table;

    tree_node *build_char_tree();

    void build_code_table(tree_node *node);

public:
    void compress(std::istream &in_stream, std::ostream &out_stream);

    void decompress(std::istream &in_stream, std::ostream &out_stream);
};