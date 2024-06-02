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
    this->number_of_nodes_ = 3;
}

void ElementTri::setNodes(const std::vector<Node*>& nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementTri requires exactly 3 nodes.");

    for (int i = 0; i < this->number_of_nodes_; i++)
        nodes_[i] = nodes[i];
}

void ElementTri::setNodes(const std::initializer_list<Node *> &nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementTri requires exactly 3 nodes.");
    std::initializer_list<Node *>::iterator it = nodes.begin();
    for (int i = 0; i < this->number_of_nodes_; i++, it++) {
        this->nodes_[i] = *it;
        (*it)->addElementRef(this, i);
    }
}

void ElementTri::calcArea() {
    area_ = 0.5;
}

void ElementTri::calcVolume() {
    volume_ = 0.0;
}

void ElementTri::calcCourantNumber(const double &delta_t) {
    courantNumber_ = 1.0;
}
