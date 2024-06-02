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
    this->number_of_nodes_ = 4;
    this->nodes_.resize(4, nullptr);  // 親クラスの nodes_ を初期化
}
// ElementQuad::ElementQuad() {
//     this->numberOfNodes_ = 4;
//     nodes_(4, nullptr);
// }

size_t ElementQuad::getNumberOfNodes() {
    return number_of_nodes_;
}

/**
 * @brief set four nodes
 *
 * @param nodes
 */
void ElementQuad::setNodes(const std::vector<Node*> &nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementQuad requires exactly 4 nodes.");
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        std::cout << "i = " << i << std::endl;
        this->nodes_[i] = nodes[i];
        nodes[i]->addElementRef(this, i);
    }
}

/**
 * @brief set four nodes
 *
 * @param nodes
 */
void ElementQuad::setNodes(const std::initializer_list<Node*> &nodes) {
    if (nodes.size() != this->number_of_nodes_)
        throw std::invalid_argument("ElementQuad requires exactly 4 nodes.");
    std::initializer_list<Node*>::iterator it = nodes.begin();
    for (size_t i = 0; i < this->number_of_nodes_; i++, it++) {
        std::cout << "i = " << i << std::endl;
        this->nodes_[i] = *it;
        (*it)->addElementRef(this, i);
    }
}

void ElementQuad::calcInvariants1(double re) {
    double re_inv = 1.0 / re;
    double six_inv = 1.0 / 6.0;

    double x0 = this->nodes_[0]->pos_.x_;
    double y0 = this->nodes_[0]->pos_.y_;
    double x1 = this->nodes_[1]->pos_.x_;
    double y1 = this->nodes_[1]->pos_.y_;
    double x2 = this->nodes_[2]->pos_.x_;
    double y2 = this->nodes_[2]->pos_.y_;
    double x3 = this->nodes_[3]->pos_.x_;
    double y3 = this->nodes_[3]->pos_.y_;

    this->calcArea3D();

    double alpha_xy = (x0 - x2) * (y1 - y3) + (x1 - x3) * (y2 - y0);
    double beta_xy  = (x2 - x3) * (y0 - y1) + (x0 - x1) * (y3 - y2);
    double gamma_xy = (x1 - x2) * (y0 - y3) + (x0 - x3) * (y2 - y1);
    this->alpha_xy_ = 1.0 / alpha_xy;
    this->beta_xy_ = 1.0 / beta_xy;
    this->gamma_xy_ = 1.0 / gamma_xy;
    double alpha_xy_inv = 1.0 / alpha_xy;
    // double beta_xy_inv = 1.0 / beta_xy_;
    // double gamma_xy_inv = 1.0 / gamma_xy;

    // concentrated mass
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->nodes_[i]->m_ += 1.0 * six_inv * (3.0 * alpha_xy * shape_a_[i] + beta_xy * shape_b_[i] + gamma_xy * shape_c_[i]);
    }

    this->alphaNy_.clear();
    this->alphaNx_.clear();
    this->betaNy_.clear();
    this->betaNx_.clear();
    this->gammaNy_.clear();
    this->gammaNx_.clear();
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->alphaNy_[i] = (N_ij_(0, i) - N_ij_(2, i)) * (y1 - y3) + (N_ij_(1, i) - N_ij_(3, i)) * (y2 - y0);
        this->alphaNx_[i] = (N_ij_(0, i) - N_ij_(2, i)) * (x1 - x3) + (N_ij_(1, i) - N_ij_(3, i)) * (x2 - x0);
        this->betaNy_[i]  = (N_ij_(2, i) - N_ij_(3, i)) * (y0 - y1) + (N_ij_(0, i) - N_ij_(1, i)) * (y3 - y2);
        this->betaNx_[i]  = (N_ij_(2, i) - N_ij_(3, i)) * (x0 - x1) + (N_ij_(0, i) - N_ij_(1, i)) * (x3 - x2);
        this->gammaNy_[i] = (N_ij_(1, i) - N_ij_(2, i)) * (y0 - y3) + (N_ij_(0, i) - N_ij_(3, i)) * (y2 - y1);
        this->gammaNx_[i] = (N_ij_(1, i) - N_ij_(2, i)) * (x0 - x3) + (N_ij_(0, i) - N_ij_(3, i)) * (x2 - x1);
    }
    this->roundN_roundX_.clear();
    this->roundN_roundY_.clear();
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->roundN_roundX_[i] = (this->alphaNy_[i] * this->betaNy_[i] * coefficient_b_[i] + this->gammaNy_[i] * coefficient_c_[i]);
        this->roundN_roundY_[i] = (this->alphaNx_[i] * this->betaNx_[i] * coefficient_b_[i] + this->gammaNx_[i] * coefficient_c_[i]);
    }
    this->jacobian_.clear();
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->jacobian_[i] = (this->alpha_xy_ * this->beta_xy_ * coefficient_b_[i] + gamma_xy_ * coefficient_c_[i]) * 0.125;
    }

    // pressure vecotr
    this->hx_.clear();
    this->hy_.clear();
    this->hx_by_area_.clear();
    this->hy_by_area_.clear();
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->hx_[i] =          0.5 * this->alphaNy_[i];
        this->hy_[i] = (-1.0) * 0.5 * this->alphaNx_[i];
    }
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
      this->hx_by_area_[i] = this->hx_[i] / this->area_;
      this->hy_by_area_[i] = this->hy_[i] / this->area_;
    }

    // diffusion matrix
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        for (size_t j = 0; j < this->number_of_nodes_; j++) {
            double the_first_term = 3 * this->alphaNy_[i] * this->alphaNy_[j] + this->betaNy_[i] * this->betaNy_[j] + this->gammaNy_[i] * this->gammaNy_[j];
            double the_second_term = 3 * this->alphaNx_[i] * this->alphaNx_[j] + this->betaNx_[i] * this->betaNx_[j] + this->gammaNx_[i] * this->gammaNx_[j];
            double the_third_term = (-1.0) * beta_xy * alpha_xy_inv * (this->alphaNy_[i] * this->betaNy_[j] + this->betaNy_[i] * this->alphaNy_[j] + this->alphaNx_[i] * this->betaNx_[j] + this->betaNx_[i] * this->alphaNx_[j]);
            double the_fourth_term = (-1.0) * gamma_xy * alpha_xy_inv * (this->alphaNy_[i] * this->gammaNy_[j] + this->gammaNy_[i] * this->alphaNy_[j] + this->alphaNx_[i] * this->gammaNx_[j] + this->gammaNx_[i] * this->alphaNx_[j]);
            this->d_(i, j) = re_inv + six_inv * alpha_xy_inv * (the_first_term + the_second_term + the_third_term + the_fourth_term);
        }
    }
}

void ElementQuad::calcInvariants2(double delta_t) {

    this->mass_matrix_inv_.clear();
    for (size_t i = 0; i < this->number_of_nodes_; i++)
        this->mass_matrix_inv_(i, i) = 1.0 / this->nodes_[i]->m_;

    double hx_m_hx = this->hx_ * this->mass_matrix_inv_ * this->hx_;
    double hy_m_hy = this->hy_ * this->mass_matrix_inv_ * this->hy_;
    this->lambda_ = this->area_ / (delta_t * (hx_m_hx + hy_m_hy));

    this->dt_hx_by_m_ = delta_t * this->mass_matrix_inv_ * this->hx_;
    this->dt_hy_by_m_ = delta_t * this->mass_matrix_inv_ * this->hy_;
}

void ElementQuad::calcVelocityPrediction(double delta_t, double re) {

    Array<4> u(
        this->nodes_[0]->vel_.x_,
        this->nodes_[1]->vel_.x_,
        this->nodes_[2]->vel_.x_,
        this->nodes_[3]->vel_.x_
    );
    Array<4> v(
        this->nodes_[0]->vel_.y_,
        this->nodes_[1]->vel_.y_,
        this->nodes_[2]->vel_.y_,
        this->nodes_[3]->vel_.y_
    );


    /** calculate advection term A
     */
    double au = this->shape_a_ * u;
    double bu = this->shape_b_ * u;
    double cu = this->shape_c_ * u;
    double du = this->shape_d_ * u;
    double av = this->shape_a_ * v;
    double bv = this->shape_b_ * v;
    double cv = this->shape_c_ * v;
    double dv = this->shape_d_ * v;

    Matrix<4, 4> a, ax, ay;
    a.clear();
    ax.clear();
    ay.clear();
    double eightenn_inv = 1.0 / 18.0;
    for (int i = 0; i < this->number_of_nodes_; i++) {
        for (int j = 0; j < this->number_of_nodes_; j++) {
            double first_term_x = 9.0 * shape_a_[i] * au * this->alphaNy_[j];
            double first_term_y = 9.0 * shape_a_[i] * av * this->alphaNx_[j];
            double second_term_x = 3.0 * ((shape_b_[i] * bu + shape_c_[i] * cu) * this->alphaNy_[j] + (shape_a_[i] * bu + shape_b_[i] * au) * this->betaNy_[j] + (shape_a_[i] * cu + shape_c_[i] * au) * this->gammaNy_[j]);
            double second_term_y = 3.0 * ((shape_b_[i] * bv + shape_c_[i] * cv) * this->alphaNx_[j] + (shape_a_[i] * bv + shape_b_[i] * av) * this->betaNx_[j] + (shape_a_[i] * cv + shape_c_[i] * av) * this->gammaNx_[j]);
            double third_term_x = shape_d_[i] * du * this->alphaNy_[j] + (shape_d_[i] * cu + shape_c_[i] * du) * this->betaNy_[j] + (shape_d_[i] * bu + shape_b_[i] * du) * this->gammaNy_[j];
            double third_term_y = shape_d_[i] * dv * this->alphaNx_[j] + (shape_d_[i] * cv + shape_c_[i] * dv) * this->betaNx_[j] + (shape_d_[i] * bv + shape_b_[i] * dv) * this->gammaNx_[j];
            ax(i, j) = first_term_x + second_term_x + third_term_x;
            ay(i, j) = first_term_y + second_term_y + third_term_y;
        }
    }
    a = eightenn_inv * (ax - ay);

    double element_length = 0.0;
    double vel_x = 0.0;
    double vel_y = 0.0;
    for (int i = 0; i < 4; i++) {
        vel_x += this->nodes_[i]->vel_.x_;
        vel_y += this->nodes_[i]->vel_.y_;
    }
    ArrayXYZ vel(vel_x / 4.0, vel_y / 4.0, 0.0);
    double vel_norm = vel.NormL2();
    ArrayXYZ vel_normalize = vel.normalize();
    for (int i = 0; i < 4; i++) {
        element_length += std::fabs(vel_normalize.x_ * this->roundN_roundX_[i] + vel_normalize.y_ * this->roundN_roundY_[i]) / (8.0 * this->jacobian_[i]);
    }
    if (element_length < 1.0e-10) {
        element_length = this->area_;
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
    axx_supg.clear();
    axy_supg.clear();
    ayx_supg.clear();
    ayy_supg.clear();
    a_supg.clear();
    double betaOverAlpha = this->beta_xy_ / this->alpha_xy_;
    double gammaOverAlpha = this->gamma_xy_ / this->alpha_xy_;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            double first_term_xx   = this->alphaNy_[i] * this->alphaNy_[j] * ((      4.0 * au * au + 4.0 / 3.0 * bu * bu + 4.0 / 3.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0  * cu * du + 4.0 / 9.0  * du * cu) - gammaOverAlpha * (4.0 / 3.0 * au * cu + 4.0 / 9.0  * bu * cu + 4.0 / 9.0 * du * bu                       ));
            double second_term_xx  = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0 * cu * du + 4.0 / 9.0  * du * cu) - betaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0  * cu * cu + 4.0 / 15.0 * du * du) - gammaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0  * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au));
            double third_term_xx   = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * cu + 4.0 / 9.0 * bu * du + 4.0 / 3.0 * cu * au + 4.0 / 9.0  * du * bu) - betaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0  * cu * bu + 4.0 / 9.0  * du * au) - gammaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 9.0  * bu * bu + 4.0 / 4.0 * cu * cu + 4.0 / 15.0 * du * du));
            double fourth_term_xx  = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * bu + 4.0 / 3.0 * bu * au + 4.0 / 9.0 * cu * du + 4.0 / 9.0  * du * cu) - betaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0  * cu * cu + 4.0 / 15.0 * du * du) - gammaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0  * bu * cu * 4.0 / 9.0 * cu * bu * 4.0 / 9.0  * du * au));
            double fifth_term_xx   = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * au + 4.0 / 5.0 * bu * bu + 4.0 / 9.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 5.0 * au * bu + 4.0 / 5.0 * bu * au + 4.0 / 15.0 * cu * du + 4.0 / 15.0 * du * cu) - gammaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 15.0 * bu * du + 4.0 / 9.0 * cu * au + 4.0 / 15.0 * du * bu));
            double sixth_term_xx   = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au) - betaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 9.0 * cu * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0  * bu * au                                             ));
            double seventh_term_xx = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * cu + 4.0 / 9.0 * bu * du + 4.0 / 3.0 * cu * au + 4.0 / 9.0  * du * bu) - betaOverAlpha * (4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0  * cu * bu + 4.0 / 9.0  * du * au) - gammaOverAlpha * (4.0 / 3.0 * au * au + 4.0 / 9.0  * bu * bu + 4.0 / 5.0 * cu * cu + 4.0 / 15.0 * du * du));
            double eighth_term_xx  = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 9.0 * au * du + 4.0 / 9.0 * bu * cu + 4.0 / 9.0 * cu * bu + 4.0 / 9.0  * du * au) - betaOverAlpha * (4.0 / 9.0 * au * cu + 4.0 / 9.0 * cu * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0  * bu * au                                             ));
            double ninth_term_xx   = this->alphaNy_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * au * au + 4.0 / 9.0 * bu * bu * 4.0 / 5.0 * cu * cu + 4.0 / 15.0 * du * du) - betaOverAlpha * (4.0 / 9.0 * au * bu + 4.0 / 9.0 * bu * au + 4.0 / 15.0 * cu * du + 4.0 / 15.0 * du * cu) - gammaOverAlpha * (4.0 / 5.0 * au * cu + 4.0 / 15.0 * bu * du + 4.0 / 5.0 * cu * au + 4.0 / 15.0 * du * bu));

            double first_term_yx   = this->alphaNx_[i] * this->alphaNy_[j] * ((      4.0 * av * au + 4.0 / 3.0 * bv * bu + 4.0 / 3.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0  * cv * du + 4.0 / 9.0  * dv * cu) - gammaOverAlpha * (4.0 / 3.0 * av * cu + 4.0 / 9.0  * bv * cu + 4.0 / 9.0 * dv * bu                       ));
            double second_term_yx  = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0 * cv * du + 4.0 / 9.0  * dv * cu) - betaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0  * cv * cu + 4.0 / 15.0 * dv * du) - gammaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0  * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au));
            double third_term_yx   = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * cu + 4.0 / 9.0 * bv * du + 4.0 / 3.0 * cv * au + 4.0 / 9.0  * dv * bu) - betaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0  * cv * bu + 4.0 / 9.0  * dv * au) - gammaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 9.0  * bv * bu + 4.0 / 4.0 * cv * cu + 4.0 / 15.0 * dv * du));
            double fourth_term_yx  = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * bu + 4.0 / 3.0 * bv * au + 4.0 / 9.0 * cv * du + 4.0 / 9.0  * dv * cu) - betaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0  * cv * cu + 4.0 / 15.0 * dv * du) - gammaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0  * bv * cu * 4.0 / 9.0 * cv * bu * 4.0 / 9.0  * dv * au));
            double fifth_term_yx   = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * au + 4.0 / 5.0 * bv * bu + 4.0 / 9.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 5.0 * av * bu + 4.0 / 5.0 * bv * au + 4.0 / 15.0 * cv * du + 4.0 / 15.0 * dv * cu) - gammaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 15.0 * bv * du + 4.0 / 9.0 * cv * au + 4.0 / 15.0 * dv * bu));
            double sixth_term_yx   = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au) - betaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 9.0 * cv * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0  * bv * au                                             ));
            double seventh_term_yx = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * cu + 4.0 / 9.0 * bv * du + 4.0 / 3.0 * cv * au + 4.0 / 9.0  * dv * bu) - betaOverAlpha * (4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0  * cv * bu + 4.0 / 9.0  * dv * au) - gammaOverAlpha * (4.0 / 3.0 * av * au + 4.0 / 9.0  * bv * bu + 4.0 / 5.0 * cv * cu + 4.0 / 15.0 * dv * du));
            double eighth_term_yx  = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 9.0 * av * du + 4.0 / 9.0 * bv * cu + 4.0 / 9.0 * cv * bu + 4.0 / 9.0  * dv * au) - betaOverAlpha * (4.0 / 9.0 * av * cu + 4.0 / 9.0 * cv * au                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0  * bv * au                                             ));
            double ninth_term_yx   = this->alphaNx_[i] * this->alphaNy_[j] * ((4.0 / 3.0 * av * au + 4.0 / 9.0 * bv * bu * 4.0 / 5.0 * cv * cu + 4.0 / 15.0 * dv * du) - betaOverAlpha * (4.0 / 9.0 * av * bu + 4.0 / 9.0 * bv * au + 4.0 / 15.0 * cv * du + 4.0 / 15.0 * dv * cu) - gammaOverAlpha * (4.0 / 5.0 * av * cu + 4.0 / 15.0 * bv * du + 4.0 / 5.0 * cv * au + 4.0 / 15.0 * dv * bu));

            double first_term_xy   = this->alphaNy_[i] * this->alphaNx_[j] * ((      4.0 * au * av + 4.0 / 3.0 * bu * bv + 4.0 / 3.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0  * cu * dv + 4.0 / 9.0  * du * cv) - gammaOverAlpha * (4.0 / 3.0 * au * cv + 4.0 / 9.0  * bu * cv + 4.0 / 9.0 * du * bv                       ));
            double second_term_xy  = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0 * cu * dv + 4.0 / 9.0  * du * cv) - betaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0  * cu * cv + 4.0 / 15.0 * du * dv) - gammaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0  * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av));
            double third_term_xy   = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * cv + 4.0 / 9.0 * bu * dv + 4.0 / 3.0 * cu * av + 4.0 / 9.0  * du * bv) - betaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0  * cu * bv + 4.0 / 9.0  * du * av) - gammaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 9.0  * bu * bv + 4.0 / 4.0 * cu * cv + 4.0 / 15.0 * du * dv));
            double fourth_term_xy  = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * bv + 4.0 / 3.0 * bu * av + 4.0 / 9.0 * cu * dv + 4.0 / 9.0  * du * cv) - betaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0  * cu * cv + 4.0 / 15.0 * du * dv) - gammaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0  * bu * cv * 4.0 / 9.0 * cu * bv * 4.0 / 9.0  * du * av));
            double fifth_term_xy   = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * av + 4.0 / 5.0 * bu * bv + 4.0 / 9.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 5.0 * au * bv + 4.0 / 5.0 * bu * av + 4.0 / 15.0 * cu * dv + 4.0 / 15.0 * du * cv) - gammaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 15.0 * bu * dv + 4.0 / 9.0 * cu * av + 4.0 / 15.0 * du * bv));
            double sixth_term_xy   = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av) - betaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 9.0 * cu * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0  * bu * av                                             ));
            double seventh_term_xy = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * cv + 4.0 / 9.0 * bu * dv + 4.0 / 3.0 * cu * av + 4.0 / 9.0  * du * bv) - betaOverAlpha * (4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0  * cu * bv + 4.0 / 9.0  * du * av) - gammaOverAlpha * (4.0 / 3.0 * au * av + 4.0 / 9.0  * bu * bv + 4.0 / 5.0 * cu * cv + 4.0 / 15.0 * du * dv));
            double eighth_term_xy  = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 9.0 * au * dv + 4.0 / 9.0 * bu * cv + 4.0 / 9.0 * cu * bv + 4.0 / 9.0  * du * av) - betaOverAlpha * (4.0 / 9.0 * au * cv + 4.0 / 9.0 * cu * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0  * bu * av                                             ));
            double ninth_term_xy   = this->alphaNy_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * au * av + 4.0 / 9.0 * bu * bv * 4.0 / 5.0 * cu * cv + 4.0 / 15.0 * du * dv) - betaOverAlpha * (4.0 / 9.0 * au * bv + 4.0 / 9.0 * bu * av + 4.0 / 15.0 * cu * dv + 4.0 / 15.0 * du * cv) - gammaOverAlpha * (4.0 / 5.0 * au * cv + 4.0 / 15.0 * bu * dv + 4.0 / 5.0 * cu * av + 4.0 / 15.0 * du * bv));

            double first_term_yy   = this->alphaNx_[i] * this->alphaNx_[j] * ((      4.0 * av * av + 4.0 / 3.0 * bv * bv + 4.0 / 3.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0  * cv * dv + 4.0 / 9.0  * dv * cv) - gammaOverAlpha * (4.0 / 3.0 * av * cv + 4.0 / 9.0  * bv * cv + 4.0 / 9.0 * dv * bv                       ));
            double second_term_yy  = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0 * cv * dv + 4.0 / 9.0  * dv * cv) - betaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0  * cv * cv + 4.0 / 15.0 * dv * dv) - gammaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0  * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av));
            double third_term_yy   = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * cv + 4.0 / 9.0 * bv * dv + 4.0 / 3.0 * cv * av + 4.0 / 9.0  * dv * bv) - betaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0  * cv * bv + 4.0 / 9.0  * dv * av) - gammaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 9.0  * bv * bv + 4.0 / 4.0 * cv * cv + 4.0 / 15.0 * dv * dv));
            double fourth_term_yy  = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * bv + 4.0 / 3.0 * bv * av + 4.0 / 9.0 * cv * dv + 4.0 / 9.0  * dv * cv) - betaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0  * cv * cv + 4.0 / 15.0 * dv * dv) - gammaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0  * bv * cv * 4.0 / 9.0 * cv * bv * 4.0 / 9.0  * dv * av));
            double fifth_term_yy   = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * av + 4.0 / 5.0 * bv * bv + 4.0 / 9.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 5.0 * av * bv + 4.0 / 5.0 * bv * av + 4.0 / 15.0 * cv * dv + 4.0 / 15.0 * dv * cv) - gammaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 15.0 * bv * dv + 4.0 / 9.0 * cv * av + 4.0 / 15.0 * dv * bv));
            double sixth_term_yy   = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av) - betaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 9.0 * cv * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0  * bv * av                                             ));
            double seventh_term_yy = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * cv + 4.0 / 9.0 * bv * dv + 4.0 / 3.0 * cv * av + 4.0 / 9.0  * dv * bv) - betaOverAlpha * (4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0  * cv * bv + 4.0 / 9.0  * dv * av) - gammaOverAlpha * (4.0 / 3.0 * av * av + 4.0 / 9.0  * bv * bv + 4.0 / 5.0 * cv * cv + 4.0 / 15.0 * dv * dv));
            double eighth_term_yy  = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 9.0 * av * dv + 4.0 / 9.0 * bv * cv + 4.0 / 9.0 * cv * bv + 4.0 / 9.0  * dv * av) - betaOverAlpha * (4.0 / 9.0 * av * cv + 4.0 / 9.0 * cv * av                                              ) - gammaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0  * bv * av                                             ));
            double ninth_term_yy   = this->alphaNx_[i] * this->alphaNx_[j] * ((4.0 / 3.0 * av * av + 4.0 / 9.0 * bv * bv * 4.0 / 5.0 * cv * cv + 4.0 / 15.0 * dv * dv) - betaOverAlpha * (4.0 / 9.0 * av * bv + 4.0 / 9.0 * bv * av + 4.0 / 15.0 * cv * dv + 4.0 / 15.0 * dv * cv) - gammaOverAlpha * (4.0 / 5.0 * av * cv + 4.0 / 15.0 * bv * dv + 4.0 / 5.0 * cv * av + 4.0 / 15.0 * dv * bv));

            axx_supg(i, j) = first_term_xx + second_term_xx + third_term_xx + fourth_term_xx + fifth_term_xx + sixth_term_xx + seventh_term_xx + eighth_term_xx + ninth_term_xx;
            ayx_supg(i, j) = first_term_yx + second_term_yx + third_term_yx + fourth_term_yx + fifth_term_yx + sixth_term_yx + seventh_term_yx + eighth_term_yx + ninth_term_yx;
            axy_supg(i, j) = first_term_xy + second_term_xy + third_term_xy + fourth_term_xy + fifth_term_xy + sixth_term_xy + seventh_term_xy + eighth_term_xy + ninth_term_xy;
            ayy_supg(i, j) = first_term_yy + second_term_yy + third_term_yy + fourth_term_yy + fifth_term_yy + sixth_term_yy + seventh_term_yy + eighth_term_yy + ninth_term_yy;
        }
    }

    a_supg = 1.0 / this->alpha_xy_ * (axx_supg + ayx_supg + axy_supg + ayy_supg);

#ifdef DEBUG_VELOCITY_PREDICTION
    Logger::out << "global id: " << this->global_index_ << std::endl;
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
    Logger::out << this->a_ << std::endl;
#endif

    Matrix<4, 4> dt_by_m;
    dt_by_m.clear();
    for (int i = 0; i < 4; i++) {
        dt_by_m(i, i) = this->nodes_[i]->delta_t_by_m_;
    }


    // TODO: -1.0を先頭に持ってくると、計算がエラーする
    this->du_.clear();
    this->dv_.clear();
    this->du_ = (-1.0) * dt_by_m * (a * u - this->hx_ * this->p_ + this->d_ * u);
    this->dv_ = (-1.0) * dt_by_m * (a * v - this->hy_ * this->p_ + this->d_ * v);
    // this->du_ = (-1.0) * dt_by_m * ((a + stabilization_parameter * a_supg) * u - this->hx_ * this->p_ + this->d_ * u);
    // this->dv_ = (-1.0) * dt_by_m * ((a + stabilization_parameter * a_supg) * v - this->hy_ * this->p_ + this->d_ * v);

#ifdef DEBUG_TTT
    Logger::out << "du: " << this->du_ << std::endl;
    Logger::out << "dv: " << this->dv_ << std::endl;
#endif

#ifdef DEBUG_VELOCITY_PREDICTION
    Logger::out << "Elem[" << global_index_ << "] :" << std::endl;
    Logger::out << " pos : " << node(0)->pos_ << "-" << node(1)->pos_ << "-" << node(2)->pos_ << "-" << node(3)->pos_ << std::endl;
    Logger::out << " vel : " << node(0)->vel_ << " " << node(1)->vel_ << " " << node(2)->vel_ << " " << node(3)->vel_ << std::endl;
#endif
    // clang-format on
}

double ElementQuad::calcDivergenceAndCorrect(double epsilon) {
        this->du_.clear();
        this->dv_.clear();

        // calc Divergence
        double abs_div = 0.0;
        double area = this->area_;
        Array<4> u, v;
        u.clear();
        v.clear();
        for (int i = 0; i < this->number_of_nodes_; i++) {
            u[i] = this->nodes_[i]->vel_.x_;
            v[i] = this->nodes_[i]->vel_.y_;
        }
        this->div_ = (this->hx_ * u + this->hy_ * v) / area;
        abs_div = std::abs(this->div_);

        // correct
        this->delta_p_ = 0.0;
        if (abs_div > epsilon) {
            this->delta_p_ = 0.5 * (-1.0) * this->lambda_ * this->div_;
            this->p_ += this->delta_p_;
            this->du_ = this->dt_hx_by_m_ * this->delta_p_;
            this->dv_ = this->dt_hy_by_m_ * this->delta_p_;
        }

        return abs_div;
    }


void ElementQuad::calcArea() {
    double x0 = this->nodes_[0]->pos_.x_;
    double x1 = this->nodes_[1]->pos_.x_;
    double x2 = this->nodes_[2]->pos_.x_;
    double x3 = this->nodes_[3]->pos_.x_;
    double y0 = this->nodes_[0]->pos_.y_;
    double y1 = this->nodes_[1]->pos_.y_;
    double y2 = this->nodes_[2]->pos_.y_;
    double y3 = this->nodes_[3]->pos_.y_;

    double area = 0.5 * ((x0 * y1 + x1 * y2 + x2 * y3 + x3 * y0) - (x1 * y0 + x2 * y1 + x3 * y2 + x0 * y3));
    if (area < 0.0) {
        this->updateElementNodesOrder();
    }

    x0 = this->nodes_[0]->pos_.x_;
    x1 = this->nodes_[1]->pos_.x_;
    x2 = this->nodes_[2]->pos_.x_;
    x3 = this->nodes_[3]->pos_.x_;
    y0 = this->nodes_[0]->pos_.y_;
    y1 = this->nodes_[1]->pos_.y_;
    y2 = this->nodes_[2]->pos_.y_;
    y3 = this->nodes_[3]->pos_.y_;

    area = 0.5 * ((x0 * y1 + x1 * y2 + x2 * y3 + x3 * y0) - (x1 * y0 + x2 * y1 + x3 * y2 + x0 * y3));

    this->area_ = area;
}

void ElementQuad::updateElementNodesOrder() {
    std::cout << "area < 0, updateElementNodesOrder\n";
    std::vector<Node*> tmp(this->number_of_nodes_);
    for (size_t i = 0; i < this->number_of_nodes_; i++)
        tmp[i] = this->nodes_[i];
    for (size_t i = 0; i < this->number_of_nodes_; i++) {
        this->nodes_[i] = tmp[this->number_of_nodes_ - 1 - i];
        this->nodes_[i]->updateElementRef(this, i);
    }
}

void ElementQuad::calcArea3D() {
    double area0 = this->calculateTriangleArea(this->nodes_[0]->pos_, this->nodes_[1]->pos_, this->nodes_[2]->pos_);
    double area1 = this->calculateTriangleArea(this->nodes_[0]->pos_, this->nodes_[2]->pos_, this->nodes_[3]->pos_);

    if (area0 < 0.0 || area1 < 0.0)
        this->updateElementNodesOrder();

    area0 = this->calculateTriangleArea(this->nodes_[0]->pos_, this->nodes_[1]->pos_, this->nodes_[2]->pos_);
    area1 = this->calculateTriangleArea(this->nodes_[0]->pos_, this->nodes_[2]->pos_, this->nodes_[3]->pos_);

    this->area_ = area0 + area1;
}

void ElementQuad::addDVel(ArrayXYZ& d_vel, int node_index) {
    d_vel.x_ += this->du_[node_index];
    d_vel.y_ += this->dv_[node_index];
}


double ElementQuad::calculateTriangleArea(const ArrayXYZ p0, const ArrayXYZ p1, const ArrayXYZ p2) {
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

void ElementQuad::calcVolume() {
    this->volume_ = 0.0;
}

void ElementQuad::calcCourantNumber(const double &delta_t) {
    this->courantNumber_ = 1.0;
}
