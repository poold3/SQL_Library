#ifndef SQLLIBRARY_H
#define SQLLIBRARY_H

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<queue>
#include<ctype.h>

using namespace std;

class Token {
    private:
    string type;
    string value;
    public:
    Token(string type, string value) {
        this->type = type;
        if (type == "Text" && value.at(0) == '\'') {
            value = value.substr(1);
            value = value.substr(0, value.length() - 1);
        }
        this->value = value;
    }

    Token() {}

    string GetType() {
        return type;
    }

    string GetValue() {
        return value;
    }
};


void Throw_Error(string message) {
    throw std::invalid_argument(message);
}

string DecimalToHex(int decimalNumber) {
    stringstream ss;
    if (decimalNumber < 0) {
        decimalNumber *= -1;
        ss << "-";
    }
    ss << std::hex << decimalNumber;
    return ss.str();
}

string DecimalToHex(string decimalNumber) {
    stringstream ss;
    if (decimalNumber.at(0) == '-') {
        ss << "-";
        decimalNumber = decimalNumber.substr(1);
    }
    ss << std::hex << stoi(decimalNumber);
    return ss.str();
}

int HexToDecimal(string hexNumber) {
    stringstream ss;
    if (hexNumber.at(0) == '-') {
        ss << "-";
        hexNumber = hexNumber.substr(1);
    }
    int decimalNumber;
    ss << std::hex << hexNumber;
    ss >> decimalNumber;
    return (decimalNumber);
}

int FindTextLength(string input) {
    int index = 1;
    //Find the size of the text between single quotes.
    while (input.at(index) != '\'' || (input.at(index) == '\'' && input.at(index - 1) == '\\')) {
        ++index;
        if (index == (int)(input.length() - 1)) {
            Throw_Error("Missing end quote!");
        }
    }
    ++index;
    return index;
}

int FindIdentifierLength(string input) {
    int index = 1;
    while (index < (int)input.length() && isalnum(input.at(index))) {
        ++index;
    }
    return index;
}

int FindIntLength(string input) {
    int index = 1;
    while (index < (int)input.length() && isdigit(input.at(index))) {
        ++index;
    }
    return index;
}

queue<Token> GetTokens(string input) {
    queue<Token> tokens;
    int size;
    string type;
    while(input.length() > 0) {
        if (input.at(0) == ',') {
            size = 1;
            type = "Comma";
        }
        else if (input.at(0) == '(') {
            size = 1;
            type = "Left-Paren";
        }
        else if (input.at(0) == ')') {
            size = 1;
            type = "Right-Paren";
        }
        else if (input.at(0) == '=') {
            size = 1;
            type = "Equal";
        }
        else if (input.substr(0, 2) == "<>" || input.substr(0, 2) == "!=") {
            size = 2;
            type = "Not Equal";
        }
        else if (input.at(0) == '>') {
            if (input.substr(0, 2) == ">=") {
                size = 2;
                type = "Greater or Equal";
            }
            else {
                size = 1;
                type = "Greater";
            }
        }
        else if (input.at(0) == '<') {
            if (input.substr(0, 2) == "<=") {
                size = 2;
                type = "Less or Equal";
            }
            else {
                size = 1;
                type = "Less";
            }
        }
        else if (input.substr(0, 6) == "SELECT") {
            size = 6;
            type = "Select";
        }
        else if (input.substr(0, 12) == "CREATE TABLE") {
            size = 12;
            type = "Create";
        }
        else if (input.substr(0, 11) == "INSERT INTO") {
            size = 11;
            type = "Insert";
        }
        else if (input.substr(0, 6) == "UPDATE") {
            size = 6;
            type = "Update";
        }
        else if (input.substr(0, 11) == "DELETE FROM") {
            size = 11;
            type = "Delete";
        }
        else if (input.substr(0, 3) == "SET") {
            size = 3;
            type = "Set";
        }
        else if (input.substr(0, 3) == "AND") {
            size = 3;
            type = "And";
        }
        else if (input.substr(0, 2) == "OR") {
            size = 2;
            type = "Or";
        }
        else if (input.substr(0, 4) == "FROM") {
            size = 4;
            type = "From";
        }
        else if (input.substr(0, 5) == "WHERE") {
            size = 5;
            type = "Where";
        }
        else if (input.substr(0, 6) == "VALUES") {
            size = 6;
            type = "Values";
        }
        else if (input.substr(0, 4) == "LIKE") {
            size = 4;
            type = "Like";
        }
        else if (input.substr(0, 7) == "IS NULL") {
            size = 7;
            type = "Is Null";
        }
        else if (input.substr(0, 11) == "IS NOT NULL") {
            size = 11;
            type = "Is Not Null";
        }
        else if (input.substr(0, 8) == "ORDER BY") {
            size = 8;
            type = "Order By";
        }
        else if (input.substr(0, 3) == "ASC") {
            size = 3;
            type = "Asc";
        }
        else if (input.substr(0, 4) == "DESC") {
            size = 4;
            type = "Desc";
        }
        else if (input.substr(0, 4) == "TEXT") {
            size = 4;
            type = "Datatype";
        }
        else if (input.substr(0, 3) == "INT") {
            size = 3;
            type = "Datatype";
        }
        else if (input.substr(0, 4) == "DATE") {
            size = 4;
            type = "Datatype";
        }
        else if (input.at(0) == '\'') {
            size = FindTextLength(input);
            type = "Text";
        }
        else if (isalpha(input.at(0))) {
            size = FindIdentifierLength(input);
            type = "Identifier";
        }
        else if (isdigit(input.at(0))) {
            size = FindIntLength(input);
            type = "Int";
        }
        else if (input.at(0) == ' ') {
            size = 1;
            type = "Space";
        }
        else {
            stringstream ss;
            ss << "Invalid SQL_Query Input: \'" << input.at(0) << "\'"; 
            Throw_Error(ss.str());
        }
        if (type != "Space") {
            Token temp(type, input.substr(0, size));
            tokens.push(temp);
        }
        input = input.substr(size);
    }

    return tokens;
}

string MatchToken(string type, queue<Token> &tokens) {
    if (tokens.front().GetType() != type) {
        Throw_Error("Invalid Sql Input!");
    }
    return tokens.front().GetValue();
}

void SQL_Query(string query) {
    queue<Token> tokens = GetTokens(query);

    //Determine which operation is being performed
    if (tokens.front().GetType() == "Create") {
        tokens.pop();

        //Create new table
        string tableName = MatchToken("Identifier", tokens);
        tableName += ".txt";
        ofstream outFile;
        outFile.open(tableName);
        if (!outFile.is_open()) {
            Throw_Error("Unable to create new table!");
        }
        tokens.pop();

        MatchToken("Left-Paren", tokens);
        tokens.pop();
        int numColumns = 0;
        while (tokens.size() > 0 && tokens.front().GetType() != "Right-Paren") {
            if (numColumns > 0) {
                MatchToken("Comma", tokens);
                tokens.pop();
            }
            string columnName = MatchToken("Identifier", tokens);
            tokens.pop();
            string dataType = MatchToken("Datatype", tokens);
            tokens.pop();
            outFile << columnName << " " << dataType << ",";
            ++numColumns;
        }
        MatchToken("Right-Paren", tokens);
        tokens.pop();
        outFile << "." << endl;
        outFile.close();
    }
    else if (tokens.front().GetType() == "Update") {

    }
    else if (tokens.front().GetType() == "Insert") {

    }
    else if (tokens.front().GetType() == "Select") {

    }
    else if (tokens.front().GetType() == "Delete") {

    }
    else {
        Throw_Error("Invalid SQL Operation!");
    }
    return;
}











#endif