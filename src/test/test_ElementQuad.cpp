#include "TestBase.hpp"
#include "ElementQuad.hpp"
#include "Logger.hpp"
#include "FileWriter.hpp"

class TestElementQuad : public TestBase {

private:

    Node nodes_[4];
    ElementQuad elem_;

    double re_;
    double delta_t_;
    double rot_;

public:

    void run();

private:

    void printVelocity();
    void applyVelocityDelta();
    void applyBoundaryCondition();
    void setup(double rot);
    void testInvariants();
    void testVelocityPrediction();
    void testVelocityCorrection();
    void outputVtk();

};

void TestElementQuad::setup(double rot) {
    this->re_ = 10.0;
    this->delta_t_ = 1.0e-3;
    this->rot_ = rot;

    Logger::out << "rotation : " << rot_ * 180.0 / M_PI << " deg.\n";

    for (int i = 0; i < 4; i++) {
        nodes_[i].clearElementRefs();
        nodes_[i].clearMass();
    }

    // setup
    double cosTheta = cos(this->rot_);
    double sinTheta = sin(this->rot_);
    nodes_[0].pos_.set(0.0 * cosTheta + 0.0 * (-sinTheta), 0.0 * sinTheta + 0.0 * cosTheta, 0.0);
    nodes_[1].pos_.set(2.0 * cosTheta + 0.0 * (-sinTheta), 2.0 * sinTheta + 0.0 * cosTheta, 0.0);
    nodes_[2].pos_.set(2.0 * cosTheta + 2.0 * (-sinTheta), 2.0 * sinTheta + 2.0 * cosTheta, 0.0);
    nodes_[3].pos_.set(0.0 * cosTheta + 2.0 * (-sinTheta), 0.0 * sinTheta + 2.0 * cosTheta, 0.0);
    for (int i = 0; i < 4; i++)
        nodes_[i].global_index_ = i + 1;
    elem_.setNodes({&nodes_[0], &nodes_[1], &nodes_[2], &nodes_[3]});
}

void TestElementQuad::testInvariants() {
    elem_.calcInvariants1(re_);

    nodes_[0].calcInvMass(delta_t_);
    nodes_[1].calcInvMass(delta_t_);
    nodes_[2].calcInvMass(delta_t_);
    nodes_[3].calcInvMass(delta_t_);

    for (int i = 0; i < 4; i++)
        test_double_equals(nodes_[i].m_, 1.0);

    double x0 = nodes_[0].pos_.x_;
    double x1 = nodes_[1].pos_.x_;
    double x2 = nodes_[2].pos_.x_;
    double x3 = nodes_[3].pos_.x_;
    double y0 = nodes_[0].pos_.y_;
    double y1 = nodes_[1].pos_.y_;
    double y2 = nodes_[2].pos_.y_;
    double y3 = nodes_[3].pos_.y_;

    double testAlphaY[4], testAlphaX[4], testBetaY[4], testBetaX[4], testGammaY[4], testGammaX[4];
    testAlphaY[0] = (1 - 0) * (y1 - y3) + (0 - 0) * (y2 - y0);
    testAlphaY[1] = (0 - 0) * (y1 - y3) + (1 - 0) * (y2 - y0);
    testAlphaY[2] = (0 - 1) * (y1 - y3) + (0 - 0) * (y2 - y0);
    testAlphaY[3] = (0 - 0) * (y1 - y3) + (0 - 1) * (y2 - y0);
    testAlphaX[0] = (1 - 0) * (x1 - x3) + (0 - 0) * (x2 - x0);
    testAlphaX[1] = (0 - 0) * (x1 - x3) + (1 - 0) * (x2 - x0);
    testAlphaX[2] = (0 - 1) * (x1 - x3) + (0 - 0) * (x2 - x0);
    testAlphaX[3] = (0 - 0) * (x1 - x3) + (0 - 1) * (x2 - x0);

    testBetaY[0]  = (0 - 0) * (y0 - y1) + (1 - 0) * (y3 - y2);
    testBetaY[1]  = (0 - 0) * (y0 - y1) + (0 - 1) * (y3 - y2);
    testBetaY[2]  = (1 - 0) * (y0 - y1) + (0 - 0) * (y3 - y2);
    testBetaY[3]  = (0 - 1) * (y0 - y1) + (0 - 0) * (y3 - y2);
    testBetaX[0]  = (0 - 0) * (x0 - x1) + (1 - 0) * (x3 - x2);
    testBetaX[1]  = (0 - 0) * (x0 - x1) + (0 - 1) * (x3 - x2);
    testBetaX[2]  = (1 - 0) * (x0 - x1) + (0 - 0) * (x3 - x2);
    testBetaX[3]  = (0 - 1) * (x0 - x1) + (0 - 0) * (x3 - x2);

    testGammaY[0] = (0 - 0) * (y0 - y3) + (1 - 0) * (y2 - y1);
    testGammaY[1] = (1 - 0) * (y0 - y3) + (0 - 0) * (y2 - y1);
    testGammaY[2] = (0 - 1) * (y0 - y3) + (0 - 0) * (y2 - y1);
    testGammaY[3] = (0 - 0) * (y0 - y3) + (0 - 1) * (y2 - y1);
    testGammaX[0] = (0 - 0) * (x0 - x3) + (1 - 0) * (x2 - x1);
    testGammaX[1] = (1 - 0) * (x0 - x3) + (0 - 0) * (x2 - x1);
    testGammaX[2] = (0 - 1) * (x0 - x3) + (0 - 0) * (x2 - x1);
    testGammaX[3] = (0 - 0) * (x0 - x3) + (0 - 1) * (x2 - x1);

    for (int i = 0; i < 4; i++) {
        test_double_equals(elem_.alphaNy_[i], testAlphaY[i]);
        test_double_equals(elem_.alphaNx_[i], testAlphaX[i]);
        test_double_equals( elem_.betaNy_[i],  testBetaY[i]);
        test_double_equals( elem_.betaNx_[i],  testBetaX[i]);
        test_double_equals(elem_.gammaNy_[i], testGammaY[i]);
        test_double_equals(elem_.gammaNx_[i], testGammaX[i]);
    }

    double testHx[4], testHy[4];
    for (int i = 0; i < 4; i++) {
        testHy[i] =          0.5 * testAlphaY[i];
        testHx[i] = (-1.0) * 0.5 * testAlphaX[i];
    }

    for (int i = 0; i < 4; i++) {
        test_double_equals(elem_.hx_[i], testHy[i]);
        test_double_equals(elem_.hy_[i], testHx[i]);
    }


    elem_.calcInvariants2(delta_t_);
}

void TestElementQuad::testVelocityPrediction() {
    this->nodes_[0].vel_.set(0.0, 0.0, 0.0);
    this->nodes_[1].vel_.set(0.0, 0.0, 0.0);
    this->nodes_[2].vel_.set(0.0, 0.0, 0.0);
    this->nodes_[3].vel_.set(0.0, 0.0, 0.0);
    this->elem_.p_ = 0.0;

    this->applyBoundaryCondition();

    Logger::out << "Start velocity prediction\n";

    elem_.calcVelocityPrediction(delta_t_, this->re_);
}

void TestElementQuad::testVelocityCorrection() {
    Logger::out << "Start velocity correction\n";
    double eps = 1.0e-4;
    double abs_div = this->elem_.calcDivergenceAndCorrect(eps);
    Logger::out << "abs_div : " << abs_div << "\n";
    Logger::out << "p : " << this->elem_.p_ << "\n";

    applyVelocityDelta();

    this->printVelocity();
}

void TestElementQuad::applyBoundaryCondition() {
    double u = 0.1 * cos(this->rot_);
    double v = 0.1 * sin(this->rot_);
    nodes_[0].vel_.set(u, v, 0.0);
}

void TestElementQuad::applyVelocityDelta() {
    for (int i = 0; i < 4; i++) {
        this->nodes_[i].gatherDVel();
        this->nodes_[i].applyDVel();
    }
    applyBoundaryCondition();
}

void TestElementQuad::printVelocity() {
    Logger::out << "vn : {" << nodes_[0].vel_;
    Logger::out << "," << nodes_[1].vel_;
    Logger::out << "," << nodes_[2].vel_;
    Logger::out << "," << nodes_[3].vel_ << "}" << "\n";
}

void TestElementQuad::outputVtk() {
    std::vector<Node*> tnodes(4);
    for (int i = 0; i < 4; i++) {
        tnodes[i] = &nodes_[i];
    };
    std::vector<Element*> telems(1);
    for (int i = 0; i < 1; i++) {
        telems[i] = &elem_;
    }
    for (int i = 0; i < 4; i++) {
        std::cout << elem_.nodes_[i]->pos_.x_ << " " << elem_.nodes_[i]->pos_.y_ << std::endl;
        std::cout << telems[0]->nodes_[i]->pos_.x_ << " " << telems[0]->nodes_[i]->pos_.y_ << std::endl;
    }

    FileWriter fr;
    fr.writeVtkCfdProcData("./test_quad_element.vtk", tnodes, telems);
}

class TestElementQuad4 : public TestBase {

public:

    Node nodes_[9];

    ElementQuad elems_[4];

    double re_ = 100;

    double delta_t_ = 1.0e-3;

    void run();

private:

    void setNode();

    void resetElementRefs();

    void setNodesToElem();

    void setNodesToElem_clockwise();

    void calcInvariants();

    void testNodes();

    void testElementRefs();

    void setRanksToElem_same();

    void testRanks_same();

    void testRnaks_4();
};

void TestElementQuad::run() {
    this->setOut(&Logger::out);
    this->setup(M_PI / 4.0);
    this->testInvariants();
    this->testVelocityPrediction();
    this->testVelocityCorrection();
    this->outputVtk();
}

int main(int argc, char *argv[]) {
    Logger::openLog("test_ElementQuad", 0);
    TestElementQuad test;
    test.run();

    return TestBase::report();
}
