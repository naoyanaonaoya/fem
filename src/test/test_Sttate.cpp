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


    st_.reset();
    st_.recordStartTime();
    test_int_equals(st_.getRound(), 0);
    test_double_equals(st_.getT(), 0);

    for (int i = 1; i < 10; i++) {
        st_.nextRound(0.1);
        test_int_equals(st_.getRound(), i);
        test_double_equals(st_.getT(), 0.1 * (double)i);
    }
    st_.measureElapsedTime();
    std::cout << "elapsed_time = " << st_.getElapsedTime() << std::endl;
}

int main(int argc, char *argv[]) {
    TestState test;
    test.run();
    return test.report();
}
