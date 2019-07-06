//
// Created by lnsf on 7/3/19.
//

#ifndef TABLE_TABLE_H
#define TABLE_TABLE_H

#include <string>
#include <vector>

using namespace std;

namespace tbl{
    enum Type {ALL, ROW_TITLE, COL_TITLE, BOTH_TITLE};

    class Table{
        int row, col, width;
        vector<int> colWidth, rowHeight, crossPos;
        vector<vector<string>> content;
        Type type;

        string hLine();
        string innerHLine(bool);
        string row_to_string(int);

    public:
        bool titleBorder;
        char hBorderChar, vBorderChar, titleHBorderChar, titleVBorderChar, crossChar;

        Table(int, int);

        void add_row(vector<string>);
        void delete_row(int);
        void show();
        string to_string();
    };
}

#endif //TABLE_TABLE_H
