#include "AVL.h"

bool AVL::contains(string id) {
    if(!_root) return false;

    else{
        return _root->searchSubtree(_root, id);
    }
}

bool AVL::isValidID(const string& id) {
    regex id_regex(R"(^\d{8}$)");
    return regex_match(id, id_regex);
}

bool AVL::isValidName(const string& name) {
    regex name_regex(R"(^[a-zA-Z\s]+$)");
    return regex_match(name, name_regex);
}

int AVL::getBalance(Node* N) {
    if(!N) return 0;
    return getHeight(N->_left) - getHeight(N->_right);
}

Node* AVL::leftRotate(Node* root) {
    if (!root || !root->_right) return root; // Defensive check

    Node* newRoot = root->_right;
    Node* leftRight = newRoot->_left;

    newRoot->_left = root;
    root->_right = leftRight;

    root->_height = 1 + max(getHeight(root->_left), getHeight(root->_right));
    newRoot->_height = 1 + max(getHeight(newRoot->_left), getHeight(newRoot->_right));

    DEBUG_PRINT("Left rotation on node with ID: " + root->_student._id);

    return newRoot;
}

Node* AVL::rightRotate(Node* root) {
    if (!root || !root->_left) return root; // Defensive check

    Node* newRoot = root->_left;
    Node* rightLeft = newRoot->_right;

    newRoot->_right = root;
    root->_left = rightLeft;

    root->_height = 1 + max(getHeight(root->_left), getHeight(root->_right));
    newRoot->_height = 1 + max(getHeight(newRoot->_left), getHeight(newRoot->_right));

    DEBUG_PRINT("Right rotation on node with ID: " + root->_student._id);

    return newRoot;
}

Node* AVL::insert(Node* root, const Student& student) {
    // Executes when we initialize the AVL, and when we insert a new leaf node
    if (!root) {
        return new Node(student);
    }

    // Recursive calls happen here to help insert student in correct position in AVL
    if (student._id < root->_student._id) {
        root->_left = insert(root->_left, student);
    }
    else if (student._id > root->_student._id) {
        root->_right = insert(root->_right, student);
    }

    // After we successfully insert a new node and the stack frames return to previous stack frames
    // Update the height of the current root
    root->_height = 1 + max(getHeight(root->_left), getHeight(root->_right));

    // Here is where the real magic happens!
    // We balance the tree from bottom up
    // Calculate the balance factor for the current node
    int balanceFact = getBalance(root);

    /********** 4 cases where the AVL becomes unbalanced at the current root **********/
    // Depending on whether a rotation operation was performed, this part of the code returns the correct root

    // Left-Left Case(balance factor > 1)
    // Root->left becomes new root
    if(balanceFact > 1 && student._id < root->_left->_student._id){
        return rightRotate(root);
    }

    // Right-Right Case(balance factor < -1)
    // Root->right becomes the new root
    if(balanceFact < -1 && student._id > root->_right->_student._id){
        return leftRotate(root);
    }

    // Left-Right Case(balance factor > 1)
    // First perform a left rotation on root->left
    // Then perform a right rotation on root
    if(balanceFact > 1 && student._id > root->_left->_student._id){
        root->_left = leftRotate(root->_left);
        return rightRotate(root);
    }

    // Right-Left Case(balance factor < -1)
    // First perform a right rotation on root->right
    // Then perform a left rotation on root
    if(balanceFact < -1 && student._id < root->_right->_student._id){
        root->_right = rightRotate(root->_right);
        return leftRotate(root);
    }

    // Balance factor is between -1 and 1
    // No need to rotate and reassign root
    return root;
}

bool AVL::insertStudent(const Student& student) {
    // Validate ID
    if(!isValidID(student._id)){
        return false;
    }

    if(!isValidName(student._name)){
        return false; // Invalid Name
    }

    // Student already exists
    if (contains(student._id)) {
        return false;
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


    cout << res;
}

int AVL::getHeight(Node* N) {
   return N ? N->_height : 0;
}

Node* AVL::getRoot() const{
    if(!_root){
        return nullptr;
    }
    return _root;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

bool AVL::searchID(Node* root, string id){
    if(!root){
        return false;
    }

    if(root->_student._id == id){
        cout << root->_student._name << endl;
        return true;
    }

    return searchID(root->_left, id) || searchID(root->_right, id);
}

bool AVL::searchName(Node* root, string name){
    if(!root){
        return false;
    }

    bool found = false;

    if(root->_student._name == name){
        cout << root->_student._id << endl;
        found = true;
    }

    found = searchName(root->_left, name) || found;
    found = searchName(root->_right, name) || found;

    return found;
}