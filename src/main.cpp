#include <iostream>
#include <vector>
#include <regex>

#include "AVL.h"

using namespace std;

vector<string> splitCommand(const string& command);
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

        string id = tokens[2];

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
        cout << '\n';
    }

    else if(tokens[0] == "search"){
        if(tokens.size() != 2){
            cerr << "Invalid search command\n";
            return;
        }

        string str = tokens[1];
        if(tree.testIsValidID(str) && tree.searchID(tree.getRoot(), str)){ // We search for ID
            cout << "successful\n";
        }

        else if(tree.testIsValidName(str) && tree.searchName(tree.getRoot(), str)){
            cout << "successful\n";
        }

        else{
            cerr << "unsuccessful\n";
        }

    }

}
