#pragma once

/* Lightweight Chrono Library utilizing the Pico SDK's timestamp
   Closely based on the awesome Project over at https://github.com/SofaPirate/Chrono
   Author: TLR
*/

//= Includes =========================================================================== Includes =

#include "pico/stdlib.h"
#include "pico/time.h"


//= PicoChrono ======================================================================= PicoChrono =

/**
 * @brief Simple Library for keeping track of Timestamps and the Time elapsed since
 * 
 * @note This Library is Based on the 64 Bit Microsecond Counter of the Pico not Milliseconds as in the original Library
 */
class PicoChrono
{
private:
    absolute_time_t StartTime; //Keeps track of start time

public:
    PicoChrono(); //Constructor.

    //Starts/restarts the chronometer.
    void start();
    void restart();

    uint64_t elapsed() const; //Elapsed Microseconds since the Timestamp

    //Returns true if elapsed time has passed given timeout.
    bool hasPassed      (uint64_t timeout) const;
    bool hasPassed      (uint64_t timeout, bool restartIfPassed);
    bool hasPassedPeriod(uint64_t timeout, uint64_t restartTime);
};