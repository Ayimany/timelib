#ifndef TIME_SPAN_H
#define TIME_SPAN_H

#include "TimeReference.hh"
#include <cstddef>

namespace timelib {

class TimeSpan {

public:

    TimeSpan(TimeReference start, TimeReference end):
        start(start), end(end) {}

    TimeSpan(TimeReference to): end(to) {}

    auto durationInUnits(TimeUnit units) -> uint64_t;

    auto isStartBeforeEnd() -> bool;

private:
    TimeSpan() {}
    TimeReference start = TimeReference::now();
    TimeReference end = start;
};

}

#endif
