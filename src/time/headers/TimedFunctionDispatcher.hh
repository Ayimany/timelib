#ifndef PREC_TIMED_FUNCTION_DISPATCHER_H
#define PREC_TIMED_FUNCTION_DISPATCHER_H

#include "Time.hh"
#include "Timer.hh"
#include <cstdint>
#include <functional>

namespace preclib { namespace time {

    class TimedFunctionDispatcher {
    public:
        TimedFunctionDispatcher
            (uint64_t count, TimeUnit unit, std::function<void()> func):
                count(count), unit(unit), func(func) {}

        /// Begins executing the stored function every time the specified
        /// time unit is reached.
        /// @times is the amount of times the function should run.
        /// Use a negative value to run it forever.
        auto run(int times) -> void;

    private:
        Timer timer;
        TimeUnit unit;
        std::function<void()> func;
        uint64_t count;
    };

}}

#endif // PREC_TIMED_FUNCTION_DISPATCHER_H
