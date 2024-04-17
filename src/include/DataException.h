/**
 * @file DataException.h
 * @brief DataException class
 * @author NaoyaIMAI
 * @date 2024-02-25
 */

#ifndef _DATA_EXCEPTION_H_
#define _DATA_EXCEPTION_H_

#include <iostream>
#include <sstream>

/**
 * @brief class for exception handling
 * @note this class is used to handle exceptions
 */
class DataException {

private:

public:

    //! source file name
    const char *source_file_;

    //! source file line number
    int source_line_;

    //! error message
    std::string msg_str_;

    /**
     * @fn
     * @brief constructor
     * @param file
     * @param line
     * @param msg_str
     */
    DataException(const char *file, int line, const std::string &msg_str) {
        source_file_ = file;
        source_line_ = line;
        msg_str_ = msg_str;
    }

    /**
     * @fn
     * @brief write the exception message to the stream
     * @param os
     * @return void
     */
    void writeTo(std::ostream &os) const {
        os << "DataException : " << msg_str_;
        os << ", at \"" << source_file_ << "\", line " << source_line_ << " ";
    }
};

inline std::ostream &operator<<(std::ostream &os, const DataException &exp) {
    exp.writeTo(os);
    return os;
}


#endif // _DATA_EXCEPTION_H_
