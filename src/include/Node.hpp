/**
 * @file node.h
 * @brief 節点の情報を保持するクラス
 * @author Naoya IMAI
 * @date 20240219
*/

#ifndef _NODE_H_
#define _NODE_H_

#include "ArrayXYZ.hpp"
// #include <algorithm>
#include <set>

// forward declarration
// have to include "Element.hpp" in source file."
class Element;

class ElementRef {

public:

    Element *element_;

    int index_in_element_;

};

class Node {

public:

    //! node number from 0-index
    int global_index_;

    //! node number from 0-index in the rank
    int local_index_;

    size_t element_ref_num_;

    ElementRef* element_refs_;

    ElementRef element_refs_array_[4];

    //! position of the node
    ArrayXYZ pos_;

    //! velocity of the node
    ArrayXYZ vel_;

    ArrayXYZ d_vel_;

    //! concentrated mass
    double m_;

    //! inverse of concentrated the mass
    double inv_m_;

    //! delta_t / m
    double delta_t_by_m_;

    Node(ArrayXYZ pos) {
        pos_ = pos;
        m_ = 0.0;
        inv_m_ = 0.0;
        delta_t_by_m_ = 0.0;
        this->element_refs_ = &this->element_refs_array_[0];
        this->element_ref_num_ = 0;
    }

    /**
     * @fn
     * @brief constructor
     * @param none
     * @return none
     */
    Node() {
        m_ = 0.0;
        inv_m_ = 0.0;
        delta_t_by_m_ = 0.0;
        this->element_refs_ = &this->element_refs_array_[0];
        this->element_ref_num_ = 0;
    }

    /**
     * @fn
     * @brief copy constructor
     * @param none
     * @return none
     */
    Node(const Node &o) {
        m_ = o.m_;
        pos_ = o.pos_;
        vel_ = o.vel_;
        this->copyElementRefsFrom(o);
    }

    // destructor
    ~Node() {
        this->clearElementRefs();
    }

    // void clearElementRefs();

    void addElementRef(Element *element, int node_index_in_element);

    void copyElementRefsFrom(const Node &o);

    void updateElementRef(Element *element, int node_index_in_element);

    void clearElementRefs();

    void clearMass();

    void calcInvMass(double delta_t);

    // void getRanks(std::set<int> &ranks) const;

    void gatherDVel();

    void applyDVel() {
        this->vel_ += d_vel_;
    }

private:

    ElementRef *allocateElementRef();

};

#endif // _NODE_H_
