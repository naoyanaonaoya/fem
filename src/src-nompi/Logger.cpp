#include <sstream>
#include "Logger.h"

std::fstream Logger::out;

void Logger::openLog(const char *progname, int rank) {
    // create a stringstream to build the file name
    std::stringstream ss;

    // build the file name for the log file
    ss << progname << ".log." << rank << ".txt";

    // open the log file
    out.open(ss.str().c_str(), std::ios::out);
}

void Logger::closeLog() {
    // close the log file
    out.close();
}

