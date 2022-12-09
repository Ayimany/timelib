#include "headers/Timer.hh"
#include "headers/TimeReference.hh"
#include "headers/TimeSpan.hh"

namespace timelib {

    auto Timer::getEllapsedTime(TimeUnit units) -> uint64_t {
        if (isRunning)
            return TimeSpan(startTime, TimeReference::now()).durationInUnits(units);

        return TimeSpan(startTime, lastReferenceSinceDisabled).durationInUnits(units);
    }

    auto Timer::spanSinceStart() -> TimeSpan {
        if (isRunning)
            return TimeSpan(startTime, TimeReference::now());
        return TimeSpan(startTime, lastReferenceSinceDisabled);
    }

    auto Timer::start() -> void {
        this -> isRunning = true;
    }

    auto Timer::stop()  -> void {
        this -> lastReferenceSinceDisabled = TimeReference::now();
        this -> isRunning = false;
    }

    auto Timer::reset() -> void {
        this -> startTime = TimeReference::now();
        this -> lastReferenceSinceDisabled = startTime;
    }

    auto Timer::setGoal(TimeReference goal) -> void {
        this -> goal = goal;
    }

    auto Timer::hasReachedGoal() -> bool {
        if (isRunning) {
            TimeReference now = TimeReference::now();
            return goal.isBefore(now);
        }
        return goal.isBefore(lastReferenceSinceDisabled);
    }

    auto Timer::timeUntilGoal(TimeUnit units) -> uint64_t {
        if (isRunning) {
            return goal.ellapsedUnits(units) -
                TimeReference::now().ellapsedUnits(units);
        }
        return goal.ellapsedUnits(units) -
            lastReferenceSinceDisabled.ellapsedUnits(units);
    }

}

