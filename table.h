//
// Created by lnsf on 7/3/19.
//

#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H

#include <string>
#include <vector>

namespace tbl{
    enum Type {ALL, ROW_TITLE, COL_TITLE, BOTH_TITLE};

    class Table{
        int row, col, width;
        std::vector<int> colWidth, rowHeight, crossPos;
        std::vector<std::vector<std::string>> content;
        Type type;

        std::string hLine();
        std::string innerHLine(bool);
        std::string row_to_string(int);

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
