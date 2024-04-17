#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <iostream>

class Element {

protected:

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

    /**
     * @fn
     * @brief calculate area
     * @param none
     * @return none
     * @note "= 0" means the function is pure virtual function
     */
    virtual void calcArea() = 0;

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
