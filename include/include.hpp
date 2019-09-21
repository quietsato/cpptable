#ifndef INCLUDE_HPP
#define INCLUDE_HPP

#include <algorithm>
#include <array>
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

enum BorderPosition
{
    TOP = 0,
    BOTTOM = 1,
    LEFT = 2,
    RIGHT = 3
};

class Border
{
private:
    int rowCount;
    int colCount;
    void updateBorderInfo();
    std::vector<std::vector<bool>> hBorders;
    std::vector<std::vector<bool>> vBorders;

public:
    Border(int, int);
    ~Border();
    void resize(int, int);
    std::array<bool, 4> getBorder(int, int);
    void setBorder(int, int, BorderPosition, bool);
};

class Table : public Border
{
private:
    std::vector<std::vector<table::Cell>> rows;
    std::string outerHorizontalLine();
    std::string innerHorizontalLine(int);
    std::string rowToString(int);
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