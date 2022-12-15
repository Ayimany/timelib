#include "headers/TimeReference.hh"
#include "headers/TimeSpan.hh"
#include <future>

using std::chrono::time_point_cast;

namespace preclib { namespace time {

    auto TimeReference::now() -> TimeReference {
        TimeReference ref;

        ref.timestamp =
            time_point_cast<microseconds>(system_clock::now());

        return ref;
    }

    auto TimeReference::inTime(uint64_t amount, TimeUnit units) -> TimeReference {
        TimeReference ref;

        TimePointMS current =
            time_point_cast<microseconds>(system_clock::now());

        auto future = std::chrono::microseconds(amount * units);

        ref.timestamp = current + future;

        return ref;
    }

    auto TimeReference::inRelative(RelativeTimeReference &relRef) -> TimeReference {
        return TimeReference::inTime(relRef.count, relRef.units);
    }

    auto TimeReference::fromTimeReference(TimePointMS &timestamp)  -> TimeReference {
        TimeReference ref;
        ref.timestamp = time_point_cast<microseconds>(timestamp);
        return ref;
    }

    auto TimeReference::plus(uint64_t count, TimeUnit units) -> TimeReference {
        TimePointMS::duration dur(timestamp.time_since_epoch().count() + count * units);
        this -> timestamp = TimePointMS(dur);
        return *this;
    }

    auto TimeReference::isBefore(TimeReference &other) -> bool {
        return this->timestamp < other.timestamp;
    }

    auto TimeReference::isAfter(TimeReference &other) -> bool {
        return this->timestamp > other.timestamp;
    }

    auto TimeReference::ellapsedUnits(TimeUnit unit) -> uint64_t {
        return this->timestamp.time_since_epoch().count() / unit;
    }

    auto TimeReference::formatTimePretty() -> std::string {
        char timefmt[30];
        std::tm *tmstrc;
        std::time_t time = system_clock::to_time_t(timestamp);
        tmstrc = std::localtime(&time);

        if (tmstrc == NULL) {
            return "00/00/00 at 00:00:00";
        }
        
        if (std::strftime(timefmt, sizeof(timefmt), "%d/%m/%y at %H:%M:%S", tmstrc) == 0) {
            return "00/00/00 at 00:00:00";
        }
        return std::string(timefmt);
    }

    auto TimeReference::formatTimeFunctional() -> std::string {
        char timefmt[30];
        std::tm *tmstrc;
        std::time_t time = system_clock::to_time_t(timestamp);
        tmstrc = std::localtime(&time);

        if (tmstrc == NULL) {
            return "00:00:00:00:00:00";
        }
        
        if (std::strftime(timefmt, sizeof(timefmt), "%d:%m:%y:%H:%M:%S", tmstrc) == 0) {
            return "00:00:00:00:00:00";
        }
        return std::string(timefmt);
    }

}}
