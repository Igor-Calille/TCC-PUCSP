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

/** \file blpapi_highresolutionclock.h */
/** \defgroup blpapi_highresolutionclock Component blpapi_highresolutionclock
\brief Provide a high resolution clock.
\file blpapi_highresolutionclock.h
\brief Provide a high resolution clock.
*/

#ifndef INCLUDED_BLPAPI_HIGHRESOLUTIONCLOCK
#define INCLUDED_BLPAPI_HIGHRESOLUTIONCLOCK
/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_highresolutionclock
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a high resolution clock.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::HighResolutionClock</td>
 * <td>a high resolution clock</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component provides a way to access the current time as a
 * <code>blpapi::TimePoint</code> value.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
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

BLPAPI_EXPORT
int blpapi_HighResolutionClock_now(blpapi_TimePoint_t *timePoint);
/*!<
 * Load the current time into the specified <code>timePoint</code> and return
 * zero, or leave timePoint unchanged and return a non-zero value.
 */
#ifdef __cplusplus
}

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_highresolutionclock
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * This utility struct provides a source for the current moment in time as a
 * <code>blpapi::TimePoint</code> object. This is currently intended for use
 * primarily in conjunction with the <code>blpapi::Message::timeReceived</code>
 * interfaces, to allow measurement of the amount of time a message spends in
 * the client event queue.
 */
/*!
 * See \ref blpapi_highresolutionclock
 */
struct HighResolutionClock {

    static TimePoint now();
    /*!<
     *     Return the current moment in time as a <code>TimePoint</code> value.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE AND TEMPLATE FUNCTION IMPLEMENTATIONS
// ============================================================================

// --------------------------
// struct HighResolutionClock
// --------------------------
inline TimePoint HighResolutionClock::now()
{
    TimePoint tp;
    BLPAPI_CALL_HIGHRESOLUTIONCLOCK_NOW(&tp);
    return tp;
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_HIGHRESOLUTIONCLOCK
