#ifndef _CFDDRIVER_SP_HPP_
#define _CFDDRIVER_SP_HPP_

#include "State.hpp"
#include "Params.hpp"
#include "CfdProcData.hpp"
#include "DataException.hpp"
#include "IoException.hpp"

class CfdDriverSp {

private:

    Params params_;

    State state_;

    CfdProcData proc_data_;

    CfdCommData comm_data_;

    std::size_t velocity_correction_count_;

public:

    CfdDriverSp();

    ~CfdDriverSp();

    void Init(std::size_t np, std::size_t rank, const char* file_name);

    Params* GetParams();

    State* GetState();

    // IoException: cannot open file
    // DataException: invalid data
    void ReadDataFile();

    void CalcInvariants();

    // at clear or reading restart file
    void SetupFieldData();

    void DoStep();

    void PrintState();

    void PrintCalcData();;

    void PrintCalcCondition();

    // e.g.
    // log file close
    // MPI finalize
    void Finalize();

private:

    void CorrectVelocity();

    void MeasureAndDistributeElapsedTime();

    void MeasureElapsedTime();
};

#endif // _CFDDRIVER_SP_HPP_