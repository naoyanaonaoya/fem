#ifndef _PARAMS_H_
#define _PARAMS_H_

#include <iostream>
#include <string>

#include "DataException.hpp"
#include "IoException.hpp"
#include "State.hpp"

class Params {

public:

    //! total number of processes
    int num_procs_;

    //! rank of this process
    int my_rank_;

    //! Reynolds number
    double re_;

    //! time step
    double delta_t_;

    //! duration of simulation
    double duration_;

    //! maximum time for simulation
    double max_cpu_time_;

    //! time for ramping up boundary conditions
    double t_ramp_;

    //! epsilon for convergence of velocity correction
    double epsilon_;

    //! maximum number of corrections for velocity correction
    int max_corrections_;

    //! interval for output
    int n_interval_;

    //! path to mesh file
    std::string mesh_file_name_;

    //! path to boundary file
    std::string boundary_file_name_;

    //! path to output file
    std::string output_file_name_;

    //! output file name pattern
    std::string output_file_name_pattern_;

    //! path to restart file
    std::string restart_file_name_;

    //! restart file name pattern
    std::string restart_file_name_pattern_;

    //! true : restart mode
    //! false : no restart mode
    bool is_restart_mode_;

    //! true : single process mode
    //! false : multi process mode
    bool is_single_process_mode_;

    /**
     * @fn
     * @brief initialize
     * @param np
     * @param rank
     * @param filename
     * @return void
     */
    void init(int np, int rank, const char *filename);

    bool shouldContinue(const State *state) const;
};

#endif // _PARAMS_H_
