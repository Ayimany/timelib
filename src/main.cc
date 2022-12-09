#include <iostream>

#include "headers/Time.hh"
#include "headers/TimeReference.hh"
#include "headers/TimeSpan.hh"
#include "headers/Timer.hh"

#define println(what) std::cout << what << "\n"

using namespace timelib;

int main(void) {
    Timer timer;
    timer.start();
    timer.setGoal(TimeReference::in(2, timelib::SECONDS));

    while (!timer.hasReachedGoal()) {
        std::cout << timer.getEllapsedTime(SECONDS) << "\n";
    }
    timer.reset();
    std::cout << timer.getEllapsedTime(SECONDS) << "\n";

    return 0;
}
