#ifndef _TESTBASE_HPP_
#define _TESTBASE_HPP_

#include <iostream>

#include "ArrayXYZ.hpp"

#define TESTBASE_DEFAULT_TOLERANCE 1.0e-9

class TestBase {

private:

    static std::ostream *pout_;

    static int test_count_;
    static int test_passed_count_;
    static int test_failed_count_;
    static double tolerance_;

public:

    TestBase();

    ~TestBase();

    static void setOut(std::ostream *pout);

    static void setTolerance(const double &tolerance);

    /**
     * @brief write a report.
     *
     * @return int
     */
    static int report();

    static void TestTrueFunc(bool expression, const char *expression_source, const char *file, int line);

    static void TestFalseFunc(bool expression, const char *expression_source, const char *file, int line);

    static void TestNotNullFunc(void *expression, const char *expression_source, const char *file, int line);

    static void TestNullFunc(void *expression, const char *expression_source, const char *file, int line);

    /**
     * @brief double version
     *
     * @param calculated_value
     * @param calculated_source
     * @param extpected_value
     * @param file
     * @param line
     */
    static void DoubleEqualsFunc(double calculated_value, const char *calculated_source, double extpected_value, const char *file, int line);

    /**
     * @brief int version
     *
     * @param calculated_value
     * @param calculated_source
     * @param extpected_value
     * @param file
     * @param line
     */
    static void IntEqualsFunc(int calculated_value, const char *calculated_source, int extpected_value, const char *file, int line);

    /**
     * @brief size_t version
     *
     * @param calculated_value
     * @param calculated_source
     * @param extpected_value
     * @param file
     * @param line
     */
    static void SizetEqualsFunc(std::size_t calculated_value, const char *calculated_source, std::size_t extpected_value, const char *file, int line);

    /**
     * @brief string version
     *
     * @param calculated_value
     * @param calculated_source
     * @param extpected_value
     * @param file
     * @param line
     */
    static void StringEqualsFunc(const std::string &calculated_value, const char *calculated_source, const std::string &extpected_value, const char *file, int line);

    /**
     * @brief pointer version
     *
     * @param calculated_value
     * @param calculated_source
     * @param extpected_value
     * @param file
     * @param line
     */
    static void PtrEqualsFunc(void *calculated_value, const char *calculated_source, void *extpected_value, const char *file, int line);

    /**
     * @brief ArrayXYZ version
     *
     * @param calculated_value
     * @param calculated_source
     * @param expected_value
     * @param file
     * @param line
     */
    static void XYZEqualsFunc(const ArrayXYZ &calculated_value, const char *calculated_source, const ArrayXYZ &expected_value, const char *file, int line);
};

#define test_true(EXPRESSION) TestTrueFunc(EXPRESSION, #EXPRESSION, __FILE__, __LINE__)

#define test_false(EXPRESSION) TestFalseFunc(EXPRESSION, #EXPRESSION, __FILE__, __LINE__)

#define test_not_null(EXPRESSION) TestNotNullFunc(EXPRESSION, #EXPRESSION, __FILE__, __LINE__)

#define test_null(EXPRESSION) TestNullFunc(EXPRESSION, #EXPRESSION, __FILE__, __LINE__)

#define test_double_equals(CALCULATED, EXPECTED) DoubleEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#define test_int_equals(CALCULATED, EXPECTED) IntEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#define test_sizet_equals(CALCULATED, EXPECTED) SizetEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#define test_string_equals(CALCULATED, EXPECTED) StringEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#define test_ptr_equals(CALCULATED, EXPECTED) PtrEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#define test_xyz_equals(CALCULATED, EXPECTED) XYZEqualsFunc(CALCULATED, #CALCULATED, EXPECTED, __FILE__, __LINE__)

#endif // _TESTBASE_HPP_
