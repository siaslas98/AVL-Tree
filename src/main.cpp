#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

#include "AVL.h"
#include "Student.h"

using namespace std;

vector<string> splitCommand(const string& command);
bool isValidName(const string& name);
bool isValidID(const string& id);
void processCommand(AVL& tree, const string& command);

int main() {
    // Instantiate AVL tree
    AVL tree;

    string numCommands;
    string command;
    getline(cin, numCommands);

    for(int i = 0; i < stoi(numCommands); ++i){
        getline(cin, command, '\n');
        processCommand(tree, command);
    }

    return 0;
}

vector<string> splitCommand(const string& command){
    vector<string> commandArgs;

    // Define the regex pattern
    regex re(R"((\"[^\"]*\")|(\S+))");

    // Create iterators to find all matches
    sregex_iterator next(command.begin(), command.end(), re);
    sregex_iterator end;

    // Iterate over all matches
    while (next != end) {
        smatch match = *next;
        commandArgs.push_back(match.str());
        ++next;
    }
    return commandArgs;
}

bool isValidName(const string& name) {
    // Regular expression to match names containing only letters and spaces
    regex name_regex(R"(^[a-zA-Z\s]+$)");
    return regex_match(name, name_regex);
}

bool isValidID(const string& id) {
    // Regular expression to match exactly 8 digits
    regex id_regex(R"(^\d{8}$)");
    return regex_match(id, id_regex);
}

void processCommand(AVL& tree, const string& command){
    vector<string> tokens = splitCommand(command);

    if(tokens.empty()){
        cerr << "Empty command\n";
        return;
    }

    if(tokens[0] == "insert"){
        if(tokens.size() != 3){
            cerr << "Invalid insert command\n";
            return;
        }

        string name = tokens[1];
        name = name.substr(1, name.size() - 2); // Remove double quotes

        // Validate name
        if (!isValidName(name)) {
            cerr << "unsuccessful\n";
            return;
        }

        string id_str = tokens[2];

        // Validate ID
        if (!isValidID(id_str)) {
            cerr << "unsuccessful\n";
            return;
        }

        int id;
        try {
            id = stoi(tokens[2]);
        }
        catch (const invalid_argument& e) {
            cerr << "unsuccessful\n";
            return;
        }
        catch (const out_of_range& e) {
            cerr << "unsuccessful\n";
            return;
        }

        Student student(name, id);
        if (tree.insertStudent(student)) {
            cout << "successful\n";
        }
        else {
            cerr << "unsuccessful\n";
        }
    }

    else if(tokens[0] == "printInorder"){
        tree.printTreeInOrder();
    }
}
