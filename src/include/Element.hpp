#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <initializer_list>
#include <iostream>
#include <vector>

#include "Node.hpp"

class Element {

protected:

    int number_of_nodes_;

public:

    std::vector<Node*> nodes_;

    //! element rank
    int rank;

    //! element index
    int global_index_;

    //! element area
    double area_;

    //! element volume
    double volume_;

    //! courant number
    double courantNumber_;

public:

    /**
     * @brief Set the Rank object
     *
     * @param rank
     */
    void setRank(const int &rank) {
        this->rank = rank;
    }

    /**
     * @brief Set the Nodes object
     *
     * @param nodes
     * @nodes pure virtual function
     */
    virtual void setNodes(const std::vector<Node*> &nodes) = 0;


    virtual void setNodes(const std::initializer_list<Node *> &nodes) = 0;

    virtual size_t getNumberOfNodes() = 0; 
    /**
     * @fn
     * @brief calculate area
     * @param none
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void calcArea() = 0;

    virtual void calcArea3D() = 0;

    virtual void addDVel(ArrayXYZ& d_vel, int node_index) = 0;

    /**
     * @fn
     * @brief calculate volume
     * @param none
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void calcVolume() = 0;

    /**
     * @fn
     * @brief calculate courant number
     * @param delta_t
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void calcCourantNumber(const double &delta_t) = 0;
};

#endif // _ELEMENT_H_
