#include <iostream>
#include "table.h"
using namespace std;
using namespace tbl;

int main() {
    auto t = Table(10, 10);

    vector<string> line;
    int mul;
    for(int i = 0; i <= 9; i++){
      for(int j = 0; j <= 9; j++){
        if(i == 0 && j == 0){
          line.push_back("  ");
        }
        else if(i == 0 || j == 0){
          line.push_back(to_string(max(i, j)).insert(0, " "));
        }
        else{
          mul = i * j;
          if(mul < 10)
            line.push_back(to_string(mul).insert(0, " "));
          else
            line.push_back(to_string(mul));
        }
      }
      t.add_row(line);
      line.clear();
    }

    t.show();

    t.setStyle(ALL);

    t.show();

    t.setStyle(COL_TITLE);

    t.show();

    t.setStyle(ROW_TITLE);

    t.show();

    t = Table(1, 1);
    t.add_row(vector<string>{"Hello"});
    t.show();

    return 0;
}