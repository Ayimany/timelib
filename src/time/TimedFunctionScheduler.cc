#include "headers/TimedFunctionScheduler.hh"
#include "headers/TimeReference.hh"
#include <future>

namespace preclib { namespace time {

    auto TimedFunctionScheduler::run() -> void {
        TimeReference relative = TimeReference::now();

        for (auto it = instructions.begin(); it != instructions.end(); it++) {

            relative = TimeReference::inRelative(it -> first);

            timer.setGoal(relative);

            timer.start();

            while (!timer.hasReachedGoal()) {
                it -> second();
            }

            timer.stop();
        }

        timer.resetGoal();

    }

    auto TimedFunctionScheduler::push(RelativeTimeReference ref, std::function<void()> func) -> void {

        reqMicro += ref.count * ref.units;

        instructions.emplace_back(TimedFunction(ref, func));
    }

    auto TimedFunctionScheduler::pop() -> void {
        instructions.pop_back();
    }

    auto TimedFunctionScheduler::remove(int index) -> void {
        instructions.erase(instructions.begin() + index);
    }

    auto TimedFunctionScheduler::size() -> int {
        return instructions.size();
    }

    auto TimedFunctionScheduler::requiredSeconds() -> uint64_t {
        return reqMicro;
    }

}}

