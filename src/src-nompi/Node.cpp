#include "Node.hpp"
#include "Element.hpp"

#include <cassert>

void Node::SetPos(double x, double y, double z) {
    this->pos_.x_ = x;
    this->pos_.y_ = y;
    this->pos_.z_ = z;
}

void Node::SetPos(const ArrayXYZ& pos) {
    this->SetPos(pos.x_, pos.y_, pos.z_);
}

void Node::SetVel(double x, double y, double z) {
    this->vel_.x_ = x;
    this->vel_.y_ = y;
    this->vel_.z_ = z;
}

void Node::SetVel(const ArrayXYZ& vel) {
    this->SetVel(vel.x_, vel.y_, vel.z_);
}

void Node::ClearElementRefs() {
    if (element_ref_num_ > 4) {
        delete[] element_refs_;
    }
    element_ref_num_ = 0;
}

void Node::CopyElementRefsFrom(const Node &o) {
    int number_of_element_ref = o.element_ref_num_;
    if (number_of_element_ref <= 4) {
        for (int i = 0; i < number_of_element_ref; i++)
            this->element_refs_array_[i] = o.element_refs_array_[i];
        this->element_ref_num_ = number_of_element_ref;
        this->element_refs_ = this->element_refs_array_;
    } else {
        this->element_ref_num_ = number_of_element_ref;
        this->element_refs_ = new ElementRef[number_of_element_ref];
        for (int i = 0; i < number_of_element_ref; i++)
            this->element_refs_[i] = o.element_refs_[i];
    }
}

void Node::AddElementRef(Element *element, int node_index_in_element) {
    ElementRef* element_ref = AllocateElementRef();
    element_ref->element_ = element;
    element_ref->index_in_element_ = node_index_in_element;
}

ElementRef* Node::AllocateElementRef() {
    // std::cout << "element_ref_num_ = " << this->element_ref_num_ << std::endl;
    // std::cout << "allocateElementRef start" << std::endl;
    if (element_ref_num_ < 4) {
        // std::cout << "element_ref_num_ < 4" << std::endl;
        return &element_refs_[element_ref_num_++];
    } else {
        // std::cout << "element_ref_num_ = 4" << std::endl;
        ElementRef* new_element_refs = new ElementRef[element_ref_num_ + 1];
        for (int i = 0; i < element_ref_num_; i++)
            new_element_refs[i] = element_refs_[i];
        // std::cout << "delete before" << std::endl;
        if (element_ref_num_ > 4)
            delete[] element_refs_;
        // std::cout << "delete after" << std::endl;
        element_refs_ = new_element_refs;
        return &new_element_refs[element_ref_num_++];
    }
    // std::cout << "allocateElementRef finish" << std::endl;
}

void Node::UpdateElementRef(Element* element, int node_index_in_element) {
    for (int i = 0; i < element_ref_num_; i++)
        if (element_refs_[i].element_ == element)
            element_refs_[i].index_in_element_ = node_index_in_element;
}

/**
 * @brief 
 * 
 * @param ranks 
 */
void Node::GetRanks(std::set<std::size_t> &ranks) const {
    ranks.clear();
    for (int i = 0; i < element_ref_num_; i++)
        ranks.insert(element_refs_[i].element_->rank_);
}

void Node::ClearMass() {
   m_ = 0.0;
}

void Node::CalcMassInv(double delta_t) {
    assert(this->m_ > 0.0);
    this->m_inv_ = 1.0 / m_;
    this->delta_t_by_m_ = delta_t * this->m_inv_;
}

void Node::GatherVelD() {
    this->vel_d_.clear();
    for (int i = 0; i < this->element_ref_num_; i++) {
        this->element_refs_[i].element_->AddVelD(this->vel_d_, this->element_refs_[i].index_in_element_);
    }
}

void Node::ApplyVelD() {
    this->vel_ += this->vel_d_;
}
