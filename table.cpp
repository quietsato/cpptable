//
// Created by lnsf on 7/3/19.
//

#include "table.h"
using namespace std;

tbl::Table::Table(int row, int col) {
    this->row = row;
    this->col = col;

    this->type = FIRST_BOTH;
}

