//
// Created by lnsf on 7/3/19.
//

#include <iostream>
#include "table.h"
using namespace std;

tbl::Table::Table(int row, int col) {
    if(row <= 0 || col <= 0)
        runtime_error("Invalid table size");

    this->row = row;
    this->col = col;

    this->type = FIRST_BOTH;

    this->hBorderChar = '-';
    this->vBorderChar = '|';
    this->titleBorder = true;
    this->titleHBorderChar = '=';
    this->titleVBorderChar = ':';
    this->crossChar = '+';
}

void tbl::Table::add_row(vector<std::string> cols) {
    while(cols.size() < this->row)
        cols.emplace_back("");

    for(int i = 0; i < this->row; i++)
        this->content.emplace_back(cols[i]);
}

void tbl::Table::delete_row(int i) {
    if(i < this->content.size())
        this->content.erase(this->content.begin() + i);
}

string tbl::Table::to_string(){
    return "";
}

void tbl::Table::show() {
    cout << this->to_string() << endl;
}