#ifndef SQLLIBRARY_H
#define SQLLIBRARY_H

#include<string>
#include<iostream>

using namespace std;

void Throw_Error(string message) {
    throw std::invalid_argument(message);
}

string DecimalToHex(string decimalNumber) {

}

string HexToDecimal(string hexNumber) {
    
}

void SQL_Query(string query) {
    //Determine what operation is being performed
    if (query.substr(0, 13) == "CREATE TABLE ") {

    }
    else if (query.substr(0, 7) == "SELECT ") {

    }
    else if (query.substr(0, 12) == "INSERT INTO ") {

    }
    else if (query.substr(0, 7) == "UPDATE ") {

    }
    else if (query.substr(0, 12) == "DELETE FROM ") {

    }
    else {
        Throw_Error("Invalid SQL Operation!");
    }
    return;
}











#endif