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

/** \file blpapi_timepoint.h */
/** \defgroup blpapi_timepoint Component blpapi_timepoint
\brief Provide a time point with respect to an epoch
\file blpapi_timepoint.h
\brief Provide a time point with respect to an epoch
*/

#ifndef INCLUDED_BLPAPI_TIMEPOINT
#define INCLUDED_BLPAPI_TIMEPOINT
/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_timepoint
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a time point with respect to an epoch
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::TimePoint</td>
 * <td>a fixed moment in a linear model of time</td>
 * </tr>
 * <tr>
 * <td>blpapi::TimePointUtil</td>
 * <td>namespace for <code>TimePoint</code> Utility functions</td>
 * </tr>
 * </table>
 * \par
 * \sa  blpapi_highresolutionclock, blpapi_datetime
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component provides a representation of a fixed moment in
 * a strict linear model of time. A function to measure the distance between
 * two such moments is provided. Note that such a moment is not associated
 * with any particular calendar or wall-clock conventions---see
 * <code>blpapi_datetime</code> for such representations (and for functions to
 * apply such conventions to an existing time point).
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_timepoint
 * @{
 */
/*!
 * This struct provides an <em>in-core</em> <em>value</em> <em>semantic</em>
 * type for representing a single moment in time, assuming a simple linear
 * model of time. The precision of such representations is guaranteed to be at
 * least at the granularity of nanoseconds, but only times relatively near
 * (within a few years of) the current moment are guaranteed to be
 * representable. The actual implementation of a time point is
 * implementation-defined and opaque to client code; in particular, time points
 * can <em>not</em> be transferred between processes. (The SDK reserves the
 * right to alter the epoch used as a base from run to run.) Clients wishing to
 * persist time points should use the
 * <code>TimePointUtil::nanosecondsBetween</code> function to measure distance
 * from a known epoch value, or convert the time point to some standard
 * calendar and wall-clock convention (e.g.  <code>blpapi::Datetime</code>).
 */
/*!
 * See \ref blpapi_timepoint
 */
struct blpapi_TimePoint {

    blpapi_Int64_t d_value;
};

typedef struct blpapi_TimePoint blpapi_TimePoint_t;

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
long long blpapi_TimePointUtil_nanosecondsBetween(
        const blpapi_TimePoint_t *start, const blpapi_TimePoint_t *end);
/*!<
 * Return the difference between <code>start</code> and <code>end</code>
 * <code>TimePoint</code> objects. The returned value is in nanoseconds
 * representing <code>end - start</code>.
 */

#ifdef __cplusplus
}

namespace BloombergLP {
namespace blpapi {

// ================
// struct TimePoint
// ================

typedef blpapi_TimePoint_t TimePoint;

/*!
 * This provides a namespace for <code>TimePoint</code> utility functions.
 */
/*!
 * See \ref blpapi_timepoint
 */
struct TimePointUtil {

    static long long nanosecondsBetween(
            const TimePoint& start, const TimePoint& end);
    /*!<
     * Return the difference between <code>start</code> and <code>end</code>
     * <code>TimePoint</code> objects. The returned value is in nanoseconds
     * representing <code>end - start</code>.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE AND TEMPLATE FUNCTION IMPLEMENTATIONS
// ============================================================================

// --------------------
// struct TimePointUtil
// --------------------

inline long long TimePointUtil::nanosecondsBetween(
        const TimePoint& start, const TimePoint& end)
{
    return BLPAPI_CALL_TIMEPOINTUTIL_NANOSECONDSBETWEEN(&start, &end);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_TIMEPOINT
