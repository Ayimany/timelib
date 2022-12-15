#ifndef TIMER_HH
#define TIMER_HH

#include "Time.hh"
#include "TimeReference.hh"
#include "TimeSpan.hh"
#include <cstdint>

namespace preclib { namespace time {

class Timer {
public:
    Timer() {}
    Timer(TimeReference goal): goal(goal) {}

    auto getEllapsedTime(TimeUnit units)    -> uint64_t;
    auto timeSpanSinceStart()               -> TimeSpan;

    auto start()    -> void;
    auto reset()    -> void;
    auto stop()     -> void;

    auto setGoal(TimeReference &goal)   -> void;
    auto resetGoal()                    -> void;
    auto hasReachedGoal()               -> bool;
    auto timeUntilGoal(TimeUnit units)  -> uint64_t;
    auto timeSpanUntilGoal()            -> TimeSpan;

private:
    TimeReference startTime = TimeReference::now();
    TimeReference lastReferenceSinceDisabled = startTime;
    TimeReference goal = startTime;
    bool isRunning = false;
    bool hasGoal = false;

};

}}

#endif // TIMER_HH
