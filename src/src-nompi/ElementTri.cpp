#include "ElementTri.hpp"
#include "Array.hpp"
#include <initializer_list>
#include <stdexcept>

Array<3> ElementTri::shape_a_ = Array<3>(1.0, 0.0, 0.0);
Array<3> ElementTri::shape_b_ = Array<3>(0.0, 1.0, 0.0);
Array<3> ElementTri::shape_c_ = Array<3>(0.0, 0.0, 1.0);
Array<3> ElementTri::coefficient_a_ = Array<3>(1.0, 0.0, 0.0);
Array<3> ElementTri::coefficient_b_ = Array<3>(0.0, 1.0, 0.0);
Array<3> ElementTri::coefficient_c_ = Array<3>(0.0, 0.0, 1.0);

ElementTri::ElementTri() {
    number_of_nodes_ = 3;
    nodes_.resize(3, nullptr);
}

void ElementTri::SetNodes(const std::vector<Node*>& nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementTri requires exactly 3 nodes.");

    for (int i = 0; i < this->number_of_nodes_; i++)
        nodes_[i] = nodes[i];
}

void ElementTri::SetNodes(const std::initializer_list<Node *> &nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementTri requires exactly 3 nodes.");
    std::initializer_list<Node *>::iterator it = nodes.begin();
    for (int i = 0; i < this->number_of_nodes_; i++, it++) {
        this->nodes_[i] = *it;
        (*it)->AddElementRef(this, i);
    }
}

void ElementTri::CalcArea() {
    area_ = 0.5;
}

void ElementTri::CalcVolume() {
    volume_ = 0.0;
}

double ElementTri::CalcCourantNumber(const double &delta_t) {
    courantNumber_ = 1.0;
    return courantNumber_;
}
