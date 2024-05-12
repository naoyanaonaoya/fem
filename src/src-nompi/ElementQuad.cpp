#include "ElementQuad.hpp"
#include "Array.hpp"

Array<4> ElementQuad::shape_a_ = Array<4>( 1.0 * 0.25,  1.0 * 0.25, 1.0 * 0.25,  1.0 * 0.25);
Array<4> ElementQuad::shape_b_ = Array<4>(-1.0 * 0.25,  1.0 * 0.25, 1.0 * 0.25, -1.0 * 0.25);
Array<4> ElementQuad::shape_c_ = Array<4>(-1.0 * 0.25, -1.0 * 0.25, 1.0 * 0.25,  1.0 * 0.25);
Array<4> ElementQuad::shape_d_ = Array<4>( 1.0 * 0.25, -1.0 * 0.25, 1.0 * 0.25, -1.0 * 0.25);
Array<4> ElementQuad::coefficient_a_ = Array<4>( 1.0,  1.0,  1.0,  1.0);
Array<4> ElementQuad::coefficient_b_ = Array<4>(-1.0,  1.0,  1.0, -1.0);
Array<4> ElementQuad::coefficient_c_ = Array<4>(-1.0, -1.0,  1.0,  1.0);
Array<4> ElementQuad::coefficient_d_ = Array<4>( 1.0, -1.0,  1.0, -1.0);

void ElementQuad::setNodes(const std::vector<Node *> &nodes) {
    if (nodes.size() != this->numberOfNodes_)
        throw std::invalid_argument("ElementQuad requires exactly 4 nodes.");

    for (int i = 0; i < this->numberOfNodes_; i++)
        nodes_[i] = nodes[i];
}

void ElementQuad::calcArea() {
    area_ = 0.5;
}

void ElementQuad::calcVolume() {
    volume_ = 0.0;
}

void ElementQuad::calcCourantNumber(const double &delta_t) {
    courantNumber_ = 1.0;
}
