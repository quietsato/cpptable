#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <algorithm>
#include <iostream>
#include <vector>

namespace table
{
class Cell
{
private:
    int width;
    int height;
    std::string value;

public:
    Cell();
    ~Cell();

    int getWidth();
    int getHeight();
    std::string getValue();
    void setWidth(int);
    void setHeight(int);
    void setValue(std::string);
    void setValueWithoutResize(std::string);
    std::vector<std::string> toVector();
};

class Table
{
private:
    std::vector<std::vector<table::Cell>> rows;
    void updateTableInfo();
    int calculateWidth();
    int rowCount;
    int colCount;
    int width;

public:
    Table(int, int);
    ~Table();
    void resize(int, int);
    table::Cell* getCell(int, int);
    std::string toString();
    int getRowCount();
    int getColCount();
};
}

#endif