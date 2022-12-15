#ifndef PREC_RELATIVE_TIME_REFERENCE_HH
#define PREC_RELATIVE_TIME_REFERENCE_HH

#include "Time.hh"
#include <cstdint>

namespace preclib { namespace time {

    typedef struct relative_time_reference_t {
        uint64_t count;
        TimeUnit units;

        relative_time_reference_t(uint64_t count, TimeUnit units):
            count(count), units(units) {}

    } RelativeTimeReference;

}}

#endif
