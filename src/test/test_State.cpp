#include "TestBase.hpp"
#include "State.hpp"


class TestState : public TestBase {

private:

    State st_;

public:
    void run();

};

void TestState::run() {
    st_.round_ = 100;
    st_.t_ = 200.0;
    st_.Reset();
    st_.RecordStartTime();
    test_sizet_equals(st_.GetRound(), 0);
    test_double_equals(st_.GetT(), 0);

    for (int i = 1; i < 10; i++) {
        st_.NextRound(0.1);
        test_sizet_equals(st_.GetRound(), i);
        test_double_equals(st_.GetT(), 0.1 * (double)i);
    }
    st_.MeasureElapsedTime();
    std::cout << "elapsed_time = " << st_.GetElapsedTime() << std::endl;
}

int main(int argc, char *argv[]) {
    TestState test;
    test.run();
    return test.report();
}
