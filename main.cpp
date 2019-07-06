#include <iostream>
#include "table.h"
using namespace std;
using namespace tbl;

int main() {
    std::cout << "Hello, World!" << std::endl;

    Table t = Table(3, 3);
    t.add_row(vector<string>{"hello", "world", "everyone"});
    t.add_row(vector<string>{"hello", "world", "everyone"});
    t.add_row(vector<string>{"hello", "world", "everyone"});

    t.show();

    return 0;
}