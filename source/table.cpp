#include "../include/include.hpp"

std::string horizontalLine(int);
std::string innerHorizontalLine(std::vector<table::Cell>);
std::string rowToString(std::vector<table::Cell>);
std::vector<table::Cell> createRow(int);

namespace table
{
Table::Table(int row, int col)
{
    this->rows = std::vector<std::vector<table::Cell>>();
    auto rowCount = std::max(row, 1);
    auto colCount = std::max(col, 1);
    this->resize(rowCount, colCount);
}
Table::~Table()
{
}

table::Cell* Table::getCell(int r, int c)
{
    return &(this->rows[r][c]);
}

void Table::resize(int newRowCount, int newColCount)
{
    if (newRowCount <= 0 || newColCount <= 0)
        return;

    while (this->rows.size() < newRowCount)
        this->rows.push_back(createRow(newColCount));
    while (this->rows.size() > newRowCount)
        this->rows.erase(this->rows.end());

    for (auto row : this->rows)
    {
        row.resize(newColCount);
        while (row.size() > newColCount)
            row.erase(row.end());
    }
    this->updateTableInfo();
}
void Table::updateTableInfo()
{
    this->rowCount = this->rows.size();
    this->colCount = this->rows[0].size();

    for (auto i = 0; i < this->colCount; i++)
    {
        auto colWidth = 0;
        for (auto j = 0; j < this->rowCount; j++)
            colWidth = std::max(this->getCell(j, i)->getWidth(), colWidth);

        for (auto j = 0; j < this->rowCount; j++)
            this->getCell(j, i)->setWidth(colWidth);
    }

    this->width = this->calculateWidth();
}

int Table::calculateWidth()
{
    int w = 1;
    for (auto c : this->rows[0])
        w += c.getWidth() + 1;
    return w;
}

std::string Table::toString()
{
    this->updateTableInfo();
    std::string table = horizontalLine(this->width);

    for (auto i = 0; i < this->rows.size(); i++)
    {
        table += rowToString(rows[i]);
        if (i != this->rows.size() - 1)
            table += innerHorizontalLine(rows[i]);
    }

    table += horizontalLine(this->width);

    return table;
}
}

std::string horizontalLine(int length)
{
    std::string l = "+";
    for (auto i = 1; i < length - 1; i++)
        l += '-';
    return (l += "+\n");
}

std::string innerHorizontalLine(std::vector<table::Cell> cells)
{
    // TODO: implement
    auto i = 1;
    for (auto c : cells)
        i += c.getWidth() + 1;
    return horizontalLine(i);
}

std::vector<table::Cell> createRow(int size)
{
    auto vec = std::vector<table::Cell>();
    for (auto i = 0; i < size; i++)
        vec.push_back(table::Cell());
    return vec;
}

int calculateRowHeight(std::vector<table::Cell> row)
{
    int h = 0;
    for (auto c : row)
        h = std::max(c.getHeight(), h);
    return h;
}

std::string rowToString(std::vector<table::Cell> cells)
{
    auto h = calculateRowHeight(cells);

    auto vec = std::vector<std::vector<std::string>>();
    std::string str = "";
    for (auto c : cells)
    {
        c.setHeight(h);
        vec.push_back(c.toVector());
    }
    for (auto r = 0; r < h; r++)
    {
        str += "|";
        for (auto c = 0; c < cells.size(); c++)
        {
            str += vec[c][r];
            str += "|";
        }
        str += "\n";
    }
    return str;
}
