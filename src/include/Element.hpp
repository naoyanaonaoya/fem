#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "Node.hpp"

#include <initializer_list>
#include <iostream>
#include <vector>

class Element {

protected:

    std::size_t number_of_nodes_;

public:

    std::vector<Node*> nodes_;

    //! element process
    std::size_t rank_;

    //! element index
    std::size_t global_index_;

    //! element pressure
    double p_;

    //! element area
    double area_;

    //! element volume
    double volume_;

    //! courant number
    double courantNumber_;

public:

    // /**
    //  * @brief copy constructor a new Element object
    //  * 
    //  * @param other 
    //  */
    // Element(const Element& other) {
    //     number_of_nodes_ = other.number_of_nodes_;
    //     nodes_ = other.nodes_;
    //     rank_ = other.rank_;
    //     global_index_ = other.global_index_;
    //     p_ = other.p_;
    //     area_ = other.area_;
    //     volume_ = other.volume_;
    //     courantNumber_ = other.courantNumber_;
    // }

    // /**
    //  * @brief copy assignment a new Element object
    //  * 
    //  * @param other 
    //  * @return Element& 
    //  */
    // Element& operator=(const Element& other) {
    //     if (this == &other)
    //         return *this;

    //     number_of_nodes_ = other.number_of_nodes_;
    //     nodes_ = other.nodes_;
    //     rank_ = other.rank_;
    //     global_index_ = other.global_index_;
    //     p_ = other.p_;
    //     area_ = other.area_;
    //     volume_ = other.volume_;
    //     courantNumber_ = other.courantNumber_;
    //     return *this;
    // }

    ~Element() {}

    /**
     * @brief Set the proc_
     *
     * @param proc_
     */
    void SetRank(const std::size_t &rank) {
        rank_ = rank;
    }

    /**
     * @brief Set the Nodes object
     *
     * @param nodes
     * @nodes pure virtual function
     */
    virtual void SetNodes(const std::vector<Node*> &nodes) = 0;

    virtual void SetNodes(const std::initializer_list<Node *> &nodes) = 0;

    virtual size_t GetNumberOfNodes() = 0; 

    virtual void CalcInvariants1(double re) = 0;

    virtual void CalcInvariants2(double delta_t) = 0;

    /**
     * @fn
     * @brief calculate area
     * @param none
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void CalcArea() = 0;

    virtual void CalcArea3D() = 0;

    virtual void AddVelD(ArrayXYZ& vel_d, int node_index) = 0;

    /**
     * @fn
     * @brief calculate volume
     * @param none
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void CalcVolume() = 0;

    /**
     * @fn
     * @brief calculate courant number
     * @param delta_t
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual double CalcCourantNumber(const double &delta_t) = 0;
};

#endif // _ELEMENT_H_
