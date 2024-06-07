#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <regex>

// Debug print to track function calls
#define DEBUG_PRINT(x) cout << x << endl

using namespace std;

struct Student {
    string _name;
    string _id;
    Student(string name, string id) : _name(name), _id(id){}
};

struct Node {
    Student _student;
    Node* _left;
    Node* _right;
    int _height;

    Node(const Student& student)
            : _student(student), _left(nullptr), _right(nullptr), _height(1) {}

    bool searchSubtree(Node* subtree, string id){
        if(subtree == nullptr){
            return false;
        }

        if(subtree->_student._id == id){
            return true;
        }

        return searchSubtree(subtree->_left, id) || searchSubtree(subtree->_right, id);
    }
    void printName(stringstream& ss){
        ss << _student._name;
    }
};

class AVL {
private:
    Node* _root;

    int getBalance(Node* N);
    Node* leftRotate(Node* root);
    Node* rightRotate(Node* root);
    Node* getIoSuccessor(Node* root);
    Node* insert(Node* root, const Student& student);
    Node* remove(Node* root, string id, bool& removed);
    bool contains(string id);
    void printInOrder(Node* root, stringstream& ss);
    void printPreOrder(Node* root, stringstream& ss);
    void printPostOrder(Node* root, stringstream& ss);

    bool isValidID(const string& id);
    bool isValidName(const string& name);

public:
    // Constructor
    AVL() : _root(nullptr) {}

    // Mutators
    bool insertStudent(const Student& student);
    bool removeStudent(string id);

    // Searching
    bool searchID(Node* root, string id);
    bool searchName(Node* root, string name);

    // Display
    void printTreeInOrder();
    void printTreePreOrder();
    void printTreePostOrder();
    void printLevelCount();

    // Public test interface
    bool testIsValidName(string name){
        return isValidName(name);
    }
    bool testIsValidID(string id){
        return isValidID(id);
    }
    bool testContains(string id) {
        return contains(id);
    }
    bool testInsert(const Student& student){
        _root = insert(_root, student);
        return _root != nullptr;
    }
    bool isBalanced(Node* root) {
        if (!root) {
            return true;
        } // An empty tree is always balanced
        int balance = getBalance(root);
        bool leftBalanced = isBalanced(root->_left);
        bool rightBalanced = isBalanced(root->_right);
        return balance >= -1 && balance <= 1 && leftBalanced && rightBalanced;
    }
    bool isHeightCorrect(Node* root){
        if(!root){
            return true;
        } // An empty tree has a height of 0
        int leftHeight = getHeight(root->_left);
        int rightHeight = getHeight(root->_right);
        bool leftHeightCorrect = isHeightCorrect(root->_left);
        bool rightHeightCorrect = isHeightCorrect(root->_right);
        return root->_height == 1 + max(leftHeight, rightHeight) && leftHeightCorrect && rightHeightCorrect;
    }
    bool validateTree(){
        return isBalanced(_root) && isHeightCorrect(_root);
    }
    void testPrintInOrder(stringstream& ss){
        printInOrder(_root, ss);
    }
    void testPrintPreOrder(stringstream& ss){
        printPreOrder(_root, ss);
    }
    void testPrintPostOrder(stringstream& ss){
        printPostOrder(_root, ss);
    }

    // Helpers
    int getHeight(Node* N);
    Node* getRoot() const;
    int max(int a, int b);
};



