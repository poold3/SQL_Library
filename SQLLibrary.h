#ifndef SQLLIBRARY_H
#define SQLLIBRARY_H

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<queue>
#include<utility>
#include<map>
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

//Find the number of chars in the string until the end single-quote character
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

//Find the number of chars until the first non-alphnumeric character
int FindIdentifierLength(string input) {
    int index = 1;
    while (index < (int)input.length() && isalnum(input.at(index))) {
        ++index;
    }
    return index;
}

//Find the number of chars until the first non-numeric character
int FindIntLength(string input) {
    int index = 1;
    while (index < (int)input.length() && isdigit(input.at(index))) {
        ++index;
    }
    return index;
}

//A basic scanner to assign tokens to the SQL_Query Input
queue<Token> GetTokens(string input) {
    queue<Token> tokens;
    int size;
    string type;
    while(input.length() > 0) {
        if (input.at(0) == ',') {
            size = 1;
            type = "Comma";
        }
        else if (input.at(0) == '.') {
            size = 1;
            type = "Period";
        }
        else if (input.at(0) == '*') {
            size = 1;
            type = "Star";
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
            type = "TEXT";
        }
        else if (isalpha(input.at(0))) {
            size = FindIdentifierLength(input);
            type = "Identifier";
        }
        else if (isdigit(input.at(0))) {
            size = FindIntLength(input);
            type = "INT";
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

//Return the table name provided in the SQL_Query Input
string GetTableName(queue<Token> &tokens) {
    string tableName = MatchToken("Identifier", tokens);
    tableName += ".txt";
    return tableName;
}

//Verifies that the front token in the queue is of the correct type.
string MatchToken(string type, queue<Token> &tokens) {
    if (tokens.size() == 0) {
        Throw_Error("Missing Input!");
    }
    else if (tokens.front().GetType() != type) {
        stringstream ss;
        ss << "Invalid Sql Input: " << type;
        Throw_Error(ss.str());
    }
    return tokens.front().GetValue();
}

//Returns the column name order of a table in a vector
vector<string> GetTableFieldsOrder(string tableName) {
    vector<string> fields;
    ifstream inFile;
    inFile.open(tableName);
    if (!inFile.is_open()) {
        stringstream ss;
        ss << "Unable to open table: " << tableName;
        Throw_Error(ss.str());
    }
    string fieldsLine;
    getline(inFile, fieldsLine);
    queue<Token> tokens = GetTokens(fieldsLine);
    while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
        string temp;
        temp = MatchToken("Identifier", tokens);
        tokens.pop();
        MatchToken("Datatype", tokens);
        tokens.pop();
        MatchToken("Comma", tokens);
        tokens.pop();
        fields.push_back(temp);
    }
    inFile.close();
    return fields;
}

//Returns each column name along with its datatype in a map
map<string,string> GetTableFieldsMap(string tableName) {
    map<string, string> fields;
    ifstream inFile;
    inFile.open(tableName);
    if (!inFile.is_open()) {
        stringstream ss;
        ss << "Unable to open table: " << tableName;
        Throw_Error(ss.str());
    }
    string fieldsLine;
    getline(inFile, fieldsLine);
    queue<Token> tokens = GetTokens(fieldsLine);
    while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
        pair<string, string> temp;
        temp.first = MatchToken("Identifier", tokens);
        tokens.pop();
        temp.second = MatchToken("Datatype", tokens);
        tokens.pop();
        MatchToken("Comma", tokens);
        tokens.pop();
        fields.insert(temp);
    }
    inFile.close();
    return fields;
}

//Makes sure that a columnName is present in the table columns
void VerifyColumnName(string columnName, map<string,string> &fields) {
    if (fields.find(columnName) == fields.end()) {
        stringstream ss;
        ss << "Column '" << columnName << "' does not exist";
        Throw_Error(ss.str());
    }
}

//Appends a new row onto a table
void AppendToTable(string tableName, string newLine) {
    ofstream outFile;
    outFile.open(tableName, ios_base::app);
    if (!outFile.is_open()) {
        stringstream ss;
        ss << "Unable to write to " << tableName;
        Throw_Error(ss.str());
    }
    outFile.write(newLine.data(), newLine.size());
    outFile.close();
}

void SQL_Query(string query) {

    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    
    //Determine which operation is being performed
    if (tokens.front().GetType() == "Create") {
        tokens.pop();
        
        //Create new table
        string tableName = GetTableName(tokens);
        ofstream outFile;
        outFile.open(tableName);
        if (!outFile.is_open()) {
            stringstream ss;
            ss << "Unable to create new table: " << tableName;
            Throw_Error(ss.str());
        }
        tokens.pop();

        //Read in column names and datatypes
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
        tokens.pop();

        //Read fields from table
        string tableName = GetTableName(tokens);
        map<string, string> fields = GetTableFieldsMap(tableName);
        vector<string> fieldOrder = GetTableFieldsOrder(tableName);
        tokens.pop();

        //If column names to insert into are provided, read them in.
        //Otherwise, the column names to insert into are the same as the columns in the table in that order
        vector<string> columnsToInsert;
        if (tokens.front().GetType() == "Left-Paren") {
            MatchToken("Left-Paren", tokens);
            tokens.pop();

            //Verify that column names in query match those in table fields
            while (tokens.size() > 0 && tokens.front().GetType() != "Right-Paren") {
                if (columnsToInsert.size() > 0) {
                    MatchToken("Comma", tokens);
                    tokens.pop();
                }
                string columnName = MatchToken("Identifier", tokens);
                tokens.pop();
                VerifyColumnName(columnName, fields);
                columnsToInsert.push_back(columnName);
            }

            MatchToken("Right-Paren", tokens);
            tokens.pop();
        }
        else {
            columnsToInsert = fieldOrder;
        }
        

        MatchToken("Values", tokens);
        tokens.pop();

        MatchToken("Left-Paren", tokens);
        tokens.pop();

        //Read in values to insert. Store in map along with column names
        map<string,string> columnAndValues;
        while (tokens.size() > 0 && tokens.front().GetType() != "Right-Paren") {
            if (columnAndValues.size() > 0) {
                MatchToken("Comma", tokens);
                tokens.pop();
            }
            string value;
            string type;
            if (tokens.front().GetType() == "INT") {
                //Turn all decimals into hex before storing
                value = DecimalToHex(MatchToken("INT", tokens));
                type = "INT";
            }
            else if (tokens.front().GetType() == "TEXT") {
                value = MatchToken("TEXT", tokens);
                type = "TEXT";
            }
            else {
                stringstream ss;
                ss << "Invalid datatype: " << tokens.front().GetValue() << " is not a valid datatype";
                Throw_Error(ss.str());
            }
            tokens.pop();

            //Ensure that the datatype of the column matches the datatype of the value being inserted
            if (fields.at(columnsToInsert.at(columnAndValues.size())) == type) {
                columnAndValues.insert(pair<string,string>(columnsToInsert.at(columnAndValues.size()), value));
            }
            else {
                stringstream ss;
                ss << "Invalid datatype: Column '" << columnsToInsert.at(columnAndValues.size()) << "' cannot accept the value " << value;
                Throw_Error(ss.str());
            }
        }

        //If the number of columns to insert into does not match the number of values provided, throw an error
        if (columnsToInsert.size() != columnAndValues.size()) {
            Throw_Error("Incorrect number of columns");
        }

        MatchToken("Right-Paren", tokens);
        tokens.pop();

        //Take our map of columns and new values and create the append string
        stringstream ss;
        map<string,string>::iterator it;

        for (string field : fieldOrder) {
            it = columnAndValues.find(field);
            if (it != columnAndValues.end()) {
                ss << it->second << ",";
            }
            else {
                ss << "NULL,";
            }
        }
        ss << "." << endl;

        //Append to table
        AppendToTable(tableName, ss.str());

    }
    else if (tokens.front().GetType() == "Select") {
        tokens.pop();

        //Read fields from table
        string tableName = GetTableName(tokens);
        map<string, string> fields = GetTableFieldsMap(tableName);
        vector<string> fieldOrder = GetTableFieldsOrder(tableName);
        tokens.pop();
        
    }
    else if (tokens.front().GetType() == "Delete") {

    }
    else {
        Throw_Error("Invalid SQL Operation!");
    }
    return;
}











#endif