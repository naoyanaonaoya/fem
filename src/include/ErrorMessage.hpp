#ifndef _ERRORMESSAGE_H_
#define _ERRORMESSAGE_H_

#include <stdexcept>
#include <string>

class ErrorMessage {

public:
    std::string out;

    std::string createErrorMessage(const std::string& message, const std::string& file, const int& line);
};


#endif
