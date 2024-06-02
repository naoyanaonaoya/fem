#ifndef _ELEMENTQUAD_H_
#define _ELEMENTQUAD_H_

#include "Node.hpp"
#include "Element.hpp"
#include "Array.hpp"
#include "ArrayXYZ.hpp"
#include "Matrix.hpp"
#include <initializer_list>

class ElementQuad : public Element {

private:

    //! shape function
    static Array<4> shape_a_, shape_b_, shape_c_, shape_d_;
    static Array<4> coefficient_a_, coefficient_b_, coefficient_c_, coefficient_d_;
    static Matrix<4, 4> N_ij_;

public:

    //! the four edge lengths
    int edge_length_[4];

    //! the four edge normals
    ArrayXYZ edge_normals_[4];

    /**
     * @brief Value obtained from shape function and y-coordinate
     */
    Array<4> alphaNx_;

    /**
     * @brief Value obtained from shape function and x-coordinate
     */
    Array<4> alphaNy_;

    /**
     * @brief Value obtained from shape function and x-coordinate
     */
    Array<4> betaNx_;

    /**
     * @brief Value obtained from shape function and x-coordinate
     */
    Array<4> betaNy_;

    /**
     * @brief Value obtained from shape function and x-coordinate
     */
    Array<4> gammaNx_;

    /**
     * @brief Value obtained from shape function and x-coordinate
     */
    Array<4> gammaNy_;

    double alpha_xy_;

    double beta_xy_;

    double gamma_xy_;

    Array<4> jacobian_;

    Array<4> roundN_roundX_;

    Array<4> roundN_roundY_;

    Array<4> hx_;

    Array<4> hy_;

    Array<4> hx_by_area_;

    Array<4> hy_by_area_;

    Matrix<4, 4> d_;

    Matrix<4, 4> mass_matrix_inv_;

    double lambda_;

    Array<4> dt_hx_by_m_;

    Array<4> dt_hy_by_m_;

    Array<4> du_;

    Array<4> dv_;

    Array<4> dw_;

    double p_;

    double delta_p_;

    double div_;

    double courant_number_;

    /**
     * @brief Construct a new Element Quad object
     *
     */
    ElementQuad();
    // ElementQuad() {
    //     this->numberOfNodes_ = 4;
    // }

    /**
     * @brief Set the Nodes object
     *
     * @param nodes
     */
    void setNodes(const std::vector<Node*> &nodes) override;

    void setNodes(const std::initializer_list<Node*> &nodes) override;

    size_t getNumberOfNodes() override;

    void calcInvariants1(double re);

    void calcInvariants2(double delta_t);

    /**
     * @brief Calculate the area
     *
     */
    void calcArea() override;

    void calcArea3D() override;

    void addDVel(ArrayXYZ& d_vel, int node_index) override;

    double calculateTriangleArea(const ArrayXYZ p0, const ArrayXYZ p1, const ArrayXYZ p2);

    void updateElementNodesOrder();

    void calcVelocityPrediction(double delta_t, double re);

    double calcDivergenceAndCorrect(double epsilon);

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
