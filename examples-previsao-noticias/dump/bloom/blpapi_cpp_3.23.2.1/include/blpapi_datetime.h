/* Copyright 2012. Bloomberg Finance L.P.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:  The above
 * copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

/** \file blpapi_datetime.h */
/** \defgroup blpapi_datetime Component blpapi_datetime
\brief Represents a date and/or time.
\file blpapi_datetime.h
\brief Represents a date and/or time.
*/

#ifndef INCLUDED_BLPAPI_DATETIME
#define INCLUDED_BLPAPI_DATETIME
/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_datetime
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Represents a date and/or time.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi_Datetime_tag</td>
 * <td>C struct for date and/or msec time</td>
 * </tr>
 * <tr>
 * <td>blpapi_HighPrecisionDatetime_tag</td>
 * <td>C struct for date and/or psec time</td>
 * </tr>
 * <tr>
 * <td>blpapi::Datetime</td>
 * <td>C++ class for date and/or psec time</td>
 * </tr>
 * <tr>
 * <td>blpapi::DatetimeParts</td>
 * <td>Identifiers for fields within date/time</td>
 * </tr>
 * <tr>
 * <td>blpapi::DatetimeUtil</td>
 * <td><code>Datetime</code> utility functions</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This file provides a C and C++ data type to represent a
 * date and/or time value.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

#ifndef INCLUDED_BLPAPI_STREAMPROXY
#include <blpapi_streamproxy.h>
#endif

#ifndef INCLUDED_BLPAPI_TIMEPOINT
#include <blpapi_timepoint.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct blpapi_Datetime_tag {
    /*!  bitmask of date/time parts that are set */
    blpapi_UChar_t parts;
    blpapi_UChar_t hours;
    blpapi_UChar_t minutes;
    blpapi_UChar_t seconds;
    blpapi_UInt16_t milliSeconds;
    blpapi_UChar_t month;
    blpapi_UChar_t day;
    blpapi_UInt16_t year;
    blpapi_Int16_t offset; // (signed) minutes ahead of UTC
};

struct blpapi_HighPrecisionDatetime_tag {
    blpapi_Datetime_t datetime;
    blpapi_UInt32_t picoseconds; // picosecond offset into current
                                 // *millisecond* i.e. the picosecond offset
                                 // into the current full second is
                                 // '1000000000LL * milliSeconds + picoseconds'
};

typedef struct blpapi_HighPrecisionDatetime_tag blpapi_HighPrecisionDatetime_t;

BLPAPI_EXPORT
int blpapi_Datetime_compare(blpapi_Datetime_t lhs, blpapi_Datetime_t rhs);

BLPAPI_EXPORT
int blpapi_Datetime_print(const blpapi_Datetime_t *datetime,
        blpapi_StreamWriter_t streamWriter,
        void *stream,
        int level,
        int spacesPerLevel);

BLPAPI_EXPORT
int blpapi_HighPrecisionDatetime_compare(
        const blpapi_HighPrecisionDatetime_t *lhs,
        const blpapi_HighPrecisionDatetime_t *rhs);

BLPAPI_EXPORT
int blpapi_HighPrecisionDatetime_print(
        const blpapi_HighPrecisionDatetime_t *datetime,
        blpapi_StreamWriter_t streamWriter,
        void *stream,
        int level,
        int spacesPerLevel);

BLPAPI_EXPORT
int blpapi_HighPrecisionDatetime_fromTimePoint(
        blpapi_HighPrecisionDatetime_t *datetime,
        const blpapi_TimePoint_t *timePoint,
        short offset);

#ifdef __cplusplus
} // extern "C"

#ifndef INCLUDED_CASSERT
#include <cassert>
#define INCLUDED_CASSERT
#endif

#ifndef INCLUDED_CSTRING
#include <cstring> // for std::memset
#define INCLUDED_CSTRING
#endif

#ifndef INCLUDED_IOSFWD
#include <iosfwd>
#define INCLUDED_IOSFWD
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_datetime
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 *     Bit flags and masks used to determine which parts of a Datetime are
 *     valid.
 */
/*!
 * See \ref blpapi_datetime
 */
struct DatetimeParts {

    /// Enumeration used to indicate which parts of the <code>Datetime</code>
    /// object have had their values set.  The actual enumeration constants are
    /// thus <em>not</em> consecutive -- they are bit fields that can be
    /// combined using bitwise operators.  Note that the constants themselves
    /// are defined in <code>blpapi_defs.h</code>.
    enum Value {

        YEAR = BLPAPI_DATETIME_YEAR_PART, ///< year is set
        MONTH = BLPAPI_DATETIME_MONTH_PART, ///< month is set
        DAY = BLPAPI_DATETIME_DAY_PART, ///< day is set
        OFFSET = BLPAPI_DATETIME_OFFSET_PART, ///< offset is set
        HOURS = BLPAPI_DATETIME_HOURS_PART, ///< hours is set
        MINUTES = BLPAPI_DATETIME_MINUTES_PART, ///< minutes is set
        SECONDS = BLPAPI_DATETIME_SECONDS_PART, ///< seconds is set
        FRACSECONDS = BLPAPI_DATETIME_FRACSECONDS_PART,
        ///< fraction-of-second (both millisecond and picosecond) is set

        MILLISECONDS = BLPAPI_DATETIME_MILLISECONDS_PART,
        ///< `MILLISECONDS` is a (legacy) synonym for `FRACSECONDS`

        DATE = BLPAPI_DATETIME_DATE_PART,
        ///< year, month, and day are set

        TIME = BLPAPI_DATETIME_TIME_PART,
        ///< hours, minutes, and seconds are set

        TIMEFRACSECONDS = BLPAPI_DATETIME_TIMEFRACSECONDS_PART,
        ///< hours, minutes, seconds, and fraction-of-second are set

        TIMEMILLI = BLPAPI_DATETIME_TIMEMILLI_PART,
        ///< `TIMEMILLI` is a (legacy) synonym for `TIMEFRACSECONDS`
    };
};

/*!
 * Represents a date and/or time.
 *
 * Datetime can represent a date and/or a time or any combination of the
 * components of a date and time.  The value is represented as eight parts
 * which can be set or queried independently.
 *
 * These parts are: year; month (from January as 1 to December as 12); day (of
 * month, from 1 to 31); hour (from 0 to 23); minute (0 to 59); second (0 to
 * 59); fraction-of-second (logically representing arbitrary precision, with
 * the current interface providing picosecond resolution); and offset (time
 * zone as minutes ahead of UTC).
 *
 * Methods are provided to set and query the parts individually and in groups,
 * e.g. <code>setDate()</code> and <code>setTime()</code>.  It is also possible
 * to determine which parts of the <code>Datetime</code> have been set (via the
 * <code>parts()</code> method).
 */
/*!  See \ref blpapi_datetime
 */
class Datetime {

    blpapi_HighPrecisionDatetime_t d_value;

    static bool isLeapYear(int year);

    struct TimeTag { };
    Datetime(unsigned hours, unsigned minutes, unsigned seconds, TimeTag);
    /*!<
     * Create a <code>Datetime</code> object having the value representing the
     * specified <code>hours</code>, <code>minutes</code>, and
     * <code>seconds</code>.  The behavior is undefined unless
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * represent a valid time as specified by the <code>isValidTime</code>
     * function.  The resulting <code>Datetime</code> object has the parts
     * specified by <code>TIME</code> set, and all other parts unset.  In
     * particular, the <code>FRACSECONDS</code> part is unset.  Note that the
     * final <code>TimeTag</code> parameter is used purely to disambiguate this
     * constructor from that for year, month, and day.  A constructor for 4 PM
     * would be written as follows:
     * \code Datetime dt = Datetime(16, 0, 0, Datetime::TimeTag()); \endcode
     * Note that this constructor is intended for internal use only; client
     * code should use the <code>createTime</code> interface.
     */

  public:
    typedef blpapi_HighPrecisionDatetime_t HighPrecision;
    struct Milliseconds {
        int d_msec;
        explicit Milliseconds(int milliseconds);
        /*!<
         * The behavior is undefined unless <code>0 \<= milliseconds \<
         * 1000</code>.
         */
    };
    struct Microseconds {
        int d_usec;
        explicit Microseconds(int microseconds);
        /*!<
         * The behavior is undefined unless
         * <code>0 \<= microseconds \< 1,000,000</code>.
         */
    };
    struct Nanoseconds {
        int d_nsec;
        explicit Nanoseconds(int nanoseconds);
        /*!<
         * The behavior is undefined unless
         * <code>0 \<= nanoseconds \< 1,000,000,000</code>.
         */
    };
    struct Picoseconds {
        long long d_psec;
        explicit Picoseconds(long long picoseconds);
        /*!<
         * The behavior is undefined unless
         * <code>0 \<= picoseconds \< 1,000,000,000,000</code>.
         */
    };
    struct Offset {
        short d_minutesAheadOfUTC;
        explicit Offset(short minutesAheadOfUTC);
        /*!<
         * The behavior is undefined unless
         * <code>-840 \<= minutesAheadOfUTC \<= 840</code>.
         */
    };

    static bool isValidDate(int year, int month, int day);
    /*!<
     * Return <code>true</code> if the specified <code>year</code>,
     * <code>month</code>, and <code>day</code> represent a valid calendar
     * date, and <code>false</code> otherwise.  Note that many functions within
     * <code>Datetime</code> provide defined behavior only when valid dates are
     * provided as arguments.
     */

    static bool isValidTime(int hours, int minutes, int seconds);
    static bool isValidTime(
            int hours, int minutes, int seconds, int milliSeconds);
    static bool isValidTime(int hours,
            int minutes,
            int seconds,
            Milliseconds fractionOfSecond);
    static bool isValidTime(int hours,
            int minutes,
            int seconds,
            Microseconds fractionOfSecond);
    static bool isValidTime(
            int hours, int minutes, int seconds, Nanoseconds fractionOfSecond);
    static bool isValidTime(
            int hours, int minutes, int seconds, Picoseconds fractionOfSecond);
    /*!<
     * Return <code>true</code> if the specified <code>hours</code>,
     * <code>minutes</code>, <code>seconds</code>, and (optionally specified)
     * <code>milliseconds</code> or <code>fractionOfSecond</code> represent a
     * valid time of day, and <code>false</code> otherwise.  Note that many
     * functions within <code>Datetime</code> provide defined behavior only
     * when valid times are provided as arguments.
     */

    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * parts.  The behavior is undefined unless <code>year</code>,
     * <code>month</code>, and <code>day</code> represent a valid date as
     * specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * represent a valid time as specified by the <code>isValidTime</code>
     * function.  The resulting <code>Datetime</code> object has the parts
     * specified by <code>DATE</code> and <code>TIME</code> set, and the
     * <code>OFFSET</code> and <code>FRACSECONDS</code> parts unset.
     */

    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Offset offset);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>offset</code> parts.  The behavior is undefined unless
     * <code>year</code>, <code>month</code>, and <code>day</code> represent a
     * valid date as specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * represent a valid time as specified by the <code>isValidTime</code>
     * function.  The resulting <code>Datetime</code> object has the parts
     * specified by <code>DATE</code>, <code>TIME</code>, and
     * <code>OFFSET</code> set, and the <code>FRACSECONDS</code> part
     * unset.
     */

    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code>.  The behavior is undefined unless
     * <code>year</code>, <code>month</code>, and <code>day</code> represent a
     * valid date as specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code> represent a valid time as specified by
     * the <code>isValidTime</code> function.  The resulting
     * <code>Datetime</code> object has the parts specified by
     * <code>DATE</code> and <code>TIMEFRACSECONDS</code> set, and the
     * <code>OFFSET</code> part unset.
     */

    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond,
            Offset offset);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond,
            Offset offset);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond,
            Offset offset);
    static Datetime createDatetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond,
            Offset offset);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>,
     * <code>fractionOfSecond</code>, and <code>offset</code>.  The
     * behavior is undefined unless <code>year</code>, <code>month</code>, and
     * <code>day</code> represent a valid date as specified by the
     * <code>isValidDate</code> function, and <code>hours</code>,
     * <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code> represent a valid time as specified by
     * the <code>isValidTime</code> function.  The resulting
     * <code>Datetime</code> object has all parts set.
     */

    static Datetime createDate(unsigned year, unsigned month, unsigned day);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, and
     * <code>day</code>.  The behavior is undefined unless <code>year</code>,
     * <code>month</code>, and <code>day</code> represent a valid date as
     * specified by the <code>isValidDate</code> function.  The resulting
     * <code>Datetime</code> object has the parts specified by
     * <code>DATE</code> set, and all other parts unset.
     */

    static Datetime createTime(
            unsigned hours, unsigned minutes, unsigned seconds);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>, and
     * <code>seconds</code>.  The behavior is undefined unless
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * represent a valid time as specified by the <code>isValidTime</code>
     * function. The resulting <code>Datetime</code> object has the parts
     * specified by <code>TIME</code> set, and all other parts unset.  Note
     * that the <code>FRACSECONDS</code> part is unset.
     */

    static Datetime createTime(
            unsigned hours, unsigned minutes, unsigned seconds, Offset offset);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>offset</code>.  The behavior is
     * undefined unless <code>hours</code>, <code>minutes</code>, and
     * <code>seconds</code> represent a valid time as specified by the
     * <code>isValidTime</code> function. The resulting <code>Datetime</code>
     * object has the parts specified by <code>TIME</code> and
     * <code>OFFSET</code> set, and all other parts unset.  Note that the
     * <code>FRACSECONDS</code> part is unset.
     */

    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            unsigned milliseconds);
    /*!<
     *     Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>milliseconds</code>.  The behavior is
     * undefined unless <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>milliseconds</code> represent a valid
     * time as specified by the <code>isValidTime</code> function.  The
     * resulting <code>Datetime</code> object has the parts specified by
     * <code>TIMEFRACSECONDS</code> set, and all other parts unset.
     */

    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            unsigned milliseconds,
            Offset offset);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, <code>milliseconds</code>, and
     * <code>offset</code>.  The behavior is undefined unless
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>milliseconds</code> represent a valid time as specified by the
     * <code>isValidTime</code> function.  The resulting <code>Datetime</code>
     * object has the parts specified by <code>TIMEFRACSECONDS</code> and
     * <code>OFFSET</code> set, and all other parts unset.
     */

    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>fractionOfSecond</code>. The behavior is
     * undefined unless <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>fractionOfSecond</code> represent a
     * valid time as specified by the <code>isValidTime</code> function.  The
     * resulting <code>Datetime</code> object has the parts specified by
     * <code>TIMEFRACSECONDS</code> set, and all other parts unset.
     */

    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond,
            Offset offset);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond,
            Offset offset);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond,
            Offset offset);
    static Datetime createTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond,
            Offset offset);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, <code>fractionOfSecond</code>, and
     * <code>offset</code>.  The behavior is undefined unless
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code> represent a valid time as specified by the
     * <code>isValidTime</code> function.  The resulting <code>Datetime</code>
     * object has the parts specified by <code>TIMEFRACSECONDS</code> and
     * <code>OFFSET</code> set, and all other parts unset.
     */

    Datetime();
    /*!<
     * Construct a <code>Datetime</code> object with all parts unset.
     */

    Datetime(const Datetime& original);
    /*!<
     * Copy constructor.
     */

    Datetime(const blpapi_Datetime_t& rawValue);

    explicit Datetime(const blpapi_HighPrecisionDatetime_t& rawValue);

    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * parts.  The behavior is undefined unless <code>year</code>,
     * <code>month</code>, and <code>day</code> represent a valid date as
     * specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, and <code>seconds</code>
     * represent a valid time as specified by the <code>isValidTime</code>
     * function.  The resulting <code>Datetime</code> object has the parts
     * specified by <code>DATE</code> and <code>TIME</code> set, and the
     * <code>OFFSET</code> and <code>FRACSECONDS</code> parts unset.
     * Use of this function is discouraged; use <code>createDatetime</code>
     * instead.
     */

    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            unsigned milliseconds);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>milliseconds</code>.  The behavior is undefined unless
     * <code>year</code>, <code>month</code>, and <code>day</code> represent a
     * valid date as specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>milliseconds</code> represent a valid time as specified by the
     * <code>isValidTime</code> function. The resulting <code>Datetime</code>
     * object has the parts specified by <code>DATE</code> and
     * <code>TIMEFRACSECONDS</code> set, and the <code>OFFSET</code> part
     * unset. Use of this function is discouraged; use
     * <code>createDatetime</code> instead.
     */

    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond);
    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond);
    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond);
    Datetime(unsigned year,
            unsigned month,
            unsigned day,
            unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, <code>day</code>,
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code>.  The behavior is undefined unless
     * <code>year</code>, <code>month</code>, and <code>day</code> represent a
     * valid date as specified by the <code>isValidDate</code> function, and
     * <code>hours</code>, <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code> represent a valid time as specified by
     * the <code>isValidTime</code> function.  The resulting
     * <code>Datetime</code> object has the parts specified by
     * <code>DATE</code> and <code>TIMEFRACSECONDS</code> set, and the
     * <code>OFFSET</code> part unset.
     * Use of these functions is discouraged; use
     * <code>createDatetime</code> instead.
     */

    Datetime(unsigned year, unsigned month, unsigned day);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>year</code>, <code>month</code>, and
     * <code>day</code>.  The behavior is undefined unless <code>year</code>,
     * <code>month</code>, and <code>day</code> represent a valid date as
     * specified by the <code>isValidDate</code> function.  The resulting
     * <code>Datetime</code> object has the parts specified by
     * <code>DATE</code> set, and all other parts unset.
     *
     * Note that constructing a <code>Datetime</code> from three integers
     * produces a date; to create a time from hour, minute, and second (without
     * the fraction-of-second part unset) use createTime(). Use of this
     * function is discouraged; use createDate() instead.
     */

    Datetime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            unsigned milliseconds);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>milliseconds</code>.  The behavior is
     * undefined unless <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>milliseconds</code> represent a valid
     * time as specified by the <code>isValidTime</code> function.  The
     * resulting <code>Datetime</code> object has the parts specified by
     * <code>TIMEFRACSECONDS</code> set, and all other parts unset. Note that
     * removing the final argument from a call to this function results in a
     * constructor creating a date, not a time.
     */

    Datetime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond);
    Datetime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond);
    Datetime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond);
    Datetime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond);
    /*!<
     * Create a <code>Datetime</code> object having the value representing
     * the specified <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>fractionOfSecond</code>. The behavior is
     * undefined unless <code>hours</code>, <code>minutes</code>,
     * <code>seconds</code>, and <code>fractionOfSecond</code> represent a
     * valid time as specified by the <code>isValidTime</code> function.  The
     * resulting <code>Datetime</code> object has the parts specified by
     * <code>TIMEFRACSECONDS</code> set, and all other parts unset. Note that
     * removing the final argument from a call to this function results in a
     * constructor creating a date, not a time.
     */

    Datetime& operator=(const Datetime& rhs);
    /*!<
     * Assignment operator.
     */

    void setDate(unsigned year, unsigned month, unsigned day);
    /*!<
     * Set the <code>DATE</code> parts of this <code>Datetime</code> object
     * to the specified <code>year</code>, <code>month</code>, and
     * <code>day</code>.  The behavior is undefined unless
     * <code>isValidDate(year, month, day)</code> would return
     * <code>true</code>.
     */

    void setTime(unsigned hours, unsigned minutes, unsigned seconds);
    /*!<
     * Set the <code>TIME</code> parts of this <code>Datetime</code> object
     * to the specified <code>hours</code>, <code>minutes</code>, and
     * <code>seconds</code>, and mark the <code>FRACSECONDS</code> part of this
     * <code>Datetime</code> as unset.  The behavior is undefined unless
     * <code>isValidTime(hours, minutes, seconds)</code> would return
     * <code>true</code>.
     */

    void setTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            unsigned milliseconds);
    /*!<
     * Set the <code>TIMEFRACSECONDS</code> parts of this
     * <code>Datetime</code> object to the specified <code>hours</code>,
     * <code>minutes</code>, <code>seconds</code>, and
     * <code>milliseconds</code>.  The behavior is undefined unless
     * <code>isValidTime(hours, minutes, seconds, milliseconds)</code>
     * would return <code>true</code>.
     */

    void setTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Milliseconds fractionOfSecond);
    void setTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Microseconds fractionOfSecond);
    void setTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Nanoseconds fractionOfSecond);
    void setTime(unsigned hours,
            unsigned minutes,
            unsigned seconds,
            Picoseconds fractionOfSecond);
    /*!<
     * Set the <code>TIMEFRACSECONDS</code> parts of this
     * <code>Datetime</code> object to the specified <code>hours</code>,
     * <code>minutes</code>, <code>seconds</code>, and
     * <code>fractionOfSecond</code>. The behavior is undefined unless
     * <code>isValidTime(hours, minutes, seconds, fractionOfSecond)</code>
     * would return <code>true</code>.
     */

    void setOffset(short minutesAheadOfUTC);
    /*!<
     * Set the <code>OFFSET</code> (i.e. timezone) part of this
     * <code>Datetime</code> object to the specified
     * <code>minutesAheadOfUTC</code>. The behavior is undefined unless
     * <code>-840 \<= minutesAheadOfUTC \<= 840</code>.
     */

    void setYear(unsigned value);
    /*!<
     *     Set the <code>YEAR</code> part of this <code>Datetime</code> object
     * to the specified <code>value</code>. The behavior is undefined unless
     * <code>1 \<= value \<= 9999</code>, and either the <code>MONTH</code>
     * part is not set, the <code>DAY</code> part is not set, or
     *     <code>isValidDate(value. this-\>month(), this-\>day()) ==
     * true</code>.
     */

    void setMonth(unsigned value);
    /*!<
     * Set the <code>MONTH</code> part of this <code>Datetime</code> object
     * to the specified <code>value</code>. The behavior is undefined unless
     * <code>1 \<= value \<= 12</code>, and either the <code>DAY</code> part is
     * not set, the <code>YEAR</code> part is not set, or
     * <code>isValidDate(this-\>year(). value, this-\>day()) ==
     * true</code>.
     */

    void setDay(unsigned value);
    /*!<
     * Set the <code>DAY</code> part of this <code>Datetime</code> object
     * to the specified <code>value</code>. The behavior is undefined unless
     * <code>1 \<= value \<= 31</code>, and either the <code>MONTH</code> part
     * is not set, the <code>YEAR</code> part is not set, or
     * <code>isValidDate(this-\>year(). this-\>month(), value) ==
     * true</code>.
     */

    void setHours(unsigned value);
    /*!<
     * Set the <code>HOURS</code> part of this <code>Datetime</code> object
     * to the specified <code>value</code>. The behavior is undefined unless
     * <code>0 \<= value \<= 23</code>.
     */

    void setMinutes(unsigned value);
    /*!<
     * Set the <code>MINUTES</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 59</code>.
     */

    void setSeconds(unsigned value);
    /*!<
     * Set the <code>SECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 59</code>.
     */

    void setMilliseconds(unsigned milliseconds);
    /*!<
     * Set the <code>FRACSECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>milliseconds</code>. The behavior is
     * undefined unless <code>0 \<= value \<= 999</code>.
     */

    void setFractionOfSecond(Milliseconds value);
    /*!<
     * Set the <code>FRACSECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 999 ms</code>.
     */

    void setFractionOfSecond(Microseconds value);
    /*!<
     * Set the <code>FRACSECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 999,999 us</code>.
     */

    void setFractionOfSecond(Nanoseconds value);
    /*!<
     * Set the <code>FRACSECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 999,999,999 ns</code>.
     */

    void setFractionOfSecond(Picoseconds value);
    /*!<
     * Set the <code>FRACSECONDS</code> part of this <code>Datetime</code>
     * object to the specified <code>value</code>. The behavior is undefined
     * unless <code>0 \<= value \<= 999,999,999,999 ps</code>.
     */

    blpapi_Datetime_t& rawValue();
    /*!<
     * Return a (modifiable) reference to the millisecond-resolution C struct
     * underlying this object.  Behavior of the object is undefined if the
     * returned struct is modified concurrently with other non-const methods of
     * this object, or if the fields of the <code>blpapi_Datetime_t</code> are
     * modified such that the <code>Datetime::isValid</code> methods of this
     * class would return <code>false</code> when passed those fields of the
     * struct whose bits are set in the struct's <code>parts</code> field.
     * Further, direct setting of the <code>FRACSECONDS</code> bit in the
     * returned struct's <code>parts</code> field will cause this
     * <code>Datetime</code> object to compute its fraction-of-second part not
     * just from the struct's <code>milliSeconds</code> field, but also from
     * the <code>picoseconds</code> field of the the struct returned from
     * <code>rawHighPrecisionValue()</code>; if neither that field nor this
     * <code>Datetime</code> objects' fraction-of-second part have been
     * initialized, then the behavior of setting the <code>FRACSECONDS</code>
     * bit directly is undefined.
     */

    blpapi_HighPrecisionDatetime_t& rawHighPrecisionValue();
    /*!<
     * Return a (modifiable) reference to the high-resolution C struct
     * underlying this object.  Behavior of the object is undefined if the
     * returned struct is modified concurrently with other non-const methods of
     * this object, or if the fields of the
     * <code>blpapi_HighPrecisionDatetime_t</code> are modified such that the
     * <code>Datetime::isValid*</code> methods of this class would return
     * <code>false</code> when passed those fields of the struct whose bits are
     * set in the struct's <code>parts</code> field.
     */

    bool hasParts(unsigned parts) const;
    /*!<
     * Return true if this <code>Datetime</code> object has all of the
     * specified <code>parts</code> set.  The <code>parts</code> parameter must
     * be constructed by or'ing together values from the
     * <code>DatetimeParts</code> enum.
     */

    unsigned parts() const;
    /*!<
     * Return a bitmask of all parts that are set in this
     * <code>Datetime</code> object.  This can be compared to the values in the
     * <code>DatetimeParts</code> enum using bitwise operations.
     */

    unsigned year() const;
    /*!<
     * Return the year value of this <code>Datetime</code> object.  The result
     * is undefined unless the <code>YEAR</code> part of this object is set.
     */

    unsigned month() const;
    /*!<
     * Return the month value of this <code>Datetime</code> object.  The result
     * is undefined unless the <code>MONTH</code> part of this object is set.
     */

    unsigned day() const;
    /*!<
     * Return the day value of this <code>Datetime</code> object.  The result
     * is undefined unless the <code>DAY</code> part of this object is set.
     */

    unsigned hours() const;
    /*!<
     * Return the hours value of this <code>Datetime</code> object.  The result
     * is undefined unless the <code>HOURS</code> part of this object is set.
     */

    unsigned minutes() const;
    /*!<
     * Return the minutes value of this <code>Datetime</code> object.  The
     * result is undefined unless the <code>MINUTES</code> part of this object
     * is set.
     */

    unsigned seconds() const;
    /*!<
     * Return the seconds value of this <code>Datetime</code> object.  The
     * result is undefined unless the <code>SECONDS</code> part of this object
     * is set.
     */

    unsigned milliSeconds() const;
    /*!<
     * Return the fraction-of-a-second value of this object in units of whole
     * milliseconds.  The result is undefined unless the
     * <code>FRACSECONDS</code> part of this object is set. This function is
     * deprecated; use <code>milliseconds()</code> instead.
     */

    unsigned milliseconds() const;
    /*!<
     * Return the fraction-of-a-second value of this object in units of whole
     * milliseconds.  The result is undefined unless the
     * <code>FRACSECONDS</code> part of this object is set.
     */

    unsigned microseconds() const;
    /*!<
     * Return the fraction-of-a-second value of this object in units of whole
     * microseconds.  The result is undefined unless the
     * <code>FRACSECONDS</code> part of this object is set.
     */

    unsigned nanoseconds() const;
    /*!<
     * Return the fraction-of-a-second value of this object in units of whole
     * nanoseconds.  The result is undefined unless the
     * <code>FRACSECONDS</code> part of this object is set.
     */

    unsigned long long picoseconds() const;
    /*!<
     * Return the fraction-of-a-second value of this object in units of whole
     * picoseconds.  The result is undefined unless the
     * <code>FRACSECONDS</code> part of this object is set.
     */

    short offset() const;
    /*!<
     * Return the number of minutes this <code>Datetime</code> object is ahead
     * of UTC. The result is undefined unless the <code>OFFSET</code> part of
     * this object is set.
     */

    const blpapi_Datetime_t& rawValue() const;
    /*!<
     * Return a (read-only) reference to the millisecond-resolution C struct
     * underlying this object.
     */

    const blpapi_HighPrecisionDatetime_t& rawHighPrecisionValue() const;
    /*!<
     * Return a (read-only) reference to the high-precision C struct underlying
     * this object.
     */

    const HighPrecision& highPrecisionValue() const;
    /*!<
     * Return a (read-only) reference to the high-precision C struct underlying
     * this object.
     */

    bool isValid() const;
    /*!<
     * Check whether the value of this <code>Datetime</code> is valid.  The
     * behaviour is undefined unless this object represents a date (has YEAR,
     * MONTH and DAY part set) or time (has HOURS, MINUTES, SECONDS and
     * MILLISECONDS part set).  Note that in almost all cases where this
     * function returns <code>false</code>, prior member function calls have
     * had undefined behavior. This function is deprecated; use
     * <code>isValidDate</code> and/or <code>isValidTime</code> directly
     * instead.
     */

    std::ostream& print(
            std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
    /*!<
     * Write the value of this object to the specified output
     * <code>stream</code> in a human-readable format, and return a reference
     * to <code>stream</code>. Optionally specify an initial indentation
     * <code>level</code>, whose absolute value is incremented recursively for
     * nested objects.  If <code>level</code> is specified, optionally specify
     * <code>spacesPerLevel</code>, whose absolute value indicates the number
     * of spaces per indentation level for this and all of its nested objects.
     * If <code>level</code> is negative, suppress indentation of the first
     * line.  If <code>spacesPerLevel</code> is negative, format the entire
     * output on one line, suppressing all but the initial indentation (as
     * governed by <code>level</code>).  If <code>stream</code> is not valid on
     * entry, this operation has no effect.  Note that this human-readable
     * format is not fully specified, and can change without notice.
     */
};

/*!
 * This provides a namespace for <code>Datetime</code> utility functions.
 */
/*!
 * See \ref blpapi_datetime
 */
struct DatetimeUtil {

    static Datetime fromTimePoint(const TimePoint& timePoint,
            Datetime::Offset offset = Datetime::Offset(0));
    /*!<
     * Create and return a <code>Datetime</code> object having the value of the
     * specified <code>timePoint</code> and the optionally specified timezone
     * <code>offset</code>, 0 by default. The resulting <code>Datetime</code>
     * object has the parts specified by <code>DATE</code>,
     * <code>TIMEFRACSECONDS</code>, and <code>OFFSET</code> set.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// --------------
// class Datetime
// --------------

// FREE OPERATORS
bool operator==(const Datetime& lhs, const Datetime& rhs);
/*!<
 * Return <code>true</code> if the specified <code>lhs</code> and
 * <code>rhs</code> have the same value, and <code>false</code> otherwise.  Two
 * <code>Datetime</code> objects have the same value if they have the same
 * parts set, and the same values for each of those parts.
 */

bool operator!=(const Datetime& lhs, const Datetime& rhs);
/*!<
 * Return <code>true</code> if the specified <code>lhs</code> and
 * <code>rhs</code> do not have the same value, and <code>false</code>
 * otherwise.  Two <code>Datetime</code> objects have the same value if they
 * have the same parts set, and the same values for each of those parts.
 */

bool operator<(const Datetime& lhs, const Datetime& rhs);
bool operator<=(const Datetime& lhs, const Datetime& rhs);
bool operator>(const Datetime& lhs, const Datetime& rhs);
bool operator>=(const Datetime& lhs, const Datetime& rhs);
/*!<
 * Compare the specified <code>lhs</code> and <code>rhs</code>.  The ordering
 * used is temporal, with earlier moments comparing less than later moments, in
 * the case that <code>lhs.parts() == rhs.parts()</code> and
 * <code>parts()</code> is one of <code>DATE</code>, <code>TIME</code>,
 * <code>TIMEFRACSECONDS</code>, <code>DATE | TIME</code>, and <code>DATE |
 * TIMEFRACSECONDS</code>; the ordering in all other cases is unspecified, but
 * guaranteed stable within process.
 */

std::ostream& operator<<(std::ostream& stream, const Datetime& datetime);
/*!<
 * Write the value of the specified <code>datetime</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified, can change without notice, and is logically
 * equivalent to:
 * \code
 * print(stream, 0, -1);
 * \endcode
 */

inline bool Datetime::isLeapYear(int y)
{
    return 0 == y % 4 && (y <= 1752 || 0 != y % 100 || 0 == y % 400);
}

inline Datetime::Datetime(
        unsigned newHours, unsigned newMinutes, unsigned newSeconds, TimeTag)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds);
}

inline Datetime::Milliseconds::Milliseconds(int milliseconds)
    : d_msec(milliseconds)
{
}

inline Datetime::Microseconds::Microseconds(int microseconds)
    : d_usec(microseconds)
{
}

inline Datetime::Nanoseconds::Nanoseconds(int nanoseconds)
    : d_nsec(nanoseconds)
{
}

inline Datetime::Picoseconds::Picoseconds(long long picoseconds)
    : d_psec(picoseconds)
{
}

inline Datetime::Offset::Offset(short minutesAheadOfUTC)
    : d_minutesAheadOfUTC(minutesAheadOfUTC)
{
}

inline bool Datetime::isValidDate(int year, int month, int day)
{
    if ((year <= 0) || (year > 9999) || (month <= 0) || (month > 12)
            || (day <= 0) || (day > 31)) {
        return false;
    }
    if (year == 1752) {
        if (month == 9 && day > 2 && day < 14) {
            return false;
        }
    }
    if (day < 29) {
        return true;
    }
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return true;

    case 4:
    case 6:
    case 9:
    case 11: {
        if (day > 30) {
            return false;
        } else {
            return true;
        }
    }
    case 2: {
        if (isLeapYear(year)) {
            if (day > 29) {
                return false;
            } else {
                return true;
            }
        } else if (day > 28) {
            return false;
        } else {
            return true;
        }
    }
    default: {
        return true;
    }
    }
}

inline bool Datetime::isValidTime(int hours, int minutes, int seconds)
{
    return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60)
            && (seconds >= 0) && (seconds < 60);
}

inline bool Datetime::isValidTime(
        int hours, int minutes, int seconds, int milliSeconds)
{
    return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60)
            && (seconds >= 0) && (seconds < 60) && (milliSeconds >= 0)
            && (milliSeconds < 1000);
}

inline bool Datetime::isValidTime(
        int hours, int minutes, int seconds, Milliseconds fractionOfSecond)
{
    return isValidTime(hours, minutes, seconds, fractionOfSecond.d_msec);
}

inline bool Datetime::isValidTime(
        int hours, int minutes, int seconds, Microseconds fractionOfSecond)
{
    return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60)
            && (seconds >= 0) && (seconds < 60)
            && (fractionOfSecond.d_usec >= 0)
            && (fractionOfSecond.d_usec < 1000 * 1000);
}

inline bool Datetime::isValidTime(
        int hours, int minutes, int seconds, Nanoseconds fractionOfSecond)
{
    return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60)
            && (seconds >= 0) && (seconds < 60)
            && (fractionOfSecond.d_nsec >= 0)
            && (fractionOfSecond.d_nsec < 1000 * 1000 * 1000);
}

inline bool Datetime::isValidTime(
        int hours, int minutes, int seconds, Picoseconds fractionOfSecond)
{
    return (hours >= 0) && (hours < 24) && (minutes >= 0) && (minutes < 60)
            && (seconds >= 0) && (seconds < 60)
            && (fractionOfSecond.d_psec >= 0)
            && (fractionOfSecond.d_psec < 1000LL * 1000 * 1000 * 1000);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds)
{
    return Datetime(year, month, day, hours, minutes, seconds);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Offset offset)
{
    Datetime dt(year, month, day, hours, minutes, seconds);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Milliseconds fractionOfSecond)
{
    return Datetime(
            year, month, day, hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Microseconds fractionOfSecond)
{
    return Datetime(
            year, month, day, hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Nanoseconds fractionOfSecond)
{
    return Datetime(
            year, month, day, hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Picoseconds fractionOfSecond)
{
    return Datetime(
            year, month, day, hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Milliseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(year, month, day, hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Microseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(year, month, day, hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Nanoseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(year, month, day, hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createDatetime(unsigned year,
        unsigned month,
        unsigned day,
        unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Picoseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(year, month, day, hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createDate(
        unsigned year, unsigned month, unsigned day)
{
    return Datetime(year, month, day);
}

inline Datetime Datetime::createTime(
        unsigned hours, unsigned minutes, unsigned seconds)
{
    return Datetime(hours, minutes, seconds, TimeTag());
}

inline Datetime Datetime::createTime(
        unsigned hours, unsigned minutes, unsigned seconds, Offset offset)
{
    Datetime dt(hours, minutes, seconds, TimeTag());
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        unsigned milliseconds)
{
    return Datetime(hours, minutes, seconds, milliseconds);
}

inline

        Datetime
        Datetime::createTime(unsigned hours,
                unsigned minutes,
                unsigned seconds,
                unsigned milliseconds,
                Offset offset)
{
    Datetime dt(hours, minutes, seconds, milliseconds);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Milliseconds fractionOfSecond)
{
    return Datetime(hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Microseconds fractionOfSecond)
{
    return Datetime(hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Nanoseconds fractionOfSecond)
{
    return Datetime(hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Picoseconds fractionOfSecond)
{
    return Datetime(hours, minutes, seconds, fractionOfSecond);
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Milliseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Microseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Nanoseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime Datetime::createTime(unsigned hours,
        unsigned minutes,
        unsigned seconds,
        Picoseconds fractionOfSecond,
        Offset offset)
{
    Datetime dt(hours, minutes, seconds, fractionOfSecond);
    dt.setOffset(offset.d_minutesAheadOfUTC);
    return dt;
}

inline Datetime::Datetime()
{
    std::memset(&d_value, 0, sizeof(d_value));
    d_value.datetime.year = 1;
    d_value.datetime.month = 1;
    d_value.datetime.day = 1;
}

inline Datetime::Datetime(const Datetime& original)
    : d_value(original.d_value)
{
}

inline Datetime::Datetime(const blpapi_Datetime_t& newRawValue)
{
    d_value.datetime = newRawValue;
    d_value.picoseconds = 0;
}

inline Datetime::Datetime(const blpapi_HighPrecisionDatetime_t& newRawValue)
    : d_value(newRawValue)
{
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = 0;
    d_value.picoseconds = 0;
    d_value.datetime.parts = DatetimeParts::DATE | DatetimeParts::TIME;
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        unsigned newMilliSeconds)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(newMilliSeconds);
    d_value.picoseconds = 0;
    d_value.datetime.parts
            = DatetimeParts::DATE | DatetimeParts::TIMEFRACSECONDS;
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Milliseconds fractionOfSecond)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(fractionOfSecond.d_msec);
    d_value.picoseconds = 0;
    d_value.datetime.parts
            = DatetimeParts::DATE | DatetimeParts::TIMEFRACSECONDS;
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Microseconds fractionOfSecond)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(fractionOfSecond.d_usec / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            (fractionOfSecond.d_usec % 1000) * 1000 * 1000);
    d_value.datetime.parts
            = DatetimeParts::DATE | DatetimeParts::TIMEFRACSECONDS;
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Nanoseconds fractionOfSecond)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(
            fractionOfSecond.d_nsec / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            (fractionOfSecond.d_nsec % (1000 * 1000)) * 1000);
    d_value.datetime.parts
            = DatetimeParts::DATE | DatetimeParts::TIMEFRACSECONDS;
}

inline Datetime::Datetime(unsigned newYear,
        unsigned newMonth,
        unsigned newDay,
        unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Picoseconds fractionOfSecond)
{
    d_value.datetime.offset = 0;
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(
            fractionOfSecond.d_psec / 1000 / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            fractionOfSecond.d_psec % (1000 * 1000 * 1000));
    d_value.datetime.parts
            = DatetimeParts::DATE | DatetimeParts::TIMEFRACSECONDS;
}

inline Datetime::Datetime(unsigned newYear, unsigned newMonth, unsigned newDay)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setDate(newYear, newMonth, newDay);
}

inline Datetime::Datetime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        unsigned newMilliSeconds)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds, newMilliSeconds);
}

inline Datetime::Datetime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Milliseconds fractionOfSecond)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds, fractionOfSecond);
}

inline Datetime::Datetime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Microseconds fractionOfSecond)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds, fractionOfSecond);
}

inline Datetime::Datetime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Nanoseconds fractionOfSecond)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds, fractionOfSecond);
}

inline Datetime::Datetime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Picoseconds fractionOfSecond)
{
    std::memset(&d_value, 0, sizeof(d_value));
    setTime(newHours, newMinutes, newSeconds, fractionOfSecond);
}

inline Datetime& Datetime::operator=(const Datetime& rhs)
{
    d_value = rhs.d_value;
    return *this;
}

inline void Datetime::setDate(
        unsigned newYear, unsigned newMonth, unsigned newDay)
{
    d_value.datetime.day = static_cast<blpapi_UChar_t>(newDay);
    d_value.datetime.month = static_cast<blpapi_UChar_t>(newMonth);
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(newYear);
    d_value.datetime.parts |= DatetimeParts::DATE;
}

inline void Datetime::setTime(
        unsigned newHours, unsigned newMinutes, unsigned newSeconds)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = 0;
    d_value.picoseconds = 0;
    d_value.datetime.parts = static_cast<blpapi_UChar_t>(
            (d_value.datetime.parts & ~DatetimeParts::FRACSECONDS)
            | DatetimeParts::TIME);
}

inline void Datetime::setTime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        unsigned newMilliSeconds)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(newMilliSeconds);
    d_value.picoseconds = 0;
    d_value.datetime.parts |= DatetimeParts::TIMEFRACSECONDS;
}

inline void Datetime::setTime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Milliseconds fractionOfSecond)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(fractionOfSecond.d_msec);
    d_value.picoseconds = 0;
    d_value.datetime.parts |= DatetimeParts::TIMEFRACSECONDS;
}

inline void Datetime::setTime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Microseconds fractionOfSecond)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(fractionOfSecond.d_usec / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            fractionOfSecond.d_usec % 1000 * 1000 * 1000);
    d_value.datetime.parts |= DatetimeParts::TIMEFRACSECONDS;
}

inline void Datetime::setTime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Nanoseconds fractionOfSecond)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(
            fractionOfSecond.d_nsec / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            fractionOfSecond.d_nsec % (1000 * 1000) * 1000);
    d_value.datetime.parts |= DatetimeParts::TIMEFRACSECONDS;
}

inline void Datetime::setTime(unsigned newHours,
        unsigned newMinutes,
        unsigned newSeconds,
        Picoseconds fractionOfSecond)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(newHours);
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(newMinutes);
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(newSeconds);
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(
            fractionOfSecond.d_psec / 1000 / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            fractionOfSecond.d_psec % (1000 * 1000 * 1000));
    d_value.datetime.parts |= DatetimeParts::TIMEFRACSECONDS;
}

inline void Datetime::setOffset(short value)
{
    d_value.datetime.offset = value;
    d_value.datetime.parts |= DatetimeParts::OFFSET;
}

inline void Datetime::setYear(unsigned value)
{
    d_value.datetime.year = static_cast<blpapi_UInt16_t>(value);
    d_value.datetime.parts |= DatetimeParts::YEAR;
}

inline void Datetime::setMonth(unsigned value)
{
    d_value.datetime.month = static_cast<blpapi_UChar_t>(value);
    d_value.datetime.parts |= DatetimeParts::MONTH;
}

inline void Datetime::setDay(unsigned value)
{
    d_value.datetime.day = static_cast<blpapi_UChar_t>(value);
    d_value.datetime.parts |= DatetimeParts::DAY;
}

inline void Datetime::setHours(unsigned value)
{
    d_value.datetime.hours = static_cast<blpapi_UChar_t>(value);
    d_value.datetime.parts |= DatetimeParts::HOURS;
}

inline void Datetime::setMinutes(unsigned value)
{
    d_value.datetime.minutes = static_cast<blpapi_UChar_t>(value);
    d_value.datetime.parts |= DatetimeParts::MINUTES;
}

inline void Datetime::setSeconds(unsigned value)
{
    d_value.datetime.seconds = static_cast<blpapi_UChar_t>(value);
    d_value.datetime.parts |= DatetimeParts::SECONDS;
}

inline void Datetime::setMilliseconds(unsigned value)
{
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(value);
    d_value.picoseconds = 0;
    d_value.datetime.parts |= DatetimeParts::FRACSECONDS;
}

inline void Datetime::setFractionOfSecond(Milliseconds value)
{
    d_value.datetime.milliSeconds = static_cast<blpapi_UInt16_t>(value.d_msec);
    d_value.picoseconds = 0;
    d_value.datetime.parts |= DatetimeParts::FRACSECONDS;
}

inline void Datetime::setFractionOfSecond(Microseconds value)
{
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(value.d_usec / 1000);
    d_value.picoseconds
            = static_cast<blpapi_UInt32_t>(value.d_usec % 1000 * 1000 * 1000);
    d_value.datetime.parts |= DatetimeParts::FRACSECONDS;
}

inline void Datetime::setFractionOfSecond(Nanoseconds value)
{
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(value.d_nsec / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            value.d_nsec % (1000 * 1000) * 1000);
    d_value.datetime.parts |= DatetimeParts::FRACSECONDS;
}

inline void Datetime::setFractionOfSecond(Picoseconds value)
{
    d_value.datetime.milliSeconds
            = static_cast<blpapi_UInt16_t>(value.d_psec / 1000 / 1000 / 1000);
    d_value.picoseconds = static_cast<blpapi_UInt32_t>(
            value.d_psec % (1000 * 1000 * 1000));
    d_value.datetime.parts |= DatetimeParts::FRACSECONDS;
}

inline blpapi_Datetime_t& Datetime::rawValue() { return d_value.datetime; }

inline blpapi_HighPrecisionDatetime_t& Datetime::rawHighPrecisionValue()
{
    return d_value;
}

inline bool Datetime::hasParts(unsigned newParts) const
{
    return newParts == (d_value.datetime.parts & newParts);
}

inline unsigned Datetime::parts() const { return d_value.datetime.parts; }

inline unsigned Datetime::year() const { return d_value.datetime.year; }

inline unsigned Datetime::month() const { return d_value.datetime.month; }

inline unsigned Datetime::day() const { return d_value.datetime.day; }

inline unsigned Datetime::hours() const { return d_value.datetime.hours; }

inline unsigned Datetime::minutes() const { return d_value.datetime.minutes; }

inline unsigned Datetime::seconds() const { return d_value.datetime.seconds; }

inline unsigned Datetime::milliSeconds() const
{
    return d_value.datetime.milliSeconds;
}

inline unsigned Datetime::milliseconds() const
{
    return d_value.datetime.milliSeconds;
}

inline unsigned Datetime::microseconds() const
{
    return d_value.datetime.milliSeconds * 1000
            + d_value.picoseconds / 1000 / 1000;
}

inline unsigned Datetime::nanoseconds() const
{
    return d_value.datetime.milliSeconds * 1000 * 1000
            + d_value.picoseconds / 1000;
}

inline unsigned long long Datetime::picoseconds() const
{
    return d_value.datetime.milliSeconds * 1000LLU * 1000U * 1000U
            + d_value.picoseconds;
}

inline short Datetime::offset() const { return d_value.datetime.offset; }

inline const blpapi_Datetime_t& Datetime::rawValue() const
{
    return d_value.datetime;
}

inline const blpapi_HighPrecisionDatetime_t&
Datetime::rawHighPrecisionValue() const
{
    return d_value;
}

inline const Datetime::HighPrecision& Datetime::highPrecisionValue() const
{
    return d_value;
}

inline bool Datetime::isValid() const
{
    if ((hasParts(DatetimeParts::YEAR) || hasParts(DatetimeParts::MONTH)
                || hasParts(DatetimeParts::DAY))
            && !isValidDate(static_cast<int>(year()),
                    static_cast<int>(month()),
                    static_cast<int>(day()))) {
        return false;
    }
    if ((hasParts(DatetimeParts::HOURS) || hasParts(DatetimeParts::MINUTES)
                || hasParts(DatetimeParts::SECONDS)
                || hasParts(DatetimeParts::MILLISECONDS))
            && !isValidTime(static_cast<int>(hours()),
                    static_cast<int>(minutes()),
                    static_cast<int>(seconds()),
                    static_cast<int>(milliSeconds()))) {
        return false;
    }
    if (hasParts(DatetimeParts::FRACSECONDS)
            && (picoseconds() >= 1000LL * 1000 * 1000 * 1000)) {
        return false;
    }
    return true;
}

inline std::ostream& Datetime::print(
        std::ostream& stream, int level, int spacesPerLevel) const
{
    BLPAPI_CALL_HIGHPRECISIONDATETIME_PRINT(&d_value,
            StreamProxyOstream::writeToStream,
            &stream,
            level,
            spacesPerLevel);
    return stream;
}

inline bool operator==(const Datetime& lhs, const Datetime& rhs)
{
    if (lhs.parts() == rhs.parts()) {
        return (BLPAPI_CALL_HIGHPRECISIONDATETIME_COMPARE(
                        &lhs.rawHighPrecisionValue(),
                        &rhs.rawHighPrecisionValue())
                == 0);
    }
    return false;
}

inline bool operator!=(const Datetime& lhs, const Datetime& rhs)
{
    return !(lhs == rhs);
}

inline bool operator<(const Datetime& lhs, const Datetime& rhs)
{
    return (BLPAPI_CALL_HIGHPRECISIONDATETIME_COMPARE(
                    &lhs.rawHighPrecisionValue(), &rhs.rawHighPrecisionValue())
            < 0);
}

inline bool operator<=(const Datetime& lhs, const Datetime& rhs)
{
    return !(rhs < lhs);
}

inline bool operator>(const Datetime& lhs, const Datetime& rhs)
{
    return rhs < lhs;
}

inline bool operator>=(const Datetime& lhs, const Datetime& rhs)
{
    return !(lhs < rhs);
}

inline std::ostream& operator<<(std::ostream& stream, const Datetime& datetime)
{
    return datetime.print(stream, 0, -1);
}

// ------------------
// class DatetimeUtil
// ------------------

inline Datetime DatetimeUtil::fromTimePoint(
        const TimePoint& timePoint, Datetime::Offset offset)
{
    blpapi_HighPrecisionDatetime_t highPrecisionDatetime;
    BLPAPI_CALL_HIGHPRECISIONDATETIME_FROMTIMEPOINT(
            &highPrecisionDatetime, &timePoint, offset.d_minutesAheadOfUTC);
    return Datetime(highPrecisionDatetime);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_DATETIME
