#include <cassert>
#include <cerrno>
#include <cstring>
#include <sstream>
#include "FileReader.h"
#include "Params.h"

/**
 * @fn
 * @brief initialize the parameters
 * @param np
 * @param rank
 * @param filename
 */
void Params::init(int np, int rank, const char *filename) {
    assert(filename != NULL);

    num_procs_ = np;
    my_rank_ = rank;
    is_restart_mode_ = false;
    is_single_process_mode_ = false;

    FileReader rdr;

    rdr.open(filename);

    rdr.readLabeledDoubleLine("Re", re_);
    rdr.readLabeledDoubleLine("delta_t", delta_t_);
    rdr.readLabeledDoubleLine("T", duration_);
    rdr.readLabeledDoubleLine("T_ramp", t_ramp_);
    rdr.readLabeledIntLine("N_interval", n_interval_);
    rdr.readLabeledDoubleLine("max_cpu_time", max_cpu_time_);
    rdr.readLabeledDoubleLine("epsilon", epsilon_);
    rdr.readLabeledIntLine("max_corrections", max_corrections_);
    rdr.readLabeledStringLine("mesh", mesh_file_name_);
    rdr.readLabeledStringLine("boundary", boundary_file_name_);
    rdr.readLabeledStringLine("restart", restart_file_name_pattern_);
    rdr.readLabeledStringLine("outfile", output_file_name_pattern_);

    char restart_file_name[2048];
    snprintf(
        restart_file_name, sizeof(restart_file_name), restart_file_name_pattern_.c_str(), rank
    );

    rdr.close();
}

/**
 * @fn
 * @brief initialize the parameters
 * @param np
 * @param rank
 * @param filename
 */
bool Params::shouldContinue(const State *state) const {
    // return ((state->getT() < duration_) && (state->getElapsedTime() < max_cpu_time_));
    if (state->getT() > duration_)
        return false;
    if (state->getElapsedTime() > max_cpu_time_)
        return false;
    return true;
}
