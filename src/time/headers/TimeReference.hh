#ifndef TIME_REFERENCE_H
#define TIME_REFERENCE_H

#include "Time.hh"
#include "RelativeTimeReference.hh"
#include <chrono>
#include <string>

using std::chrono::time_point;
using std::chrono::system_clock;
using std::chrono::microseconds;

#define TimePointMS time_point<system_clock, microseconds>

namespace preclib { namespace time {

    class TimeReference {

    public:

        /// Get a time reference to the time at the object's creation
        static auto now() -> TimeReference;

        /// Get a time reference equivalent to @amount @units relative
        /// to the time of the object's crreation
        static auto inTime(uint64_t count, TimeUnit units) -> TimeReference;

        /// Get a time reference in the amount of time specified by the
        /// RelativeTimeReference
        static auto inRelative(RelativeTimeReference &relRef) -> TimeReference;

        /// Get a time reference at the specified time through
        /// means of the system clock
        static auto fromTimeReference(TimePointMS &timeReference) -> TimeReference;

        // Adds @count @units relatie to the current time stamp
        auto plus(uint64_t count, TimeUnit units) -> TimeReference;

        // Returns weither this time reference is set before another or not
        auto isBefore(TimeReference &other) -> bool;

        /// Returns wether this time reference is set after another or not
        auto isAfter(TimeReference &other) -> bool;
        
        /// Seconds from epoch to this reference
        auto ellapsedUnits(TimeUnit units) -> uint64_t;

        /// Get the time in a pretty format
        /// D/M/Y at H:M:S
        auto formatTimePretty() -> std::string;

        /// Get the time in a workable format
        /// D:M:Y:H:M:S
        auto formatTimeFunctional() -> std::string;

    private:
        TimeReference() {}
        TimePointMS timestamp;
    };

}}

#endif // TIME_REFERENCE_H
