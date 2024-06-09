#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include "ErrorMessage.hpp"
#include "Array.hpp"

#define INDEX2D(row, col, i, j) (col * i + j)

/**
 * @brief class for Matrix of ROW x COL elements
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 */
template <std::size_t ROW, std::size_t COL>
class Matrix {

private:

    std::array<double, ROW * COL> v_;

public:

    /**
     * @brief Construct a new Matrix<ROW, COL>
     *
     * @tparam Args
     * @param args
     * @note Matrix<3, 3> m33_0(0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
     * @note cant not like Matrix<3, 3> m33_0 = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
     * @note because explicit
     * @note Args : template parameter pack. Containing the inferred type.
     * @note args : function parameter pack. Containing the arguments.
     */
    template<typename... Args>
    explicit Matrix<ROW, COL>(Args... args) : v_{{args...}} {
        // std::cout << "Matrix constructor1\n";
        static_assert(sizeof...(args) == ROW * COL, "The number of arguments must be equal to the size of the Matrix.");
    }

    /**
     * @brief Construct a new Matrix< N> object
     *
     * @note Matrix<3, 3> v33_0();
     */
    explicit Matrix<ROW, COL>() {
        // std::cout << "Matrix constructor0\n";
        static_assert(ROW > 0 && COL > 0, "Matrix dimensions must be greater than zero.");
    }

    /**
     * @brief Return the number of elements in the matrix.
     *
     * @return
     * @note int numberOfElement = m33_0.size();
     */
    size_t Size() const {
        return ROW * COL;
    }

    /**
     * @brief Return the number of row in the matrix.
     *
     * @return
     * @note int numberOFRow = m33_0.sizeRow();
     */
    size_t SizeRow() const {
        return ROW;
    }

    /**
     * @brief Return the number of col in the matrix.
     *
     * @return
     * @note int numberOfCol = m33_0.sizeCOL();
     */
    size_t SizeCol() const {
        return COL;
    }

    /**
     * @brief
     * @note m33_0.clear();
     */
    void Clear() {
        // std::cout << "Matrix clear\n";
        for (std::size_t i = 0; i < ROW * COL; i++)
            this->v_[i] = 0.0;
    }

    /**
     * @brief
     *
     * @param value
     * @note m33_0.set(3.0);
     */
    void Set(const double& value) {
        // std::cout << "Matrix set " << value << "\n";
        for (std::size_t i = 0; i < ROW * COL; i++)
            this->v_[i] = value;
    }

    /**
     * @fn
     * @brief Return the value of element.
     *
     * @param row
     * @param col
     *
     * @return
     * @note mat(1, 2) = 5.0;
     */
    double& operator()(std::size_t row, std::size_t col) {
        if (row < 0 || row >= ROW || col < 0 || col >= COL)
            throw std::out_of_range("Matrix index out of range");
        return v_[INDEX2D(ROW, COL, row, col)];
    }

    /**
     * @brief Return the value of elemnt and cannot change the value.
     *
     * @param row
     * @param col
     *
     * @return
     * @note double value = mat(1, 2);
     */
    double operator()(std::size_t row, std::size_t col) const {
        if (row < 0 || row >= ROW || col < 0 || col >= COL)
            throw std::out_of_range("Matrix index out of range");
        return v_[INDEX2D(ROW, COL, row, col)];
    }

    /**
     * @brief Update the matrix values using initializer list via operator().
     *
     * @param values
     * @note m22_0.update({0.0, 1.0, 2.0, 3.0});
     */
    void Update(std::initializer_list<double> values) {
        std::cout << "Matrix update using initializer_list\n";
        if (values.size() != ROW * COL)
            throw std::invalid_argument("Initializer list must have exactly " + std::to_string(ROW * COL) + " elements.");
        std::copy(values.begin(), values.end(), v_.begin());
    }

    /**
     * @brief Update the matrix values using parameter apck
     *
     * @tparam Args
     * @param args
     * @note m22_0.update(0.0, 1.0, 2.0, 3.0);
     */
    template<typename... Args>
    void Update(Args... args) {
        std::cout << "Matrix update using template\n";
        static_assert(sizeof...(args) == ROW * COL, "The number of arguments must be equal to the size of the Matrix.");
        v_ = {args...};
    }

    /**
     * @brief Matrix transpose
     *
     * @return Matrix<COL, ROW>
     * @note Matirx<4, 3> m43_0 = ~m34_0;
     */
    Matrix<COL, ROW> operator~() const {
        Matrix<COL, ROW> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(j, i) = (*this)(i, j);
        return result;
    }

    /**
     * @brief Matrix transpose in place
     * @note !m44_0;
     */
    void operator!() {
        static_assert(ROW == COL, "Transopse in place is only applicable to square matrix.");
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = i + 1; j < COL; j++) {
                // std::cout << "(i, j) = " << "(" << i << ", " << j << ")\n";
                std::swap((*this)(i, j), (*this)(j, i));
            }
    }

    /**
     * @brief Matrix and Matrix addition.
     *
     * @tparam size_t o_row
     * @tparam size_t o_col
     * @param Matrix<ROW, COL> other
     *
     * @return Matrix<ROW, COL> result
     * @note Matrix<4, 3> m43_2 = m43_0 + m43_1;
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, COL> operator+(const Matrix<o_row, o_col> &other) const {
        // std::cout << "matrix operator +\n";
        static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for addition");
        Matrix<ROW, COL> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(i, j) = (*this)(i, j) + other(i, j);
        return result;
    }

    /**
     * @brief Matrix and Matrix subtraction.
     *
     * @tparam o_row
     * @tparam o_col
     * @param other
     *
     * @return
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, COL> operator-(const Matrix<o_row, o_col> &other) const {
        // std::cout << "matrix operator -\n";
        static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for addition");
        Matrix<ROW, COL> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(i, j) = (*this)(i, j) - other(i, j);
        return result;
    }

    /**
     * @brief Matirx and Matrix multiplication.
     *
     * @tparam o_row
     * @tparam o_col
     * @param other
     *
     * @return 
     * @note mat43_1 = mat44_0 * mat43_0;
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, o_col> operator*(const Matrix<o_row, o_col>& other) const {
        static_assert(COL == o_row, "Matrix dimensions must match for multiplication.");
        if (COL != other.SizeRow())
            throw std::invalid_argument("Matrix dimensions must match for multiplication.");

        Matrix<ROW, o_col> result;
        for (std::size_t i = 0; i < ROW; ++i) {
            for (std::size_t j = 0; j < o_col; ++j) {
                result(i, j) = 0.0;
                double sum = 0.0;
                for (std::size_t k = 0; k < COL; ++k)
                    sum += (*this)(i, k) * other(k, j);
                result(i, j) = sum;
            }
        }
        return result;
    }

    /**
     * @brief Matrix and Matrix multiplication each elements.
     *
     * @tparam size_t o_row
     * @tparam size_t o_col
     * @param Array<o_row, o_col> other
     *
     * @return Array<ROW, COL>
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, o_col> operator&(const Matrix<o_row, o_col>& other) const {
        static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for multiplication.");
        if (ROW != o_row || COL != o_col)
            throw std::invalid_argument("Matrix dimensions must match for multiplication.");

        Matrix<ROW, o_col> result;
        for (std::size_t i = 0; i < ROW; ++i)
            for (std::size_t j = 0; j < o_col; ++j)
                    result(i, j) = (*this)(i, j) * other(i, j);
        return result;
    }

    /**
     * @brief
     * Due to the properties of Matrix multiplication,
     * the multiply-assign operator cannot be defined.
     *
     */
    template <std::size_t o_row, std::size_t o_col>
    [[deprecated("Matrix multiplication does not support the *= operator.")]]
    Matrix<ROW, o_col>& operator*=(const Matrix<o_row, o_col>& other) {
        // std::cout << "matrix ooperator *=\n";
        ErrorMessage err;
        throw std::runtime_error(err.createErrorMessage("Matrix multiplication does not support the *= operator.", __FILE__, __LINE__));
        if (COL != other.getRowSize())
            throw std::invalid_argument("Matrix dimensions must match for multiplication.");

        Matrix<ROW, o_col> result;
        result.clear();
        result = (*this) * other;
        // for (std::size_t i = 0; i < ROW; i++) {
        //     for (std::size_t j = 0; j < o_col; j++) {
        //         double sum = 0.0;
        //         for (std::size_t)
        //         (*this)(i, j) = result(i, j);
        //     }
        // }
        // return *this;
    }

    // ============================================================
    // we want to compare speed of return in copy or reference!!
    // ============================================================
    //
    // template <std::size_t o_row, std::size_t o_col>
    // Matrix<ROW, COL> operator+=(const Matrix<o_row, o_col> &m) {
    //     std::cout << "matrix operator +\n" << std::endl;
    //     static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for addition");
    //     for (std::size_t i = 0; i < ROW; i++) {
    //         for (std::size_t j = 0; j < COL; j++) {
    //             (*this)(i, j) += m(i, j);
    //         }
    //     }
    //     return *this;
    // }


    /**
     * @brief Matrix and matrix additive assignments.
     *
     * @tparam o_row
     * @tparam o_col
     * @param m
     *
     * @return 
     * @note mat32_0 += mat32_1;
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, COL>& operator+=(const Matrix<o_row, o_col> &m) {
        // std::cout << "matrix operator +=\n" << std::endl;
        static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for addition");
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                (*this)(i, j) += m(i, j);
        return *this;
    }

    /**
     * @brief Matrix and matrix subtraction ssignments.
     *
     * @tparam o_row
     * @tparam o_col
     * @param m
     *
     * @return 
     * @note mat32_0 -= mat32_1;
     */
    template <std::size_t o_row, std::size_t o_col>
    Matrix<ROW, COL>& operator-=(const Matrix<o_row, o_col> &m) {
        // std::cout << "matrix operator -=\n" << std::endl;
        static_assert(ROW == o_row && COL == o_col, "Matrix dimensions must match for addition");
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                (*this)(i, j) -= m(i, j);
        return *this;
    }
    
    
    /**
     * @brief Matrix and scalar addition.
     *
     * @param s
     *
     * @return 
     * @note mat32_0 = mat32_0 + 5.0;
     */
    Matrix<ROW, COL> operator+(const double &s) const  {
        Matrix<ROW, COL> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(i, j) = (*this)(i, j) + s;
        return result;
    }


    /**
     * @brief Matrix and scalar subtraction.
     *
     * @param s
     *
     * @return 
     * @note mat32_0 = mat32_0 - 5.0;
     */
    Matrix<ROW, COL> operator-(const double &s) const {
        Matrix<ROW, COL> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(i, j) = (*this)(i, j) - s;
        return result;
    }

    /**
     * @brief Matrix and scalar multiplicatino.
     *
     * @param s
     *
     * @return 
     * @note mat32_0 = mat32_0 * 5.0;
     */
    Matrix<ROW, COL> operator*(const double &s) const {
        Matrix<ROW, COL> result;
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                result(i, j) = (*this)(i, j) * s;
        return result;
    }

    /**
     * @brief Matrix and scalar additive assignments. 
     *
     * @param s
     *
     * @return 
     * @note mat32_0 += 5.0;
     */
    Matrix<ROW, COL> operator+=(const double &s) {
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                (*this)(i, j) += s;
        return *this;
    }

    /**
     * @brief Matrix and scalar subtraction assignments.
     *
     * @param s
     *
     * @return 
     * @note mat32_0 -= 5.0;
     */
    Matrix<ROW, COL> operator-=(const double &s) {
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                (*this)(i, j) -= s;
        return *this;
    }

    /**
     * @brief Matrix and scalar multiplication assignment.
     *
     * @param s
     *
     * @return 
     * @note mat32_0 *= 5.0;
     */
    Matrix<ROW, COL> operator*=(const double &s) {
        for (std::size_t i = 0; i < ROW; i++)
            for (std::size_t j = 0; j < COL; j++)
                (*this)(i, j) *= s;
        return *this;
    }


    /**
     * @brief Output the matrix elements.
     *
     * @param os
     */
    void WriteTo(std::ostream &os) const {
        // save the current format flags
        std::ios_base::fmtflags originalFlags = os.flags();
        std::streamsize originalPrecision = os.precision();
        
        os << std::fixed << std::setprecision(5);
        os << "(\n";
        for (std::size_t i = 0; i < ROW; i++) {
            os << "(";
            for (std::size_t j = 0; j < COL; j++) {
                // os << v_[INDEX2D(ROW, COL, i, j)];
                os << (*this)(i, j);
                if (j < COL - 1)
                    os << ", ";
            }
            os << ")";
            if (i < ROW - 1)
                os << ",\n";
        }
        os << "\n)";

        os.flags(originalFlags);
        os.precision(originalPrecision);
    }


private:

    /**
     * @brief Calcualte row sum for matrix and vector multiplication.
     *
     * @tparam size_t N
     * @param size_t i : row number of matrix
     * @param Array<N> arr
     *
     * @return double
     * @note The const modifier is required because this function is
     * @note called from a member function with the const modifier.
     */
    template <std::size_t N>
    inline double MultRow(const std::size_t& i, const Array<N>& arr) const {
        double ret = 0.0;
        for (std::size_t j = 0; j < N; j++)
            ret += (*this)(i, j) * arr[j];
        return ret;
    } 

public:

    /**
     * @brief Matrix and vector multiplication. 
     *
     * @tparam size_t o_row
     * @param Array<o_row> arr
     *
     * @return Array<ROW>
     * @note Array<4> a4_0 = m43_0 * arr3_0;
     */
    template <std::size_t o_row>
    Array<ROW> operator*(const Array<o_row>& arr) const {
        static_assert(COL == o_row, "Matrix and vector multiplication must match for matrix col vector size.");
        
        Array<ROW> result;
        for (std::size_t i = 0; i < ROW; i++)
            result[i] = MultRow(i, arr);
        return result;
    }

};

/**
 * @brief 
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param Matrix<ROW, COL> mat
 *
 * @return Matrix<ROW, COL> mat
 * @note Matrix<3, 4> m34_1 = -m34_0;
 * @note This template is need, because this is not inside of the calss definition.
 */
template <std::size_t ROW, std::size_t COL>
inline static Matrix<ROW, COL> operator-(const Matrix<ROW, COL> &mat) {
    return mat * -1.0;
}

/**
 * @brief scalar and Matrix addition.
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param scalar s
 * @param Matrix<ROW, COL> mat
 *
 * @return Matrix<ROW, COL> mat
 * @note Matri32_1 = sca + Matrix32_0;
 */
template <std::size_t ROW, std::size_t COL>
inline static Matrix<ROW, COL> operator+(const double &s, const Matrix<ROW, COL> &mat) {
    return mat + s;
}

/**
 * @brief scalar and Matrix subtraction.
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param scalar s
 * @param Matrix<ROW, COL> mat
 *
 * @return Matrix<ROW, COL> mat
 * @note Matrix<3, 4> m34_1 = sca - m34_0;
 */
template <std::size_t ROW, std::size_t COL>
inline static Matrix<ROW, COL> operator-(const double &s, const Matrix<ROW, COL> &mat) {
    return -mat + s;
}

/**
 * @brief scalar and Matrix multiplication
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param scalar s
 * @param Matrix<ROW, COL> mat
 *
 * @return Matrix<ROW, COL>
 * @note mat32_0 = sca * mat32_0;
 */
template <std::size_t ROW, std::size_t COL>
inline static Matrix<ROW, COL> operator*(const double &s, const Matrix<ROW, COL> &mat) {
    return mat * s;
}

template <std::size_t o_col, std::size_t ROW, std::size_t COL>
inline static double MultCol(const std::size_t& j, const Array<o_col>& arr, const Matrix<ROW, COL>& mat) {
    double ret = 0.0;
    for (std::size_t row = 0; row < mat.SizeRow(); row++)
        ret += arr[row] * mat(row, j);
    return ret;
}

/**
 * @brief Vector and Matrix multiplication. 
 *
 * @tparam size_t o_col
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param Array<o_col> arr
 * @param Array<ROW, COL> mat
 *
 * @return Array<COL>
 * @note Array<4> arr4_0 = arr3_0 * m34_0;
 */
template <std::size_t o_col, std::size_t ROW, std::size_t COL>
inline static Array<COL> operator*(const Array<o_col>& arr, const Matrix<ROW, COL>& mat) {
    static_assert(o_col == ROW, "Array and Matrix multiplication must match for vector size and matrix row");
    // std::cout << "operator * array and matrix multiplicatoin\n";
    Array<COL> result;
    for (std::size_t j = 0; j < mat.SizeCol(); j++) {
       result[j] = MultCol(j, arr, mat); 
    }
    return result;
}


/**
 * @brief Output the matrix elemetns.
 *
 * @tparam size_t ROW
 * @tparam size_t COL
 * @param os
 * @param Array<ROW, COL> mat
 *
 * @return 
 * @note std::cout << mat32_0 << std::end;
 */
template <std::size_t ROW, std::size_t COL>
inline static std::ostream &operator<<(std::ostream &os, const Matrix<ROW, COL> &mat) {
    mat.WriteTo(os);
    return os;
}

#endif // _MATRIX_H_
