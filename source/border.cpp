#include "../include/include.hpp"

namespace table {
Border::Border(int r, int c) {
  this->hBorders = std::vector<std::vector<bool>>();
  this->vBorders = std::vector<std::vector<bool>>();
  this->resize(r, c);
}
Border::~Border() {}
void Border::updateBorderInfo() {
  this->rowCount = this->vBorders.size();
  this->colCount = this->hBorders.size();
}
void Border::resize(int newRowCount, int newColCount) {
  newRowCount = std::max(newRowCount, 1);
  newColCount = std::max(newColCount, 1);

  while (this->vBorders.size() < newRowCount)
    this->vBorders.push_back(std::vector<bool>(newColCount + 1, true));
  while (this->vBorders.size() > newRowCount)
    this->vBorders.pop_back();

  while (this->hBorders.size() < newRowCount + 1)
    this->hBorders.push_back(std::vector<bool>(newColCount, true));
  while (this->hBorders.size() > newRowCount + 1)
    this->hBorders.pop_back();

  for (auto hRow : this->hBorders) {
    while (hRow.size() < newColCount)
      hRow.push_back(true);
    while (hRow.size() > newColCount)
      hRow.pop_back();

    for (auto vRow : this->vBorders) {
      while (vRow.size() < newColCount + 1)
        vRow.push_back(true);
      while (vRow.size() > newColCount + 1)
        vRow.pop_back();
    }
  }

  this->updateBorderInfo();
}
std::array<bool, 4> Border::getBorder(int r, int c) {
  auto a = std::array<bool, 4>();
  a[TOP] = this->hBorders[r][c];
  a[BOTTOM] = this->hBorders[r + 1][c];
  a[LEFT] = this->vBorders[r][c];
  a[RIGHT] = this->vBorders[r][c + 1];
  return a;
}
void Border::setBorder(int r, int c, BorderPosition p, bool b) {
  if (r < 0 || r >= this->rowCount || c < 0 || c >= this->colCount)
    return;
  switch (p) {
  case TOP:
    this->hBorders[r][c] = b;
    break;
  case BOTTOM:
    this->hBorders[r + 1][c] = b;
    break;
  case LEFT:
    this->vBorders[r][c] = b;
    break;
  case RIGHT:
    this->vBorders[r][c + 1] = b;
    break;
  default:
    break;
  }
}
} // namespace table