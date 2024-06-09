#include "TestBase.hpp"
#include "Matrix.hpp"

class TestMatrix : public TestBase {

private:

public:

    void run();

};

void TestMatrix::run() {

    Matrix<3, 3> m33_0(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), i * m33_0.SizeCol() + j);
    m33_0.Clear();
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), 0.0);
    m33_0.Update({0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0});
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), i * m33_0.SizeCol() + j);

    Matrix<3, 3> m33_1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    Matrix<3, 3> m33_2 = m33_0 + m33_1;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_2(i, j), (m33_0(i, j) + m33_1(i, j)));
    Matrix<3, 3> m33_3 = m33_0 - m33_1;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_3(i, j), (m33_0(i, j) - m33_1(i, j)));
    Matrix<3, 3> m33_4 = m33_0 & m33_1;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_4(i, j), (m33_0(i, j) * m33_1(i, j)));

    m33_2.Clear();
    m33_2 += m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_2(i, j), (m33_0(i, j)));
    m33_2.Clear();
    m33_2 -= m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_2(i, j), (-m33_0(i, j)));

    Matrix<3, 3> m33_5 = m33_0 + 1.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_5(i, j), (m33_0(i, j) + 1.0));
    Matrix<3, 3> m33_6 = m33_0 - 1.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_6(i, j), (m33_0(i, j) - 1.0));
    Matrix<3, 3> m33_7 = m33_0 * 1.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_7(i, j), (m33_0(i, j) * 1.0));

    std::cout<< "tttttttttttttttttttttttttt\n";
    m33_0.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m33_1.Update(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    std::cout<< "tttttttttttttttttttttttttt\n";
    m33_0.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m33_0 += 2.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), (m33_1(i, j) + 2.0));
    m33_0.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m33_0 -= 2.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), (m33_1(i, j) - 2.0));
    m33_0.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    m33_0 *= 2.0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_0(i, j), (m33_1(i, j) * 2.0));


    m33_0.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    Matrix<3, 3> m33_8 = -m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_8(i, j), (m33_0(i, j) * (-1.0)));
    Matrix<3, 3> m33_9 = 1.0 + m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_9(i, j), (m33_0(i, j) + 1.0));
    Matrix<3, 3> m33_10 = 1.0 - m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_10(i, j), (-m33_0(i, j) + 1.0));
    Matrix<3, 3> m33_11 = 1.0 * m33_0;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_11(i, j), m33_0(i, j));

    // transpose
    m33_1.Update({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0});
    Matrix<3, 3> m33_12 = ~m33_1;
    std::cout << m33_1 << std::endl;
    std::cout << m33_12 << std::endl;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_12(i, j), m33_0(j, i));
    !m33_12;
    std::cout << "m33_12" << std::endl;
    std::cout << m33_12 << std::endl;
    for (size_t i = 0; i < m33_0.SizeRow(); i++)
        for (size_t j = 0; j < m33_0.SizeCol(); j++)
            test_double_equals(m33_12(i, j), m33_0(i, j));

    // Matrix and Vector multiplication.
    Matrix<4, 3> m43_0;
    for (std::size_t i = 0; i < m43_0.SizeRow(); i++)
        for (std::size_t j = 0; j < m43_0.SizeCol(); j++)
            m43_0(i, j) = i * m43_0.SizeCol() + j;
    Array<3> arr3_0;
    for (std::size_t i = 0; i < arr3_0.Size(); i++)
        arr3_0[i] = i;
    std::cout << m43_0 << std::endl;
    std::cout << arr3_0 << std::endl;
    Array<4> arr4_0 = m43_0 * arr3_0;
    std::cout << arr4_0 << std::endl;
    for (std::size_t i = 0; i < m43_0.SizeRow(); i++) {
        double sum = 0.0;
        for (std::size_t j = 0; j < m43_0.SizeCol(); j++) {
            sum += m43_0(i, j) * arr3_0[j];
        }
        test_double_equals(arr4_0[i], sum);
    }

    // Vector and Matrix multiplication.
    Array<3> arr3_1;
    for (std::size_t i = 0; i < arr3_1.Size(); i++)
        arr3_1[i] = i;
    Matrix<3, 4> m34_0;
    for (std::size_t i = 0; i < m34_0.SizeRow(); i++)
        for (std::size_t j = 0; j < m34_0.SizeCol(); j++)
            m34_0(i, j) = i * m34_0.SizeCol() + j;
    std::cout << arr3_1 << std::endl;
    std::cout << m34_0 << std::endl;
    Array<4> arr4_1 = arr3_1 * m34_0;
    std::cout << arr4_1 << std::endl;
    for (std::size_t j = 0; j < m34_0.SizeCol(); j++) {
        double sum = 0.0;
        for (std::size_t i = 0; i < arr3_1.Size(); i++) {
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
