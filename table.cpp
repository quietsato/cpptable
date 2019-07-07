//
// Created by lnsf on 7/3/19.
//

#include <iostream>
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

    setStyle(BOTH_TITLE);
}

void tbl::Table::setStyle(Type t){
    type = t;
    switch (type)
    {
    case ALL:
        this->hBorderChar = '-';
        this->vBorderChar = '|';
        this->outerHBorderChar = '-';
        this->outerVBorderChar = '|';
        this->titleHBorderChar = '=';
        this->titleVBorderChar = ':';
        this->crossChar = '+';
        break;
    
    case ROW_TITLE:
        this->hBorderChar = ' ';
        this->vBorderChar = '|';
        this->outerHBorderChar = '-';
        this->outerVBorderChar = '|';
        this->titleHBorderChar = '=';
        this->titleVBorderChar = '|';
        this->crossChar = '+';
        break;

    case COL_TITLE:
        this->hBorderChar = '-';
        this->vBorderChar = ' ';
        this->outerHBorderChar = '-';
        this->outerVBorderChar = '|';
        this->titleHBorderChar = '-';
        this->titleVBorderChar = ':';
        this->crossChar = '+';
        break;

    case BOTH_TITLE:
        this->hBorderChar = ' ';
        this->vBorderChar = ' ';
        this->outerHBorderChar = '-';
        this->outerVBorderChar = '|';
        this->titleHBorderChar = '=';
        this->titleVBorderChar = ':';
        this->crossChar = '+';
        break;
    }
}

void tbl::Table::add_row(vector<string> cols) {
    while (cols.size() < this->row)
        cols.push_back("");

    this->content.push_back(cols);
}

void tbl::Table::delete_row(int i) {
    if (i < this->content.size())
        this->content.erase(this->content.begin() + i);
}

void tbl::Table::clear(){
    this->content.clear();
}

string tbl::Table::to_string() {
    string str;

    this->colWidth.resize(this->col, 0);
    this->rowHeight.resize(this->row, 0);

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
        if(i == row - 1) break;
        str += innerHLine(!(row == 1 || i > 0));
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
    for (int i = 0; i < width - 1; i++) {
        str += this->outerHBorderChar;
    }
    str += this->crossChar;
    return str + '\n';
}

string tbl::Table::row_to_string(int r) {
    string ret;

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
        lines.push_back(cell);
        lines.resize(_height);
        separate.push_back(lines);
        lines.clear();
    }

    bool isColTitle = true;
    for(int l = 0; l < _height; l++){
        ret += outerVBorderChar;
        for(int c = 0; c < col; c++){
            separate[c][l].resize(colWidth[c], ' ');
            ret += separate[c][l];
            if (isColTitle) {
                if (type == ROW_TITLE)
                    ret += vBorderChar;
                else
                    ret += titleVBorderChar;

                isColTitle = false;
            } 
            else
            if(c == col - 1)
                ret += outerVBorderChar;
            else
                ret += vBorderChar;
        }
        isColTitle = true;
        ret += '\n';
    }

    return ret;
}

string tbl::Table::innerHLine(bool isRowTitle) {
    bool isColTitle = true;
    string str;
    str += outerVBorderChar;
    for (int i = 0; i < width - 1; i++) {
        auto found = find(crossPos.begin(), crossPos.end(), i);
        if (found != crossPos.end()) {
            if (isColTitle) {
                if (type == ROW_TITLE)
                    str += vBorderChar;
                else
                    str += titleVBorderChar;

                isColTitle = false;
            } 
            else if(type == BOTH_TITLE || type == ROW_TITLE){
                if(type == BOTH_TITLE && isRowTitle)
                    str += titleHBorderChar;
                else
                    str += vBorderChar;
                
            }    
            else if(type == COL_TITLE)
                str += hBorderChar;
            else
                str += vBorderChar;

        } 
        else {
            if (isRowTitle) {
                if (type == COL_TITLE)
                    str += hBorderChar;
                else
                    str += titleHBorderChar;
            } 
            else
                str += hBorderChar;
        }
    }
    str += outerVBorderChar;
    str += '\n';

    return str;
}

int getWidth(const string &s) {
    int w = 0;
    size_t f = -1, prev = 0;
    while ((f = s.find('\n', prev + 1)) != string::npos) {
        w = max(w, (int) (f - prev));
        prev = f + 1;
    }
    return max(w, (int) (s.size() - prev));
}

int getHeight(const string &s) {
    return count(s.begin(), s.end(), '\n') + 1;
}

vector<int> findCross(const vector<int> &col) {
    int i = 0;
    bool first = true;
    vector<int> ret;
    
    for (int j = 0; j < col.size() - 1; j++) {
        i += col[j];
        if(first)
            first = false;
        else
            i++;
        ret.push_back(i);
    }

    return ret;
}

int sum(vector<int> &v) {
    return accumulate(v.begin(), v.end(), 0);
}
