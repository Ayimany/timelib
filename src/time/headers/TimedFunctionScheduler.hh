#ifndef PREC_TIMED_SCHEDULER_HH
#define PREC_TIMED_SCHEDULER_HH

#include "RelativeTimeReference.hh"
#include "Timer.hh"
#include <functional>
#include <utility>
#include <vector>

typedef std::pair<preclib::time::RelativeTimeReference, std::function<void()>>
    TimedFunction;

namespace preclib { namespace time {

    /// Takes in a list of instructions and executes each one according to a
    /// specified period of time.
    class TimedFunctionScheduler {
    public:

        /// Creates a TimedScheduler.
        TimedFunctionScheduler(): reqMicro(0), currentIndex(0) {}

        /// Starts the execution of all functions currently contained.
        auto run() -> void;

        /// Adds a new instruction.
        auto push(RelativeTimeReference, std::function<void()>) -> void;

        /// Removes the last instruction.
        auto pop() -> void;

        /// Removes an instruction at an index.
        auto remove(int index) -> void;

        /// Get the current instruction count.
        auto size() -> int;

        /// Query the theoretical time it'll take to execute everything
        auto requiredSeconds() -> uint64_t;

    private:
        time::Timer timer;
        
        std::vector<TimedFunction> instructions;

        uint64_t reqMicro;
        int currentIndex;
    };

}}

#endif // PREC_TIMED_SCHEDULER_HH
