#ifndef _FILEWRITER_H_
#define _FILEWRITER_H_

#include <fstream>
#include <sstream>
#include <string>
#include "Node.h"
#include "QuadElement.h"
#include "DataException.h"
#include "IoException.h"

class FileWriter {

private:

    std::string file_name_;

    std::fstream in_;

    std::fstream out_;

    std::stringstream cur_line_;

    int line_no_;

    int pointDataHeader;

    int cellDataHeader;

public:

    FileWriter();

    ~FileWriter();

    void open(const char *file_name);

    void open(const std::string &file_name) {
        open(file_name.c_str());
    }

    void close();

    /**
     * @fn
     * @brief 
     * @param val 
     * @param label 
     */
    void writeInt(const int &val, const char *label);

};

#endif // _FILEWRITER_H_