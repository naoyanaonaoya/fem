#ifndef _BOUNDARY_HPP_
#define _BOUNDARY_HPP_

#include "Node.hpp"

#include <vector>

/**
 * @brief class that holds the definition of the boundary conditions
 * velocities can be specified for nodes on boundary conditions,
 * but depending on the coordinates of the nodes.
 * 
 * the coordinates of a node point are (x, y, z) and the rate of acceleration is c (0 <= c <= 1.0),
 * the velocity (u, v, w) there is defined by the following equation.
 * 
 * u(x, y, c) = c * (a0_ + a1_ * x + a2_ * y + a3_ * x^2 + a4_ * x * y + a5_ * y^2)
 * v(x, y, c) = c * (b0_ + b1_ * x + b2_ * y + b3_ * x^2 + b4_ * x * y + b5_ * y^2)
 * w(x, y, c) = c * (c0_ + c1_ * x + c2_ * y + c3_ * x^2 + c4_ * x * y + c5_ * y^2)
 * 
 * c is the time to t_ramp based on the simulation time at the caller of this function.
 * Set up the function so that it gradually accelerates over time.
 * (use cos curve so that derivative = 0 at t = 0, t_ramp)
 */
class Boundary {

private:

    std::vector<Node*> nodes_;

public:

    //! Whether to set x, y and z boundary conditions
    //! 0: not set, 1: set
    std::size_t exist_of_x_boundary_ = 0;
    std::size_t exist_of_y_boundary_ = 0;
    std::size_t exist_of_z_boundary_ = 0;

    double a0_, a1_, a2_, a3_, a4_, a5_;
    double b0_, b1_, b2_, b3_, b4_, b5_;
    double c0_, c1_, c2_, c3_, c4_, c5_;

    /**
     * @brief add Nodes to boundary
     * @param node 
     */
    void AddNode(Node* node);

    /**
     * @fn
     * @brief 
     * @param c 
     */
    void Apply(double c);
};

#endif // _BOUNDARY_HPP_