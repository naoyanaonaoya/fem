#include "ElementQuad.hpp"
#include "Array.hpp"
#include <initializer_list>
#include <stdexcept>

Array<4> ElementQuad::shape_a_ = Array<4>( 1.0 * 0.25,  1.0 * 0.25, 1.0 * 0.25,  1.0 * 0.25);
Array<4> ElementQuad::shape_b_ = Array<4>(-1.0 * 0.25,  1.0 * 0.25, 1.0 * 0.25, -1.0 * 0.25);
Array<4> ElementQuad::shape_c_ = Array<4>(-1.0 * 0.25, -1.0 * 0.25, 1.0 * 0.25,  1.0 * 0.25);
Array<4> ElementQuad::shape_d_ = Array<4>( 1.0 * 0.25, -1.0 * 0.25, 1.0 * 0.25, -1.0 * 0.25);
Array<4> ElementQuad::coefficient_a_ = Array<4>( 1.0,  1.0,  1.0,  1.0);
Array<4> ElementQuad::coefficient_b_ = Array<4>(-1.0,  1.0,  1.0, -1.0);
Array<4> ElementQuad::coefficient_c_ = Array<4>(-1.0, -1.0,  1.0,  1.0);
Array<4> ElementQuad::coefficient_d_ = Array<4>( 1.0, -1.0,  1.0, -1.0);
Matrix<4, 4> ElementQuad::N_ij_(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

/**
 * @brief constructor
 */
ElementQuad::ElementQuad() {
    number_of_nodes_ = 4;
    nodes_.resize(4, nullptr);  // 親クラスの nodes_ を初期化
}
// ElementQuad::ElementQuad() {
//     numberOfNodes_ = 4;
//     nodes_(4, nullptr);
// }

size_t ElementQuad::GetNumberOfNodes() {
    return number_of_nodes_;
}

void ElementQuad::SetNodes(Node* nodes0, Node* nodes1, Node* nodes2, Node* nodes3) {
    nodes_[0] = nodes0;
    nodes_[1] = nodes1;
    nodes_[2] = nodes2;
    nodes_[3] = nodes3;
    for (size_t i = 0; i < number_of_nodes_; i++)
        nodes_[i]->AddElementRef(this, i);
}

/**
 * @brief set four nodes
 *
 * @param nodes
 */
void ElementQuad::SetNodes(const std::vector<Node*> &nodes) {
    if (nodes.size() != number_of_nodes_)
        throw std::invalid_argument("ElementQuad requires exactly 4 nodes.");
    for (size_t i = 0; i < number_of_nodes_; i++) {
        // std::cout << "i = " << i << std::endl;
        nodes_[i] = nodes[i];
        nodes[i]->AddElementRef(this, i);
    }
}

/**
 * @brief set four nodes
 *
 * @param nodes
 */
void ElementQuad::SetNodes(const std::initializer_list<Node*> &nodes) {
    if (nodes.size() != number_of_nodes_)
        throw std::invalid_argument("ElementQuad requires exactly 4 nodes.");
    std::initializer_list<Node*>::iterator it = nodes.begin();
    for (size_t i = 0; i < number_of_nodes_; i++, it++) {
        // std::cout << "i = " << i << std::endl;
        nodes_[i] = *it;
        (*it)->AddElementRef(this, i);
    }
}

void ElementQuad::CalcInvariants1(double re) {
    double re_inv = 1.0 / re;
    double six_inv = 1.0 / 6.0;

    double x0 = nodes_[0]->pos_.x_;
    double y0 = nodes_[0]->pos_.y_;
    double x1 = nodes_[1]->pos_.x_;
    double y1 = nodes_[1]->pos_.y_;
    double x2 = nodes_[2]->pos_.x_;
    double y2 = nodes_[2]->pos_.y_;
    double x3 = nodes_[3]->pos_.x_;
    double y3 = nodes_[3]->pos_.y_;

    CalcArea3D();

    double alpha_xy = (x0 - x2) * (y1 - y3) + (x1 - x3) * (y2 - y0);
    double beta_xy  = (x2 - x3) * (y0 - y1) + (x0 - x1) * (y3 - y2);
    double gamma_xy = (x1 - x2) * (y0 - y3) + (x0 - x3) * (y2 - y1);
    alpha_xy_ = 1.0 / alpha_xy;
    beta_xy_ = 1.0 / beta_xy;
    gamma_xy_ = 1.0 / gamma_xy;
    double alpha_xy_inv = 1.0 / alpha_xy;
    // double beta_xy_inv = 1.0 / beta_xy_;
    // double gamma_xy_inv = 1.0 / gamma_xy;

    // concentrated mass
    for (size_t i = 0; i <  number_of_nodes_; i++) {
        nodes_[i]->m_ += 1.0 * six_inv * (3.0 * alpha_xy * shape_a_[i] + beta_xy * shape_b_[i] + gamma_xy * shape_c_[i]);
    }

    alphaNy_.Clear();
    alphaNx_.Clear();
    betaNy_.Clear();
    betaNx_.Clear();
    gammaNy_.Clear();
    gammaNx_.Clear();
    for (size_t i = 0; i < number_of_nodes_; i++) {
        alphaNy_[i] = (N_ij_(0, i) - N_ij_(2, i)) * (y1 - y3) + (N_ij_(1, i) - N_ij_(3, i)) * (y2 - y0);
        alphaNx_[i] = (N_ij_(0, i) - N_ij_(2, i)) * (x1 - x3) + (N_ij_(1, i) - N_ij_(3, i)) * (x2 - x0);
        betaNy_[i]  = (N_ij_(2, i) - N_ij_(3, i)) * (y0 - y1) + (N_ij_(0, i) - N_ij_(1, i)) * (y3 - y2);
        betaNx_[i]  = (N_ij_(2, i) - N_ij_(3, i)) * (x0 - x1) + (N_ij_(0, i) - N_ij_(1, i)) * (x3 - x2);
        gammaNy_[i] = (N_ij_(1, i) - N_ij_(2, i)) * (y0 - y3) + (N_ij_(0, i) - N_ij_(3, i)) * (y2 - y1);
        gammaNx_[i] = (N_ij_(1, i) - N_ij_(2, i)) * (x0 - x3) + (N_ij_(0, i) - N_ij_(3, i)) * (x2 - x1);
    }
    roundN_roundX_.Clear();
    roundN_roundY_.Clear();
    for (size_t i = 0; i < number_of_nodes_; i++) {
        roundN_roundX_[i] = (alphaNy_[i] * betaNy_[i] * coefficient_b_[i] + gammaNy_[i] * coefficient_c_[i]);
        roundN_roundY_[i] = (alphaNx_[i] * betaNx_[i] * coefficient_b_[i] + gammaNx_[i] * coefficient_c_[i]);
    }
    jacobian_.Clear();
    for (size_t i = 0; i < number_of_nodes_; i++) {
        jacobian_[i] = (alpha_xy_ * beta_xy_ * coefficient_b_[i] + gamma_xy_ * coefficient_c_[i]) * 0.125;
    }

    // pressure vecotr
    hx_.Clear();
    hy_.Clear();
    hx_by_area_.Clear();
    hy_by_area_.Clear();
    for (size_t i = 0; i < number_of_nodes_; i++) {
        hx_[i] =          0.5 * alphaNy_[i];
        hy_[i] = (-1.0) * 0.5 * alphaNx_[i];
    }
    for (size_t i = 0; i < number_of_nodes_; i++) {
        hx_by_area_[i] = hx_[i] / area_;
        hy_by_area_[i] = hy_[i] / area_;
    }

    // diffusion matrix
    for (size_t i = 0; i < number_of_nodes_; i++) {
        for (size_t j = 0; j < number_of_nodes_; j++) {
            double the_first_term = 3 * alphaNy_[i] * alphaNy_[j] + betaNy_[i] * betaNy_[j] + gammaNy_[i] * gammaNy_[j];
            double the_second_term = 3 * alphaNx_[i] * alphaNx_[j] + betaNx_[i] * betaNx_[j] + gammaNx_[i] * gammaNx_[j];
            double the_third_term = (-1.0) * beta_xy * alpha_xy_inv * (alphaNy_[i] * betaNy_[j] + betaNy_[i] * alphaNy_[j] + alphaNx_[i] * betaNx_[j] + betaNx_[i] * alphaNx_[j]);
            double the_fourth_term = (-1.0) * gamma_xy * alpha_xy_inv * (alphaNy_[i] * gammaNy_[j] + gammaNy_[i] * alphaNy_[j] + alphaNx_[i] * gammaNx_[j] + gammaNx_[i] * alphaNx_[j]);
            d_(i, j) = re_inv + six_inv * alpha_xy_inv * (the_first_term + the_second_term + the_third_term + the_fourth_term);
        }
    }
}

void ElementQuad::CalcInvariants2(double delta_t) {

    mass_matrix_inv_.Clear();
    for (size_t i = 0; i <  number_of_nodes_; i++)
        mass_matrix_inv_(i, i) = 1.0 / nodes_[i]->m_;

    double hx_m_hx = hx_ * mass_matrix_inv_ * hx_;
    double hy_m_hy = hy_ * mass_matrix_inv_ * hy_;
    lambda_ = area_ / (delta_t * (hx_m_hx + hy_m_hy));

    dt_hx_by_m_ = delta_t * mass_matrix_inv_ * hx_;
    dt_hy_by_m_ = delta_t * mass_matrix_inv_ * hy_;
}

void ElementQuad::CalcVelocityPrediction(double delta_t, double re) {

    Array<4> u(
        nodes_[0]->vel_.x_,
        nodes_[1]->vel_.x_,
        nodes_[2]->vel_.x_,
        nodes_[3]->vel_.x_
    );
    Array<4> v(
        nodes_[0]->vel_.y_,
        nodes_[1]->vel_.y_,
        nodes_[2]->vel_.y_,
        nodes_[3]->vel_.y_
    );


    /** calculate advection term A
     */
    double au = shape_a_ * u;
    double bu = shape_b_ * u;
    double cu = shape_c_ * u;
    double du = shape_d_ * u;
    double av = shape_a_ * v;
    double bv = shape_b_ * v;
    double cv = shape_c_ * v;
    double dv = shape_d_ * v;

    Matrix<4, 4> a, ax, ay;
    a.Clear();
    ax.Clear();
    ay.Clear();
    double eightenn_inv = 1.0 / 18.0;
    for (int i = 0; i < number_of_nodes_; i++) {
        for (int j = 0; j < number_of_nodes_; j++) {
            double first_term_x = 9.0 * shape_a_[i] * au * alphaNy_[j];
            double first_term_y = 9.0 * shape_a_[i] * av * alphaNx_[j];
            double second_term_x = 3.0 * ((shape_b_[i] * bu + shape_c_[i] * cu) * alphaNy_[j] + (shape_a_[i] * bu + shape_b_[i] * au) * betaNy_[j] + (shape_a_[i] * cu + shape_c_[i] * au) * gammaNy_[j]);
            double second_term_y = 3.0 * ((shape_b_[i] * bv + shape_c_[i] * cv) * alphaNx_[j] + (shape_a_[i] * bv + shape_b_[i] * av) * betaNx_[j] + (shape_a_[i] * cv + shape_c_[i] * av) * gammaNx_[j]);
            double third_term_x = shape_d_[i] * du * alphaNy_[j] + (shape_d_[i] * cu + shape_c_[i] * du) * betaNy_[j] + (shape_d_[i] * bu + shape_b_[i] * du) * gammaNy_[j];
            double third_term_y = shape_d_[i] * dv * alphaNx_[j] + (shape_d_[i] * cv + shape_c_[i] * dv) * betaNx_[j] + (shape_d_[i] * bv + shape_b_[i] * dv) * gammaNx_[j];
            ax(i, j) = first_term_x + second_term_x + third_term_x;
            ay(i, j) = first_term_y + second_term_y + third_term_y;
        }
    }
    a = eightenn_inv * (ax - ay);

    double element_length = 0.0;
    double vel_x = 0.0;
    double vel_y = 0.0;
    for (int i = 0; i < 4; i++) {
        vel_x += nodes_[i]->vel_.x_;
        vel_y += nodes_[i]->vel_.y_;
    }
    ArrayXYZ vel(vel_x / 4.0, vel_y / 4.0, 0.0);
    double vel_norm = vel.NormL2();
    ArrayXYZ vel_normalize = vel.normalize();
    for (int i = 0; i < 4; i++) {
        element_length += std::fabs(vel_normalize.x_ * roundN_roundX_[i] + vel_normalize.y_ * roundN_roundY_[i]) / (8.0 * jacobian_[i]);
    }
    if (element_length < 1.0e-10) {
        element_length = area_;
        element_length = std::sqrt(element_length);
        element_length = 1.0 / element_length;
        element_length = 2.0 * element_length;
    } else {
        element_length = 1.0 / element_length;
        element_length = 2.0 * element_length;
    }
    double stabilization_parameter_first_term = (2.0 / delta_t) * (2.0 / delta_t);
    double stabilization_parameter_second_term = (2.0 * vel_norm / element_length) * (2.0 * vel_norm / element_length);
    double stabilization_parameter_third_term = (4.0 / (re * element_length * element_length)) * (4.0 / (re * element_length * element_length));
    double stabilization_parameter = 1.0 / std::sqrt(stabilization_parameter_first_term + stabilization_parameter_second_term + stabilization_parameter_third_term);

    Matrix<4, 4> a_supg, axx_supg, axy_supg, ayx_supg, ayy_supg;
    axx_supg.Clear();
    axy_supg.Clear();
    ayx_supg.Clear();
    ayy_supg.Clear();
    a_supg.Clear();
    double betaOverAlpha = beta_xy_ / alpha_xy_;
    double gammaOverAlpha = gamma_xy_ / alpha_xy_;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double first_term_xx   = alphaNy_[i] * alphaNy_[j] * ((      4.0 * au * au + 4.0 / 3.0 * bu * bu + 4.0 / 3.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0  * cu * du + 4.0 / 9.0  * du * cu) - gammaOverAlpha * (4.0 / 3.0 * au * cu + 4.0 / 9.0  * bu * cu + 4.0 / 9.0 * du * bu                       ));
            double second_term_xx  = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0 * cu * du + 4.0 / 9.0  * du * cu) - betaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0  * cu * cu + 4.0 / 15.0 * du * du) - gammaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0  * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au));
            double third_term_xx   = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * cu + 4.0 / 9.0 * bu * du + 4.0 / 3.0 * cu * au + 4.0 / 9.0  * du * bu) - betaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0  * cu * bu + 4.0 / 9.0  * du * au) - gammaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 9.0  * bu * bu + 4.0 / 4.0 * cu * cu + 4.0 / 15.0 * du * du));
            double fourth_term_xx  = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0 * cu * du + 4.0 / 9.0  * du * cu) - betaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0  * cu * cu + 4.0 / 15.0 * du * du) - gammaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0  * bu * cu * 4.0 / 9.0 * cu * bu * 4.0 / 9.0  * du * au));
            double fifth_term_xx   = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 5.0 * au * bu + 4.0 / 5.0 * bu * au + 4.0 / 15.0 * cu * du + 4.0 / 15.0 * du * cu) - gammaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 15.0 * bu * du + 4.0 / 9.0 * cu * au + 4.0 / 15.0 * du * bu));
            double sixth_term_xx   = alphaNy_[i] * alphaNy_[j] * ((4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au) - betaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 9.0 * cu * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0  * bu * au                                             ));
            double seventh_term_xx = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * cu + 4.0 / 9.0 * bu * du + 4.0 / 3.0 * cu * au + 4.0 / 9.0  * du * bu) - betaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0  * cu * bu + 4.0 / 9.0  * du * au) - gammaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 9.0  * bu * bu + 4.0 / 5.0 * cu * cu + 4.0 / 15.0 * du * du));
            double eighth_term_xx  = alphaNy_[i] * alphaNy_[j] * ((4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au) - betaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 9.0 * cu * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0  * bu * au                                             ));
            double ninth_term_xx   = alphaNy_[i] * alphaNy_[j] * ((4.0 / 3.0 * au * au + 4.0 / 9.0 * bu * bu * 4.0 / 5.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0 * bu * au + 4.0 / 15.0 * cu * du + 4.0 / 15.0 * du * cu) - gammaOverAlpha * (4.0 / 5.0 * au * cu + 4.0 / 15.0 * bu * du + 4.0 / 5.0 * cu * au + 4.0 / 15.0 * du * bu));

            double first_term_yx   = alphaNx_[i] * alphaNy_[j] * ((      4.0 * av * au + 4.0 / 3.0 * bv * bu + 4.0 / 3.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0  * cv * du + 4.0 / 9.0  * dv * cu) - gammaOverAlpha * (4.0 / 3.0 * av * cu + 4.0 / 9.0  * bv * cu + 4.0 / 9.0 * dv * bu                       ));
            double second_term_yx  = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0 * cv * du + 4.0 / 9.0  * dv * cu) - betaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0  * cv * cu + 4.0 / 15.0 * dv * du) - gammaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0  * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au));
            double third_term_yx   = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * cu + 4.0 / 9.0 * bv * du + 4.0 / 3.0 * cv * au + 4.0 / 9.0  * dv * bu) - betaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0  * cv * bu + 4.0 / 9.0  * dv * au) - gammaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 9.0  * bv * bu + 4.0 / 4.0 * cv * cu + 4.0 / 15.0 * dv * du));
            double fourth_term_yx  = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0 * cv * du + 4.0 / 9.0  * dv * cu) - betaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0  * cv * cu + 4.0 / 15.0 * dv * du) - gammaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0  * bv * cu * 4.0 / 9.0 * cv * bu * 4.0 / 9.0  * dv * au));
            double fifth_term_yx   = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 5.0 * av * bu + 4.0 / 5.0 * bv * au + 4.0 / 15.0 * cv * du + 4.0 / 15.0 * dv * cu) - gammaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 15.0 * bv * du + 4.0 / 9.0 * cv * au + 4.0 / 15.0 * dv * bu));
            double sixth_term_yx   = alphaNx_[i] * alphaNy_[j] * ((4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au) - betaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 9.0 * cv * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0  * bv * au                                             ));
            double seventh_term_yx = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * cu + 4.0 / 9.0 * bv * du + 4.0 / 3.0 * cv * au + 4.0 / 9.0  * dv * bu) - betaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0  * cv * bu + 4.0 / 9.0  * dv * au) - gammaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 9.0  * bv * bu + 4.0 / 5.0 * cv * cu + 4.0 / 15.0 * dv * du));
            double eighth_term_yx  = alphaNx_[i] * alphaNy_[j] * ((4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au) - betaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 9.0 * cv * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0  * bv * au                                             ));
            double ninth_term_yx   = alphaNx_[i] * alphaNy_[j] * ((4.0 / 3.0 * av * au + 4.0 / 9.0 * bv * bu * 4.0 / 5.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0 * bv * au + 4.0 / 15.0 * cv * du + 4.0 / 15.0 * dv * cu) - gammaOverAlpha * (4.0 / 5.0 * av * cu + 4.0 / 15.0 * bv * du + 4.0 / 5.0 * cv * au + 4.0 / 15.0 * dv * bu));

            double first_term_xy   = alphaNy_[i] * alphaNx_[j] * ((      4.0 * au * av + 4.0 / 3.0 * bu * bv + 4.0 / 3.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0  * cu * dv + 4.0 / 9.0  * du * cv) - gammaOverAlpha * (4.0 / 3.0 * au * cv + 4.0 / 9.0  * bu * cv + 4.0 / 9.0 * du * bv                       ));
            double second_term_xy  = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0 * cu * dv + 4.0 / 9.0  * du * cv) - betaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0  * cu * cv + 4.0 / 15.0 * du * dv) - gammaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0  * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av));
            double third_term_xy   = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * cv + 4.0 / 9.0 * bu * dv + 4.0 / 3.0 * cu * av + 4.0 / 9.0  * du * bv) - betaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0  * cu * bv + 4.0 / 9.0  * du * av) - gammaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 9.0  * bu * bv + 4.0 / 4.0 * cu * cv + 4.0 / 15.0 * du * dv));
            double fourth_term_xy  = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0 * cu * dv + 4.0 / 9.0  * du * cv) - betaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0  * cu * cv + 4.0 / 15.0 * du * dv) - gammaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0  * bu * cv * 4.0 / 9.0 * cu * bv * 4.0 / 9.0  * du * av));
            double fifth_term_xy   = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 5.0 * au * bv + 4.0 / 5.0 * bu * av + 4.0 / 15.0 * cu * dv + 4.0 / 15.0 * du * cv) - gammaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 15.0 * bu * dv + 4.0 / 9.0 * cu * av + 4.0 / 15.0 * du * bv));
            double sixth_term_xy   = alphaNy_[i] * alphaNx_[j] * ((4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av) - betaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 9.0 * cu * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0  * bu * av                                             ));
            double seventh_term_xy = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * cv + 4.0 / 9.0 * bu * dv + 4.0 / 3.0 * cu * av + 4.0 / 9.0  * du * bv) - betaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0  * cu * bv + 4.0 / 9.0  * du * av) - gammaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 9.0  * bu * bv + 4.0 / 5.0 * cu * cv + 4.0 / 15.0 * du * dv));
            double eighth_term_xy  = alphaNy_[i] * alphaNx_[j] * ((4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av) - betaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 9.0 * cu * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0  * bu * av                                             ));
            double ninth_term_xy   = alphaNy_[i] * alphaNx_[j] * ((4.0 / 3.0 * au * av + 4.0 / 9.0 * bu * bv * 4.0 / 5.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0 * bu * av + 4.0 / 15.0 * cu * dv + 4.0 / 15.0 * du * cv) - gammaOverAlpha * (4.0 / 5.0 * au * cv + 4.0 / 15.0 * bu * dv + 4.0 / 5.0 * cu * av + 4.0 / 15.0 * du * bv));

            double first_term_yy   = alphaNx_[i] * alphaNx_[j] * ((      4.0 * av * av + 4.0 / 3.0 * bv * bv + 4.0 / 3.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0  * cv * dv + 4.0 / 9.0  * dv * cv) - gammaOverAlpha * (4.0 / 3.0 * av * cv + 4.0 / 9.0  * bv * cv + 4.0 / 9.0 * dv * bv                       ));
            double second_term_yy  = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0 * cv * dv + 4.0 / 9.0  * dv * cv) - betaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0  * cv * cv + 4.0 / 15.0 * dv * dv) - gammaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0  * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av));
            double third_term_yy   = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * cv + 4.0 / 9.0 * bv * dv + 4.0 / 3.0 * cv * av + 4.0 / 9.0  * dv * bv) - betaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0  * cv * bv + 4.0 / 9.0  * dv * av) - gammaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 9.0  * bv * bv + 4.0 / 4.0 * cv * cv + 4.0 / 15.0 * dv * dv));
            double fourth_term_yy  = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0 * cv * dv + 4.0 / 9.0  * dv * cv) - betaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0  * cv * cv + 4.0 / 15.0 * dv * dv) - gammaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0  * bv * cv * 4.0 / 9.0 * cv * bv * 4.0 / 9.0  * dv * av));
            double fifth_term_yy   = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 5.0 * av * bv + 4.0 / 5.0 * bv * av + 4.0 / 15.0 * cv * dv + 4.0 / 15.0 * dv * cv) - gammaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 15.0 * bv * dv + 4.0 / 9.0 * cv * av + 4.0 / 15.0 * dv * bv));
            double sixth_term_yy   = alphaNx_[i] * alphaNx_[j] * ((4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av) - betaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 9.0 * cv * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0  * bv * av                                             ));
            double seventh_term_yy = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * cv + 4.0 / 9.0 * bv * dv + 4.0 / 3.0 * cv * av + 4.0 / 9.0  * dv * bv) - betaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0  * cv * bv + 4.0 / 9.0  * dv * av) - gammaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 9.0  * bv * bv + 4.0 / 5.0 * cv * cv + 4.0 / 15.0 * dv * dv));
            double eighth_term_yy  = alphaNx_[i] * alphaNx_[j] * ((4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av) - betaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 9.0 * cv * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0  * bv * av                                             ));
            double ninth_term_yy   = alphaNx_[i] * alphaNx_[j] * ((4.0 / 3.0 * av * av + 4.0 / 9.0 * bv * bv * 4.0 / 5.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0 * bv * av + 4.0 / 15.0 * cv * dv + 4.0 / 15.0 * dv * cv) - gammaOverAlpha * (4.0 / 5.0 * av * cv + 4.0 / 15.0 * bv * dv + 4.0 / 5.0 * cv * av + 4.0 / 15.0 * dv * bv));

            axx_supg(i, j) = first_term_xx + second_term_xx + third_term_xx + fourth_term_xx + fifth_term_xx + sixth_term_xx + seventh_term_xx + eighth_term_xx + ninth_term_xx;
            ayx_supg(i, j) = first_term_yx + second_term_yx + third_term_yx + fourth_term_yx + fifth_term_yx + sixth_term_yx + seventh_term_yx + eighth_term_yx + ninth_term_yx;
            axy_supg(i, j) = first_term_xy + second_term_xy + third_term_xy + fourth_term_xy + fifth_term_xy + sixth_term_xy + seventh_term_xy + eighth_term_xy + ninth_term_xy;
            ayy_supg(i, j) = first_term_yy + second_term_yy + third_term_yy + fourth_term_yy + fifth_term_yy + sixth_term_yy + seventh_term_yy + eighth_term_yy + ninth_term_yy;
        }
    }

    a_supg = 1.0 / alpha_xy_ * (axx_supg + ayx_supg + axy_supg + ayy_supg);

#ifdef DEBUG_VELOCITY_PREDICTION
    Logger::out << "global id: " << global_index_ << std::endl;
    Logger::out << "u: " << std::endl;
    Logger::out << u << std::endl;
    Logger::out << "v: " << std::endl;
    Logger::out << v << std::endl;
    Logger::out << "Au: " << std::endl;
    Logger::out << Au << std::endl;
    Logger::out << "Bu: " << std::endl;
    Logger::out << Bu << std::endl;
    Logger::out << "Cu: " << std::endl;
    Logger::out << Cu << std::endl;
    Logger::out << "Du: " << std::endl;
    Logger::out << Du << std::endl;
    Logger::out << "Av: " << std::endl;
    Logger::out << Av << std::endl;
    Logger::out << "Bv: " << std::endl;
    Logger::out << Bv << std::endl;
    Logger::out << "Cv: " << std::endl;
    Logger::out << Cv << std::endl;
    Logger::out << "Dv: " << std::endl;
    Logger::out << Dv << std::endl;

    Logger::out << "ax: " << std::endl;
    Logger::out << ax << std::endl;
    Logger::out << "ay: " << std::endl;
    Logger::out << ay << std::endl;
    Logger::out << "a: " << std::endl;
    Logger::out << a_ << std::endl;
#endif

    Matrix<4, 4> dt_by_m;
    dt_by_m.Clear();
    for (int i = 0; i < 4; i++) {
        dt_by_m(i, i) = nodes_[i]->delta_t_by_m_;
    }


    // TODO: -1.0を先頭に持ってくると、計算がエラーする
    du_.Clear();
    dv_.Clear();
    du_ = (-1.0) * dt_by_m * (a * u - hx_ * p_ + d_ * u);
    dv_ = (-1.0) * dt_by_m * (a * v - hy_ * p_ + d_ * v);
    //  du_ = (-1.0) * dt_by_m * ((a + stabilization_parameter * a_supg) * u -  hx_ *  p_ +  d_ * u);
    //  dv_ = (-1.0) * dt_by_m * ((a + stabilization_parameter * a_supg) * v -  hy_ *  p_ +  d_ * v);

#ifdef DEBUG_TTT
    Logger::out << "du: " <<  du_ << std::endl;
    Logger::out << "dv: " <<  dv_ << std::endl;
#endif

#ifdef DEBUG_VELOCITY_PREDICTION
    Logger::out << "Elem[" << global_index_ << "] :" << std::endl;
    Logger::out << " pos : " << node(0)->pos_ << "-" << node(1)->pos_ << "-" << node(2)->pos_ << "-" << node(3)->pos_ << std::endl;
    Logger::out << " vel : " << node(0)->vel_ << " " << node(1)->vel_ << " " << node(2)->vel_ << " " << node(3)->vel_ << std::endl;
#endif
    // clang-format on
}

double ElementQuad::CalcDivergenceAndCorrect(double epsilon) {
         du_.Clear();
         dv_.Clear();

        // calc Divergence
        double abs_div = 0.0;
        double area =  area_;
        Array<4> u, v;
        u.Clear();
        v.Clear();
        for (int i = 0; i <  number_of_nodes_; i++) {
            u[i] =  nodes_[i]->vel_.x_;
            v[i] =  nodes_[i]->vel_.y_;
        }
         div_ = ( hx_ * u +  hy_ * v) / area;
        abs_div = std::abs( div_);

        // correct
         delta_p_ = 0.0;
        if (abs_div > epsilon) {
             delta_p_ = 0.5 * (-1.0) *  lambda_ *  div_;
             p_ +=  delta_p_;
             du_ =  dt_hx_by_m_ *  delta_p_;
             dv_ =  dt_hy_by_m_ *  delta_p_;
        }

        return abs_div;
    }


void ElementQuad::CalcArea() {
    double x0 =  nodes_[0]->pos_.x_;
    double x1 =  nodes_[1]->pos_.x_;
    double x2 =  nodes_[2]->pos_.x_;
    double x3 =  nodes_[3]->pos_.x_;
    double y0 =  nodes_[0]->pos_.y_;
    double y1 =  nodes_[1]->pos_.y_;
    double y2 =  nodes_[2]->pos_.y_;
    double y3 =  nodes_[3]->pos_.y_;

    double area = 0.5 * ((x0 * y1 + x1 * y2 + x2 * y3 + x3 * y0) - (x1 * y0 + x2 * y1 + x3 * y2 + x0 * y3));
    if (area < 0.0) {
        UpdateElementNodesOrder();
    }

    x0 =  nodes_[0]->pos_.x_;
    x1 =  nodes_[1]->pos_.x_;
    x2 =  nodes_[2]->pos_.x_;
    x3 =  nodes_[3]->pos_.x_;
    y0 =  nodes_[0]->pos_.y_;
    y1 =  nodes_[1]->pos_.y_;
    y2 =  nodes_[2]->pos_.y_;
    y3 =  nodes_[3]->pos_.y_;

    area = 0.5 * ((x0 * y1 + x1 * y2 + x2 * y3 + x3 * y0) - (x1 * y0 + x2 * y1 + x3 * y2 + x0 * y3));

     area_ = area;
}

void ElementQuad::UpdateElementNodesOrder() {
    std::cout << "area < 0, updateElementNodesOrder\n";
    std::vector<Node*> tmp( number_of_nodes_);
    for (size_t i = 0; i <  number_of_nodes_; i++)
        tmp[i] =  nodes_[i];
    for (size_t i = 0; i <  number_of_nodes_; i++) {
        nodes_[i] = tmp[ number_of_nodes_ - 1 - i];
        nodes_[i]->UpdateElementRef(this, i);
    }
}

void ElementQuad::CalcArea3D() {
    double area0 = CalculateTriangleArea( nodes_[0]->pos_,  nodes_[1]->pos_,  nodes_[2]->pos_);
    double area1 = CalculateTriangleArea( nodes_[0]->pos_,  nodes_[2]->pos_,  nodes_[3]->pos_);

    if (area0 < 0.0 || area1 < 0.0)
        UpdateElementNodesOrder();

    area0 =  CalculateTriangleArea( nodes_[0]->pos_,  nodes_[1]->pos_,  nodes_[2]->pos_);
    area1 =  CalculateTriangleArea( nodes_[0]->pos_,  nodes_[2]->pos_,  nodes_[3]->pos_);

    area_ = area0 + area1;
}

void ElementQuad::AddVelD(ArrayXYZ& vel_d, int node_index) {
    vel_d.x_ += du_[node_index];
    vel_d.y_ += dv_[node_index];
}


double ElementQuad::CalculateTriangleArea(const ArrayXYZ p0, const ArrayXYZ p1, const ArrayXYZ p2) {
    double vec0_x = p1.x_ - p0.x_;
    double vec0_y = p1.y_ - p0.y_;
    double vec0_z = p1.z_ - p0.z_;

    double vec1_x = p2.x_ - p0.x_;
    double vec1_y = p2.y_ - p0.y_;
    double vec1_z = p2.z_ - p0.z_;

    double vec2_x = vec0_y * vec1_z - vec0_z * vec1_y;
    double vec2_y = vec0_z * vec1_x - vec0_x * vec1_z;
    double vec2_z = vec0_x * vec1_y - vec0_y * vec1_x;

    return 0.5 * std::sqrt(vec2_x * vec2_x + vec2_y * vec2_y + vec2_z * vec2_z);
}

void ElementQuad::CalcVolume() {
    volume_ = 0.0;
}

double ElementQuad::CalcCourantNumber(const double &delta_t) {
    courantNumber_ = 1.0;
    return courantNumber_;
}
