#include "FileWriter.h"
#include "Logger.h"

#ifdef DEBUG_FILEWRITER
#else
#endif

FileWriter::FileWriter() {}

FileWriter::~FileWriter() {
    if (in_.is_open()) {
        in_.close();
    }
    if (out_.is_open()) {
        out_.close();
    }
}

void FileWriter::open(const char *file_name) {
    this->pointDataHeader = 0;
    this->cellDataHeader = 0;
    file_name_ = file_name;

    out_.open(file_name, std::ios::out);
    if (!out_.is_open()) {
        throw IoException(__FILE__, __LINE__, file_name);
    }
    line_no_ = 0;

#ifdef DEBUG_FILEWRITER
    Logger::out << "FileWriter::open : " << file_name_ << std::endl;
#endif
}

void FileWriter::close() {
    this->pointDataHeader = 0;
    this->cellDataHeader = 0;
    out_.close();
}

void FileWriter::writeInt(const int &val, const char *label) {
    out_ << val << std::endl;
}