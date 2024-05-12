#ifndef _STATE_H_
#define _STATE_H_

#include <iostream>
#include <chrono>

class State {

    //! friend declaration to allow access to private members of this class from the test class
    friend class TestState;


private:

    //! current simulation time in dimensionless time
    double t_;

    //! current round in the simulation
    int round_;

    //! elapsed time of the simulation
    double elapsed_time_;

    //! time stamp
    std::time_t time_stamp;

    //! start time point of the simulation
    std::chrono::steady_clock::time_point start_time_point_;

    //! start time point of the simulation
    std::chrono::system_clock::time_point start_time_point_system_;

public:

    /**
     * @fn
     * @brief reset the simulation time and round to 0
     * @param none
     * @return none
     */
    void reset();

    /**
     * @fn
     * @brief reset the simulation time and round to the specified values in the case of restart
     * @param delta_t
     * @param step
     */
    void resetRestart(const double &delta_t, const int &step);

    /**
     * @fn
     * @brief get the current simulation time
     * @param none
     * @return double
     */
    double getT() const;

    /**
     * @fn
     * @brief get the current round
     * @param none
     * @return int
     */
    int getRound() const;

    /**
     * @fn
     * @brief proceed to the next round
     * @param delta_t
     * @return none
     */
    void nextRound(double delta_t);

    /**
     * @fn
     * @brief record the start time of the simulation
     * @param none
     * @return none
     */
    void recordStartTime();

    /**
     * @fn
     * @brief measure the elapsed time of the simulation
     * @param none
     * @return none
     */
    void measureElapsedTime();

    /**
     * @fn
     * @brief get the elapsed time of the simulation
     * @param none
     * @return double
     */
    double getElapsedTime() const;
    /**
     * @fn
     * @brief Set the Elapsed Time
     * @param elapsed_time
     * @return none
     */
    void setElapsedTime(double elapsed_time);
};

#endif // _STATE_H_
