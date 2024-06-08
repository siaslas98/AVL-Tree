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

    else if(tokens[0] == "remove"){
        string id = tokens[1];
        if(tree.removeStudent(id)){
            cout << "successful\n";
        }

        else {
            cerr << "unsuccessful\n";
        }

    }

    else if(tokens[0] == "removeInorder"){
        if(tokens.size() < 2 || !all_of(tokens[1].begin(), tokens[1].end(), ::isdigit)){
            cerr << "unsuccessful\n";
            return;
        }
        else{
            int N = stoi(tokens[1]);
            if(tree.removeNthStudent(tree.getRoot(), N)){
                cout << "successful\n";
            }
            else{
                cerr << "unsuccessful\n";
            }
            return;
        }
    }

    else if(tokens[0] == "printInorder"){
        tree.printTreeInOrder();
        cout << '\n';
    }

    else if(tokens[0] == "printPreorder"){
        tree.printTreePreOrder();
        cout << '\n';
    }

    else if(tokens[0] == "printPostorder"){
        tree.printTreePostOrder();
        cout << '\n';
    }

    else if(tokens[0] == "printLevelCount"){
        tree.printLevelCount();
    }

    else if(tokens[0] == "search"){
        if(tokens.size() != 2){
            return;
        }

        string str = tokens[1];
        string str1 = str;
        string str2 = str.substr(1, str.size() - 2); // Remove double quotes
        vector<string> v;
        if(tree.testIsValidID(str) && tree.searchID(tree.getRoot(), str1)){ // We search for ID
        }


        else if(tree.testIsValidName(str2)){
            tree.searchName(tree.getRoot(), str2, v);
            if(v.size() > 0){
                for(auto& id : v){
                    cout << id << endl;
                }
            }
        }

        else{
            cout << "unsuccessful\n";
        }

    }
}
