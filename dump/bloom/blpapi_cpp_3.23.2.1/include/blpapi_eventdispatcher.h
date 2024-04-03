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

/** \file blpapi_eventdispatcher.h */
/** \defgroup blpapi_eventdispatcher Component blpapi_eventdispatcher
\brief Provide a dispatcher to dispatch events.
\file blpapi_eventdispatcher.h
\brief Provide a dispatcher to dispatch events.
*/

#ifndef INCLUDED_BLPAPI_EVENTDISPATCHER
#define INCLUDED_BLPAPI_EVENTDISPATCHER

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_eventdispatcher
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a dispatcher to dispatch events.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::EventDispatcher</td>
 * <td>Dispatches events from one or more Sessions through callbacks</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a dispatcher to dispatch events from
 * one or more <code>Session</code> through callbacks.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#include <stddef.h> // for size_t

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_EventDispatcher_t *blpapi_EventDispatcher_create(
        size_t numDispatcherThreads);

BLPAPI_EXPORT
void blpapi_EventDispatcher_destroy(blpapi_EventDispatcher_t *handle);

BLPAPI_EXPORT
int blpapi_EventDispatcher_start(blpapi_EventDispatcher_t *handle);

BLPAPI_EXPORT
int blpapi_EventDispatcher_stop(blpapi_EventDispatcher_t *handle, int async);

BLPAPI_EXPORT
int blpapi_EventDispatcher_dispatchEvents(blpapi_EventDispatcher_t *handle);

#ifdef __cplusplus
} // extern "C"

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_eventdispatcher
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * Dispatches events from one or more Sessions through callbacks
 *
 * EventDispatcher objects are optionally specified when Session
 * objects are constructed. A single EventDispatcher can be shared
 * by multiple Session objects.
 *
 * The EventDispatcher provides an event-driven interface,
 * generating callbacks from one or more internal threads for one
 * or more sessions.
 */
/*!
 * See \ref blpapi_eventdispatcher
 */
class EventDispatcher {

    blpapi_EventDispatcher_t *d_impl_p;

  private:
    // NOT IMPLEMENTED
    EventDispatcher(const EventDispatcher&);
    EventDispatcher& operator=(const EventDispatcher&);

  public:
    EventDispatcher(size_t numDispatcherThreads = 1);
    /*!<
     * Construct an EventDispatcher with the specified
     * <code>numDispatcherThreads</code>. If <code>numDispatcherThreads</code>
     * is 1 (the default) then a single internal thread is created to dispatch
     * events. If <code>numDispatcherThreads</code> is greater than 1 then an
     * internal pool of <code>numDispatcherThreads</code> threads is created to
     * dispatch events. The behavior is undefined if
     * <code>numDispatcherThreads</code> is 0.
     */

    ~EventDispatcher();
    /*!<
     * Destructor.
     */

    int start();
    /*!<
     * Start generating callbacks for events from sessions associated with this
     * EventDispatcher. Return 0 on success and a non zero value otherwise.
     */

    int stop(bool async = false);
    /*!<
     * Shutdown this event dispatcher object and stop generating
     * callbacks for events from sessions associated with it.  If the specified
     * <code>async</code> is false (the default) then this method blocks until
     * all current callbacks which were dispatched through this EventDispatcher
     * have completed.  Return 0 on success and a non zero value otherwise.
     *
     * Note: Calling stop with <code>async</code> of false from within a
     * callback dispatched by this EventDispatcher is undefined and may result
     * in a deadlock.
     */

    blpapi_EventDispatcher_t *impl() const;
    /*!<
     * Returns the internal implementation.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE AND TEMPLATE FUNCTION IMPLEMENTATIONS
// ============================================================================

// ---------------------
// class EventDispatcher
// ---------------------

inline EventDispatcher::EventDispatcher(size_t numDispatcherThreads)
    : d_impl_p(blpapi_EventDispatcher_create(numDispatcherThreads))
{
}

inline EventDispatcher::~EventDispatcher()
{
    blpapi_EventDispatcher_destroy(d_impl_p);
}

inline int EventDispatcher::start()
{
    return blpapi_EventDispatcher_start(d_impl_p);
}

inline int EventDispatcher::stop(bool async)
{
    return blpapi_EventDispatcher_stop(d_impl_p, async);
}

inline blpapi_EventDispatcher_t *EventDispatcher::impl() const
{
    return d_impl_p;
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // ifdef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_EVENTDISPATCHER
