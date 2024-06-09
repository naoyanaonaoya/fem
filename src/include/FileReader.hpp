#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include "DataException.hpp"
#include "IoException.hpp"
#include "Node.hpp"
#include "Element.hpp"
#include "ElementQuad.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
    void Open(const char *file_name_);

    /**
     * @fn
     * @brief open the file
     * @param file_name_
     * @return none
     * @exception IoException : cannot open the file
     */
    void Open(const std::string &file_name_);

    /**
     * @fn
     * @brief close the file
     * @param none
     * @return none
     */
    void Close();

    /**
     * @fn
     * @brief read the line from the file
     * @param none
     * @return none
     */
    void ReadLine();

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void ReadLabeledDoubleLine(const char *label, double &val);

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void ReadLabeledIntLine(const char *label, int &val);

    /**
     * @fn
     * @brief
     * @param label 
     * @param val
     * @return none 
     */
    void ReadLabeledSizeTLine(const char *label, std::size_t &val);

    /**
     * @fn
     * @brief
     * @param label
     * @param val
     * @return none
     */
    void ReadLabeledStringLine(const char *label, std::string &val);

    /**
     * @fn
     * @brief read the keyword from the buffer
     * @param keyword
     * @return none
     * @note __FILE__, __LINE__ is macro to get the file name and line number
     */
    void ReadKeyword(const char *keyword);

    /**
     * @fn
     * @brief read the double value from the buffer
     * @param val
     * @param label
     * @return none
     */
    void ReadDouble(double &val, const char *label);

    /**
     * @fn
     * @brief read the integer value from the buffer
     * @param val
     * @param label
     * @return none
     */
    void ReadInt(int &val, const char *label);

    void ReadSizeT(std::size_t &val, const char *label);

    /**
     * @fn
     * @brief read the integer value from the buffer and compare with the expected value
     * @param expected_val
     * @param label
     */
    void ReadExpectedInt(int expected_val, const char *label);

    /**
     * @fn
     * @brief read the string from the buffer
     * @param val
     * @param label
     * @return none
     */
    void ReadString(std::string &val, const char *label);

    void ReadExpectedSizeT(std::size_t expected_val, const char *label);

    void ReadBinaryCfdProcData(const std::string &file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const std::size_t &step);
    
    void ReadBinaryCfdProcData(const char *file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const std::size_t &step);

private:

    /**
     * @fn
     * @brief add the file name and line number to the error message
     * @param ss
     * @return none
     */
    void AddFileNameAndLineNoTo(std::stringstream &ss);

};

#endif // _FILE_READER_H_
