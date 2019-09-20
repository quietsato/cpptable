#include "../include/include.hpp"

int calculateWidth(std::string);
int calculateHeight(std::string);
std::string repeatSpace(int);

namespace table
{
Cell::Cell()
{
    this->setValue(" ");
}

Cell::~Cell()
{
}

int Cell::getWidth()
{
    return this->width;
}

int Cell::getHeight()
{
    return this->height;
}

std::string Cell::getValue()
{
    return this->value;
}

void Cell::setWidth(int w)
{
    this->width = std::max(w, calculateWidth(this->value));
}

void Cell::setHeight(int h)
{
    this->height = std::max(h, calculateHeight(this->value));
}

void Cell::setValue(std::string v)
{
    this->value = v;
    this->setWidth(-1);
    this->setHeight(-1);
}

void Cell::setValueWithoutResize(std::string v)
{
    this->value = v;
    this->setWidth(this->width);
    this->setHeight(this->height);
}

std::vector<std::string> Cell::toVector()
{
    auto vec = std::vector<std::string>();
    std::string line = "";
    for (char c : this->value)
    {
        if (c == '\n')
        {
            line += repeatSpace(this->width - line.size());
            vec.push_back(line);
            line = "";
        }
        else
            line += c;
    }
    while ((int)vec.size() < this->height)
    {
        line += repeatSpace(this->width - (int)line.size());
        vec.push_back(line);
        line = "";
    }
    return vec;
}
}

int calculateWidth(std::string s)
{
    unsigned int width = 0, maxWidth = 0;
    for (char c : s)
    {
        if (c == '\n')
        {
            maxWidth = std::max(width, maxWidth);
            width = 0;
        }
        else if (isprint(c))
            width++;
    }
    maxWidth = std::max(width, maxWidth);

    return maxWidth;
}

int calculateHeight(std::string s)
{
    return std::count(s.begin(), s.end(), '\n') + 1;
}

std::string repeatSpace(int count)
{
    std::string s = "";
    for (int i = 0; i < count; i++)
        s += ' ';
    return s;
}
