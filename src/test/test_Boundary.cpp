#include "Boundary.hpp"
#include "TestBase.hpp"

class TestBoundary : public TestBase {

private:

    Boundary boundary_;

    Node nodes_[4];

public:

    void run();

    void setup();

    void testApply();

};

void TestBoundary::setup() {
    nodes_[0].SetPos(0, 0, 0);
    nodes_[1].SetPos(1, 0, 0);
    nodes_[2].SetPos(2, 1, 0);
    nodes_[3].SetPos(3, 1, 0);
    boundary_.AddNode(&nodes_[0]);
    boundary_.AddNode(&nodes_[1]);
    boundary_.AddNode(&nodes_[2]);
    boundary_.AddNode(&nodes_[3]);
    // 速度を定める多項式の係数
    boundary_.a0_ = 6.0;
    boundary_.a1_ = 5.0;
    boundary_.a2_ = 4.0;
    boundary_.a3_ = 3.0;
    boundary_.a4_ = 2.0;
    boundary_.a5_ = 1.0;
    boundary_.b0_ = 0.6;
    boundary_.b1_ = 0.5;
    boundary_.b2_ = 0.4;
    boundary_.b3_ = 0.3;
    boundary_.b4_ = 0.2;
    boundary_.b5_ = 0.1;
    boundary_.exist_of_x_boundary_ = 1;
    boundary_.exist_of_y_boundary_ = 1;
    boundary_.exist_of_z_boundary_ = 1;
}

void TestBoundary::testApply() {
    boundary_.Apply(1.0);
    // 計算された速度を確認する (TestBase.hを参照)
    test_xyz_equals(nodes_[0].vel_, ArrayXYZ(6.0, 0.6, 0.0));
    test_xyz_equals(nodes_[1].vel_, ArrayXYZ(14.0, 1.4, 0.0));
    test_xyz_equals(nodes_[2].vel_, ArrayXYZ(37.0, 3.7, 0.0));
    test_xyz_equals(nodes_[3].vel_, ArrayXYZ(59.0, 5.9, 0.0));
}

void TestBoundary::run() {
    setup();
    testApply();
}

int main(int argc, char *argv[]) {
    TestBoundary test;
    test.run();
    return test.report();
}