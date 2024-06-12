#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/AVL.h"

/********** ALl Function calls starting with "test" is for testing private member functions **********/

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
        REQUIRE(tree.testContains("954699999") == false); // Tree does not contain this id
    }

    SECTION("Avoid Inserting Duplicates") {
        Student s1("Alice", "00000001"); // Use a valid 8-digit ID
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
        REQUIRE(tree.testIsValidName("John123") == false); // Digits in name
        REQUIRE(tree.testIsValidName("Alice!") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Mary_Jane") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Michael@Johnson") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Emily#Rose") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Robert$Smith") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Jessica%Lee") == false); // Non letter character
        REQUIRE(tree.testIsValidName("William&Brown") == false); // Non letter character
        REQUIRE(tree.testIsValidName("David*Wilson") == false); // Non letter character
        REQUIRE(tree.testIsValidName("Sarah Miller2") == false); // Digit in name
        REQUIRE(tree.testIsValidName("") == false);
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


        // 11 Invalid ID
        REQUIRE(tree.testIsValidID("1234567") == false); // Only 7 digits
        REQUIRE(tree.testIsValidID("123456789") == false); // 9 digits
        REQUIRE(tree.testIsValidID("abcdefgh") == false); // Non-numeric characters
        REQUIRE(tree.testIsValidID("1234abcd") == false); // Mixed numeric and alphabetic characters
        REQUIRE(tree.testIsValidID("12 345678") == false); // Space within digits
        REQUIRE(tree.testIsValidID("123-45678") == false); // Hyphen in middle
        REQUIRE(tree.testIsValidID("12.345678") == false); // Dot in digits
        REQUIRE(tree.testIsValidID(" 12345678") == false); // Leading space
        REQUIRE(tree.testIsValidID("12345678 ") == false); // Trailing space
        REQUIRE(tree.testIsValidID("?123 45678") == false); // Leading question mark
        REQUIRE(tree.testIsValidID("") == false); // Empty String
    }
}
TEST_CASE("Insertion/Rotation"){
    AVL tree;

    SECTION("Single Insertion"){
        Student student("John Doe", "12345678");
        tree.testInsert(student);

        REQUIRE(tree.getRoot() != nullptr);
        REQUIRE(tree.getRoot()->_student._id == "12345678");
        REQUIRE(tree.getRoot()->_height == 1);
    }

    SECTION("Right Rotation") {
        // Insert nodes to trigger right rotation
        Student student1("Alice", "3");
        Student student2("Bob", "2");
        Student student3("Charlie", "1");

        REQUIRE(tree.testInsert(student1) == true);
        REQUIRE(tree.testInsert(student2) == true);
        REQUIRE(tree.testInsert(student3) == true);

        // After right rotation, "Bob" should be the new root
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

    SECTION("More Complex Insertion Sequence") {
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
        REQUIRE(tree.getRoot()->_student._name == "Charlie");
        REQUIRE(tree.validateTree() == true);

        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str() == "Sybil, Mallory, Frank, Niaj, Ivan, Alice, Grace, Olivia, Charlie, David, Heidi, Bob, Judy, Peggy, Eve");

        ss.str("");
        ss.clear();

        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str() == "Charlie, Ivan, Frank, Mallory, Sybil, Niaj, Grace, Alice, Olivia, Bob, David, Heidi, Peggy, Judy, Eve");

        ss.str("");
        ss.clear();

        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str() == "Sybil, Mallory, Niaj, Frank, Alice, Olivia, Grace, Ivan, Heidi, David, Judy, Eve, Peggy, Bob, Charlie");

        ss.str("");
        ss.clear();
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

    SECTION("More Complex Removal Sequence") {
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
TEST_CASE("Remove Nth Node"){
    AVL tree;

    Student students[] = {
            {"Sybil", "10"},{"Mallory", "11"},{"Frank", "15"},
            {"Niaj", "17"}, {"Ivan", "2"}, {"Alice", "20"},
            {"Grace", "21"}, {"Olivia", "23"}, {"Charlie", "26"},
            {"David", "3"}, {"Heidi", "30"}, {"Bob", "4"},
            {"Judy", "7"},{"Peggy", "8"}, {"Eve", "9"}
    };

    for (const auto& student : students) {
        tree.testInsert(student);
        REQUIRE(tree.validateTree() == true);
    }

    REQUIRE(tree.getRoot()->_student._id == "23");


    stringstream ss;
    tree.testPrintInOrder(ss);

    // Remove the 5th student (in in-order traversal)
    int N = 5;
    REQUIRE(tree.removeNthStudent(tree.getRoot(), N) == true);
    REQUIRE(tree.validateTree() == true);

    ss.str(""); // Clear the stringstream
    tree.testPrintInOrder(ss);

    // Further tests can be added to remove other Nth students and verify the tree structure
    ss.str(""); // Clear the stringstream
    tree.testPrintInOrder(ss);

    N = 2;
    REQUIRE(tree.removeNthStudent(tree.getRoot(), N) == true);
    REQUIRE(tree.validateTree() == true);

    ss.str(""); // Clear the stringstream
    tree.testPrintInOrder(ss);
}
TEST_CASE("100 Student AVL Tree Insertion, Deletion, and Tree Validation"){
    AVL tree;
    Student students[] = {
            {"Alice", "00"}, {"Bob", "01"}, {"Chris", "02"},
            {"David", "03"}, {"Eve", "04"}, {"Young", "05"},
            {"Grace", "06"}, {"Heidi", "07"}, {"Ivan", "08"},
            {"Judy", "09"}, {"Mallory", "10"}, {"Niaj", "11"},
            {"Olivia", "12"}, {"Peggy", "13"}, {"Sybil", "14"},
            {"Trent", "15"}, {"Uma", "16"}, {"Victor", "17"},
            {"Walter", "18"}, {"Xavier", "19"}, {"Yvonne", "20"},
            {"Zach", "21"}, {"Amber", "22"}, {"Brian", "23"},
            {"Chloe", "24"}, {"Derek", "25"}, {"Elena", "26"},
            {"Felix", "27"}, {"Georgia", "28"}, {"Harry", "29"},
            {"Isabella", "30"}, {"Jack", "31"}, {"Karen", "32"},
            {"Leon", "33"}, {"Maria", "34"}, {"Nathan", "35"},
            {"Oscar", "36"}, {"Paula", "37"}, {"Quinn", "38"},
            {"Rachel", "39"}, {"Sam", "40"}, {"Tina", "41"},
            {"Umar", "42"}, {"Vera", "43"}, {"Wendy", "44"},
            {"Xander", "45"}, {"Yara", "46"}, {"Zane", "47"},
            {"Aiden", "48"}, {"Bella", "49"}, {"Caleb", "50"},
            {"Diana", "51"}, {"Ethan", "52"}, {"Fiona", "53"},
            {"Gavin", "54"}, {"Hannah", "55"}, {"Isaac", "56"},
            {"Jenna", "57"}, {"Kyle", "58"}, {"Lily", "59"},
            {"Mason", "60"}, {"Nina", "61"}, {"Owen", "62"},
            {"Piper", "63"}, {"Quincy", "64"}, {"Reed", "65"},
            {"Sophia", "66"}, {"Tyler", "67"}, {"Ursula", "68"},
            {"Victor", "69"}, {"Willow", "70"}, {"Xenia", "71"},
            {"Yusuf", "72"}, {"Zoe", "73"}, {"Arthur", "74"},
            {"Beth", "75"}, {"Cody", "76"}, {"Dana", "77"},
            {"Eli", "78"}, {"Faye", "79"}, {"George", "80"},
            {"Helen", "81"}, {"Ian", "82"}, {"Jade", "83"},
            {"Kane", "84"}, {"Lara", "85"}, {"Max", "86"},
            {"Nash", "87"}, {"Opal", "88"}, {"Paul", "89"},
            {"Quinn", "90"}, {"Ruth", "91"}, {"Steve", "92"},
            {"Tess", "93"}, {"Uma", "94"}, {"Violet", "95"},
            {"Walt", "96"}, {"Xander", "97"}, {"Yara", "98"},
            {"Zane", "99"}
    };

    vector<string> idsToRemove = {
            "30", "45", "50", "62", "66", "78", "80", "88", "94", "17"
    };

    for (auto& student : students) {
        tree.testInsert(student);
        REQUIRE(tree.validateTree() == true);
    }

    REQUIRE(tree.getRoot() != nullptr);
    REQUIRE(tree.validateTree() == true);

    for(auto& id: idsToRemove){
        tree.removeStudent(id);
    }

    REQUIRE(tree.validateTree() == true);
    stringstream ss;
    tree.testPrintInOrder(ss);
    REQUIRE(ss.str() == "Alice, Bob, Chris, David, Eve, Young, Grace, Heidi, Ivan, Judy,"
                        " Mallory, Niaj, Olivia, Peggy, Sybil, Trent, Uma, Walter, Xavier, Yvonne,"
                        " Zach, Amber, Brian, Chloe, Derek, Elena, Felix, Georgia, Harry, Jack,"
                        " Karen, Leon, Maria, Nathan, Oscar, Paula, Quinn, Rachel, Sam, Tina,"
                        " Umar, Vera, Wendy, Yara, Zane, Aiden, Bella, Diana, Ethan, Fiona,"
                        " Gavin, Hannah, Isaac, Jenna, Kyle, Lily, Mason, Nina, Piper, Quincy,"
                        " Reed, Tyler, Ursula, Victor, Willow, Xenia, Yusuf, Zoe, Arthur, Beth,"
                        " Cody, Dana, Faye, Helen, Ian, Jade, Kane, Lara, Max, Nash,"
                        " Paul, Quinn, Ruth, Steve, Tess, Violet, Walt, Xander, Yara, Zane");
    }
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
TEST_CASE("Five Incorrect Commands"){
    AVL tree;
    SECTION("Incorrect Names") {
        Student s1("Bro123", "45679999");
        Student s2("123Bro", "45679999" );
        Student s3("1b1b1b1b1", "45679999");
        Student s4("123456", "45679999");
        Student s5("????????", "45679999");

        REQUIRE(tree.insertStudent(s1) == false);
        REQUIRE(tree.insertStudent(s2) == false);
        REQUIRE(tree.insertStudent(s3) == false);
        REQUIRE(tree.insertStudent(s4) == false);
        REQUIRE(tree.insertStudent(s5) == false);
    }
    SECTION("Incorrect IDs") {
        Student s1("LeBron James", "4567999"); // 7 Digit Id
        Student s2("Stephen Curry", "456799999" ); // 9 Digit Id
        Student s3("Kevin Durant", "4567ccc9"); // Non digit characters
        Student s4("Anthony Davis", "ccc79999"); // Non digit characters
        Student s5("James Harden", ""); // Empty id

        REQUIRE(tree.insertStudent(s1) == false);
        REQUIRE(tree.insertStudent(s2) == false);
        REQUIRE(tree.insertStudent(s3) == false);
        REQUIRE(tree.insertStudent(s4) == false);
        REQUIRE(tree.insertStudent(s5) == false);
    }
}
TEST_CASE("Various Edge Cases"){
    AVL tree;

    SECTION("Removing non-existent id when there is no tree") {
        REQUIRE(tree.removeStudent("11111111") == false);
    }

    SECTION("Insert a student then remove a non-existent student") {
        Student s1("Lebron James", "45679999");
        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.removeStudent("22222222") == false);
    }

    SECTION("Insert 3 names with similar ids, then print in order, pre order, and post order"){
        Student s1("Lebron James", "00000001");
        Student s2("Stephen Curry", "00000002");
        Student s3("Kevin Durant", "00000003");

        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s2) == true);
        REQUIRE(tree.insertStudent(s3) == true);

        stringstream ss;
        tree.testPrintInOrder(ss);
        REQUIRE(ss.str() == "Lebron James, Stephen Curry, Kevin Durant");

        ss.str("");
        ss.clear();

        tree.testPrintPreOrder(ss);
        REQUIRE(ss.str() == "Stephen Curry, Lebron James, Kevin Durant");

        ss.str("");
        ss.clear();

        tree.testPrintPostOrder(ss);
        REQUIRE(ss.str() == "Lebron James, Kevin Durant, Stephen Curry");

        ss.str("");
        ss.clear();
    }
}
