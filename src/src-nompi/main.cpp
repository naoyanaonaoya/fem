#include <iostream>
#include "VectorXYZ.h"
#include "QuadElement.h"

/**
 * @fn
 * @brief main function
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {
    std::cout << "Hello, world!\n";

    VectorXYZ v1(1.0, 2.0, 3.0);
    std::cout << v1 << std::endl;
    VectorXYZ v2(4.0, 5.0, 6.0);
    std::cout << v2 << std::endl;
    VectorXYZ v3 = v1 + v2;
    std::cout << v3 << std::endl;

    QuadElement e1(0, 1, 2, 3);

    return 0;
}

