#include "AVL.h"

bool AVL::contains(int id) {
    if(!_root) return false;

    else{
        return _root->searchSubtree(_root, id);
    }
}

Node* AVL::insert(Node* currNode, const Student& student) {
    if (!currNode) {
        currNode = new Node(student);
        return currNode;
    }

    if (student._id < currNode->_student._id) {
        currNode->_left = insert(currNode->_left, student);
    }
    else if (student._id > currNode->_student._id) {
        currNode->_right = insert(currNode->_right, student);
    }

    return currNode;
}

bool AVL::insertStudent(const Student& student) {
    if (contains(student._id)) {
        return false; // Student already exists
    }

    _root = insert(_root, student); // Perform the insertion
    return true; // Insertion was successful
}

void AVL::printInOrder(Node* root, stringstream& ss) {
    if(!root){
        return;
    }

    if(root->_left){
        printInOrder(root->_left, ss);
        ss << ", ";
    }

    root->printName(ss);

    if(root->_right){
        ss << ", ";
        printInOrder(root->_right, ss);
    }
}

void AVL::printTreeInOrder() {
    if(!_root){
        return;
    }

    if(_root->_left == nullptr && _root->_right == nullptr){
        cout << _root->_student._name << endl;
        return;
    }

    stringstream ss;
    printInOrder(_root, ss);

    string res = ss.str();

    // Remove trailing comma and space if present
    if (res.size() >= 2 && res.substr(res.size() - 2) == ", ") {
        res.erase(res.size() - 2);
    }

    // Remove trailing newline if present
    if (!res.empty() && res.back() == '\n') {
        res.pop_back();
    }


    cout << res << endl;
}