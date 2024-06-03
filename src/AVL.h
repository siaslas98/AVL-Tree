#pragma once

#include <iostream>
#include <sstream>
#include "Student.h"


struct Node {
    Student _student;
    Node* _left;
    Node* _right;
    int _height;

    Node(const Student& student)
            : _student(student), _left(nullptr), _right(nullptr), _height(0) {}

    bool searchSubtree(Node* subtree, int val){
        if(subtree == nullptr){
            return false;
        }

        if(subtree->_student._id == val){
            return true;
        }

        return searchSubtree(subtree->_left, val) || searchSubtree(subtree->_right, val);
    }

    void printName(stringstream& ss){
        ss << _student._name;
    }
};

class AVL {
private:
    Node* _root;

    // Helper methods for AVL tree operations
    Node* insert(Node* currNode, const Student& student);
    bool contains(int id);

    void printInOrder(Node* root, stringstream& ss);


public:
    AVL() : _root(nullptr) {} // Constructor initializes root to nullptr

    // Public method to insert a student into the AVL tree
    bool insertStudent(const Student& student);

    void printTreeInOrder();

    // Public test interface
    bool testContains(int id) {
        return contains(id);
    }
};



