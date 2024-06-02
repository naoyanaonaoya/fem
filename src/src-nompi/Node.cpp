#include "Node.hpp"
#include "Element.hpp"
#include <cassert>

void Node::clearElementRefs() {
    if (element_ref_num_ > 4) {
        delete[] element_refs_;
    }
    element_ref_num_ = 0;
}

void Node::copyElementRefsFrom(const Node &o) {
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

void Node::addElementRef(Element *element, int node_index_in_element) {
    ElementRef *element_ref = this->allocateElementRef();
    element_ref->element_ = element;
    element_ref->index_in_element_ = node_index_in_element;
}

ElementRef* Node::allocateElementRef() {
    std::cout << "element_ref_num_ = " << this->element_ref_num_ << std::endl;
    std::cout << "allocateElementRef start" << std::endl;
    if (this->element_ref_num_ < 4) {
        std::cout << "this->element_ref_num_ < 4" << std::endl;
        return &element_refs_[element_ref_num_++];
    } else {
        std::cout << "this->element_ref_num_ = 4" << std::endl;
        ElementRef *new_element_refs = new ElementRef[element_ref_num_ + 1];
        for (int i = 0; i < element_ref_num_; i++)
            new_element_refs[i] = element_refs_[i];
        std::cout << "delete before" << std::endl;
        if (element_ref_num_ > 4)
            delete[] element_refs_;
        std::cout << "delete after" << std::endl;
        element_refs_ = new_element_refs;
        return &new_element_refs[element_ref_num_++];
    }
    std::cout << "allocateElementRef finish" << std::endl;
}

void Node::updateElementRef(Element* element, int node_index_in_element) {
    for (int i = 0; i < element_ref_num_; i++)
        if (element_refs_[i].element_ == element)
            element_refs_[i].index_in_element_ = node_index_in_element;
}

void Node::clearMass() {
   this->m_ = 0.0;
}

void Node::calcInvMass(double delta_t) {
    assert(this->m_ > 0.0);
    this->inv_m_ = 1.0 / m_;
    this->delta_t_by_m_ = delta_t * this->inv_m_;
}

void Node::gatherDVel() {
    this->d_vel_.clear();
    for (int i = 0; i < this->element_ref_num_; i++) {
        this->element_refs_[i].element_->addDVel(this->d_vel_, this->element_refs_[i].index_in_element_);
    }
}
