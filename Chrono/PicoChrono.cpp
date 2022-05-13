/*
 * Lightweight chronometer class.
 * Simple chronometer/stopwatch class that counts the time passed since started.
 *
 * (c) 2015 Sofian Audry        :: info(@)sofianaudry(.)com
 * (c) 2015 Thomas O Fredericks :: tof(@)t-o-f(.)info
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "PicoChrono.hpp"


//= Public =============================================================================== Public =


/**
 * @brief Contructs a new PicoChrono Object and starts the Timer
 *
 */
PicoChrono::PicoChrono()
{
    restart();
}


/**
 * @brief Sets the Start Time
 *
 * @note Redundant - Use restart() instead
 */
void PicoChrono::start()
{
    restart();
}


/**
 * @brief Resets the Start Time to the Current Time
 *
 */
void PicoChrono::restart()
{
    StartTime = get_absolute_time();
}


/**
 * @brief Returns the Elapsed Time since the Start in us
 *
 * @return uint64_t Elapsed Time in Microseconds
 *
 * @note Function theoretically could return negative, but only in the case of an overflow... which will take a few thousand Years
 */
uint64_t PicoChrono::elapsed() const
{
    return absolute_time_diff_us(StartTime, get_absolute_time());
}


/**
 * @brief Checks if the elapsed Time has passed the specified Timespan
 *
 * @param timespan Timespan in Microseconds
 * @returns True if the Timespan has elapsed
 */
bool PicoChrono::hasPassed(uint64_t timespan) const
{
    return elapsed() >= timespan;
}


/**
 * @brief Checks if the elapsed Time has passed the specified Timespan and restarts when specified
 *
 * @param timespan Timespan in Microseconds
 * @param restartIfPassed Restarts the Timer if True and the Timespan has elapsed
 * @returns True if the Timespan has elapsed
 *
 * @note Will slowly accumulate an Error elongating the Period when used on a busy core, use hasTime(uint64, uint64) instead for Periodics
 */
bool PicoChrono::hasPassed(uint64_t timespan, bool restartIfPassed)
{
    if(hasPassed(timespan))
    {
        if(restartIfPassed) restart();
        return true;
    }
    return false;
}


/**
 * @brief Checks if the elapsed Time has passed the specified Timespan sets new Timer Value based on the Restart Time
 *
 * @param timespan Timespan in Microseconds
 * @param restartTime Time in Microseconds that the Start time will be moved forward
 * @returns True if the Timespan has elapsed
 *
 * @note Useful when Consistent Periods over a long Time are required but a Synchronous Solution with Callbacks is not
 */
bool PicoChrono::hasPassedPeriod(uint64_t timespan, uint64_t restartTime)
{
    if(hasPassed(timespan))
    {
        StartTime = delayed_by_us(StartTime, timespan);
        return true;
    }
    return false;
}