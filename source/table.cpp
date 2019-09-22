#include "../include/include.hpp"

std::string horizontalLine(int, char);
std::string rowToString(std::vector<table::Cell>);
int calculateRowHeight(std::vector<table::Cell>);
std::vector<table::Cell> createRow(int);

namespace table {
Table::Table(int row, int col) : Border::Border(row, col) {
  this->rows = std::vector<std::vector<table::Cell>>();
  auto rowCount = std::max(row, 1);
  auto colCount = std::max(col, 1);
  this->resize(rowCount, colCount);
}
Table::~Table() {}

table::Cell *Table::getCell(int r, int c) { return &(this->rows[r][c]); }

void Table::resize(int newRowCount, int newColCount) {
  if (newRowCount <= 0 || newColCount <= 0)
    return;

  Border::resize(newRowCount, newColCount);

  while (this->rows.size() < newRowCount)
    this->rows.push_back(createRow(newColCount));
  while (this->rows.size() > newRowCount)
    this->rows.pop_back();

  for (auto row : this->rows) {
    while (row.size() < newColCount)
      row.push_back(table::Cell());
    while (row.size() > newColCount)
      row.pop_back();
  }
  this->updateTableInfo();
}
void Table::updateTableInfo() {
  this->rowCount = this->rows.size();
  this->colCount = this->rows[0].size();

  for (auto i = 0; i < this->colCount; i++) {
    auto colWidth = 0;
    for (auto j = 0; j < this->rowCount; j++)
      colWidth = std::max(this->getCell(j, i)->getWidth(), colWidth);

    for (auto j = 0; j < this->rowCount; j++)
      this->getCell(j, i)->setWidth(colWidth);
  }

  this->width = this->calculateWidth();
}

int Table::calculateWidth() {
  int w = 1;
  for (auto c : this->rows[0])
    w += c.getWidth() + 1;
  return w;
}

std::string Table::toString() {
  this->updateTableInfo();
  std::string table = outerHorizontalLine();

  for (auto i = 0; i < this->rows.size(); i++) {
    table += rowToString(i);
    if (i != this->rows.size() - 1)
      table += innerHorizontalLine(i);
  }

  table += outerHorizontalLine();

  return table;
}

std::string Table::innerHorizontalLine(int r) {
  std::string l = "+";

  for (auto c = 0; c < this->rows[r].size(); c++) {
    if (this->getBorder(r, c)[BOTTOM])
      l += horizontalLine(rows[r][c].getWidth(), '-');
    else
      l += horizontalLine(rows[r][c].getWidth(), ' ');

    if (c == this->rows[r].size() - 1)
      break;

    if (c == this->rows[r].size() - 1 || r == this->rows.size() - 1 ||
        this->getBorder(r, c)[BOTTOM] || this->getBorder(r, c + 1)[BOTTOM] ||
        this->getBorder(r, c)[RIGHT] || this->getBorder(r + 1, c)[RIGHT])
      l += '+';
    else
      l += ' ';
  }

  return (l += "+\n");
}
std::string Table::outerHorizontalLine() {
  std::string l = "+";
  l += horizontalLine(this->width - 2, '-');
  return l += "+\n";
}
std::string Table::rowToString(int r) {
  auto h = calculateRowHeight(this->rows[r]);

  auto vec = std::vector<std::vector<std::string>>();
  std::string str = "";
  for (auto c : this->rows[r]) {
    c.setHeight(h);
    vec.push_back(c.toVector());
  }
  for (auto i = 0; i < h; i++) {
    str += "|";
    for (auto c = 0; c < this->rows[r].size(); c++) {
      str += vec[c][i];
      if (c == this->rows[r].size() - 1)
        break;
      if (this->getBorder(r, c)[RIGHT])
        str += "|";
      else
        str += " ";
    }
    str += "|\n";
  }
  return str;
}
} // namespace table

std::vector<table::Cell> createRow(int size) {
  auto vec = std::vector<table::Cell>();
  for (auto i = 0; i < size; i++)
    vec.push_back(table::Cell());
  return vec;
}

int calculateRowHeight(std::vector<table::Cell> row) {
  int h = 0;
  for (auto c : row)
    h = std::max(c.getHeight(), h);
  return h;
}

std::string horizontalLine(int length, char c) {
  std::string l = "";
  for (auto i = 0; i < length; i++)
    l += c;
  return l;
}
