#include <iostream>
#include <string>
#include <vector>

#include "SQLLibrary.h"

using namespace std;

int main () {
    //SQL_Query("CREATE TABLE table (id INT, name TEXT)");
    SQL_Query("SELECT * FROM table");
    
    return 0;
}