#include <cassert>
#include <cerrno>
#include <cstring>
#include <sstream>

#include "FileReader.hpp"
#include "Params.hpp"

/**
 * @fn
 * @brief initialize the parameters
 * @param np
 * @param rank
 * @param filename
 */
void Params::init(std::size_t np, std::size_t rank, const char *filename) {
    assert(filename != NULL);

    num_procs_ = np;
    my_rank_ = rank;
    is_restart_mode_ = false;
    is_single_process_mode_ = false;

    FileReader rdr;

    rdr.Open(filename);

    rdr.ReadLabeledDoubleLine("Re", re_);
    rdr.ReadLabeledDoubleLine("delta_t", delta_t_);
    rdr.ReadLabeledDoubleLine("T", duration_);
    rdr.ReadLabeledDoubleLine("T_ramp", t_ramp_);
    rdr.ReadLabeledSizeTLine("N_interval", n_interval_);
    rdr.ReadLabeledDoubleLine("max_cpu_time", max_cpu_time_);
    rdr.ReadLabeledDoubleLine("epsilon", epsilon_);
    rdr.ReadLabeledSizeTLine("max_corrections", max_corrections_);
    rdr.ReadLabeledStringLine("mesh", mesh_file_name_);
    rdr.ReadLabeledStringLine("boundary", boundary_file_name_);
    rdr.ReadLabeledStringLine("restart", restart_file_name_pattern_);
    rdr.ReadLabeledStringLine("outfile", output_file_name_pattern_);

    char restart_file_name[2048];
    snprintf(
        restart_file_name, sizeof(restart_file_name), restart_file_name_pattern_.c_str(), rank
    );

    rdr.Close();
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
    if (state->GetT() > duration_)
        return false;
    if (state->GetElapsedTime() > max_cpu_time_)
        return false;
    return true;
}
