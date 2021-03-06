#ifndef SQLLIBRARY_H
#define SQLLIBRARY_H

#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<ctype.h>

using namespace std;

typedef vector<map<string,string>> SQL_Query_Results;
SQL_Query_Results undefined;
map<string,string> undefinedMap;
class Token {
    private:
    string type;
    string value;
    public:
    Token(string type, string value) {
        this->type = type;
        this->value = value;
    }

    Token() {}

    string GetType() {
        return type;
    }

    string GetValue() {
        return value;
    }

    void SetValue(string value) {
        this->value = value;
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

string HexToDecimal(string hexNumber) {
    stringstream ss;
    if (hexNumber.at(0) == '-') {
        ss << "-";
        hexNumber = hexNumber.substr(1);
    }
    int decimalNumber;
    ss << std::hex << hexNumber;
    ss >> decimalNumber;
    return (to_string(decimalNumber));
}

string RemoveSingleQuotes(string value) {
    value = value.substr(1);
    value = value.substr(0, value.length() - 1);
    return value;
}

//Find the number of chars in the string until the end single-quote character
int FindTextLength(string input) {
    int index = 1;
    //Find the size of the text between single quotes.
    while (input.at(index) != '\'') {
        if (index == (int)(input.length() - 1)) {
            Throw_Error("Missing end quote!");
        }
        ++index;
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
    while (index < (int)input.length() && isalnum(input.at(index))) {
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
            type = "Logic";
        }
        else if (input.substr(0, 2) == "<>" || input.substr(0, 2) == "!=") {
            size = 2;
            type = "Logic";
        }
        else if (input.at(0) == '>') {
            if (input.substr(0, 2) == ">=") {
                size = 2;
                type = "Logic";
            }
            else {
                size = 1;
                type = "Logic";
            }
        }
        else if (input.at(0) == '<') {
            if (input.substr(0, 2) == "<=") {
                size = 2;
                type = "Logic";
            }
            else {
                size = 1;
                type = "Logic";
            }
        }
        else if (input.substr(0, 6) == "SELECT") {
            size = 6;
            type = "Select";
        }
        else if (input.substr(0, 8) == "DISTINCT") {
            size = 8;
            type = "Distinct";
        }
        else if (input.substr(0, 3) == "AS ") {
            size = 2;
            type = "As";
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
        else if (input.substr(0, 4) == "AND ") {
            size = 3;
            type = "And";
        }
        else if (input.substr(0, 3) == "OR ") {
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

//Verifies that the token is of the correct type.
string MatchToken(string type, Token token) {
    if (token.GetType() != type) {
        stringstream ss;
        ss << "Invalid Sql Input. Expected " << type << ". Received " << token.GetType() << ": " << token.GetValue();
        Throw_Error(ss.str());
    }
    return token.GetValue();
}

//Verifies that the front token in the queue is of the correct type.
string MatchToken(string type, queue<Token> &tokens) {
    if (tokens.size() == 0) {
        Throw_Error("Missing Input!");
    }
    else if (tokens.front().GetType() != type) {
        stringstream ss;
        ss << "Invalid Sql Input. Expected " << type << ". Received " << tokens.front().GetType() << ": " << tokens.front().GetValue();
        Throw_Error(ss.str());
    }
    return tokens.front().GetValue();
}

//Return the table name provided in the SQL_Query Input
string GetTableName(queue<Token> &tokens) {
    string tableName = MatchToken("Identifier", tokens);
    tableName += ".txt";
    return tableName;
}

//Return every table column and its position stored in a map
map<string,int> GetTableFieldsOrderMap(string tableName) {
    map<string,int> fields;
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
    int columnNumber = 0;
    while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
        string temp;
        temp = MatchToken("Identifier", tokens);
        tokens.pop();
        MatchToken("Datatype", tokens);
        tokens.pop();
        MatchToken("Comma", tokens);
        tokens.pop();
        fields.insert(pair<string,int>(temp, columnNumber));
        ++columnNumber;
    }
    inFile.close();
    return fields;
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

string ConditionEval(string realValue, string condition, string testValue, string dataType) {
    if (condition == "=") {
        if (realValue == testValue) {
            return "True";
        }
    }
    else if (condition == "<>" || condition == "!=") {
        if (realValue != testValue) {
            return "True";
        }
    }
    else {
        int realValueInt;
        int testValueInt;
        if (dataType == "INT") {
            //Convert both values into integers
            stringstream ss;
            ss << realValue << " " << testValue;
            ss >> realValueInt >> testValueInt;
        }
        if (condition == "<") {
            if (dataType == "INT" && realValueInt < testValueInt) {
                return "True";
            }
            else if (dataType == "TEXT" && realValue < testValue) {
                return "True";
            }
        }
        else if (condition == "<=") {
            if (dataType == "INT" && realValueInt <= testValueInt) {
                return "True";
            }
            else if (dataType == "TEXT" && realValue <= testValue) {
                return "True";
            }
        }
        else if (condition == ">") {
            if (dataType == "INT" && realValueInt > testValueInt) {
                return "True";
            }
            else if (dataType == "TEXT" && realValue > testValue) {
                return "True";
            }
        }
        else if (condition == ">=") {
            if (dataType == "INT" && realValueInt >= testValueInt) {
                return "True";
            }
            else if (dataType == "TEXT" && realValue >= testValue) {
                return "True";
            }
        }
    }
    
    return "False";
}

//Calculate where a table row meets the WHERE requirements
vector<Token> RunConditionEval(queue<Token> tokens, vector<Token> whereTokens, map<string,int> &fieldOrder, map<string,string> &fields) {
    //Construct vector of tokens that contain only the values from the row
    vector<string> rowValues;
    while (tokens.size() > 0) {
        if (tokens.front().GetType() != "Comma" && tokens.front().GetType() != "Period") {
            rowValues.push_back(tokens.front().GetValue());
        }
        tokens.pop();
    }

    //Build new whereTokens vector with evaluated conditions: true and false values
    vector<Token> whereTokensCopy = whereTokens;
    whereTokens.clear();
    for (unsigned long i = 0; i < whereTokensCopy.size(); ++i) {
        if (i < whereTokensCopy.size() - 3 && whereTokensCopy.at(i).GetType() == "Identifier") {
            string columnName = MatchToken("Identifier", whereTokensCopy.at(i));
            string condition = MatchToken("Logic", whereTokensCopy.at(i + 1));
            string testValue = whereTokensCopy.at(i + 2).GetValue();
            string realValue = rowValues.at(fieldOrder.at(columnName));
            string dataType = fields.at(columnName);
            if (dataType == "INT") {
                realValue = HexToDecimal(realValue);
            }
            string evalResult = ConditionEval(realValue, condition, testValue, dataType);
            whereTokens.push_back(Token("Eval", evalResult));
            i += 2;
        }
        else {
            whereTokens.push_back(whereTokensCopy.at(i));
        }
    }
    whereTokensCopy.clear();

    return whereTokens;
}

bool ComputeLogic(vector<Token> tokens) {
    while (tokens.size() > 1) {
        //First, look for True/False values alone within parenthesis
        for (unsigned long i = 0; i < tokens.size(); ++i) {
            if (tokens.at(i).GetType() == "Left-Paren") {
                if (tokens.at(i + 1).GetType() == "Eval" && tokens.at(i + 2).GetType() == "Right-Paren") {
                    tokens.erase(tokens.begin() + i + 2);
                    tokens.erase(tokens.begin() + i);
                }
            }
        }

        //Look for ANDs because they have precedence over ORs
        for (unsigned long i = 0; i < tokens.size(); ++i) {
            if (tokens.at(i).GetType() == "And") {
                if (tokens.at(i - 1).GetType() == "Eval" && tokens.at(i + 1).GetType() == "Eval") {
                    string valueOne = tokens.at(i - 1).GetValue();
                    string valueTwo = tokens.at(i + 1).GetValue();
                    string newValue;
                    if (valueOne != valueTwo) {
                        newValue = "False";
                    }
                    else if (valueOne == "True") {
                        newValue = "True";
                    }
                    else {
                        newValue = "False";
                    }
                    tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 2);
                    --i;
                    tokens.insert(tokens.begin() + i, Token("Eval", newValue));
                }
            }
        }

        //Look for ORs
        for (unsigned long i = 0; i < tokens.size(); ++i) {
            if (tokens.at(i).GetType() == "Or") {
                if (tokens.at(i - 1).GetType() == "Eval" && tokens.at(i + 1).GetType() == "Eval") {
                    string valueOne = tokens.at(i - 1).GetValue();
                    string valueTwo = tokens.at(i + 1).GetValue();
                    string newValue;
                    if (valueOne == "True" || valueTwo == "True") {
                        newValue = "True";
                    }
                    else {
                        newValue = "False";
                    }
                    tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 2);
                    --i;
                    tokens.insert(tokens.begin() + i, Token("Eval", newValue));
                }
            }
        }
    }

    if (tokens.at(0).GetValue() == "True") {
        return true;
    }
    else {
        return false;
    }
}

SQL_Query_Results DeleteRows(string tableName, set<string> &columnNames, vector<Token> &whereTokens) {
    SQL_Query_Results results;
    map<string,int> fieldOrder = GetTableFieldsOrderMap(tableName);
    map<string,string> fields = GetTableFieldsMap(tableName);

    //Save positions of columns to store
    map<int, string> positions;
    for (string columnName: columnNames) {
        positions.insert(pair<int,string>(fieldOrder.at(columnName), columnName));
    }

    ifstream inFile;
    inFile.open(tableName);
    if (!inFile.is_open()) {
        stringstream ss;
        ss << "Could not read from " << tableName;
        Throw_Error(ss.str());
    }

    //Read in first line because first line are the field definitions
    string tableRow;
    getline(inFile, tableRow);

    //Iterate through the rest of the table rows
    while (getline(inFile, tableRow)) {
        map<string,string> rowResults;
        queue<Token> tokens = GetTokens(tableRow);

        bool isDeleted;
        if (whereTokens.size() != 0) {
            vector<Token> semiEvaluated = RunConditionEval(tokens, whereTokens, fieldOrder, fields);
            isDeleted = ComputeLogic(semiEvaluated);
        }

        //Use where tokens to determine if we need this row
        if (whereTokens.size() > 0 && isDeleted == false) {
            int columnNumber = 0;
            while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
                if (columnNumber > 0) {
                    MatchToken("Comma", tokens);
                    tokens.pop();
                }
                if (positions.find(columnNumber) != positions.end()) {
                    //We know we need this column. Find what the datatype it is supposed to be.
                    string columnName = positions.at(columnNumber);
                    string dataType = fields.at(columnName);
                    string value;
                    if (dataType == "INT") {
                        value = HexToDecimal(tokens.front().GetValue());
                    }
                    else if (dataType == "TEXT") {
                        value = tokens.front().GetValue();
                    }
                    else {
                        Throw_Error("Invalid datatype in table field");
                    }
                    rowResults.insert(pair<string,string>(columnName, value));
                }
                tokens.pop();
                ++columnNumber;
            }
            results.push_back(rowResults);

        }
    }   

    inFile.close();
    return results;
}

SQL_Query_Results UpdateRows(string tableName, set<string> &columnNames, vector<Token> &whereTokens, map<string,string> newValues = undefinedMap) {
    SQL_Query_Results results;
    map<string,int> fieldOrder = GetTableFieldsOrderMap(tableName);
    map<string,string> fields = GetTableFieldsMap(tableName);

    //Save positions of columns to store
    map<int, string> positions;
    for (string columnName: columnNames) {
        positions.insert(pair<int,string>(fieldOrder.at(columnName), columnName));
    }

    ifstream inFile;
    inFile.open(tableName);
    if (!inFile.is_open()) {
        stringstream ss;
        ss << "Could not read from " << tableName;
        Throw_Error(ss.str());
    }

    //Read in first line because first line are the field definitions
    string tableRow;
    getline(inFile, tableRow);

    //Iterate through the rest of the table rows
    while (getline(inFile, tableRow)) {
        map<string,string> rowResults;
        queue<Token> tokens = GetTokens(tableRow);

        bool isNeeded;
        if (whereTokens.size() != 0) {
            vector<Token> semiEvaluated = RunConditionEval(tokens, whereTokens, fieldOrder, fields);
            isNeeded = ComputeLogic(semiEvaluated);
        }

        //Use where tokens to determine if we need this row
        int columnNumber = 0;
        while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
            if (columnNumber > 0) {
                MatchToken("Comma", tokens);
                tokens.pop();
            }
            if (positions.find(columnNumber) != positions.end()) {
                //We know we need this column. Find what the datatype it is supposed to be.
                string columnName = positions.at(columnNumber);
                string dataType = fields.at(columnName);
                string value;
                if (newValues.size() > 0 && isNeeded == true && newValues.find(columnName) != newValues.end()) {
                    value = newValues.at(columnName);
                }
                else if (dataType == "INT") {
                    value = HexToDecimal(tokens.front().GetValue());
                }
                else if (dataType == "TEXT") {
                    value = tokens.front().GetValue();
                }
                else {
                    Throw_Error("Invalid datatype in table field");
                }
                rowResults.insert(pair<string,string>(columnName, value));
            }
            tokens.pop();
            ++columnNumber;
        }
        results.push_back(rowResults);
    }   

    inFile.close();
    return results;
}

SQL_Query_Results SelectRows(string tableName, set<string> &columnNames, vector<Token> &whereTokens, bool distinct = false, map<string,string> columnToSelectedAs = undefinedMap) {
    SQL_Query_Results results;
    map<string,int> fieldOrder = GetTableFieldsOrderMap(tableName);
    map<string,string> fields = GetTableFieldsMap(tableName);

    //Save positions of columns to store
    map<int, string> positions;
    for (string columnName: columnNames) {
        positions.insert(pair<int,string>(fieldOrder.at(columnName), columnName));
    }
    
    ifstream inFile;
    inFile.open(tableName);
    if (!inFile.is_open()) {
        stringstream ss;
        ss << "Could not read from " << tableName;
        Throw_Error(ss.str());
    }

    //Read in first line because first line are the field definitions
    string tableRow;
    getline(inFile, tableRow);

    //Declare set for DISTINCT Eval
    set<map<string,string>> distinctResults;

    //Iterate through the rest of the table rows
    while (getline(inFile, tableRow)) {
        map<string,string> rowResults;
        queue<Token> tokens = GetTokens(tableRow);

        bool isNeeded;
        if (whereTokens.size() != 0) {
            vector<Token> semiEvaluated = RunConditionEval(tokens, whereTokens, fieldOrder, fields);
            isNeeded = ComputeLogic(semiEvaluated);
        }
        
        //Use where tokens to determine if we need this row
        if (whereTokens.size() == 0 || isNeeded == true) {
            int columnNumber = 0;
            while (tokens.size() > 0 && tokens.front().GetType() != "Period") {
                if (columnNumber > 0) {
                    MatchToken("Comma", tokens);
                    tokens.pop();
                }
                if (positions.find(columnNumber) != positions.end()) {
                    //We know we need this column. Find what the datatype it is supposed to be.
                    string columnName = positions.at(columnNumber);
                    string dataType = fields.at(columnName);
                    if (columnToSelectedAs.size() > 0 && columnToSelectedAs.find(columnName) != columnToSelectedAs.end()) {
                        columnName = columnToSelectedAs.at(columnName);
                    }
                    string value;
                    if (dataType == "INT") {
                        value = HexToDecimal(tokens.front().GetValue());
                    }
                    else if (dataType == "TEXT") {
                        value = tokens.front().GetValue();
                    }
                    else {
                        Throw_Error("Invalid datatype in table field");
                    }
                    rowResults.insert(pair<string,string>(columnName, value));
                }
                tokens.pop();
                ++columnNumber;
            }
            if (distinct == false) {
                results.push_back(rowResults);
            }
            else if (distinctResults.find(rowResults) == distinctResults.end()) {
                results.push_back(rowResults);
            }
            distinctResults.insert(rowResults);
        }
    }   

    inFile.close();
    return results;
}

set<string> OrderColumnValuesText(string columnName, vector<map<string,string>> data) {
    set<string> orderedColumnValues;
    for (map<string,string> row: data) {
        orderedColumnValues.insert(row.at(columnName));
    }
    return orderedColumnValues;
}

set<int> OrderColumnValuesInt(string columnName, vector<map<string,string>> data) {
    set<int> orderedColumnValues;
    for (map<string,string> row: data) {
        orderedColumnValues.insert(stoi(row.at(columnName)));
    }
    return orderedColumnValues;
}

vector<Token> GetWhereTokens(queue<Token> &tokens, map<string,string> &fields, map<string,string> aliases = undefinedMap) {
    vector<Token> whereTokens;
    if (tokens.size() > 0 && tokens.front().GetType() == "Where") {   
        MatchToken("Where", tokens);
        tokens.pop();
        whereTokens.push_back(Token("Left-Paren", "("));
        while (tokens.size() > 0 && tokens.front().GetType() != "Order By") {
            if (tokens.front().GetType() == "Identifier") {
                if (aliases.size() > 0 && aliases.find(tokens.front().GetValue()) != aliases.end()) {
                    tokens.front().SetValue(aliases.at(tokens.front().GetValue()));
                }
                VerifyColumnName(tokens.front().GetValue(), fields);
            }
            else if (tokens.front().GetType() == "INT") {
                tokens.front().SetValue(tokens.front().GetValue());
            }
            else if (tokens.front().GetType() == "TEXT") {
                tokens.front().SetValue(RemoveSingleQuotes(tokens.front().GetValue()));
            }
            whereTokens.push_back(tokens.front());
            tokens.pop();
        }
        whereTokens.push_back(Token("Right-Paren", ")"));
    }
    return whereTokens;
}

vector<pair<string,string>> GetOrderByColumns(queue<Token> &tokens, map<string,string> &fields, map<string,string> aliases = undefinedMap) {
    vector<pair<string,string>> orderByColumns;
    if (tokens.size() > 0 && tokens.front().GetType() == "Order By") {
        MatchToken("Order By", tokens);
        tokens.pop();

        while (tokens.size() > 0) {
            if (orderByColumns.size() > 0) {
                MatchToken("Comma", tokens);
                tokens.pop();
            }
            string columnName = MatchToken("Identifier", tokens);
            if (aliases.size() > 0 && aliases.find(columnName) != aliases.end()) {
                columnName = aliases.at(columnName);
            }
            VerifyColumnName(columnName, fields);
            tokens.pop();
            if (tokens.size() > 0 && tokens.front().GetType() == "Desc") {
                orderByColumns.push_back(pair<string,string>(columnName, "Desc"));
                tokens.pop();
            }
            else if (tokens.size() > 0 && tokens.front().GetType() == "Asc") {
                orderByColumns.push_back(pair<string,string>(columnName, "Asc"));
                tokens.pop();
            }
            else {
                orderByColumns.push_back(pair<string,string>(columnName, "Asc"));
            }
        }
    }
    return orderByColumns;
}

map<string,string> GetSetValues(queue<Token> &tokens, map<string,string> &fields) {
    map<string,string> newValues;
    while (tokens.size() > 0 && tokens.front().GetType() != "Where") {
        if (newValues.size() > 0) {
            MatchToken("Comma", tokens);
            tokens.pop();
        }
        string columnName = MatchToken("Identifier", tokens);
        VerifyColumnName(columnName, fields);
        tokens.pop();
        string logicOperator = MatchToken("Logic", tokens);
        tokens.pop();
        if (logicOperator != "=") {
            stringstream ss;
            ss << "Invalid logical operator: " << logicOperator;
            Throw_Error(ss.str());
        }
        string value;
        if (fields.at(columnName) == "INT") {
            value = MatchToken("INT", tokens);
            tokens.pop();
        }
        else if (fields.at(columnName) == "TEXT") {
            value = RemoveSingleQuotes(MatchToken("TEXT", tokens));
            tokens.pop();
        }
        newValues.insert(pair<string,string>(columnName, value));
    }
    return newValues;
}

void SortResults(vector<map<string,string>> &results, vector<pair<string,string>> orderByColumns, map<string,string> &fields, map<string,string> aliases = undefinedMap) {
    for (unsigned int i = 0; i < orderByColumns.size(); ++i) {
        //First obtain a set that orders that column value for all results
        vector<map<string,string>> newResults;
        string columnName = orderByColumns.at(i).first;
        string dataType = fields.at(columnName);
        string orderOrder = orderByColumns.at(i).second;
        
        //Change the columnName to the alias if it exists
        if (aliases.find(columnName) != aliases.end()) {
            orderByColumns.at(i).first = aliases.at(columnName);
            columnName = aliases.at(columnName);
        }

        if (dataType == "TEXT") {
            set<string> orderedColumnValues = OrderColumnValuesText(columnName, results);
            if (i == 0) {
                if (orderOrder == "Asc") {
                    for (string columnValue: orderedColumnValues) {
                        for (map<string,string> row: results) {
                            if (row.at(columnName) == columnValue) {
                                newResults.push_back(row);
                            }
                        }
                    }
                }
                else if (orderOrder == "Desc") {
                    for (set<string>::reverse_iterator rit = orderedColumnValues.rbegin(); rit != orderedColumnValues.rend(); ++rit) {
                        for (map<string,string> row: results) {
                            if (row.at(columnName) == *rit) {
                                newResults.push_back(row);
                            }
                        }
                    }
                }
            }
            else {
                int sameSize = 0;
                for (unsigned long j = 0; j < results.size(); ++j) {
                    if (j != results.size() - 1 && results.at(j).at(orderByColumns.at(i - 1).first) == results.at(j + 1).at(orderByColumns.at(i - 1).first)) {
                        ++sameSize;
                    }
                    else if (sameSize == 0) {
                        newResults.push_back(results.at(j));
                    }
                    else if (sameSize > 0) {
                        if (orderOrder == "Asc") {
                            for (string columnValue: orderedColumnValues) {
                                for (unsigned int k = j - sameSize; k <= j; ++k) {
                                    if (results.at(k).at(columnName) == columnValue) {
                                        newResults.push_back(results.at(k));
                                    }
                                }
                            }
                        }
                        else if (orderOrder == "Desc") {
                            for (set<string>::reverse_iterator rit = orderedColumnValues.rbegin(); rit != orderedColumnValues.rend(); ++rit) {
                                for (unsigned int k = j - sameSize; k <= j; ++k) {
                                    if (results.at(k).at(columnName) == *rit) {
                                        newResults.push_back(results.at(k));
                                    }
                                }
                            }
                        }
                        sameSize = 0;
                    }
                }
            }
        }
        else if (dataType == "INT") {
            set<int> orderedColumnValues = OrderColumnValuesInt(columnName, results);
            if (i == 0) {
                if (orderOrder == "Asc") {
                    for (int columnValue: orderedColumnValues) {
                        for (map<string,string> row: results) {
                            if (row.at(columnName) == to_string(columnValue)) {
                                newResults.push_back(row);
                            }
                        }
                    }
                }
                else if (orderOrder == "Desc") {
                    for (set<int>::reverse_iterator rit = orderedColumnValues.rbegin(); rit != orderedColumnValues.rend(); ++rit) {
                        for (map<string,string> row: results) {
                            if (row.at(columnName) == to_string(*rit)) {
                                newResults.push_back(row);
                            }
                        }
                    }
                }
            }
            else {
                int sameSize = 0;
                for (unsigned long j = 0; j < results.size(); ++j) {
                    if (j != results.size() - 1 && results.at(j).at(orderByColumns.at(i - 1).first) == results.at(j + 1).at(orderByColumns.at(i - 1).first)) {
                        ++sameSize;
                    }
                    else if (sameSize == 0) {
                        newResults.push_back(results.at(j));
                    }
                    else if (sameSize > 0) {
                        if (orderOrder == "Asc") {
                            for (int columnValue: orderedColumnValues) {
                                for (unsigned int k = j - sameSize; k <= j; ++k) {
                                    if (results.at(k).at(columnName) == to_string(columnValue)) {
                                        newResults.push_back(results.at(k));
                                    }
                                }
                            }
                        }
                        else if (orderOrder == "Desc") {
                            for (set<int>::reverse_iterator rit = orderedColumnValues.rbegin(); rit != orderedColumnValues.rend(); ++rit) {
                                for (unsigned int k = j - sameSize; k <= j; ++k) {
                                    if (results.at(k).at(columnName) == to_string(*rit)) {
                                        newResults.push_back(results.at(k));
                                    }
                                }
                            }
                        }
                        sameSize = 0;
                    }
                }
                
            }
        }

        results.clear();
        results = newResults;
    }
}

void SQL_Query_Create(string query) {
    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    MatchToken("Create", tokens);
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

void SQL_Query_Update(string query) {
    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    MatchToken("Update", tokens);
    tokens.pop();

    string tableName = GetTableName(tokens);
    tokens.pop();
    map<string,string> fields = GetTableFieldsMap(tableName);
    vector<string> fieldOrder = GetTableFieldsOrder(tableName);

    MatchToken("Set", tokens);
    tokens.pop();

    //Obtain new values
    map<string,string> newValues = GetSetValues(tokens, fields);

    //Get WHERE Tokens
    vector<Token> whereTokens = GetWhereTokens(tokens, fields);

    //Read in entire table
    set<string> columnNames;
    for (string field: fieldOrder) {
        columnNames.insert(field);
    }
    vector<Token> empty;
    SQL_Query_Results results = UpdateRows(tableName, columnNames, whereTokens, newValues);

    //Rewrite table
    ofstream outFile;
    outFile.open(tableName);
    if (!outFile.is_open()) {
        stringstream ss;
        ss << "Unable to write to " << tableName;
        Throw_Error(ss.str());
    }
    //Add Table Definition first
    for (string field: fieldOrder) {
        outFile << field << " " << fields.at(field) << ",";
    }
    outFile << "." << endl;

    //Add new table rows
    for (map<string,string> &row: results) {
        for (string field: fieldOrder) {
            string value = row.at(field);
            if (fields.at(field) == "INT") {
                value = DecimalToHex(value);
            }
            outFile << value << ",";
        }
        outFile << "." << endl;
    }

    outFile.close();
    return;
}

void SQL_Query_Insert(string query) {
    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    MatchToken("Insert", tokens);
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
            value = RemoveSingleQuotes(MatchToken("TEXT", tokens));
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

SQL_Query_Results SQL_Query_Select(string query) {
    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    MatchToken("Select", tokens);
    tokens.pop();

    queue<Token> tokensCopy = tokens;
    while (tokensCopy.front().GetType() != "From") {
        tokensCopy.pop();
    }
    tokensCopy.pop();
    //Read fields from table
    string tableName = GetTableName(tokensCopy);
    map<string, string> fields = GetTableFieldsMap(tableName);
    vector<string> fieldOrder = GetTableFieldsOrder(tableName);
    tokensCopy.pop();

    tokensCopy = queue<Token>();

    bool distinct = false;
    if (tokens.front().GetType() == "Distinct") {
        MatchToken("Distinct", tokens);
        tokens.pop();
        distinct = true;
    }

    set<string> columnsSelected;
    map<string,string> selectedAsToColumn;
    map<string,string> columnToSelectedAs;
    //Read the columns selected in the SQL_QUERY Input
    while (tokens.size() > 0 && tokens.front().GetType() != "From") {
        if (columnsSelected.size() > 0) {
            MatchToken("Comma", tokens);
            tokens.pop();
        }
        if (tokens.front().GetType() == "Star") {
            columnsSelected.clear();
            for (string column: fieldOrder) {
                columnsSelected.insert(column);
            }
            break;
        }
        string columnName = MatchToken("Identifier", tokens);
        tokens.pop();
        VerifyColumnName(columnName, fields);
        columnsSelected.insert(columnName);
        //Look for the AS keyword
        if (tokens.size() > 0 && tokens.front().GetType() == "As") {
            MatchToken("As", tokens);
            tokens.pop();
            string selectAs = MatchToken("Identifier", tokens);
            tokens.pop();
            selectedAsToColumn.insert(pair<string,string>(selectAs, columnName));
            columnToSelectedAs.insert(pair<string,string>(columnName, selectAs));
        }
    }
    MatchToken("From", tokens);
    tokens.pop();
    MatchToken("Identifier", tokens);
    tokens.pop();

    //Obtain WHERE tokens
    vector<Token> whereTokens = GetWhereTokens(tokens, fields, selectedAsToColumn);
    
    //Obtain ORDER BY Columns
    vector<pair<string,string>> orderByColumns = GetOrderByColumns(tokens, fields, selectedAsToColumn);
    
    set<string> originalColumnsSelected = columnsSelected;
    //Add on any ORDER BY columns
    for (pair<string,string> column: orderByColumns) {
        columnsSelected.insert(column.first);
    }
    
    SQL_Query_Results results = SelectRows(tableName, columnsSelected, whereTokens, distinct, columnToSelectedAs);

    //Computer Order By logic
    if (orderByColumns.size() > 0) {
        SortResults(results, orderByColumns, fields, columnToSelectedAs);

        //Remove ORDER BY columns from results that aren't in the SELECT columns
        for (pair<string,string> column: orderByColumns) {
            if (originalColumnsSelected.find(column.first) == originalColumnsSelected.end()) {
                for (map<string,string> &result: results) {
                    result.erase(column.first);
                }
            }
        }
    }

    return results;
}

void SQL_Query_Delete(string query) {
    //Get tokens from input
    queue<Token> tokens = GetTokens(query);
    MatchToken("Delete", tokens);
    tokens.pop();

    string tableName = GetTableName(tokens);
    tokens.pop();
    map<string,string> fields = GetTableFieldsMap(tableName);
    vector<string> fieldOrder = GetTableFieldsOrder(tableName);

    //Get WHERE Tokens
    vector<Token> whereTokens = GetWhereTokens(tokens, fields);

    //Read in entire table
    set<string> columnNames;
    for (string field: fieldOrder) {
        columnNames.insert(field);
    }
    vector<Token> empty;
    SQL_Query_Results results = DeleteRows(tableName, columnNames, whereTokens);

    //Rewrite table
    ofstream outFile;
    outFile.open(tableName);
    if (!outFile.is_open()) {
        stringstream ss;
        ss << "Unable to write to " << tableName;
        Throw_Error(ss.str());
    }
    //Add Table Definition first
    for (string field: fieldOrder) {
        outFile << field << " " << fields.at(field) << ",";
    }
    outFile << "." << endl;

    //Add new table rows
    for (map<string,string> &row: results) {
        for (string field: fieldOrder) {
            string value = row.at(field);
            if (fields.at(field) == "INT") {
                value = DecimalToHex(value);
            }
            outFile << value << ",";
        }
        outFile << "." << endl;
    }

    outFile.close();
    return;
}

#endif