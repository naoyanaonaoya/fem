#include <iostream>
#include "ArrayXYZ.hpp"
#include "ElementTri.hpp"
#include "ElementQuad.hpp"
#include "Array.hpp"
#include "Matrix.hpp"
#include "Node.hpp"

/**
 * @fn
 * @brief main function
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
    std::cout << "Hello, world!\n";

    Logger::openLog("./test", 0);
    Logger::out << "test\n";
    Logger::out << "hello world\n";
    Logger::closeLog();

    ArrayXYZ v1(1.0, 2.0, 3.0);
    std::cout << v1 << std::endl;
    ArrayXYZ v2(4.0, 5.0, 6.0);
    std::cout << v2 << std::endl;
    ArrayXYZ v3 = v1 + v2;
    std::cout << v3 << std::endl;

    Array<3> a3_1(1.0, 2.0, 3.0);

    Array<4> a4_1(4.0, 3.0, 2.0, 1.0);
    std::cout << "========\n";
    Array<4> a4_2;
    std::cout << a4_2 << std::endl;
    a4_1 = a4_1;
    a4_2.clear();
    a4_2 = a4_1;
    std::cout << a4_2 << std::endl;
    std::cout << "========\n";
    
    // Array<3> a3_2 = a3_1;
    // Array<4> a4_3 = a3_1;

    std::cout << "========\n";
    a4_2 = a4_1 + a4_1;
    std::cout << a4_2 << std::endl;
    std::cout << "========\n";



    ElementTri t1;
    ElementQuad q1;
    std::vector<Node*> nodes3;
    std::vector<Node*> nodes4;
    ArrayXYZ v4(1.0, 2.0, 3.0);
    Node node0 = Node(v4);
    Node node1 = Node(v4);
    Node node2 = Node(v4);
    for (int i = 0; i < 3; i++) {
        nodes3.push_back(&node0);
    }
    for (int i = 0; i < 4; i++) {
        nodes4.push_back(&node0);
    }
    t1.setNodes(nodes3);
    q1.setNodes(nodes4);
    // ElementQuad e1(0, 1, 2, 3);

    Matrix<4, 4> m44_0;
    Matrix<3, 2> m32_0;
    Matrix<2, 1> m21_0;
    m44_0.clear();
    m32_0.clear();
    m21_0.clear();
    for (std::size_t i = 0; i < m44_0.sizeRow(); i++)
        for (std::size_t j = 0; j < m44_0.sizeCol(); j++)
            m44_0(i, j) = i * m44_0.sizeCol() + j;
    for (std::size_t i = 0; i < m32_0.sizeRow(); i++)
        for (std::size_t j = 0; j < m32_0.sizeCol(); j++)
            m32_0(i, j) = i * m32_0.sizeCol() + j;
    for (std::size_t i = 0; i < m21_0.sizeRow(); i++)
        for (std::size_t j = 0; j < m21_0.sizeCol(); j++)
            m21_0(i, j) = i * m21_0.sizeCol() + j;

    std::cout << "test0" << std::endl;

    Matrix<4, 4> m44_1;
    m44_1.clear();
    for (std::size_t i = 0; i < m44_1.sizeRow(); i++)
        for (std::size_t j = 0; j < m44_1.sizeCol(); j++)
            m44_1(j, i) = i * m44_1.sizeCol() + j;

    std::cout << "m44_0" << std::endl;
    std::cout << m44_0 << std::endl;
    std::cout << "m44_1" << std::endl;
    std::cout << m44_1 << std::endl;
    Matrix<4, 4> m44_2 = m44_0 + m44_1;
    std::cout << "m44_2" << std::endl;
    std::cout << m44_2 << std::endl;

    Matrix<4, 4> m44_3 = -m44_0;
    std::cout << "m44_3" << std::endl;
    std::cout << m44_3 << std::endl;

    Matrix<4, 3> m43_0;
    for (std::size_t i = 0; i < m43_0.sizeRow(); i++)
        for (std::size_t j = 0; j < m43_0.sizeCol(); j++)
            m43_0(i, j) = i * m43_0.sizeCol() + j;
    std::cout << "m43_0" << std::endl;
    std::cout << m43_0 << std::endl;
    Matrix<4, 3> m43_1 = m44_0 * m43_0;
    std::cout << "m43_1" << std::endl;
    std::cout << m43_1 << std::endl;
    // Matrix<4, 2> m43_2 = m44_0 * m32_0;
    // std::cout << "m43_2" << std::endl;
    // std::cout << m43_2 << std::endl;

    // this code should make error at the compile timing!!
    // m44_2 = m44_0 + m32_0;
    // std::cout << m44_2 << std::endl;
    
    Matrix<4, 2> m42_0(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    std::cout << m42_0 << std::endl;

    return 0;
}

