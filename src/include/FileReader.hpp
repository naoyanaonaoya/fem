#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <fstream>
#include <sstream>
#include <string>

#include "DataException.hpp"
#include "IoException.hpp"
#include "Node.hpp"

class FileReader {

private:

    //! file name
    std::string file_name_;

    //! input stream
    std::fstream in_;

    //! buffer to hold one line of data
    std::stringstream cur_line_;

    //! line number in the file
    //! for detect where the error occurs
    int line_no_;

public:

    /**
     * @fn
     * @brief Construct a new File Reader object
     */
    FileReader();

    /**
     * @fn
     * @brief Destroy the File Reader object
     */
    ~FileReader();

    /**
     * @fn
     * @brief open the file
     * @param file_name_
     * @return none
     * @exception IoException : cannot open the file
     */
    void open(const char *file_name_);

    /**
     * @fn
     * @brief open the file
     * @param file_name_
     * @return none
     * @exception IoException : cannot open the file
     */
    void open(const std::string &file_name_) {
        open(file_name_.c_str());
    }

    /**
     * @fn
     * @brief close the file
     * @param none
     * @return none
     */
    void close();

    /**
     * @fn
     * @brief read the line from the file
     * @param none
     * @return none
     */
    void readLine();

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void readLabeledDoubleLine(const char *label, double &val);

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void readLabeledIntLine(const char *label, int &val);

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void readLabeledStringLine(const char *label, std::string &val);

    /**
     * @fn
     * @brief read the keyword from the buffer
     * @param keyword
     * @return none
     * @note __FILE__, __LINE__ is macro to get the file name and line number
     */
    void readKeyword(const char *keyword);

    /**
     * @fn
     * @brief read the double value from the buffer
     * @param val
     * @param label
     * @return none
     */
    void readDouble(double &val, const char *label);

    /**
     * @fn
     * @brief read the integer value from the buffer
     * @param val
     * @param label
     * @return none
     */
    void readInt(int &val, const char *label);

    /**
     * @fn
     * @brief read the integer value from the buffer and compare with the expected value
     * @param expected_val
     * @param label
     */
    void readExpectedInt(int expected_val, const char *label);

    /**
     * @fn
     * @brief read the string from the buffer
     * @param val
     * @param label
     * @return none
     */
    void readString(std::string &val, const char *label);

    // void readBinCfdProcData();
    // void readBinCfdProcData(const char *file_name, const std::vector)


private:

    /**
     * @fn
     * @brief add the file name and line number to the error message
     * @param ss
     * @return none
     */
    void addFileNameAndLineNoTo(std::stringstream &ss);

};

#endif // _FILE_READER_H_
