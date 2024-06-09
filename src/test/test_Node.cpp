#include "Node.hpp"
#include "TestBase.hpp"

class TestNode : public TestBase {

private:

    Node node_;

public:

    void run();

private:

    void testPos();

    void testVel();

    void testMass();

    void testProcs();

};

void TestNode::testPos() {
    node_.pos_.x_ = 1.0;
    node_.pos_.y_ = 2.0;
    node_.pos_.z_ = 0.0;

    test_double_equals(node_.pos_.x_, 1.0);
    test_double_equals(node_.pos_.y_, 2.0);
    test_double_equals(node_.pos_.z_, 0.0);

    node_.SetPos(3.0, 4.0, 0.0);
    test_double_equals(node_.pos_.x_, 3.0);
    test_double_equals(node_.pos_.y_, 4.0);
    test_double_equals(node_.pos_.z_, 0.0);

    ArrayXYZ pos(5.0, 6.0, 0.0);
    node_.SetPos(pos);
    test_double_equals(node_.pos_.x_, 5.0);
    test_double_equals(node_.pos_.y_, 6.0);
    test_double_equals(node_.pos_.z_, 0.0);
}

void TestNode::testVel() {
    node_.vel_.x_ = 1.0;
    node_.vel_.y_ = 2.0;
    node_.vel_.z_ = 0.0;
    test_double_equals(node_.vel_.x_, 1.0);
    test_double_equals(node_.vel_.y_, 2.0);
    test_double_equals(node_.vel_.z_, 0.0);

    node_.SetVel(3.0, 4.0, 0.0);
    test_double_equals(node_.vel_.x_, 3.0);
    test_double_equals(node_.vel_.y_, 4.0);
    test_double_equals(node_.vel_.z_, 0.0);

    ArrayXYZ vel(5.0, 6.0, 0.0);
    node_.SetVel(vel);
    test_double_equals(node_.vel_.x_, 5.0);
    test_double_equals(node_.vel_.y_, 6.0);
    test_double_equals(node_.vel_.z_, 0.0);
}

void TestNode::testMass() {
    double delta_t = 1.0e-3;
    node_.m_ = 2.0;
    node_.CalcMassInv(delta_t);
    test_double_equals(node_.m_inv_, 0.5);
}

void TestNode::testProcs() {
    std::set<std::size_t> ranks;
    node_.GetRanks(ranks);
    test_int_equals(ranks.size(), 0);
}

void TestNode::run() {
    testPos();
    testVel();
    testMass();
    testProcs();
}

int main(int argc, char *argv[]) {
    TestNode test;
    test.run();
    return test.report();
}