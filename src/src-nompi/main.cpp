#include "CfdDriver_sp.hpp"

#include <iostream>

void PrintUsage() {
    std::cerr << "Usage : main casefile [-r]\n";
    std::cerr << " -r : restart mode\n";
}

class Abmac2DSpArgs {

public:

    std::string case_file_name_;

    bool is_restart_mode_;

    bool analyze(int argc, char* argv[]) {
        case_file_name_ = "";
        is_restart_mode_ = false;
        for (std::size_t i = 1; i < argc; i++) {
            std::string str = argv[i];
            if (str == "-r")
                is_restart_mode_ = true;
            else {
                if (case_file_name_ == "")
                    case_file_name_ = str;
                else {
                    PrintUsage();
                    return false;
                }
            }
        }
        if (case_file_name_ == "") {
            PrintUsage();
            return false;
        }
        return true;
    }

};

/**
 * @fn
 * @brief main function
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[]) {

    CfdDriverSp driver_sp;
    std::size_t rank = 0;
    std::size_t num_procs = 1;

    Abmac2DSpArgs args;
    if (!args.analyze(argc, argv))
        return EXIT_FAILURE;

    std::cout << "test0" << "\n";
    // return EXIT_SUCCESS;

    try {
        driver_sp.Init(num_procs, rank, args.case_file_name_.c_str());
        std::cout << "test1" << "\n";
        Params* params = driver_sp.GetParams();
        std::cout << "test2" << "\n";
        params->is_restart_mode_ = args.is_restart_mode_;
        params->is_single_process_mode_ = true;
        driver_sp.ReadDataFile();
        std::cout << "test3" << "\n";
        driver_sp.CalcInvariants();
        driver_sp.SetupFieldData();

        std::cout << "test1" << "\n";
    
        driver_sp.PrintCalcCondition();
        // return EXIT_SUCCESS;
        /*
         * 時間発展ループ
         */
        // IMPLEMENT ME
        // while (driver_sp.getState()->getT() <= params->duration_) {
        while (params->shouldContinue(driver_sp.GetState())) {
            driver_sp.PrintState();
            driver_sp.DoStep();
            driver_sp.PrintCalcData();
        }

        /*
         * 後処理
         */
        driver_sp.Finalize();


    } catch (DataException &exp) {
        std::cerr << exp << "\n";
        return EXIT_FAILURE;
    } catch (IoException &exp) {
        std::cerr << exp << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

