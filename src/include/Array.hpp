#ifndef _ARRAY_HPP_
#define _ARRAY_HPP_

#include <cmath>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <iomanip>
#include <stdexcept>

/**
 * @brief class for Array of N elements
 * <notes>Parameterization of values determined at compile time.</notes>
 */
template <std::size_t N>
class Array {

private:
    //! array of the elements
    std::array<double, N> v_;

public:

    /**
     * @brief Construct a new Array object
     * template<typename>>> Args> : variadic template
     * Args... args : Perfect forwarding
     * v_{{args...}} : list initialization, uniform initialization
     * @tparam Args 
     * @param args 
     * @note Array<2> a2_0(1.0, 2.0);
     */
    template<typename... Args>
    explicit Array<N>(Args... args) : v_{{args...}} {
        static_assert(sizeof...(args) == N, "The number of arguments must be equal to the size of the Array.");
        std::cout << "Array constructor 1\n";
    }
 
    /**
     * @brief Construct a new Array N object
     * @note not initialize the member variables
     * @note Array<3> a3_0;
     */
    explicit Array<N>()
    {
        std::cout << "Array constructor 0\n";
        static_assert(N > 0, "Array dimensions must be greater than zero.");
    }

    /**
     * @brief Return the number of elements.
     *
     * @return size_t
     * @note size_t a30Size = a3_0.size();
     */
    size_t size() const {
        return N;
    }

    /**
     * @brief Set all elements to 0.0.
     * @note a3.clear();
     */
    void clear() {
        std::cout << "Array clear\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] = 0.0;
    }

    /**
     * @brief Return the value of element.
     *
     * @param i
     *
     * @return 
     * @note a3[2] = 5.0;
     */
    double &operator[](size_t i) {
        if (i < 0 || i >= N)
            throw std::out_of_range("Array index out of range.");
        return v_[i];
    }

    /**
     * @brief Return the value of element.
     *
     * @param i
     *
     * @return 
     * @note duuble balue = a3[2];;
     */
    double operator[](size_t i) const {
        if (i < 0 || i >= N)
            throw std::out_of_range("Array index out of range.");
        return v_[i];
    }

    /**
     * @brief Copy construct a new Array N object
     *
     * @param other
     */
    Array<N>(const Array<N> &other) {
        std::cout << "Array copy constructor\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] = other[i];
    }

    /**
     * @brief Update the array values using initializer list via operator().
     *
     * @param values
     * @note a4_0({1.0, 2.0, 3.0, 4.0});
     */
    void operator()(std::initializer_list<double> values) {
       if (values.size() != N)
           throw std::invalid_argument("Initializer list must have exactly " + std::to_string(N) + " elements.");
       std::cout << "Array update\n";
       std::copy(values.begin(), values.end(), v_.begin());
    }

    /**
     * @brief 
     *
     * @tparam size_t M
     * @param Array<M> other
     *
     * @return Array<N>
     */
    template <std::size_t M>
    Array<N>& operator=(const Array<M>& other) {
        static_assert(N == M, "Cannot assign Arrays of different dimensions.");
        // Check ofr self-assignment to prevent issues like resource doulbe-freeing
        if (this == &other)
            return *this;
        std::cout << "array operator = (same dimension)\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] = other.v_[i];
    }

    // Array<N>& operator=(const Array<N>& other) {
    //     // Check for self-assignment to prevent issues like resource doulbe-freeing
    //     if (this != &other) {
    //         // Actual assignment operations go here
    //         std::cout << "Array operator= (same dimension)\n";
    //         for (std::size_t i = 0; i < N; i++) {
    //             this->v_[i] = other.v_[i];
    //         }
    //     }
    //     return *this;
    // }

    // /**
    //  * @brief 
    //  * 
    //  * @tparam M 
    //  * @param other 
    //  * @return Array<N>&
    //  * @note Array<3> a3_2 = a2_1; 
    //  */
    // template <std::size_t M>
    // Array<N>& operator=(const Array<M>& other) {
    //     static_assert(N == M, "Cannot assign Arrays of different dimensions.");
    // }

    /**
     * @brief Array and array addition. 
     * 
     * @tparam size_t M 
     * @param Array<M> other 
     * @return Array<N> 
     * @note a3_2 = a3_0 + a3_1;
     */
    template <std::size_t M>
    Array<N> operator+(const Array<M>& other) const {
        static_assert(N == M, "Cannot add Arrays of different dimensions.");
        std::cout << "Array operator +\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++)
            result[i] = this->v_[i] + other[i];
        return result;
    }

    /**
     * @brief Array and array subtraction.
     *
     * @tparam size_t M
     * @param Array<M> other
     *
     * @return 
     * @note a3_2 = a3_0 - a3_1;
     */
    template <std::size_t M>
    Array<N> operator-(const Array<M>& other) const {
        static_assert(N == M, "Cannot subtract Arrays of different dimensions.");
        std::cout << "Array operator -\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++)
            result[i] = this->v_[i] - other[i];
        return result;
    }

    /**
     * @brief Array and array multiplication. 
     *
     * @tparam size_t M
     * @param Array<N> other
     *
     * @return Array<N>
     * @note a3_2 = a3_0 * a3_1;
     */
    template <std::size_t M>
    Array<N> operator*(const Array<M>& other) const {
        static_assert(N == M, "Cannot subtract Arrays of different dimensions.");
        std::cout << "Array operator *\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++)
            result[i] = this->v_[i] * other[i];
        return result;
    }

    /**
     * @brief Array and array additive assignments.
     *
     * @tparam sizt_t M
     * @param Array<M> other
     *
     * @return Array<N>&
     * @note a3_2 += a3_1;
     */
    template <std::size_t M>
    Array<N>& operator+=(const Array<M>& other) {
        static_assert(N == M, "Cannot add Arrays of different dimensions.");
        std::cout << "Array operator+=\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] += other[i];
        return *this;
    }

    /**
     * @brief Array and array subtraction assignments.
     *
     * @tparam sizt_t M
     * @param Array<M> other
     *
     * @return Array<N>&
     * @note a3_2 -= a3_1;
     */
    template <std::size_t M>
    Array<N>& operator-=(const Array<M>& other) {
        static_assert(N == M, "Cannot subtract Arrays of different dimensions.");
        std::cout << "Array operator-=\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] -= other[i];
        return *this;
    }

    /**
     * @brief Array and array multiplication assignments.
     *
     * @tparam sizt_t M
     * @param Array<M> other
     *
     * @return Array<N>&
     * @note a3_2 *= a3_1;
     */
    template <std::size_t M>
    Array<N>& operator*=(const Array<M>& other) {
        static_assert(N == M, "Cannot subtract Arrays of different dimensions.");
        std::cout << "Array operator-=\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] *= other[i];
        return *this;
    }

    /**
     * @brief Array and scalar addiction.
     *
     * @param scalar
     *
     * @return Arary<N>
     * @note a3_2 = a3_1 + 5.0;
     */
    Array<N> operator+(const double scalar) const {
        std::cout << "Arary operator + scala\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++)
            result[i] = this->v_[i] + scalar;
        return result;
    }

    /**
     * @brief Array and scalar subtraction.
     *
     * @param scalar
     *
     * @return Arary<N>
     * @note a3_2 = a3_1 - 5.0;
     */
    Array<N> operator-(const double scalar) const {
        std::cout << "Array operator - scalar\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++) 
            result[i] = this->v_[i] - scalar;
        return result;
    }

    /**
     * @brief Array and scalar multiplication.
     *
     * @param scalar
     *
     * @return Array<N>
     * @note a3_2 = a3_1 * 5.0;
     */
    Array<N> operator*(const double& scalar) const {
        std::cout << "Array operator * scalar\n";
        Array<N> result;
        for (std::size_t i = 0; i < N; i++)
            result[i] = this->v_[i] * scalar;
        return result;
    }

    /**
     * @brief Array and scalar additive assignments.
     *
     * @param scalar
     *
     * @return Array<N>
     * @note a3_1 += 5.0;
     */
    Array<N>& operator+=(const double& scalar) {
        std::cout << "Array operator += scalar\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] += scalar;
        return *this;
    }

    /**
     * @brief Array and scalar subtraction assignments.
     *
     * @param scalar
     *
     * @return Array<N>
     * @note a3_1 -= 5.0;
     */
    Array<N>& operator-=(const double& scalar) {
        std::cout << "Array operator -= scalar\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] -= scalar;
        return *this;
    }

    /**
     * @brief Array and scalar multiplication assignments.
     *
     * @param scalar
     *
     * @return Array<N>
     * @note a3_1 *= 5.0;
     */
    Array<N>& operator*=(const double& scalar) {
        std::cout << "Array operator -= scalar\n";
        for (std::size_t i = 0; i < N; i++)
            this->v_[i] *= scalar;
        return *this;
    }

    void Test(double input) const {
        std::cout << "input = " << input << std::endl;
        std::cout << "test" << std::endl;
    }

    void Test() const {
        std::cout << "test" << std::endl;
    }

    void TestTest() const {
        std::cout << "testtest" << std::endl;
    }

    void TT() const {
        std::cout << "tt" << std::endl;
    }
    
    void TTT() const {
        std::cout << "ttt" << std::endl;
    }

    /**
     * @brief Return the dot product.
     *
     * @tparam size_t M
     * @param Array<M> other
     *
     * @return double
     * @note a3_2.Dot(a3_1);
     */
    template <std::size_t M>
    double Dot(const Array<M>& other) const {
        static_assert(N == M, "Cannot dot product of different dimensions.");
        std::cout << "Array operator Dot\n";
        double value = 0.0;
        for (std::size_t i = 0; i < N; i++)
            value += this->v_[i] * other[i];
        return value;
    }

    template <std::size_t M>
    double DotDot(const Array<M>& other) const {
        static_assert(N == M, "Cannot DotDot product of different dimensions.");
        std::cout << "Array operator DotDot\n";
        double value = 0.0;
        for (std::size_t i = 0; i < N; i++)
            value += this->v_[i] * other[i];
        return value * value;
    }

    /**
     * @brief Return the array L1 Norm. 
     *
     * @return double
     * @note a3_0.NormL1();
     */
    double NormL1() const {
        double max = 0.0;
        for (std::size_t i = 0; i < N; i++)
            if (std::abs(v_[i]) > max)
                max = std::abs(v_[i]);
        return max;
    }

    /**
     * @brief Return the array L2 Norm. 
     *
     * @return double
     * @note a3_0.NormL2();
     */
    double NormL2() const {
        double sum = 0.0;
        for (std::size_t i = 0; i < N; i++)
            sum += v_[i] * v_[i];
        return std::sqrt(sum);
    }

    /**
     * @brief Output the array elements.
     *
     * @param os
     */
    void write_to(std::ostream &os) const {
        // save the current format flags
        std::ios_base::fmtflags originalFlags = os.flags();
        std::streamsize originalPrecision = os.precision();
        
        os << std::fixed << std::setprecision(5);
        os << "(";
        for (std::size_t i = 0; i < N; i++) {
            os << v_[i];
            if (i != N - 1) {
                os << ", ";
            }
        }
        os << ")";

        os.flags(originalFlags);
        os.precision(originalPrecision);
    }
};

// this tempate is nedd, because this is not inside of the clas definition.
template <std::size_t N>
inline static Array<N> operator-(const Array<N>& arr) {
    return arr * -1.0;
}

template <std::size_t N>
inline static Array<N> operator+(const double &s, const Array<N>& arr) {
    return arr + s;
}

template <std::size_t N>
inline static Array<N> operator-(const double &s, const Array<N>& arr) {
    return -arr + s;
}

template <std::size_t N>
inline static Array<N> operator*(const double &s, const Array<N>& arr) {
    return arr * s;
}

/**
 * @brief Output the array elements.
 *
 * @tparam size_t N
 * @param os
 * @param v
 *
 * @return 
 * @note std::cout << a3_0 << std::endl;
 */
template <std::size_t N>
inline static std::ostream &operator<<(std::ostream &os, const Array<N> &arr) {
    arr.write_to(os);
    return os;
}

#endif // _ARRAY_HPP_
