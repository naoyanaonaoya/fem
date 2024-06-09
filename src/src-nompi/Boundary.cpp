#include "Boundary.hpp"

void Boundary::AddNode(Node* node) {
    nodes_.push_back(node);
}

void Boundary::Apply(double c) {
    std::size_t number_of_nodes = nodes_.size();

    for (std::size_t i = 0; i < number_of_nodes; i++) {
        double x = nodes_[i]->pos_.x_;
        double y = nodes_[i]->pos_.y_;
        double z = nodes_[i]->pos_.z_;

        if (this->exist_of_x_boundary_ == 1) {
            double a0 = this->a0_;
            double a1 = this->a1_;
            double a2 = this->a2_;
            double a3 = this->a3_;
            double a4 = this->a4_;
            double a5 = this->a5_;
            this->nodes_[i]->vel_.x_ = c * (a0 + a1 * x + a2 * y + a3 * x * x + a4 * x * y + a5 * y * y);
        }
        if (this->exist_of_y_boundary_ == 1) {
            double b0 = this->b0_;
            double b1 = this->b1_;
            double b2 = this->b2_;
            double b3 = this->b3_;
            double b4 = this->b4_;
            double b5 = this->b5_;
            this->nodes_[i]->vel_.y_ = c * (b0 + b1 * x + b2 * y + b3 * x * x + b4 * x * y + b5 * y * y);
        }
        if (this->exist_of_z_boundary_ == 1) {
            double c0 = this->c0_;
            double c1 = this->c1_;
            double c2 = this->c2_;
            double c3 = this->c3_;
            double c4 = this->c4_;
            double c5 = this->c5_;
            this->nodes_[i]->vel_.z_ = c * (c0 + c1 * x + c2 * y + c3 * x * x + c4 * x * y + c5 * y * y);
        }
    }
}