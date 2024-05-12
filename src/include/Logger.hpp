#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <iostream>

/**
 * @brief class for logging
 * @note static members only, so do not need to create an instance
 */
class Logger {

private:

public:

    //! static member variable
    //! stream of the log
    //! Logger::out << "This is a log message." << std::endl;
    static std::fstream out;

    /**
     * @fn
     * @brief open the log file
     * @param progname
     * @param rank
     * @return none
     * @note Logger::openLog("test_Node", 0)
     * @note rank is 0 if not using MPI
     */
    static void openLog(const char *progname, int rank);

    /**
     * @fn
     * @brief close the log file
     * @param none
     * @return none
     */
    static void closeLog();
};

#endif // _LOGGER_H_
