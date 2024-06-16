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
        nodes_[i].ClearElementRefs();
        nodes_[i].ClearMass();
    }

    // setup
    double cosTheta = cos(this->rot_);
    double sinTheta = sin(this->rot_);
    nodes_[0].pos_.Set(0.0 * cosTheta + 0.0 * (-sinTheta), 0.0 * sinTheta + 0.0 * cosTheta, 0.0);
    nodes_[1].pos_.Set(2.0 * cosTheta + 0.0 * (-sinTheta), 2.0 * sinTheta + 0.0 * cosTheta, 0.0);
    nodes_[2].pos_.Set(2.0 * cosTheta + 2.0 * (-sinTheta), 2.0 * sinTheta + 2.0 * cosTheta, 0.0);
    nodes_[3].pos_.Set(0.0 * cosTheta + 2.0 * (-sinTheta), 0.0 * sinTheta + 2.0 * cosTheta, 0.0);
    for (int i = 0; i < 4; i++)
        nodes_[i].global_index_ = i + 1;
    elem_.SetNodes({&nodes_[0], &nodes_[1], &nodes_[2], &nodes_[3]});
}

void TestElementQuad::testInvariants() {
    elem_.CalcInvariants1(re_);

    nodes_[0].CalcMassInv(delta_t_);
    nodes_[1].CalcMassInv(delta_t_);
    nodes_[2].CalcMassInv(delta_t_);
    nodes_[3].CalcMassInv(delta_t_);

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


    elem_.CalcInvariants2(delta_t_);
}

void TestElementQuad::testVelocityPrediction() {
    this->nodes_[0].vel_.Set(0.0, 0.0, 0.0);
    this->nodes_[1].vel_.Set(0.0, 0.0, 0.0);
    this->nodes_[2].vel_.Set(0.0, 0.0, 0.0);
    this->nodes_[3].vel_.Set(0.0, 0.0, 0.0);
    this->elem_.p_ = 0.0;

    this->applyBoundaryCondition();

    Logger::out << "Start velocity prediction\n";

    elem_.CalcVelocityPrediction(delta_t_, this->re_);
}

void TestElementQuad::testVelocityCorrection() {
    Logger::out << "Start velocity correction\n";
    double eps = 1.0e-4;
    double abs_div = this->elem_.CalcDivergenceAndCorrect(eps);
    Logger::out << "abs_div : " << abs_div << "\n";
    Logger::out << "p : " << this->elem_.p_ << "\n";

    applyVelocityDelta();

    this->printVelocity();
}

void TestElementQuad::applyBoundaryCondition() {
    double u = 0.1 * cos(this->rot_);
    double v = 0.1 * sin(this->rot_);
    nodes_[0].vel_.Set(u, v, 0.0);
}

void TestElementQuad::applyVelocityDelta() {
    for (int i = 0; i < 4; i++) {
        this->nodes_[i].GatherVelD();
        this->nodes_[i].ApplyVelD();
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
    std::vector<ElementQuad*> telems(1);
    for (int i = 0; i < 1; i++) {
        telems[i] = &elem_;
    }
    for (int i = 0; i < 4; i++) {
        std::cout << elem_.nodes_[i]->pos_.x_ << " " << elem_.nodes_[i]->pos_.y_ << std::endl;
        std::cout << telems[0]->nodes_[i]->pos_.x_ << " " << telems[0]->nodes_[i]->pos_.y_ << std::endl;
    }

    FileWriter fr;
    fr.WriteVtkCfdProcData("./test_quad_element.vtk", tnodes, telems);
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

    void setProcsToElem_same();

    void setProcsToElem_4();

    void testProcs_same();

    void testProcs_4();

    void applyBoundaryCondition();

    void applyVelocityDelta();

    void testVelocityPrediction();

    void testVelocityCorrection();

    void outputVTK();
};

void TestElementQuad4::setNode() {
    /**
     * @brief Set the Node
     * 9 nodes, order:
     * 6 - 7 - 8
     * | 2 | 3 |
     * 3 - 4 - 5
     * | 0 | 1 |
     * 0 - 1 - 2
     */
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int ni = y * 3 + x;
            nodes_[ni].pos_.Set(2.0 * x, 2.0 * y, 0.0);
            nodes_[ni].global_index_ = ni;
            // std::cout << "n[" << ni << "] = " << n_[ni].pos_ << std::endl;
        }
    }
}

void TestElementQuad4::resetElementRefs() {
    for (int ni = 0; ni < 9; ni++) {
        nodes_[ni].ClearElementRefs();
    }
}

void TestElementQuad4::setNodesToElem() {
    /*
     * この関数が呼ばれる前に他のテストで ElementRef が作成済みだった場合に備えて
     * ElementRefを一旦クリアする
     */

    // int a = 0;
    // a++と++aはすこし異なる
    // test[a++] = 1;
    // test[0]に1が入ってから、aがインクリメントされる
    // n_[0].element_refs_array_[n_[0].element_ref_num_++].element_ = &e_[0];
    // std::cout << "n_[0].element_ref_num_ = " << n_[0].element_ref_num_ << std::endl;

    this->resetElementRefs();
    /**
     * @brief Set the element to the node
     * 9 nodes, 4 elements, order:
     * 6 - 7 - 8
     * | 2 | 3 |
     * 3 - 4 - 5
     * | 0 | 1 |
     * 0 - 1 - 2
     */
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            int ei = 2 * y + x;
            int ni = 3 * y + x;
            /* counter clockwise になるように注意 */
            elems_[ei].SetNodes(
                &nodes_[ni + 0],
                &nodes_[ni + 1],
                &nodes_[ni + 4],
                &nodes_[ni + 3]
            );
        }
    }
}

void TestElementQuad4::setNodesToElem_clockwise() {
    /*
     * この関数が呼ばれる前に他のテストで ElementRef が作成済みだった場合に備えて
     * ElementRefを一旦クリアする
     */
    resetElementRefs();

    /*
     * 要素に節点を登録する。ただし、要素0だけは、節点をわざと時計周りに登録する
     *
     * 要素の並び順は:
     *
     * 0  1
     * 3  2
     * こっちが正解？
     * 2 3
     * 0 1
     */
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            int ei = 2 * y + x;
            int ni = 3 * y + x;
            if (ei == 0) {
                /* 要素0だけ時計周り(通常と逆順)に節点を登録 */
                elems_[ei].SetNodes(
                    &nodes_[ni + 3],
                    &nodes_[ni + 4],
                    &nodes_[ni + 1],
                    &nodes_[ni    ]
                );
            } else {
                /* 通常は反時計周りに節点を登録 */
                elems_[ei].SetNodes(
                    &nodes_[ni    ],
                    &nodes_[ni + 1],
                    &nodes_[ni + 4],
                    &nodes_[ni + 3]
                );
            }
        }
    }
}

void TestElementQuad4::calcInvariants() {
    for (int ei = 0; ei < 4; ei++)
        elems_[ei].CalcInvariants1(re_);

    for (int ei = 0; ei < 4; ei++)
        elems_[ei].CalcInvariants2(delta_t_);
}

void TestElementQuad4::testNodes() {
    test_ptr_equals(elems_[0].nodes_[0], &nodes_[0]);
    test_ptr_equals(elems_[0].nodes_[1], &nodes_[1]);
    test_ptr_equals(elems_[0].nodes_[2], &nodes_[4]);
    test_ptr_equals(elems_[0].nodes_[3], &nodes_[3]);
    test_ptr_equals(elems_[1].nodes_[0], &nodes_[1]);
    test_ptr_equals(elems_[1].nodes_[1], &nodes_[2]);
    test_ptr_equals(elems_[1].nodes_[2], &nodes_[5]);
    test_ptr_equals(elems_[1].nodes_[3], &nodes_[4]);
    test_ptr_equals(elems_[2].nodes_[0], &nodes_[3]);
    test_ptr_equals(elems_[2].nodes_[1], &nodes_[4]);
    test_ptr_equals(elems_[2].nodes_[2], &nodes_[7]);
    test_ptr_equals(elems_[2].nodes_[3], &nodes_[6]);
    test_ptr_equals(elems_[3].nodes_[0], &nodes_[4]);
    test_ptr_equals(elems_[3].nodes_[1], &nodes_[5]);
    test_ptr_equals(elems_[3].nodes_[2], &nodes_[8]);
    test_ptr_equals(elems_[3].nodes_[3], &nodes_[7]);
}

void TestElementQuad4::testElementRefs() {
    test_int_equals(nodes_[0].element_ref_num_, 1);
    test_ptr_equals(nodes_[0].element_refs_[0].element_, &elems_[0]);
    test_int_equals(nodes_[0].element_refs_[0].index_in_element_, 0);

    test_int_equals(nodes_[1].element_ref_num_, 2);
    test_ptr_equals(nodes_[1].element_refs_[0].element_, &elems_[0]);
    test_int_equals(nodes_[1].element_refs_[0].index_in_element_, 1);
    test_ptr_equals(nodes_[1].element_refs_[1].element_, &elems_[1]);
    test_int_equals(nodes_[1].element_refs_[1].index_in_element_, 0);

    test_int_equals(nodes_[2].element_ref_num_, 1);
    test_ptr_equals(nodes_[2].element_refs_[0].element_, &elems_[1]);
    test_int_equals(nodes_[2].element_refs_[0].index_in_element_, 1);

    test_int_equals(nodes_[3].element_ref_num_, 2);
    test_ptr_equals(nodes_[3].element_refs_[0].element_, &elems_[0]);
    test_int_equals(nodes_[3].element_refs_[0].index_in_element_, 3);
    test_ptr_equals(nodes_[3].element_refs_[1].element_, &elems_[2]);
    test_int_equals(nodes_[3].element_refs_[1].index_in_element_, 0);

    test_int_equals(nodes_[4].element_ref_num_, 4);
    test_ptr_equals(nodes_[4].element_refs_[0].element_, &elems_[0]);
    test_int_equals(nodes_[4].element_refs_[0].index_in_element_, 2);
    test_ptr_equals(nodes_[4].element_refs_[1].element_, &elems_[1]);
    test_int_equals(nodes_[4].element_refs_[1].index_in_element_, 3);
    test_ptr_equals(nodes_[4].element_refs_[2].element_, &elems_[2]);
    test_int_equals(nodes_[4].element_refs_[2].index_in_element_, 1);
    test_ptr_equals(nodes_[4].element_refs_[3].element_, &elems_[3]);
    test_int_equals(nodes_[4].element_refs_[3].index_in_element_, 0);

    test_int_equals(nodes_[5].element_ref_num_, 2);
    test_ptr_equals(nodes_[5].element_refs_[0].element_, &elems_[1]);
    test_int_equals(nodes_[5].element_refs_[0].index_in_element_, 2);
    test_ptr_equals(nodes_[5].element_refs_[1].element_, &elems_[3]);
    test_int_equals(nodes_[5].element_refs_[1].index_in_element_, 1);

    test_int_equals(nodes_[6].element_ref_num_, 1);
    test_ptr_equals(nodes_[6].element_refs_[0].element_, &elems_[2]);
    test_int_equals(nodes_[6].element_refs_[0].index_in_element_, 3);

    test_int_equals(nodes_[7].element_ref_num_, 2);
    test_ptr_equals(nodes_[7].element_refs_[0].element_, &elems_[2]);
    test_int_equals(nodes_[7].element_refs_[0].index_in_element_, 2);
    test_ptr_equals(nodes_[7].element_refs_[1].element_, &elems_[3]);
    test_int_equals(nodes_[7].element_refs_[1].index_in_element_, 3);

    test_int_equals(nodes_[8].element_ref_num_, 1);
    test_ptr_equals(nodes_[8].element_refs_[0].element_, &elems_[3]);
    test_int_equals(nodes_[8].element_refs_[0].index_in_element_, 2);
}

void TestElementQuad4::setProcsToElem_same() {
    for (int ei = 0; ei < 4; ei++) {
        elems_[ei].SetRank(0);
    }
}

void TestElementQuad4::testProcs_same() {
    std::set<std::size_t> ranks;
    nodes_[0].GetRanks(ranks);
    test_sizet_equals(ranks.size(), 1);
    test_sizet_equals(ranks.count(0), 1);
    test_sizet_equals(ranks.count(1), 0);

    nodes_[4].GetRanks(ranks);
    test_sizet_equals(ranks.size(), 1);
    test_sizet_equals(ranks.count(0), 1);
    test_sizet_equals(ranks.count(1), 0);
}


void TestElementQuad4::setProcsToElem_4() {
    for (int ei = 0; ei < 4; ei++) {
        elems_[ei].SetRank(ei);
    }
}

void TestElementQuad4::testProcs_4() {
    std::set<std::size_t> ranks;
    nodes_[4].GetRanks(ranks);
    test_sizet_equals(ranks.size(), 4);
    for (int ei = 0; ei < 4; ei++) {
        test_sizet_equals(ranks.count(ei), 1);
    }
    test_sizet_equals(ranks.count(4), 0);
}

void TestElementQuad4::testVelocityPrediction() {
    for (int i = 0; i < 9; i++) {
        nodes_[i].vel_.Set(0.0, 0.0, 0.0);
    }
    for (int i = 0; i < 4; i++) {
        elems_[i].p_ = 0.0;
    }

    applyBoundaryCondition();
}

void TestElementQuad4::applyBoundaryCondition() {
    double u = 0.1;
    double v = 0.0;
    nodes_[0].vel_.Set(u, v, 0.0);
    nodes_[3].vel_.Set(u, v, 0.0);
    nodes_[6].vel_.Set(u, v, 0.0);
}

void TestElementQuad4::outputVTK() {
    std::vector<Node*> tnodes(9);
    for (std::size_t i = 0; i < tnodes.size(); i++) {
        tnodes[i] = &nodes_[i];
    };
    std::vector<ElementQuad*> telems(4);
    for (std::size_t i = 0; i < telems.size(); i++) {
        telems[i] = &elems_[i];
    }

    FileWriter fr;
    fr.WriteVtkCfdProcData("./test_quad_element.vtk", tnodes, telems);
}

void TestElementQuad::run() {
    this->setOut(&Logger::out);
    this->setup(M_PI / 4.0);
    this->testInvariants();
    this->testVelocityPrediction();
    this->testVelocityCorrection();
    this->outputVtk();
}

void TestElementQuad4::run() {
    this->setOut(&Logger::out);

    this->setNode();
    this->setNodesToElem();
    this->testNodes();
    this->testElementRefs();

    this->setProcsToElem_same();
    this->testProcs_same();

    this->setProcsToElem_4();
    this->testProcs_4();
    
    this->calcInvariants();

    this->testVelocityPrediction();
    
    // this->outputVTK();
}

int main(int argc, char *argv[]) {
    Logger::OpenLog("test_ElementQuad", 0);
    
    // TestElementQuad test;
    // test.run();

    TestElementQuad4 test4;
    test4.run();

    // Logger::out << "test0" << "\n";

    test4.report();
    Logger::CloseLog();

    // Logger::out << "test1" << "\n";

    std::cout << "test4" << std::endl;


    std::cout << "test4" << std::endl;

    return 0;
}
