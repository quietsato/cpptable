#include "../include/include.hpp"

int cellTest();
int tableTest();

int main(void)
{
    if (cellTest() == -1){
        std::cerr << "Cell Test Failure..." << std::endl;
        return -1;
    }
    std::cout << "Cell Test Passed!\n" << std::endl;
    
    if(tableTest() == -1){
        std::cerr << "Table Test Failure..." << std::endl;
        return -1;
    }
    std::cout << "Table Test Passed!\n" << std::endl;

    std::cout << '\n' << "All Test Passed!" << std::endl;
    return 0;
}

template <typename T>
bool testMan(std::string description, T output, T expected)
{
    if (output == expected)
    {
        std::cout << description << ": OK!" << std::endl;
        return true;
    }
    std::cerr << description << ": Failed..." << std::endl;
    std::cerr << "Output: " << output << std::endl;
    return false;
}

int cellTest()
{
    std::string testStr = "12345\n1234\n123\n12\n1\n";
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
    return 0;
}

int tableTest(){
    auto t = table::Table(3, 4);
    for(auto i = 0; i < 3; i++){
        for(auto j = 0; j < 4; j++){
            t.getCell(i, j)->setValue("Hello World\nunko");
            if(i == j)
                t.getCell(i, j)->setValue(std::to_string(i) + std::to_string(j));
        }
    }
    std::cout << t.toString() << std::endl;
    return 0;
}