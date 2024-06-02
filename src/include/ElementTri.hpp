#ifndef _ELEMENTTRI_HPP_
#define _ELEMENTTRI_HPP_

#include "Logger.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "Array.hpp"
#include "ArrayXYZ.hpp"
#include <initializer_list>

class ElementTri : public Element {

private:

    //! shape function
    static Array<3> shape_a_ ,shape_b_ ,shape_c_;

    //! coefficient
    static Array<3> coefficient_a_, coefficient_b_, coefficient_c_;

public:

    //! pointer to the three nodes
    Node *nodes_[3];

    //! the three edge lengths
    int edge_length_[3];

    ArrayXYZ *edge_normals_[3];


    ElementTri();

    void setNodes(const std::vector<Node*>& nodes) override;

    void setNodes(const std::initializer_list<Node *> &nodes) override;

    void calcArea() override;

    void calcVolume() override;

    void calcCourantNumber(const double &delta_t) override;
};

#endif // _ELEMENTTRI_HPP_
