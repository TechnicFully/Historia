#include "historia.hpp"

#include <chrono>
#include <exception>
#include <random>
#include <string>
#include <thread>

#include <gtest/gtest.h>


/**************************/
/***** Access methods *****/
/**************************/
/*** Previous */
TEST(Previous, returnsSameValue) {
    Historia<int> Historia;
    Historia.push(0);
    ASSERT_EQ(Historia.previous(), 0);
}

TEST(Previous, returnsPreviousValue) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.previous(), 0);
}

/*** Next ***/
TEST(Next, returnsSameValue) {
    Historia<int> Historia;
    Historia.push(0);
    ASSERT_EQ(Historia.next(), 0);
}

TEST(Next, returnsNextValue) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    Historia.previous();
    ASSERT_EQ(Historia.next(), 1);
}

/*** Current ***/
TEST(current, returnsCurrentValue) {
    Historia<int> Historia;
    Historia.push(0);
    ASSERT_EQ(Historia.current(), 0);
}

TEST(current, returnsCurrentValueAfterTwoPushes) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.current(), 1);
}

TEST(current, returnsEmptyResult) {
    Historia<int> Historia;
    std::optional<int> emptyResult = Historia.current();
    ASSERT_FALSE(emptyResult.has_value());
}

/*** First ***/
TEST(first, returnsFirstValue) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.first(), 0);
}

/*** Last ***/
TEST(last, returnsLastValue) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.last(), 1);
}


/****************************/
/***** Modifier methods *****/
/****************************/
/*** Push ***/
TEST(push, pushesCorrectValue) {
    Historia<int> Historia;
    Historia.push(0);
    ASSERT_EQ(Historia.current(), 0);
}

TEST(push, pushesTwoCorrectValues) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.current(), 1);
}

TEST(push, noDuplicateValues) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.size(), 2);
}

TEST(push, pushThreeValuesAndReturnsCorrectMiddleValue) {
    //Ensure that identical data that is not directly followed by another is not deleted
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    Historia.push(0);
    ASSERT_EQ(Historia.previous(), 1);
}

TEST(push, testLimit) {
    Historia<int> Historia;
    for (int i = 0; i < Historia.max_size(); i++) { 
        Historia.push(i);
    }

    for (size_t i = Historia.max_size(); i > 0; i--) { //Minimum size should always logically be zero
        Historia.previous();
    }

    ASSERT_EQ(Historia.current(), 0);
}

/*********************************/
/***** Informational methods *****/
/*********************************/
/*** Size ***/
TEST(size, sizeIsZeroWhenEmpty) {
    Historia<int> Historia;
    ASSERT_EQ(Historia.size(), 0);
}

TEST(size, sizeIsOneWhenOneElement) {
    Historia<int> Historia;
    Historia.push(0);
    ASSERT_EQ(Historia.size(), 1);
} 

TEST(size, noDuplicateElements) {
    Historia<int> Historia;
    Historia.push(0);
    Historia.push(1);
    ASSERT_EQ(Historia.size(), 2);
}

/*** MaxSize*/
TEST(maxSize, maxSizeIsGreaterThanZero) {
    Historia<int> Historia;
    ASSERT_GT(Historia.max_size(), 0);
}


/**********************************/
/***** Miscellaneous methods ******/
/**********************************/
TEST(constructor, constructDifferentTypes) {
    Historia<int> HistoriaInt;
    Historia<int*> HistoriaIntPointer;
    Historia<char> HistoriaChar;
    Historia<char*> HistoriaCharPointer;
    Historia<char**> HistoriaCharDoublePointer;
    Historia<bool> HistoriaBool;
    Historia<float> HistoriaFloat;
    Historia<wchar_t> HistoriaWideChar;
    Historia<long> HistoriaLong;
    Historia<double> HistoriaDouble;

    Historia<std::string> HistoriaStdString;
}


TEST(randomMethods, randomizedFunctionCalls) {
    Historia<int> history;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 7); // 8 methods

    for (int i = 0; i < 10000; i++) {
        int choice = distrib(gen);

        switch (choice) {
            case 0: std::cout << "Calling push" << std::endl; history.push(0);  break;
            case 1: std::cout << "Calling current" << std::endl; history.current(); break;
            case 2: std::cout << "Calling last" << std::endl; history.last(); break;
            case 3: std::cout << "Calling max_size" << std::endl; history.max_size(); break;
            case 4: std::cout << "Calling next " << std::endl; history.next(); break;
            case 5: std::cout << "Calling previous" << std::endl; history.previous(); break;
            case 6: std::cout << "Calling size" << std::endl; history.size(); break;
       }
    }
}


/****************/
/***** MAIN *****/
/****************/
int main(int argc, char** argv) {
    (void)argc; //Silence unused parameter warning
    (void)argv; //Silence unused parameter warning
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
