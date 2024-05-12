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

class Node {
    public:
        
        //! node number from 0-index
        int global_index_;
        
        //! node number from 0-index in the rank
        int local_index_;

        /// position of the node
        ArrayXYZ pos_;
        
        //! velocity of the node
        ArrayXYZ vel_;

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
        }

        //! destructor
        // ~Node() {
        //     clearElementRefs();
        // }

        // void clearElementRefs();

    private:

};

#endif // _NODE_H_
