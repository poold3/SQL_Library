#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "SQLLibrary.h"

using namespace std;

int main () {
    /*
    SQL_Query("CREATE TABLE table (id INT, name TEXT)");
    vector<string> names {"Dallin", "Kelly", "Samuel", "Taylor", "Olivia", "Francis", "Julia", "Trevor", "Heather"};
    int nameId = 1;
    for (string name: names) {
        stringstream ss;
        ss << "INSERT INTO table VALUES (" << nameId << ",'" << names.at(nameId - 1) << "')";
        SQL_Query(ss.str());
        ++nameId;
        TEST
    }
    SQL_Query_Results results = SQL_Query_Select("SELECT id,name FROM table WHERE name = 'Dallin' ORDER BY age DESC");
    */
    SQL_Query_Update("UPDATE table SET name = 'New', id = 10 WHERE age = 50");
    
    return 0;
}