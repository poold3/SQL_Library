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
    SQL_Query_Results results = SQL_Query_Select("SELECT id,name FROM table WHERE name = 'Dallin' ORDER BY age ASC");
    for (map<string,string>row : results) {
        cout << row.at("id") << " " << row.at("name") << endl;
    }
    */
    //SQL_Query_Delete("DELETE FROM table WHERE id <= 3");
    //SQL_Query_Update("UPDATE table SET name = 'YOUNG' WHERE age <> 22");
    
    SQL_Query_Results results = SQL_Query_Select("SELECT id AS employeeID,name AS title FROM table ORDER BY employeeID ASC, name DESC");

    for (map<string,string>row : results) {
        cout << row.at("employeeID") << " " << row.at("title") << endl;
    }
    return 0;
}