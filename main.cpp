#include <iostream>
#include <string>
#include <vector>

#include "SQLLibrary.h"

using namespace std;

int main () {
    //SQL_Query("CREATE TABLE table (id INT, name TEXT)");
    vector<string> names{"Dallin", "Ryan", "Madaleine", "Seth", "Mike"};
    stringstream ss;
    for (int i = 0; i < (int)names.size(); ++i) {
        ss << "INSERT INTO table (id, name) VALUES (" << i << ",'" << names.at(i) << "')";
        SQL_Query(ss.str());
        ss.str( std::string() );
        ss.clear();
    }
    
    return 0;
}