#include <iostream>
#include <string>
#include <vector>

#include "SQLLibrary.h"

using namespace std;

int main () {
    SQL_Query("INSERT INTO table (id, name) VALUES (1, 'Dallin')");
    return 0;
}