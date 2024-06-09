#include "Params.hpp"
#include "TestBase.hpp"

class TestParams : public TestBase {

private:

    Params params_;

public:

    void run();

private:

    void setup();

    void test();

};

void TestParams::setup() {
    params_.init(0, 4, "./../data/test/params/case.txt");
}

void TestParams::test() {
    // investigate results.
    test_double_equals(params_.re_, 10);
    test_double_equals(params_.delta_t_, 1.0e-3);
    test_double_equals(params_.duration_, 2.0);
    test_double_equals(params_.t_ramp_, 1.0);
    test_int_equals(params_.n_interval_, 50);
    test_double_equals(params_.max_cpu_time_, 600);
    test_double_equals(params_.epsilon_, 1.0e-4);
    test_int_equals(params_.max_corrections_, 100);
    test_string_equals(params_.mesh_file_name_, "mesh1.txt");
    test_string_equals(params_.boundary_file_name_, "boundary.txt");
    test_string_equals(params_.restart_file_name_pattern_, "output/restart.%02d.bin");
    test_string_equals(params_.output_file_name_pattern_, "output/result.%02d.%04d.vtk");
}

void TestParams::run() {
    setup();
    test();
}

/*
 * 本プログラムは、cfdプロジェクトのルートディレクトリで実行する必要がある。
 * (CMakeLists.txt が置いてあるディレクトリ)
 */
int main(int argc, char *argv[]) {
    TestParams test;
    try {
        test.run();
    } catch (IoException &exp) {
        std::cout << exp << std::endl;
    } catch (DataException &exp) {
        std::cout << exp << std::endl;
    }
    return test.report();
}
