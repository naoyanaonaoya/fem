#include "FileReader.hpp"
#include "Logger.hpp"

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
FileReader::FileReader() {
    std::cout << "FileReader constructor" << "\n";
}

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
void FileReader::Open(const char *file_name) {
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

void FileReader::Open(const std::string &file_name) {
    Open(file_name.c_str());
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::Close() {
    in_.close();

#ifdef DEBUG_FILEREADER
    Logger::out << "File closed: " << file_name_ << std::endl;
#endif
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadLine() {
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
void FileReader::ReadLabeledDoubleLine(const char *label, double &val) {
    ReadLine();

    ReadKeyword(label);

    ReadDouble(val, label);
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadLabeledIntLine(const char *label, int &val) {
    ReadLine();

    ReadKeyword(label);

    ReadInt(val, label);

}

void FileReader::ReadLabeledSizeTLine(const char *label, std::size_t &val) {
    ReadLine();

    ReadKeyword(label);

    ReadSizeT(val, label);
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadLabeledStringLine(const char *label, std::string &val) {
    ReadLine();

    ReadKeyword(label);

    ReadString(val, label);
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadKeyword(const char *keyword) {
    std::string word;

    cur_line_ >> word;

    if (word != keyword || cur_line_.fail()) {
        std::stringstream msg;
        msg << "keyword '" << keyword << "' was expected, but '" << word << "' was found at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadDouble(double &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "double value for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadInt(int &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "integer value for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

void FileReader::ReadSizeT(std::size_t& val, const char* label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "size_t value for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadString(std::string &val, const char *label) {
    cur_line_ >> val;

    if (cur_line_.fail()) {
        std::stringstream msg;
        msg << "string for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::ReadExpectedInt(int expected_val, const char *label) {
    int val;
    cur_line_ >> val;

    if (cur_line_.fail() || val != expected_val) {
        std::stringstream msg;
        msg << "integer value " << expected_val << " for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

void FileReader::ReadExpectedSizeT(std::size_t expected_val, const char* label) {
    std::size_t val;
    cur_line_ >> val;

    if (cur_line_.fail() || val != expected_val) {
        std::stringstream msg;
        msg << "size_t value " << expected_val << " for " << label << " was expected at ";
        AddFileNameAndLineNoTo(msg);
        throw DataException(__FILE__, __LINE__, msg.str());
    }
}

void FileReader::ReadBinaryCfdProcData(const std::string &file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const std::size_t &step) {
    ReadBinaryCfdProcData(file_name.c_str(), my_nodes, my_elems, step);
}

void FileReader::ReadBinaryCfdProcData(const char* file_name, const std::vector<Node*> &my_nodes, const std::vector<ElementQuad*> &my_elems, const std::size_t &step) {
    file_name_ = file_name;

    in_.open(file_name, std::ios::in | std::ios::binary);

    std::size_t n_my_nodes = my_nodes.size();
    std::size_t n_my_elems = my_elems.size();
    std::size_t file_number_of_nodes = 0;
    std::size_t file_number_of_elems = 0;
    in_.read((char*)&step, sizeof(std::size_t));
    in_.read((char*)&file_number_of_nodes, sizeof(std::size_t));
    in_.read((char*)&file_number_of_elems, sizeof(std::size_t));
    if (file_number_of_nodes != n_my_nodes)
        throw DataException(__FILE__, __LINE__, "Number of nodes in the file does not match the number of nodes in the data structure");
    if (file_number_of_elems != n_my_elems)
        throw DataException(__FILE__, __LINE__, "Number of elements in the file does not match the number of elements in the data structure");

    std::size_t local_index = 0;

    for (std::size_t i = 0; i < n_my_nodes; i++) {
        in_.read((char*)&local_index, sizeof(std::size_t));
        in_.read((char*)&my_nodes[i]->vel_.x_, sizeof(double));
        in_.read((char*)&my_nodes[i]->vel_.y_, sizeof(double));
        in_.read((char*)&my_nodes[i]->vel_.z_, sizeof(double));
    }
    for (std::size_t i = 0; i < n_my_elems; i++) {
        in_.read((char*)&local_index, sizeof(int));
        in_.read((char*)&my_elems[i]->p_, sizeof(double));
    }

    in_.close();
}

/**
 * @fn
 * @brief Construct a new File Reader:: File Reader object
 */
void FileReader::AddFileNameAndLineNoTo(std::stringstream &ss) {
    ss << "'" << file_name_ << ", line " << line_no_;
}
