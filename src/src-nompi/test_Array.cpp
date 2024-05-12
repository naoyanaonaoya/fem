#include "TestBase.hpp"
#include "Array.hpp"

class TestArray : public TestBase {

private:

public:
    void run();
        
};

void TestArray::run() {

    // declaration
    Array<2> a2_0(1.0, 2.0);
    test_double_equals(a2_0[0], 1.0);
    test_double_equals(a2_0[1], 2.0);
    a2_0.clear();
    test_double_equals(a2_0[0], 0.0);
    test_double_equals(a2_0[1], 0.0);
    std::cout << "clear" << std::endl;
    int a20Size = a2_0.size();
    test_int_equals(a20Size, 2);


    Array<2> a2_1(2.0, 3.0);
    Array<2> a2_2(3.0, 4.0);
    Array<2> a2_3 = a2_1 + a2_2;
    Array<2> a2_4 = a2_1 - a2_2;
    Array<2> a2_5 = a2_1 * a2_2;
    test_double_equals(a2_3[0], 5.0);
    test_double_equals(a2_3[1], 7.0);
    test_double_equals(a2_4[0], -1.0);
    test_double_equals(a2_4[1], -1.0);
    test_double_equals(a2_5[0], 6.0);
    test_double_equals(a2_5[1], 12.0);
    a2_3.clear();
    test_double_equals(a2_3[0], 0.0);    
    test_double_equals(a2_3[1], 0.0);    
    
    Array<2> a2_6(3.0, 4.0);
    double l1Norm = a2_6.NormL1();
    test_double_equals(l1Norm, 4.0);
    double l2Norm = a2_6.NormL2();
    test_double_equals(l2Norm, 5.0);

    Array<3> a3_0(2.0, 3.0, 4.0);
    Array<3> a3_1(1.0, 2.0, 3.0);
    double dotProduct = a3_0.Dot(a3_1);
    test_double_equals(dotProduct, 20.0);

    Array<3> a3_2;
    a3_2.clear();
    for (size_t i = 0; i < a3_2.size(); i++)
        test_double_equals(a3_2[i], 0.0);

    Array<3> a3_3(0.0, 1.0, 2.0);
    Array<3> a3_4(1.0, 2.0, 3.0);
    Array<3> a3_5(1.0, 2.0, 3.0);
    Array<3> a3_6(1.0, 2.0, 3.0);
    Array<3> a3_7(1.0, 2.0, 3.0);
    a3_4 += a3_3;
    a3_5 -= a3_3;
    a3_6 *= a3_3;
    test_double_equals(a3_4[0], 1.0);
    test_double_equals(a3_4[1], 3.0);
    test_double_equals(a3_4[2], 5.0);
    test_double_equals(a3_5[0], 1.0);
    test_double_equals(a3_5[1], 1.0);
    test_double_equals(a3_5[2], 1.0);
    test_double_equals(a3_6[0], 0.0);
    test_double_equals(a3_6[1], 2.0);
    test_double_equals(a3_6[2], 6.0);

    Array<4> a4_0(1.0, 2.0, 3.0, 4.0);
    Array<4> a4_1 = a4_0 + 2.0;
    Array<4> a4_2 = a4_0 - 2.0;
    Array<4> a4_3 = a4_0 * 2.0;
    test_double_equals(a4_1[0], 3.0);
    test_double_equals(a4_1[1], 4.0);
    test_double_equals(a4_1[2], 5.0);
    test_double_equals(a4_1[3], 6.0);
    test_double_equals(a4_2[0], -1.0);
    test_double_equals(a4_2[1], 0.0);
    test_double_equals(a4_2[2], 1.0);
    test_double_equals(a4_2[3], 2.0);
    test_double_equals(a4_3[0], 2.0);
    test_double_equals(a4_3[1], 4.0);
    test_double_equals(a4_3[2], 6.0);
    test_double_equals(a4_3[3], 8.0);

    a4_0 += 2.0;
    test_double_equals(a4_0[0], 3.0);
    test_double_equals(a4_0[1], 4.0);
    test_double_equals(a4_0[2], 5.0);
    test_double_equals(a4_0[3], 6.0);
    a4_0({1.0, 2.0, 3.0, 4.0});
    test_double_equals(a4_0[0], 1.0);
    test_double_equals(a4_0[1], 2.0);
    test_double_equals(a4_0[2], 3.0);
    test_double_equals(a4_0[3], 4.0);
    a4_0 -= 2.0;
    test_double_equals(a4_0[0], -1.0);
    test_double_equals(a4_0[1], 0.0);
    test_double_equals(a4_0[2], 1.0);
    test_double_equals(a4_0[3], 2.0);
    a4_0({1.0, 2.0, 3.0, 4.0});
    a4_0 *= 2.0;
    test_double_equals(a4_0[0], 2.0);
    test_double_equals(a4_0[1], 4.0);
    test_double_equals(a4_0[2], 6.0);
    test_double_equals(a4_0[3], 8.0);
}

int main(int argc, char *argv[]) {
    TestArray test;
    test.run();
    return test.report();
}
