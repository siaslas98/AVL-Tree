# AVL-Tree


##  About Implementation 
    
    - main.cpp will read and process command arguments.
    - avl.h/avl.cpp will declare and define functionalities for the AVL Tree.

// Helper methods for AVL tree operations
Node* insert(Node* currNode, const Student& student);
bool contains(int id);
void printInOrder(Node* root, stringstream& ss);

// Constructor initializes root to nullptr
AVL() : _root(nullptr) {}

    // Public method to insert a student into the AVL tree
    bool insertStudent(const Student& student);

    void printTreeInOrder();

    // Public test interface
    bool testContains(int id) {
        return contains(id);
    }