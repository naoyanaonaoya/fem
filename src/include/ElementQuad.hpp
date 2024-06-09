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

    void SetNodes(Node* n1, Node* n2, Node* n3, Node* n4);

    /**
     * @brief Set the Nodes
     *
     * @param nodes
     */
    void SetNodes(const std::vector<Node*> &nodes) override;

    void SetNodes(const std::initializer_list<Node*> &nodes) override;

    size_t GetNumberOfNodes() override;

    void CalcInvariants1(double re) override;
    
    void CalcInvariants2(double delta_t) override;

    /**
     * @brief Calculate the area
     *
     */
    void CalcArea() override;

    void CalcArea3D() override;

    void AddVelD(ArrayXYZ& vel_d, int node_index) override;

    double CalculateTriangleArea(const ArrayXYZ p0, const ArrayXYZ p1, const ArrayXYZ p2);

    void UpdateElementNodesOrder();

    void CalcVelocityPrediction(double delta_t, double re);

    double CalcDivergenceAndCorrect(double epsilon);

    /**
     * @brief Calculate the volume
     *
     */
    void CalcVolume() override;

    /**
     * @brief Calculate the Courant number
     *
     * @param delta_t
     */
    double CalcCourantNumber(const double &delta_t) override;
};

#endif // _ELEMENTQUAD_H_
