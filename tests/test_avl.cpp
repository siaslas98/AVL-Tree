#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/AVL.h"

TEST_CASE("Basic AVL Tree Operations") {
    AVL tree;

    SECTION("Insert and Search Nodes") {
        Student s1("Brandon", "45679999");
        Student s2("Brian", "35459999");
        Student s3("Briana", "87879999");
        Student s4("Bella", "95469999");
        Student s5("Ben","00000000");

        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s2) == true);
        REQUIRE(tree.insertStudent(s3) == true);
        REQUIRE(tree.insertStudent(s4) == true);
        REQUIRE(tree.insertStudent(s5) == true);

        REQUIRE(tree.testContains("45679999") == true);
        REQUIRE(tree.testContains("35459999") == true);
        REQUIRE(tree.testContains("87879999") == true);
        REQUIRE(tree.testContains("95469999") == true);
        REQUIRE(tree.testContains("00000000") == true);
        REQUIRE(tree.testContains("954699999") == false);
    }

    SECTION("Avoid Inserting Duplicates") {
        Student s1("Alice", "10000001"); // Use a valid 8-digit ID
        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s1) == false);
    }

    SECTION("Print in order") {
        Student s1("Brandon", "45679999");
        Student s2("Brian", "35459999");
        Student s3("Briana", "87879999");
        Student s4("Bella", "95469999");
        Student s5("Bella", "95469999");
        Student s6("Ben","00000000");

        tree.insertStudent(s1);
        tree.insertStudent(s2);
        tree.insertStudent(s3);
        tree.insertStudent(s4);
        tree.insertStudent(s5);
        tree.insertStudent(s6);

        stringstream buffer;
        streambuf* old = cout.rdbuf(buffer.rdbuf());

        tree.printTreeInOrder();

        cout.rdbuf(old);
        string output = buffer.str();

        // Debug output: Print the captured output to the console
        cout << "Captured output: " << output << endl;

        REQUIRE(output == "Ben, Brian, Brandon, Briana, Bella");
    }
}
TEST_CASE("Input Validation"){
    AVL tree;

    SECTION("Check isValidName"){
        // 10 Valid Names
        REQUIRE(tree.testIsValidName("John Doe") == true);
        REQUIRE(tree.testIsValidName("Alice") == true);
        REQUIRE(tree.testIsValidName("Mary Jane") == true);
        REQUIRE(tree.testIsValidName("Michael Johnson") == true);
        REQUIRE(tree.testIsValidName("Emily Rose") == true);
        REQUIRE(tree.testIsValidName("Robert Smith") == true);
        REQUIRE(tree.testIsValidName("Jessica Lee") == true);
        REQUIRE(tree.testIsValidName("William Brown") == true);
        REQUIRE(tree.testIsValidName("David Wilson") == true);
        REQUIRE(tree.testIsValidName("Sarah Miller") == true);

        // 10 Invalid Names
        REQUIRE(tree.testIsValidName("John123") == false);
        REQUIRE(tree.testIsValidName("Alice!") == false);
        REQUIRE(tree.testIsValidName("Mary_Jane") == false);
        REQUIRE(tree.testIsValidName("Michael@Johnson") == false);
        REQUIRE(tree.testIsValidName("Emily#Rose") == false);
        REQUIRE(tree.testIsValidName("Robert$Smith") == false);
        REQUIRE(tree.testIsValidName("Jessica%Lee") == false);
        REQUIRE(tree.testIsValidName("William&Brown") == false);
        REQUIRE(tree.testIsValidName("David*Wilson") == false);
        REQUIRE(tree.testIsValidName("Sarah Miller2") == false);
    }
    
    SECTION("Check isValidID"){
        // 10 Valid ID
        REQUIRE(tree.testIsValidID("12345678") == true);
        REQUIRE(tree.testIsValidID("87654321") == true);
        REQUIRE(tree.testIsValidID("00000001") == true);
        REQUIRE(tree.testIsValidID("12341234") == true);
        REQUIRE(tree.testIsValidID("56785678") == true);
        REQUIRE(tree.testIsValidID("11112222") == true);
        REQUIRE(tree.testIsValidID("33334444") == true);
        REQUIRE(tree.testIsValidID("55556666") == true);
        REQUIRE(tree.testIsValidID("77778888") == true);
        REQUIRE(tree.testIsValidID("99990000") == true);

        // 10 Invalid ID
        REQUIRE(tree.testIsValidID("1234567") == false); // Only 7 digits
        REQUIRE(tree.testIsValidID("123456789") == false); // 9 digits
        REQUIRE(tree.testIsValidID("abcdefgh") == false); // Non-numeric characters
        REQUIRE(tree.testIsValidID("1234abcd") == false); // Mixed numeric and alphabetic characters
        REQUIRE(tree.testIsValidID("12 345678") == false); // Space within digits
        REQUIRE(tree.testIsValidID("123-45678") == false); // Hyphen within middle
        REQUIRE(tree.testIsValidID("12.345678") == false); // Dot within digits
        REQUIRE(tree.testIsValidID(" 12345678") == false); // Leading space
        REQUIRE(tree.testIsValidID("12345678 ") == false); // Trailing space
        REQUIRE(tree.testIsValidID("?123 45678") == false); // Leading question mark
    }
}
TEST_CASE("Insertion"){
    AVL tree;

    SECTION("Single Insertion"){
        Student student("John Doe", "12345678");
        tree.testInsert(student);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "12345678");
        REQUIRE(tree.getRoot()->_height == 1);
    }

    SECTION("Right Rotation") {
        Student student1("Alice", "3");
        Student student2("Bob", "2");
        Student student3("Charlie", "1");

        REQUIRE(tree.testInsert(student1) == true);
        REQUIRE(tree.testInsert(student2) == true);
        REQUIRE(tree.testInsert(student3) == true);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right->_student._id == "3");

        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Left Rotation"){
        // Insert nodes to trigger left rotation
        Student student1("Alice", "1");
        Student student2("Bob", "2");
        Student student3("Charlie", "3");

        REQUIRE(tree.testInsert(student1) == true);
        REQUIRE(tree.testInsert(student2) == true);
        REQUIRE(tree.testInsert(student3) == true);

        // After left rotation, "Bob" should be the new root
        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right->_student._id == "3");
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Left-Right Rotation"){
        // Insert nodes to trigger left-right rotation
        Student student1("Charlie", "3");
        Student student2("Alice", "1");
        Student student3("Bob", "2");

        REQUIRE(tree.testInsert(student1) == true);
        REQUIRE(tree.testInsert(student2) == true);
        REQUIRE(tree.testInsert(student3) == true);

        // After left-right rotation, "Bob" should be the new root
        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right->_student._id == "3");
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Right-Left Rotation"){
        // Insert nodes to trigger right-left rotation
        Student student1("Alice", "1");
        Student student2("Charlie", "3");
        Student student3("Bob", "2");

        REQUIRE(tree.testInsert(student1) == true);
        REQUIRE(tree.testInsert(student2) == true);
        REQUIRE(tree.testInsert(student3) == true);

        // After right-left rotation, "Bob" should be the new root
        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right->_student._id == "3");
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Complex Insertion Sequence") {
        Student students[] = {
                {"Alice", "20"}, {"Bob", "4"}, {"Charlie", "26"},
                {"David", "3"}, {"Eve", "9"}, {"Frank", "15"},
                {"Grace", "21"}, {"Heidi", "30"}, {"Ivan", "2"},
                {"Judy", "7"}, {"Mallory", "11"}, {"Niaj", "17"},
                {"Olivia", "23"}, {"Peggy", "8"}, {"Sybil", "10"}
        };

        for (const auto& student : students) {
            tree.testInsert(student);
            REQUIRE(tree.validateTree() == true);
        }

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.validateTree() == true);
    }
}
TEST_CASE("Remove Node Given ID"){
    AVL tree;

    SECTION("Remove Leaf Node"){
        Student student1("Alice", "1");
        Student student2("Bob", "2");
        Student student3("Charlie", "3");

        tree.testInsert(student1);
        tree.testInsert(student2);
        tree.testInsert(student3);

        REQUIRE(tree.removeStudent("3") == true);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right == nullptr);
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Remove Node with One Child") {
        Student student1("Alice", "1");
        Student student2("Bob", "2");
        Student student3("Charlie", "3");
        Student student4("David", "4");

        tree.testInsert(student1);
        tree.testInsert(student2);
        tree.testInsert(student3);
        tree.testInsert(student4);

        REQUIRE(tree.removeStudent("3") == true);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_right->_student._id == "4");
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Remove Node with Two Children") {
        Student student1("Alice", "1");
        Student student2("Bob", "2");
        Student student3("Charlie", "3");
        Student student4("David", "0");
        Student student5("Eve", "5");

        tree.testInsert(student1);
        tree.testInsert(student2);
        tree.testInsert(student3);
        tree.testInsert(student4);
        tree.testInsert(student5);

        REQUIRE(tree.removeStudent("2") == true);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "3");
        REQUIRE(tree.getRoot()->_left->_student._id == "1");
        REQUIRE(tree.getRoot()->_left->_left->_student._id == "0");
        REQUIRE(tree.getRoot()->_right->_student._id == "5");
        REQUIRE(tree.validateTree() == true);
    }

    SECTION("Complex Removal Sequence") {
        Student students[] = {
                {"Sybil", "10"}, {"Mallory", "11"}, {"Frank", "15"},
                {"Niaj", "17"}, {"Ivan", "2"}, {"Alice", "20"},
                {"Grace", "21"}
        };

        for (const auto& student : students) {
            tree.testInsert(student);
            REQUIRE(tree.validateTree() == true);
        }

        // Remove some nodes and validate after each removal
        REQUIRE(tree.getRoot()->_student._id == "17");
        REQUIRE(tree.removeStudent("17") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "2");
        REQUIRE(tree.removeStudent("2") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "20");
        REQUIRE(tree.removeStudent("20") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "11");
        REQUIRE(tree.removeStudent("11") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "15");
        REQUIRE(tree.removeStudent("15") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "21");
        REQUIRE(tree.removeStudent("21") == true);
        REQUIRE(tree.validateTree() == true);

        REQUIRE(tree.getRoot()->_student._id == "10");
        REQUIRE(tree.removeStudent("10") == true);
        REQUIRE(tree.validateTree() == true);
    }
}
TEST_CASE("Remove Nth Node"){}
TEST_CASE("Printing"){
    AVL tree;

    /********** Testing Inorder Printing **********/
    SECTION("Empty Tree") {
        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str().empty());
    }

    SECTION("Single Node Tree") {
        Student student("Kyrie Irving", "66666666");
        tree.insertStudent(student);
        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str() == "Kyrie Irving");
    }

    SECTION("3 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str() == "LeBron James, Stephen Curry, Kevin Durant");
    }

    SECTION("5 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        tree.insertStudent(Student("Anthony Davis", "45678901"));
        tree.insertStudent(Student("James Harden", "56789012"));
        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str() == "LeBron James, Stephen Curry, Kevin Durant, Anthony Davis, James Harden");
    }

    /********** Testing Preorder Printing **********/
    SECTION("Empty Tree") {
        stringstream ss;
        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str().empty());
    }

    SECTION("Single Node Tree") {
        Student student("Kyrie Irving", "66666666");
        tree.insertStudent(student);
        stringstream ss;
        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str() == "Kyrie Irving");
    }

    SECTION("3 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        stringstream ss;
        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str() == "Stephen Curry, LeBron James, Kevin Durant");
    }

    SECTION("5 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        tree.insertStudent(Student("Anthony Davis", "45678901"));
        tree.insertStudent(Student("James Harden", "56789012"));
        stringstream ss;
        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str() == "Stephen Curry, LeBron James, Anthony Davis, Kevin Durant, James Harden");
    }

    /********** Testing Postorder Printing **********/
    SECTION("Empty Tree") {
        stringstream ss;
        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str().empty());
    }

    SECTION("Single Node Tree") {
        Student student("Kyrie Irving", "66666666");
        tree.insertStudent(student);
        stringstream ss;
        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str() == "Kyrie Irving");
    }

    SECTION("3 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        stringstream ss;
        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str() == "LeBron James, Kevin Durant, Stephen Curry");
    }

    SECTION("5 Nodes Tree") {
        tree.insertStudent(Student("LeBron James", "12345678"));
        tree.insertStudent(Student("Stephen Curry", "23456789"));
        tree.insertStudent(Student("Kevin Durant", "34567890"));
        tree.insertStudent(Student("Anthony Davis", "45678901"));
        tree.insertStudent(Student("James Harden", "56789012"));
        stringstream ss;
        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str() == "LeBron James, Kevin Durant, James Harden, Anthony Davis, Stephen Curry");
    }
}

