#include "FileReader.hpp"
#include "Logger.hpp"

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
FileReader::FileReader() {}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
FileReader::~FileReader() {
    if (in_.is_open()) {
        in_.close();
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::open(const char *file_name) {
    file_name_ = file_name;

    in_.open(file_name, std::ios::in);

    if (!in_.is_open()) {
        throw IoException(__FILE__, __LINE__, file_name);
    }

    line_no_ = 0;

#ifdef DEBUG_FILEREADER
    Logger::out << "File opened: " << file_name_ << std::endl;
#endif
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::close() {
    in_.close();

#ifdef DEBUG_FILEREADER
    Logger::out << "File closed: " << file_name_ << std::endl;
#endif
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readLine() {
    // Used to temporarily hold a single line of data read from a file.
    std::string line_buf;

    // Data is read from the input stream specified
    // in the first argument and stored in the string
    // specified in the second argument until a newline character is found.
    // The newline character itself is read, but is not included in line_buf.
    std::getline(in_, line_buf);

    line_no_++;

    // initialize the contents of the std:;stringstream object
    // named cur_line_ with the contents of line_buf.
    cur_line_.str(line_buf);

    // Clear the internal status flag of cur_line_.
    cur_line_.clear();
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readLabeledDoubleLine(const char *label, double &val) {
    readLine();

    readKeyword(label);

    readDouble(val, label);
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readLabeledIntLine(const char *label, int &val) {
    readLine();

    readKeyword(label);

    readInt(val, label);

}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readLabeledStringLine(const char *label, std::string &val) {
    readLine();

    readKeyword(label);

    readString(val, label);
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readKeyword(const char *keyword) {
    std::string word;

    cur_line_ >> word;

    if (word != keyword || cur_line_.fail()) {
        std::stringstream msg;
        msg << "keyword '" << keyword << "' was expected, but '" << word << "' was found at ";
        addFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readDouble(double &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "double value for " << label << " was expected at ";
        addFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readInt(int &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "integer value for " << label << " was expected at ";
        addFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readString(std::string &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "string for " << label << " was expected at ";
        addFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::readExpectedInt(int expected_val, const char *label) {
    int val;
    cur_line_ >> val;

    if (cur_line_.fail() || val != expected_val) {
        std::stringstream msg;
        msg << "integer value " << expected_val << " for " << label << " was expected at ";
        addFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::addFileNameAndLineNoTo(std::stringstream &ss) {
    ss << "'" << file_name_ << ", line " << line_no_;
}
