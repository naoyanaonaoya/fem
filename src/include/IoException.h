#ifndef _IO_EXCEPTION_H_
#define _IO_EXCEPTION_H_

#include <iostream>
#include <cstring>
#include <string>
#include <cerrno>
// macro for error conditions encountered in the standard library

class IoException {

private:

    //! file name of the source file where the error was encountered
    const char *source_file_;

    //! line number in the source file where the error was encountered
    int source_line_;

    //! error code
    int errno_;

    //! name of the file that caused the error
    std::string file_name_;

public:

    IoException(const char *source_file, int source_line, const char *file_name) {
        source_file_ = source_file;
        source_line_ = source_line;
        file_name_ = file_name;
        errno_ = errno; // right hand side is the error number passed from the OS
    }

    IoException(const char *source_file, int source_line, const std::string &file_name) {
        source_file_ = source_file;
        source_line_ = source_line;
        file_name_ = file_name;
        errno_ = errno;
    }

    void writeTo(std::ostream &os) const {
        os << "IoException : " << strerror(errno_) << ":" << file_name_;
        os << ", at " << source_file_ << "(" << source_line_ << ")\n";
    }
};

/**
 * @fn
 * @brief
 * @param os
 * @param exp
 * @return std::ostream&
 */
inline std::ostream& operator<<(std::ostream &os, const IoException &exp) {
    exp.writeTo(os);
    return os;
}

#endif // _IO_EXCEPTION_H_
