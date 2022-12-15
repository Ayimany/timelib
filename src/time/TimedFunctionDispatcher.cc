#include "headers/TimedFunctionDispatcher.hh"
#include "headers/TimeReference.hh"
#include "headers/Timer.hh"

namespace preclib { namespace time {

    auto TimedFunctionDispatcher::run(int times) -> void {
        TimeReference ref = TimeReference::inTime(count, unit);

        timer.start();

        for (int i = times; i != 0; i--) {
            timer.setGoal(ref);
            while (!timer.hasReachedGoal()) {}
            func();
            ref = TimeReference::inTime(count, unit);
        }

    }

}}

