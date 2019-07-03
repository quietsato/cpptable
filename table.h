//
// Created by lnsf on 7/3/19.
//

#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H

#include <string>
#include <vector>

namespace tbl{
    enum Type {ALL, ONLY_ROW, ONLY_COLUMN, FIRST_BOTH};

    class Table{
        int row, col;
        std::vector<std::vector<std::string>> content;
        Type type;

    public:
        bool titleBorder;
        char hBorderChar, vBorderChar, titleHBorderChar, titleVBorderChar, crossChar;

        Table(int, int);

        void add_row(std::vector<std::string>);
        void delete_row(int);
        void show();
        std::string to_string();
    };
}

#endif //TABLE_TABLE_H
