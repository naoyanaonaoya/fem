/**
 * @file node.h
 * @brief 節点の情報を保持するクラス
 * @author Naoya IMAI
 * @date 20240219
*/

#ifndef _NODE_H_
#define _NODE_H_

#include "ArrayXYZ.hpp"
#include "Logger.hpp"

// #include <algorithm>
#include <set>

// forward declarration
// have to include "Element.hpp" in source file."
class Element;

class ElementRef {

public:

    Element* element_;

    std::size_t index_in_element_;

};

class Node {

public:

    //! node number from 0-index
    std::size_t global_index_;

    //! node number from 0-index in the rank
    std::size_t local_index_;

    std::size_t element_ref_num_;

    ElementRef* element_refs_;

    ElementRef element_refs_array_[4];

    //! position of the node
    ArrayXYZ pos_;

    //! velocity of the node
    ArrayXYZ vel_;

    ArrayXYZ vel_d_;

    //! concentrated mass
    double m_;

    //! inverse of concentrated the mass
    double m_inv_;

    //! delta_t / m
    double delta_t_by_m_;

    Node(ArrayXYZ pos) {
        pos_ = pos;
        m_ = 0.0;
        m_inv_ = 0.0;
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
        // Logger::out << "Node()" << "\n";
        m_ = 0.0;
        m_inv_ = 0.0;
        delta_t_by_m_ = 0.0;
        element_refs_ = &element_refs_array_[0];
        element_ref_num_ = 0;
    }

    Node(double x, double y, double z) {
        pos_.x_ = x;
        pos_.y_ = y;
        pos_.z_ = z;
        m_ = 0.0;
        m_inv_ = 0.0;
        delta_t_by_m_ = 0.0;
        element_refs_ = &element_refs_array_[0];
        element_ref_num_ = 0;
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
        this->CopyElementRefsFrom(o);
    }

    // destructor
    ~Node() {
        this->ClearElementRefs();
    }

    // void clearElementRefs();

    void SetPos(double x, double y, double z);

    void SetPos(const ArrayXYZ& pos);

    void SetVel(double x, double y, double z);

    void SetVel(const ArrayXYZ& vel);

    void AddElementRef(Element *element, int node_index_in_element);

    void CopyElementRefsFrom(const Node &o);

    void UpdateElementRef(Element *element, int node_index_in_element);

    void GetRanks(std::set<std::size_t> &ranks) const;

    void ClearElementRefs();

    void ClearMass();

    void CalcMassInv(double delta_t);

    void GatherVelD();

    void ApplyVelD();

private:

    ElementRef* AllocateElementRef();

};

#endif // _NODE_H_
