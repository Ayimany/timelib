#include "headers/Timer.hh"
#include "headers/TimeReference.hh"
#include "headers/TimeSpan.hh"

namespace preclib { namespace time {

    auto Timer::getEllapsedTime(TimeUnit units) -> uint64_t {
        if (isRunning)
            return TimeSpan(startTime, TimeReference::now())
                .durationInUnits(units);

        return TimeSpan(startTime, lastReferenceSinceDisabled)
            .durationInUnits(units);
    }

    auto Timer::timeSpanSinceStart() -> TimeSpan {
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

    auto Timer::setGoal(TimeReference &goal) -> void {
        this -> hasGoal = true;
        this -> goal = goal;
    }

    auto Timer::resetGoal() -> void {
        this -> hasGoal = false;
    }

    auto Timer::hasReachedGoal() -> bool {
        if (isRunning) {
            TimeReference now = TimeReference::now();
            return hasGoal && goal.isBefore(now);
        }

        return hasGoal && goal.isBefore(lastReferenceSinceDisabled);
    }

    auto Timer::timeUntilGoal(TimeUnit units) -> uint64_t {
        if (!hasGoal) return 0;

        if (isRunning)
            return goal.ellapsedUnits(units) -
                TimeReference::now().ellapsedUnits(units);

        return goal.ellapsedUnits(units) -
            lastReferenceSinceDisabled.ellapsedUnits(units);
    }

    auto Timer::timeSpanUntilGoal() -> TimeSpan {
        if (isRunning)
            return TimeSpan(TimeReference::now(), goal);

        return TimeSpan(lastReferenceSinceDisabled, goal);
    }

}}

