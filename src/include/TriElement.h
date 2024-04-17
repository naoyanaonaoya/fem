#ifndef _TRIELEMENT_H_
#define _TRIELEMENT_H_

#include <iostream>
#include "Element.h"

class TriElement : public Element {

private:

    void calcArea() override {
        // area_ = 0.5 * (node_[1]->x_ * (node_[2]->y_ - node_[3]->y_) + node_[2]->x_ * (node_[3]->y_ - node_[1]->y_) + node_[3]->x_ * (node_[1]->y_ - node_[2]->y_));
    }

    void calcVolume() override {
        volume_ = 0.0;
    }


    void calcCourantNumber(const double &delta_t) override {
        courantNumber_ = 1.0;
    }

};

#endif // _TRIELEMENT_H_
