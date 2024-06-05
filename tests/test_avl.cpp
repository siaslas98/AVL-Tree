#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/AVL.h"

TEST_CASE("Basic AVL Tree Operations", "[avl]") {
    AVL tree;

    SECTION("Insert and search nodes") {
        Student s1("Brandon", "45679999");
        Student s2("Brian", "35459999");
        Student s3("Briana", "87879999");
        Student s4("Bella", "95469999"); // Repeat id on next line
        Student s5("Bella", "95469999");
        Student s6("Benny", "954699999"); // Use 9 digits
        Student s7("Ben","00000000");

        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s2) == true);
        REQUIRE(tree.insertStudent(s3) == true);
        REQUIRE(tree.insertStudent(s4) == true);
        REQUIRE(tree.insertStudent(s5) == false);
        REQUIRE(tree.insertStudent(s6) == false);
        REQUIRE(tree.insertStudent(s7) == true);


        REQUIRE(tree.testContains("45679999") == true);
        REQUIRE(tree.testContains("35459999") == true);
        REQUIRE(tree.testContains("87879999") == true);
        REQUIRE(tree.testContains("95469999") == true);
        REQUIRE(tree.testContains("954699999") == false);
        REQUIRE(tree.testContains("00000000") == true);
    }

    SECTION("Avoid inserting duplicates") {
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

