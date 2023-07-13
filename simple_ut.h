/**
 * @file simple_ut.h
 * @author Marat Melgizin (m.melgizin@gmail.com)
 * @brief Simple Unit-Test Framework
 * @version 0.1
 *
 * @copyright Copyright (c) 2023
 *
 * This file contains the declarations and definitions of a simple unit testing framework.
 */

#ifndef SIMPLE_UT_H
#define SIMPLE_UT_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using test_function = std::function<void()>;

/**
* @struct test_case
* @brief Structure representing a test case.
*/
struct test_case
{
    std::string name;
    test_function func;
};

/**
* @brief Get the reference to the vector of test cases.
* @return Reference to the vector of test cases.
*/
std::vector<test_case>& get_test_cases()
{
    static std::vector<test_case> test_cases;
    return test_cases;
}

/**
* @def TEST(name)
* @brief Macro to define a test case function.
* @param name The name of the test case function.
*
* This macro is used to define a test case function.
* It also registers the test case by adding it to the vector of test cases.
*/
#define TEST(name)                                 \
    void name();                                   \
    static const bool name##_registered = [] {     \
        get_test_cases().push_back({#name, name}); \
        return true;                               \
    }();                                           \
    void name()

/**
* @def ASSERT_EQ(expected, actual)
* @brief Macro to assert that two values are equal.
* @param expected The expected value.
* @param actual The actual value.
*
* This macro compares the expected and actual values.
* If they are not equal, it throws a runtime_error exception with the corresponding error message.
*/
#define ASSERT_EQ(expected, actual)                                             \
    do                                                                          \
    {                                                                           \
        auto&& e = (expected);                                                  \
        auto&& a = (actual);                                                    \
        if (e != a)                                                             \
        {                                                                       \
            throw std::runtime_error(                                           \
                std::string(__FILE__) + ":" + std::to_string(__LINE__)          \
                + ": expected " + #expected + "==" + #actual);                  \
        }                                                                       \
    } while (0)

/**
* @def ASSERT_NE(expected, actual)
* @brief Macro to assert that two values are not equal.
* @param expected The expected value.
* @param actual The actual value.
*
* This macro compares the expected and actual values.
* If they are equal, it throws a runtime_error exception with the corresponding error message.
*/
#define ASSERT_NE(expected, actual)                                    \
    do                                                                 \
    {                                                                  \
        auto&& e = (expected);                                         \
        auto&& a = (actual);                                           \
        if (e == a)                                                    \
        {                                                              \
            throw std::runtime_error(                                  \
                std::string(__FILE__) + ":" + std::to_string(__LINE__) \
                + ": expected " + #expected + "!=" + #actual);         \
        }                                                              \
    } while (0)

/**
* @brief Run all the registered test cases and print the results.
* @param os The output stream where the results will be printed. Default is std::cout.
* @return The number of test failures.
*
* This function runs all the registered test cases and prints the results to the specified output stream.
* It returns the number of test failures.
*/
int run_all_tests(std::ostream& os = std::cout)
{
    int num_failures = 0;

    for (const auto& test : get_test_cases())
    {
        os << "Running test: " << test.name << "... ";
        try
        {
            test.func();
            os << "PASS\n";
        }
        catch (const std::exception& e)
        {
            os << "FAIL: " << e.what() << "\n";
            ++num_failures;
        }
        catch (...)
        {
            os << "FAIL: Unknown exception\n";
            ++num_failures;
        }
    }

    os << "Total tests run: " << get_test_cases().size() << std::endl;
    os << "Total failures: " << num_failures << std::endl;

    return num_failures;
}

#endif // !SIMPLE_UT_H