#include "TestBase.hpp"
#include "Matrix.hpp"

class TestMatrix : public TestBase {

private:

public:
    void run();

};

void TestMatrix::run() {

    Matrix<3, 3> m3_0(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), i * m3_0.sizeCol() + j);
    m3_0.clear();
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), 0.0);
    m3_0({0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), i * m3_0.sizeCol() + j);

    Matrix<3, 3> m3_1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    Matrix<3, 3> m3_2 = m3_0 + m3_1;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_2(i, j), (m3_0(i, j) + m3_1(i, j)));
    Matrix<3, 3> m3_3 = m3_0 - m3_1;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_3(i, j), (m3_0(i, j) - m3_1(i, j)));
    Matrix<3, 3> m3_4 = m3_0 & m3_1;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_4(i, j), (m3_0(i, j) * m3_1(i, j)));

    m3_2.clear();
    m3_2 += m3_0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_2(i, j), (m3_0(i, j)));
    m3_2.clear();
    m3_2 -= m3_0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_2(i, j), (-m3_0(i, j)));

    Matrix<3, 3> m3_5 = m3_0 + 1.0;
    Matrix<3, 3> m3_6 = m3_0 - 1.0;
    Matrix<3, 3> m3_7 = m3_0 * 1.0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_5(i, j), (m3_0(i, j) + 1.0));
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_6(i, j), (m3_0(i, j) - 1.0));
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_7(i, j), (m3_0(i, j) * 1.0));

    m3_0({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m3_1({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m3_0 += 2.0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), (m3_1(i, j) + 2.0));
    m3_0({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m3_0 -= 2.0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), (m3_1(i, j) - 2.0));
    m3_0({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m3_0 *= 2.0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_0(i, j), (m3_1(i, j) * 2.0));

    
    m3_0({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    Matrix<3, 3> m3_8 = -m3_0; 
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_8(i, j), (m3_0(i, j) * (-1.0)));
    Matrix<3, 3> m3_9 = 1.0 + m3_0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_9(i, j), (m3_0(i, j) + 1.0));
    Matrix<3, 3> m3_10 = 1.0 - m3_0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_10(i, j), (-m3_0(i, j) + 1.0));
    Matrix<3, 3> m3_11 = 1.0 * m3_0;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m3_11(i, j), m3_0(i, j));

    m3_1({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    Matrix<3, 3> m33_12 = ~m3_1; 
    std::cout << m3_1 << std::endl;
    std::cout << m33_12 << std::endl;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m33_12(i, j), m3_0(j, i));
    !m33_12;
    std::cout << m33_12 << std::endl;
    for (size_t i = 0; i < m3_0.sizeRow(); i++)
        for (size_t j = 0; j < m3_0.sizeCol(); j++)
            test_double_equals(m33_12(i, j), m3_0(i, j));

    // Matrix<4, 3> m43_0;
    // m43_0.clear();
    // !m43_0;
    
    Matrix<4, 3> m43_0;
    Array<3> arr3_0;
    for (std::size_t i = 0; i < m43_0.sizeRow(); i++) 
        for (std::size_t j = 0; j < m43_0.sizeCol(); j++)
            m43_0(i, j) = i * m43_0.sizeCol() + j;
    for (std::size_t i = 0; i < arr3_0.size(); i++)
        arr3_0[i] = i;
    std::cout << m43_0 << std::endl;
    std::cout << arr3_0 << std::endl;
    Array<4> arr4_0 = m43_0 * arr3_0;
    std::cout << arr4_0 << std::endl;
    for (std::size_t i = 0; i < m43_0.sizeRow(); i++) {
        double sum = 0.0;
        for (std::size_t j = 0; j < m43_0.sizeCol(); j++) {
            sum += m43_0(i, j) * arr3_0[j];
        }
        test_double_equals(arr4_0[i], sum);
    }

    Array<3> arr3_1;
    for (std::size_t i = 0; i < arr3_1.size(); i++)
        arr3_1[i] = i;
    Matrix<3, 4> m34_0;
    for (std::size_t i = 0; i < m34_0.sizeRow(); i++) 
        for (std::size_t j = 0; j < m34_0.sizeCol(); j++)
            m34_0(i, j) = i * m34_0.sizeCol() + j;
    std::cout << arr3_1 << std::endl;
    std::cout << m34_0 << std::endl;
    Array<4> arr4_1 = arr3_1 * m34_0;
    std::cout << arr4_1 << std::endl;
    for (std::size_t j = 0; j < m34_0.sizeCol(); j++) {
        double sum = 0.0;
        for (std::size_t i = 0; i < arr3_1.size(); i++) {
            sum += arr3_1[i] * m34_0(i, j);
        }
        test_double_equals(arr4_1[j], sum);
    }
        
}

int main(int argc, char *argv[]) {
    TestMatrix test;
    test.run();
    return test.report();
}
