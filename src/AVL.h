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
    Node* leftRotate(Node* currNode);
    Node* rightRotate(Node* currNode);
    Node* insert(Node* currNode, const Student& student);
    bool contains(string id);
    void printInOrder(Node* root, stringstream& ss);

    bool isValidID(const string& id);
    bool isValidName(const string& name);

public:
    // Constructor
    AVL() : _root(nullptr) {}

    // Mutators
    bool insertStudent(const Student& student);

    // Display
    void printTreeInOrder();

    // Public test interface
    bool testContains(string id) {
        return contains(id);
    }

    // Helpers
    int getHeight(Node* N);
    int max(int a, int b);
};



