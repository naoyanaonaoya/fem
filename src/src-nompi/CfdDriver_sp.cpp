#include "CfdDriver_sp.hpp"
#include "Logger.hpp"

// DEBUG_DRIVER_STEPS is controlled in CMakeLists.txt
#ifdef DEBUG_DRIVER_STEPS
#define LOG_DRIVER_STEP(S) Logger::out << "CfdDriver : " << S << std::endl
#else
#define LOG_DRIVER_STEP(S)
#endif


CfdDriverSp::CfdDriverSp() {};

CfdDriverSp::~CfdDriverSp() {};

void CfdDriverSp::Init(std::size_t np, std::size_t rank, const char* file_name) {
    Logger::OpenLog("main", rank);
    Logger::out << "Start" "\n";

    params_.init(np, rank, file_name);

    state_.RecordStartTime();

    comm_data_.Init(&params_, &state_);

    proc_data_.Init(&params_, &state_, &comm_data_);

    state_.Reset();
}

Params* CfdDriverSp::GetParams() {
    return &params_;
}

State* CfdDriverSp::GetState() {
    return &state_;
}

void CfdDriverSp::ReadDataFile() {
    proc_data_.ReadMeshFile();
    proc_data_.FindOwnData();
    proc_data_.ReadBoundaryFile();
}

void CfdDriverSp::CalcInvariants() {
    proc_data_.CalcInvariants1();
    proc_data_.CalcInvariants2();

}

void CfdDriverSp::SetupFieldData() {
    if (params_.is_restart_mode_) {
        std::cout << "restart mode" << "\n";
        std::cout << "\n";
        proc_data_.ReadRestartFile();
    } else {
        std::cout << "new mode" << "\n";
        std::cout << "\n";
        proc_data_.InitZero();
    }
}

void CfdDriverSp::DoStep() {
    LOG_DRIVER_STEP("doStep:start");
    LOG_DRIVER_STEP("calcVelocityPrediction");

    proc_data_.ApplyBoundaryConditions();

    proc_data_.CalcVelocityPrediction();

    // （spでは不要）：通信処理

    proc_data_.ApplyVelocityDelta();

    proc_data_.ApplyBoundaryConditions();

    CorrectVelocity();

    state_.NextRound(params_.delta_t_);

    proc_data_.CalcCourantNumber();

    MeasureElapsedTime();

    // 一定回数ごとに可視化用に場のデータを出力する。
    // 経過時間を測定してstate_に格納する
    if (state_.GetRound() % params_.n_interval_ == 0) {
        proc_data_.WriteMeshFile();
        proc_data_.WriteRestartFile();
    }

    LOG_DRIVER_STEP("doStep:end");
}

void CfdDriverSp::CorrectVelocity() {
    // 全要素の速度を補正する。
    // 収束するか、打ち切り条件に達するまで繰り返す。
    // 繰り返し回数は velocity_correction_count_ に記録する(ログに出力するため)
    // IMPLEMENT ME

#ifdef DEBUG_DELTAPSUM
    proc_data_.resetDeltaPSum();
#endif

    this->velocity_correction_count_ = 0;
    for (int i = 0; i < this->params_.max_corrections_; i++) {

#ifdef DEBUG_VELOCITY_CORRECTION
    Logger::out << "================================================" << std::endl;
#endif
        this->proc_data_.CalcDivergenceAndCorrect();
        this->proc_data_.ApplyVelocityDelta();
        this->proc_data_.ApplyBoundaryConditions();
        this->velocity_correction_count_ = i + 1;
        if (proc_data_.GetGlobalMaxAbsDiv() < this->params_.epsilon_) {
            break;
        }
    }

#ifdef DEBUG_DELTAPSUM
    proc_data_.printDeltaPSum();
#endif
}

void CfdDriverSp::PrintCalcData() {
    if (params_.my_rank_ == 0) {
        std::cout << "max cournat number = " << proc_data_.GetGlobalMaxCourantNumber() << " ";
        std::cout << "correct count = " << velocity_correction_count_ << "\n";
        std::cout << "max abs div = " << proc_data_.GetGlobalMaxAbsDiv() << "\n";
        std::cout << "\n";
    }
}

void CfdDriverSp::PrintState() {
    if (params_.my_rank_ == 0) {
        std::cout << "Elapsed time = " << state_.GetElapsedTime() << " ";
        std::cout << "Round = " << state_.GetRound() << " ";
        std::cout << "Time = " << state_.GetT() << "\n";
    }
}

void CfdDriverSp::PrintCalcCondition() {
    if (params_.my_rank_ == 0) {
        std::cout << "=====================================================================" << "\n";
        std::cout << "Re: " << params_.re_ << "\n";
        std::cout << "delta_t: " << params_.delta_t_ << "\n";
        std::cout << "T: " << params_.duration_ << "\n";
        std::cout << "T_ramp: " << params_.t_ramp_ << "\n";
        std::cout << "N_interval: " << params_.n_interval_ << "\n";
        std::cout << "max_cpu_time: " << params_.max_cpu_time_ << "\n";
        std::cout << "epsilon: " << params_.epsilon_ << "\n";
        std::cout << "max_corrections: " << params_.max_corrections_ << "\n";
        std::cout << "mesh: " << params_.mesh_file_name_ << "\n";
        std::cout << "boundary: " << params_.boundary_file_name_ << "\n";
        std::cout << "restart: " << params_.restart_file_name_pattern_ << "\n";
        std::cout << "outfile: " << params_.output_file_name_pattern_ << "\n";
        std::cout << "=====================================================================" << "\n";
        std::cout << "\n";
        std::cout << "\n";
    }
}

void CfdDriverSp::Finalize() {
    proc_data_.WriteMeshFile();
    proc_data_.WriteRestartFile();
    std::cout << "Finish." << "\n";
    Logger::out << "Finish." << "\n";
    Logger::CloseLog();
}

void CfdDriverSp::MeasureElapsedTime() {
    state_.MeasureElapsedTime();
}