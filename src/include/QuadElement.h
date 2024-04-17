#ifndef _QUADELEMENT_H_
#define _QUADELEMENT_H_

#include "Logger.h"
#include "Node.h"
#include "Element.h"
#include "VectorXYZ.h"

class QuadElement : public Element {

private:


public:

    Node *nodes_[4];

    int *edge_length_[4];

    VectorXYZ *edge_normals_[4];

    static int shape_a, shape_b, shape_c, shape_d;

    QuadElement(int shape_a, int shape_b, int shape_c, int shape_d) {
        shape_a = 0;
        shape_b = 0;
        shape_c = 0;
        shape_d = 0;
    }

    void calcArea() override {
        area_ = 0.5;
    }

    void calcVolume() override {
        volume_ = 0.0;
    }

    void calcCourantNumber(const double &delta_t) override {
        courantNumber_ = 1.0;
    }
};

#endif // _QUADELEMENT_H_
