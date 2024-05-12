#ifndef _ELEMENTQUAD_H_
#define _ELEMENTQUAD_H_

#include "Logger.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "Array.hpp"
#include "ArrayXYZ.hpp"

class ElementQuad : public Element {

private:

    //! shape function
    static Array<4> shape_a_, shape_b_, shape_c_, shape_d_;
    static Array<4> coefficient_a_, coefficient_b_, coefficient_c_, coefficient_d_;

public:

    //! pointer to the four nodes
    Node *nodes_[4];

    //! the four edge lengths
    int edge_length_[4];

    //! the four edge normals
    ArrayXYZ edge_normals_[4];

    /**
     * @brief Construct a new Element Quad object
     * 
     */
    ElementQuad() {
        this->numberOfNodes_ = 4;
    }

    /**
     * @brief Set the Nodes object
     * 
     * @param nodes 
     */
    void setNodes(const std::vector<Node *> &nodes);

    /**
     * @brief Calculate the area
     * 
     */
    void calcArea() override;

    /**
     * @brief Calculate the volume
     * 
     */
    void calcVolume() override;

    /**
     * @brief Calculate the Courant number
     * 
     * @param delta_t 
     */
    void calcCourantNumber(const double &delta_t) override;
};

#endif // _ELEMENTQUAD_H_
