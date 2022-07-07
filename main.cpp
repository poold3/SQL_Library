#include <iostream>
#include <string>
#include <vector>

#include "SQLLibrary.h"

using namespace std;

int main () {
    //SQL_Query("CREATE TABLE table (id INT, name TEXT)");
    vector<string> names{"Dallin", "Ryan", "Madaleine", "Seth", "Mike"};
    for (int i = 0; i < (int)names.size(); ++i) {
        SQL_Query(3, "INSERT INTO table (id, name) VALUES (*var* ,'*var*')",i,names.at(i));
    }
    
    return 0;
}