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
    }
    */
    SQL_Query_Results results = SQL_Query_Select("SELECT DISTINCT id,name FROM table");
    
    cout << results.size() << " rows returned." << endl;
    for (map<string,string> row: results) {
        cout << row.at("id") << " " << row.at("name") << endl;
    }
    
    return 0;
}