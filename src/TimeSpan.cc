#include "headers/TimeSpan.hh"
#include "headers/Time.hh"

namespace timelib {

auto TimeSpan::durationInUnits(TimeUnit units) -> uint64_t {
    return end.ellapsedUnits(units) - start.ellapsedUnits(units);
}

auto TimeSpan::isStartBeforeEnd() -> bool {
    return start.isBefore(end);
}

}

