#include "TestBase.hpp"

#include <cmath>

std::ostream *TestBase::pout_ = &std::cout;

int TestBase::test_count_ = 0;
int TestBase::test_passed_count_ = 0;
int TestBase::test_failed_count_ = 0;
double TestBase::tolerance_ = 1.0e-10;

TestBase::~TestBase() {
    if (test_failed_count_ == 0) {
        *pout_ << "All tests passed.\n";
    } else {
        *pout_ << "Some tests failed.\n";
    }
}

TestBase::TestBase() {}

void TestBase::setOut(std::ostream *pout) {
    pout_ = pout;
}

void TestBase::setTolerance(const double &tolerance) {
    tolerance_ = tolerance;
}

int TestBase::report() {
    (*pout_) << "Test results : ";
    if (test_count_ == 0) {
        (*pout_) << "No tests were done.\n";
        return 0; 
    } else if (test_failed_count_ == 0) {
        (*pout_) << "All " << test_passed_count_ << " tests passed.\n";
        return 0;
    } else {
        (*pout_) << test_count_ << " tests done. ";
        (*pout_) << test_passed_count_ << " tests passed. ";
        (*pout_) << test_failed_count_ << " tests failed.\n";
        return 1;
    }
}

void TestBase::TestTrueFunc(
    bool expression,
    const char *expression_source,
    const char* file,
    int line
) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "] ";
    if (expression) {
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        test_failed_count_++;
        (*pout_) << "FAILED, true expected : ";
    }
    (*pout_) << "\"" << expression_source << "\" = " << expression << " at \""; 
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

void TestBase::TestFalseFunc(
    bool expression, const char *expression_source, const char *file, int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";
    if (!expression) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, false expected : ";
    }
    (*pout_) << "\"" << expression_source << "\" = " << expression << " at \"";
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

void TestBase::TestNotNullFunc(
    void *expression, const char *expression_source, const char *file, int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";
    if (expression != NULL) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, non NULL expected : ";
    }
    (*pout_) << "\"" << expression_source << "\" = " << expression << " at \"";
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

void TestBase::TestNullFunc(
    void *expression, const char *expression_source, const char *file, int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";
    if (expression == NULL) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, NULL expected : ";
    }
    (*pout_) << "\"" << expression_source << "\" = " << expression << " at \"";
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

/* double version */
void TestBase::DoubleEqualsFunc(
    double calculated_value, const char *calculated_source, double expected_value, const char *file,
    int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";
    double error = fabs(calculated_value - expected_value);

    if (error < tolerance_) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = " << calculated_value;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

/* int version */
void TestBase::IntEqualsFunc(
    int calculated_value, const char *calculated_source, int expected_value, const char *file,
    int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";

    if (calculated_value == expected_value) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = " << calculated_value;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

/* size_t version */
void TestBase::SizetEqualsFunc(
    size_t calculated_value, const char *calculated_source, size_t expected_value, const char *file,
    int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";

    if (calculated_value == expected_value) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = " << calculated_value;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

void TestBase::StringEqualsFunc(
    const std::string &calculated_value, const char *calculated_source,
    const std::string &expected_value, const char *file, int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";

    if (calculated_value == expected_value) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = " << calculated_value;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

/* pointer version */
void TestBase::PtrEqualsFunc(
    void *calculated_value, const char *calculated_source, void *expected_value, const char *file,
    int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";

    if (calculated_value == expected_value) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << std::hex << (unsigned long)expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = ";
    (*pout_) << std::hex << (unsigned long)calculated_value << std::dec;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}

/* VectorXY version */
void TestBase::XYZEqualsFunc(
    const ArrayXYZ &calculated_value, const char *calculated_source, const ArrayXYZ &expected_value,
    const char *file, int line) {
    test_count_++;
    (*pout_) << "[" << test_count_ << "]";

    ArrayXYZ diff = calculated_value - expected_value;
    if (diff.NormL2() < tolerance_) {
        /* test passed */
        test_passed_count_++;
        (*pout_) << "PASSED : ";
    } else {
        /* test failed */
        test_failed_count_++;
        (*pout_) << "FAILED, " << expected_value << " expected : ";
    }
    (*pout_) << "\"" << calculated_source << "\" = ";
    (*pout_) << calculated_source << "\" = " << calculated_value;
    (*pout_) << " at \"" << file << "\", line " << line << std::endl;
}
