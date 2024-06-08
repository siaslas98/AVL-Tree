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

    return newRoot;
}

Node* AVL::getIoSuccessor(Node* root) {
   if(!root->_left){
       return root;
   }
   return getIoSuccessor(root->_left);
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

Node* AVL::remove(Node* root, string id, bool& removed) {
    if(!root){
        return nullptr;
    }

    if(id < root->_student._id){
        root->_left = remove(root->_left, id, removed);
    }

    else if(id > root->_student._id){
        root->_right = remove(root->_right, id, removed);
    }

    else{ // Node found
        removed = true;

        if(!root->_left && !root->_right){ // Simply delete, there are no children
            delete root;
            return nullptr;
        }

        else if(root->_left && !root->_right){ // 1 left child
            Node* newRoot = root->_left;
            delete root;
            return newRoot;
        }

        else if(!root->_left && root->_right){ // 1 right child
            Node* newRoot = root->_right;
            delete root;
            return newRoot;
        }

        else{ // 2 children
            Node* successor = getIoSuccessor(root->_right);

            // Replace root's data with successor's data
            root->_student = successor->_student;

            // Recursively remove the in-order successor
            root->_right = remove(root->_right, successor->_student._id, removed);
        }
    }

    root->_height = 1 + max(getHeight(root->_left), getHeight(root->_right));

    // Update node heights along the path and perform rotations
    int balanceFact = getBalance(root);

    // Left heavy
    if (balanceFact > 1){
        if(getBalance(root->_left) >= 0){ // Left-Left case - perform right rotation
            return rightRotate(root);
        }
        else{ // Left-Right case - perform double rotation. Left rotation, then right rotation
            root->_left = leftRotate(root->_left);
            return rightRotate(root);
        }
    }

    // Right heavy
    if (balanceFact < -1){

        if(getBalance(root->_right) <= 0){ // Right-Right case - perform left rotation
            return leftRotate(root);
        }

        else{ // Right-Left case - Right rotation, then left rotation
            root->_right = rightRotate(root->_right);
            return leftRotate(root);
        }
    }

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

bool AVL::removeStudent(string id) {
    if(!_root){ // We don't have an actual tree, so there is nothing to remove
        return false;
    }

    bool removed = false;
    _root = remove(_root, id, removed);
    return removed;
}

bool AVL::removeNthStudent(Node* root, int& N) {
    if(!root){
        return false;
    }

    if(root->_left){
        if(removeNthStudent(root->_left, N)){
            return true;
        }
    }


    if(N == 0){
        return removeStudent(root->_student._id);
    }
    --N;

    if(root->_right){
        if(removeNthStudent(root->_right, N)){
            return true;
        }
    }

    return false;
}

void AVL::printInOrder(Node* root, stringstream& ss) {
    if(!root){
        return;
    }

    printInOrder(root->_left, ss);

    if (ss.tellp() > 0) { // Check if the stringstream is not empty
        ss << ", ";
    }

    root->printName(ss);

    printInOrder(root->_right, ss);
}

void AVL::printPreOrder(Node* root, std::stringstream& ss) {
    if(!root){
        return;
    }

    root->printName(ss);

    if (root->_left || root->_right) { // Check if there are children before adding a comma
        ss << ", ";
    }

    printPreOrder(root->_left, ss);

    if (root->_right) { // Check if there are children before adding a comma
        ss << ", ";
    }

    printPreOrder(root->_right, ss);
}

void AVL::printPostOrder(Node* root, std::stringstream& ss) {
    if(!root){
        return;
    }

    printPostOrder(root->_left, ss);
    printPostOrder(root->_right, ss);

    if(ss.tellp() > 0){
        ss << ", ";
    }

    root->printName(ss);
}

void AVL::printTreeInOrder() {
    if(!_root){
        return;
    }

    stringstream ss;
    printInOrder(_root, ss);

    string res = ss.str();

    cout << res;
}

void AVL::printTreePreOrder() {
    if(!_root){
        return;
    }

    stringstream ss;
    printPreOrder(_root, ss);

    string res = ss.str();

    cout << res;
}

void AVL::printTreePostOrder(){
    if(!_root){
        return;
    }

    stringstream ss;
    printPostOrder(_root, ss);

    string res = ss.str();

    cout << res;
}

void AVL::printLevelCount() {
    if(_root == nullptr){
        cout << 0 << endl;
        return;
    }

    cout << _root->_height << endl;
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

void AVL::searchName(Node* root, const string& name, vector<string>& v){
    if(!root){
        return;
    }

    searchName(root->_left, name, v);

    if(root->_student._name == name){
        v.push_back(root->_student._id);
    }

    searchName(root->_right, name, v);
}