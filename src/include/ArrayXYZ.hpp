#ifndef _ARRAYXYZ_H_
#define _ARRAYXYZ_H_

#include <cmath>
#include <iostream>
#include <iomanip>

class ArrayXYZ {

public:

    //! x, y, z components
    double x_, y_, z_;

    /**
     * @fn
     * @brief constructor
     * @param none
     * @return none
    */
    ArrayXYZ() {
        x_ = 0.0;
        y_ = 0.0;
        z_ = 0.0;
    }

    /**
     * @fn
     * @brief constructor
     * @param x double x component
     * @param y double y component
     * @param z double z component
     * @return none
    */
    ArrayXYZ(double x, double y, double z) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
     * @fn
     * @brief copy constructor
     * @param o ArrayXYZ object
     * @return none
    */
    ArrayXYZ(const ArrayXYZ &o) {
        x_ = o.x_;
        y_ = o.y_;
        z_ = o.z_;
    }

    /**
     * @fn
     * @brief set vector
     * @param x double x component
     * @param y double y component
     * @param z double z component
     * @return none
    */
    void set(double x, double y, double z) {
        x_ = x;
        y_ = y;
        z_ = z;
    }

    /**
     * @fn
     * @brief clear vector
     * @param none
     * @return none
    */
    void clear() {
        x_ = 0.0;
        y_ = 0.0;
        z_ = 0.0;
    }

    /**
     * @fn
     * @brief vector addition
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
    */
    ArrayXYZ operator+(const ArrayXYZ &o) const {
        ArrayXYZ v;
        v.x_ = x_ + o.x_;
        v.y_ = y_ + o.y_;
        v.z_ = z_ + o.z_;
        return v;
    }

    /**
     * @fn
     * @brief scalar addition
     * @param c double scalar
     * @return ArrayXYZ object
    */
    ArrayXYZ operator+(const double &c) const {
        ArrayXYZ v;
        v.x_ = x_ + c;
        v.y_ = y_ + c;
        v.z_ = z_ + c;
        return v;
    }

    /**
     * @fn
     * @brief vector subtraction
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
    */
    ArrayXYZ operator-(const ArrayXYZ &o) const {
        ArrayXYZ v;
        v.x_ = x_ - o.x_;
        v.y_ = y_ - o.y_;
        v.z_ = z_ - o.z_;
        return v;
    }

    /**
     * @fn
     * @brief scalar subtraction
     * @param c double scalar
     * @return ArrayXYZ object
    */
    ArrayXYZ operator-(const double &c) const {
        ArrayXYZ v;
        v.x_ = x_ - c;
        v.y_ = y_ - c;
        v.z_ = z_ - c;
        return v;
    }

    /**
     * @fn
     * @brief vector multiplication
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
    */
    ArrayXYZ operator*(const ArrayXYZ &o) const {
        ArrayXYZ v;
        v.x_ = x_ * o.x_;
        v.y_ = y_ * o.y_;
        v.z_ = z_ * o.z_;
        return v;
    }

    /**
     * @fn
     * @brief scalar multiplication
     * @param c double scalar
     * @return ArrayXYZ object
    */
    ArrayXYZ operator*(const double &c) const {
        ArrayXYZ v;
        v.x_ = x_ * c;
        v.y_ = y_ * c;
        v.z_ = z_ * c;
        return v;
    }

    /**
     * @fn
     * @brief vector assignment
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator=(const ArrayXYZ &o) {
        x_ = o.x_;
        y_ = o.y_;
        z_ = o.z_;
        return *this;
    }

    /**
     * @fn
     * @brief vector addition and assignment
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator+=(const ArrayXYZ &o) {
        x_ += o.x_;
        y_ += o.y_;
        z_ += o.z_;
        return *this;
    }

    /**
     * @fn
     * @brief scalar addition and assignment
     * @param c double scalar
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator+=(const double &c) {
        x_ += c;
        y_ += c;
        z_ += c;
        return *this;
    }

    /**
     * @fn
     * @brief vector subtraction and assignment
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator-=(const ArrayXYZ &o) {
        x_ -= o.x_;
        y_ -= o.y_;
        z_ -= o.z_;
        return *this;
    }

    /**
     * @fn
     * @brief scalar subtraction and assignment
     * @param c double scalar
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator-=(const double &c) {
        x_ -= c;
        y_ -= c;
        z_ -= c;
        return *this;
    }

    /**
     * @fn
     * @brief vector multiplication and assignment
     * @param o ArrayXYZ object
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator*=(const ArrayXYZ &o) {
        x_ *= o.x_;
        y_ *= o.y_;
        z_ *= o.z_;
        return *this;
    }

    /**
     * @fn
     * @brief scalar multiplication and assignment
     * @param c double scalar
     * @return ArrayXYZ object
     */
    ArrayXYZ &operator*=(const double &c) {
        x_ *= c;
        y_ *= c;
        z_ *= c;
        return *this;
    }

    /**
     * @fn
     * @brief ArrayXYZ minus operator
     * @param v ArrayXYZ object
     * @return ArrayXYZ object
     */
    inline ArrayXYZ operator-(const ArrayXYZ &v) {
        return v * -1.0;
    }

    /**
     * @fn
     * @brief inner product
     * @param o ArrayXYZ object
     * @return double
     */
    double dot(const ArrayXYZ &o) const {
        double dot = x_ * o.x_ + y_ * o.y_ + z_ * o.z_;
        return dot;
    }

    /**
     * @fn
     * @brief L1 norm
     * @param none
     * @return double
     */
    double NormL1() const {
        double l1norm = std::abs(x_) + std::abs(y_) + std::abs(z_);
        return l1norm;
    }

    /**
     * @fn
     * @brief L2 norm
     * @param none
     * @return double
     */
    double NormL2() const {
        double l2norm = std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
        return l2norm;
    }

    /**
     * @fn
     * @brief normalize ArrayXYZ
     * @param none
     * @return ArrayXYZ object
     */
    ArrayXYZ normalize() const {
        double l2norm = NormL2();
        ArrayXYZ v;
        v.clear();
        if (l2norm != 0.0) {
            v.x_ = x_ / l2norm;
            v.y_ = y_ / l2norm;
            v.z_ = z_ / l2norm;
            return v;
        } else {
            return v;
        }
    }
};


/**
 * @fn
 * @brief scalar addition
 * @param c
 * @param v
 * @return ArrayXYZ
 */
inline ArrayXYZ operator+(const double &c, const ArrayXYZ &v) {
    return v + c;
}

/**
 * @fn
 * @brief scalar subtraction
 * @param c
 * @param v
 * @return ArrayXYZ
 */
inline ArrayXYZ operator-(const double &c, const ArrayXYZ &v) {
    return v - c;
}

/**
 * @fn
 * @brief scalar multiplication
 * @param c
 * @param v
 * @return ArrayXYZ
 */
inline ArrayXYZ operator*(const double &c, const ArrayXYZ &v) {
    return v * c;
}

/**
 * @fn
 * @brief output ArrayXYZ
 * @param os
 * @param v
 * @return std::ostream
 */
inline std::ostream& operator<<(std::ostream &os, const ArrayXYZ &v) {
    // save the current format flags
    std::ios_base::fmtflags originalFlags = os.flags();
    std::streamsize originalPrecision = os.precision();

    os << std::fixed << std::setprecision(5);
    os << "(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";

    // restore the original format flags
    os.flags(originalFlags);
    os.precision(originalPrecision);

    return os;
}

#endif // _ARRAYXYZ_H_
