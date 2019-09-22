#include "../include/include.hpp"

int cellTest();
int tableTest();

int main(void) {
  if (cellTest() == -1) {
    std::cerr << "Cell Test Failure..." << std::endl;
    return -1;
  }
  std::cout << "Cell Test Passed!\n" << std::endl;

  if (tableTest() == -1) {
    std::cerr << "Table Test Failure..." << std::endl;
    return -1;
  }
  std::cout << "Table Test Passed!\n" << std::endl;

  std::cout << "All Test Passed!" << std::endl;
  return 0;
}

template <typename T>
bool testMan(std::string description, T output, T expected) {
  if (output == expected) {
    std::cout << description << ": OK!" << std::endl;
    return true;
  }
  std::cerr << description << ": Failed..." << std::endl;
  std::cerr << "Output: " << output << std::endl;
  return false;
}

int cellTest() {
  std::string testStr = "12345\n1234\n123\n12\n1\n";
  auto testVec = std::vector<std::string>();
  testVec.push_back("12345");
  testVec.push_back("1234 ");
  testVec.push_back("123  ");
  testVec.push_back("12   ");
  testVec.push_back("1    ");
  testVec.push_back("     ");
  int testStrWidth = 5;
  int testStrHeight = 6;

  auto cell = table::Cell();
  cell.setValue(testStr);
  if (!testMan<std::string>("cell.getValue()", cell.getValue(), testStr))
    return -1;
  if (!testMan<int>("cell.getWidth()", cell.getWidth(), testStrWidth))
    return -1;
  if (!testMan<int>("cell.getHeight()", cell.getHeight(), testStrHeight))
    return -1;
  bool vecEq = true;
  std::vector<std::string> resVec = cell.toVector();
  for (int i = 0; i < testVec.size() && vecEq; i++)
    vecEq = (testVec[i] == resVec[i]);
  if (!testMan<bool>("cell.toVector()", vecEq, true))
    return -1;

  testStr = "123";
  testStrWidth = 3;
  testStrHeight = 1;
  cell.setValue(testStr);
  if (!testMan<std::string>("cell.getValue()", cell.getValue(), testStr))
    return -1;
  if (!testMan<int>("cell.getWidth()", cell.getWidth(), testStrWidth))
    return -1;
  if (!testMan<int>("cell.getHeight()", cell.getHeight(), testStrHeight))
    return -1;

  testStr = "\n";
  testStrWidth = 0;
  testStrHeight = 2;
  cell.setValue(testStr);
  if (!testMan<std::string>("cell.getValue()", cell.getValue(), testStr))
    return -1;
  if (!testMan<int>("cell.getWidth()", cell.getWidth(), testStrWidth))
    return -1;
  if (!testMan<int>("cell.getHeight()", cell.getHeight(), testStrHeight))
    return -1;

  return 0;
}

int tableTest() {
  std::string expectedRes = "";
  expectedRes += "+-----------------------------------------------+\n";
  expectedRes += "|00         |Hello World|Hello World|Hello World|\n";
  expectedRes += "|           |0,1        |0,2        |0,3        |\n";
  expectedRes += "+-----------+-----------+-----------+-----------+\n";
  expectedRes += "|Hello World|11         |Hello World|Hello World|\n";
  expectedRes += "|1,0        |           |1,2        |1,3        |\n";
  expectedRes += "+-----------+-----------+-----------+-----------+\n";
  expectedRes += "|Hello World|Hello World|22         |Hello World|\n";
  expectedRes += "|2,0        |2,1        |           |2,3        |\n";
  expectedRes += "+-----------------------------------------------+\n";

  auto t = table::Table(3, 4);
  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 4; j++) {
      t.getCell(i, j)->setValue("Hello World\n" + std::to_string(i) + "," +
                                std::to_string(j));

      if (i == j)
        t.getCell(i, j)->setValue(std::to_string(i) + std::to_string(j));
    }
  }
  std::string res = t.toString();
  if (!testMan<std::string>("table test1", expectedRes, res))
    return -1;

  expectedRes = "";
  expectedRes += "+-----------+\n";
  expectedRes += "|Single Cell|\n";
  expectedRes += "+-----------+\n";

  t.resize(1, 1);
  t.getCell(0, 0)->setValue("Single Cell");
  res = t.toString();
  if (!testMan<std::string>("table test2", expectedRes, res))
    return -1;

  expectedRes = "";
  expectedRes += "+-----------+\n";
  expectedRes += "|0,0 0,1|0,2|\n";
  expectedRes += "+       +---+\n";
  expectedRes += "|1,0 1,1|1,2|\n";
  expectedRes += "+---+---+---+\n";
  expectedRes += "|2,0|2,1|2,2|\n";
  expectedRes += "+-----------+\n";

  t.resize(3, 3);
  for (auto i = 0; i < 3; i++) {
    for (auto j = 0; j < 3; j++) {
      t.getCell(i, j)->setValue(std::to_string(i) + "," + std::to_string(j));
      if (i < 2 && j < 2) {
        t.setBorder(i, j, table::TOP, false);
        t.setBorder(i, j, table::LEFT, false);
      }
    }
  }
  res = t.toString();
  if (!testMan<std::string>("table test3", expectedRes, res))
    return -1;

  return 0;
}
