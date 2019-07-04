//
// Created by lnsf on 7/3/19.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>
#include "table.h"

using namespace std;

int getWidth(const string &);

int getHeight(const string &);

int sum(vector<int> &);

vector<int> findCross(const vector<int> &);

tbl::Table::Table(int row, int col) {
    if (row <= 0 || col <= 0)
        runtime_error("Invalid table size");

    this->row = row;
    this->col = col;

    this->type = BOTH_TITLE;

    this->hBorderChar = '-';
    this->vBorderChar = '|';
    this->titleBorder = true;
    this->titleHBorderChar = '=';
    this->titleVBorderChar = ':';
    this->crossChar = '+';
}

void tbl::Table::add_row(vector<std::string> cols) {
    while (cols.size() < this->row)
        cols.emplace_back("");

    for (int i = 0; i < this->row; i++)
        this->content.emplace_back(cols[i]);
}

void tbl::Table::delete_row(int i) {
    if (i < this->content.size())
        this->content.erase(this->content.begin() + i);
}

string tbl::Table::to_string() {
    string str;

    this->colWidth.resize(this->col);
    this->rowHeight.resize(this->row);

    for (int r = 0; r < this->row; r++) {
        for (int c = 0; c < this->col; c++) {
            this->colWidth[c] = max(colWidth[c], getWidth(content[r][c]));
            this->rowHeight[r] = max(rowHeight[r], getHeight(content[r][c]));
        }
    }

    this->width = sum(this->colWidth) + this->col;
    this->crossPos = findCross(colWidth);


    str += hLine();

    for (int i = 0; i < row; i++) {
        str += row_to_string(i);
        str += innerHLine(!(row == 1 || i > 1));
    }

    str += hLine();

    return str;
}

void tbl::Table::show() {
    cout << this->to_string();
}

string tbl::Table::hLine() {
    string str;
    str += this->crossChar;
    for (int i = 0; i < width; i++) {
        str += this->hBorderChar;
    }
    str += this->crossChar;
    return str + '\n';
}

string tbl::Table::row_to_string(int r) {
    vector<string> _row = content[r];
    int _height = rowHeight[r];
    vector<vector<string>> separate;
    separate.reserve(row);

    vector<string> lines;
    size_t pos = 0;

    for(string cell : _row){
        while((pos = cell.find('\n')) != string::npos){
            lines.push_back(cell.substr(0, pos));
            cell.erase(0, pos + 1);
        }
    }

    return "";
}

string tbl::Table::innerHLine(bool isRowTitle) {
    bool isColTitle = true;
    string str;
    str += crossChar;
    for (int i = 0; i < width; i++) {
        auto found = find(crossPos.begin(), crossPos.end(), i);
        if (found != crossPos.end()) {
            if (isColTitle) {
                if (type == ROW_TITLE)
                    str += vBorderChar;
                else
                    str += titleVBorderChar;

                isColTitle = false;
            } else
                str += vBorderChar;
        } else {
            if (isRowTitle) {
                if (type == COL_TITLE)
                    str += hBorderChar;
                else
                    str += titleHBorderChar;
            } else
                str += hBorderChar;
        }
    }
    str += crossChar;
    str += '\n';

    return str;
}

int getWidth(const string &s) {
    int w = 0, prev = 0;
    size_t f;
    while ((f = s.find('\n')) != string::npos) {
        w = max(w, (int) (f - prev));
        prev = f;
    }
    return max(w, (int) (s.size() - prev));
}

int getHeight(const string &s) {
    return count(s.begin(), s.end(), '\n') + 1;
}

vector<int> findCross(const vector<int> &col) {
    int i = 0;
    vector<int> ret;
    for (int p : col) {
        i += p;
        ret.emplace_back(i);
    }

    return ret;
}

int sum(vector<int> &v) {
    return accumulate(v.begin(), v.end(), 0);
}
