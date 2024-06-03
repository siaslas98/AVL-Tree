#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/AVL.h"

TEST_CASE("Basic AVL Tree Operations", "[avl]") {
    AVL tree;

    SECTION("Insert and search nodes") {
        Student s1("Alice", 1);
        Student s2("Bob", 2);
        Student s3("Charlie", 3);

        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s2) == true);
        REQUIRE(tree.insertStudent(s3) == true);

        REQUIRE(tree.testContains(1) == true);
        REQUIRE(tree.testContains(2) == true);
        REQUIRE(tree.testContains(3) == true);
        REQUIRE(tree.testContains(4) == false);
    }

    SECTION("Avoid inserting duplicates") {
        Student s1("Alice", 1);
        REQUIRE(tree.insertStudent(s1) == true);
        REQUIRE(tree.insertStudent(s1) == false);
    }

    SECTION("Print in order") {
        Student s1("Brian", 1);
        Student s2("Brandon", 2);
        Student s3("Briana", 3);
        Student s4("Bella", 4);

        tree.insertStudent(s1);
        tree.insertStudent(s2);
        tree.insertStudent(s3);
        tree.insertStudent(s4);

        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        tree.printTreeInOrder();

        std::cout.rdbuf(old);
        std::string output = buffer.str();

        REQUIRE(output == "Brian, Brandon, Briana, Bella");
    }
}

