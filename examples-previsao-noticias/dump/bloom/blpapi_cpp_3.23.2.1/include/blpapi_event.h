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

/** \file blpapi_event.h */
/** \defgroup blpapi_event Component blpapi_event
\brief A component which defines events related operations
\file blpapi_event.h
\brief A component which defines events related operations
*/

#ifndef INCLUDED_BLPAPI_EVENT
#define INCLUDED_BLPAPI_EVENT

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_event
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * A component which defines events related operations
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Event</td>
 * <td>an event resulting from a subscription or request.</td>
 * </tr>
 * <tr>
 * <td>blpapi::EventQueue</td>
 * <td>A construct to handle replies synchronously.</td>
 * </tr>
 * <tr>
 * <td>blpapi::MessageIterator</td>
 * <td>An iterator over the Messages within an Event.</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This file defines an <code>Event</code>. One or more <code>Event</code>s
 * are generated as a result of a subscription or a request.
 * <code>Event</code>s contain <code>Message</code> objects which can be
 * accessed using range based <code>for</code> loop or a
 * <code>MessageIterator</code>.
 * This file also defines a <code>EventQueue</code> for handling replies
 * synchronously.
 * \par
 * \par
 * <A NAME="usage"></A>
 * <A NAME="description.usage"></A>
 * <A NAME="3.1"> \par Usage: </A>
 * There are two ways to iterate the messages in an <code>Event</code>.
 * \code
 * for (Message msg : event) {
 *     ...
 * }
 * \endcode
 * OR
 * \code
 * MessageIterator iter(event);
 * while (iter.next()) {
 *     Message msg = iter.message();
 *     ...
 * }
 * \endcode
 * \par
 * The following code snippet shows a how a <code>EventQueue</code> is used
 * with a <code>generateToken</code> request. For any established session
 * <code>session</code> pass an <code>EventQueue</code> object
 * <code>tokenEventQueue</code> when calling <code>generateToken</code>.  All
 * Events in responses to <code>generateToken</code> request will be returned
 * in <code>tokenEventQueue</code>.
 * \code
 * //...
 * EventQueue tokenEventQueue;
 * session->generateToken(CorrelationId(), &tokenEventQueue);
 * \endcode
 * \par
 * Synchronously read the response <code>event</code> and parse over messages
 * \code
 * Event event = tokenEventQueue.nextEvent();
 * if (event.eventType() == Event::TOKEN_STATUS) {
 *      for (Message msg : event) {
 *          //...
 *      }
 * }
 * \endcode
 */
/** @} */
/** @} */

#include <blpapi_call.h>
#include <blpapi_defs.h>
#include <blpapi_message.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
int blpapi_Event_eventType(const blpapi_Event_t *event);

BLPAPI_EXPORT
int blpapi_Event_addRef(const blpapi_Event_t *event);

BLPAPI_EXPORT
int blpapi_Event_release(const blpapi_Event_t *event);

BLPAPI_EXPORT
blpapi_EventQueue_t *blpapi_EventQueue_create(void);

BLPAPI_EXPORT
int blpapi_EventQueue_destroy(blpapi_EventQueue_t *eventQueue);

BLPAPI_EXPORT
blpapi_Event_t *blpapi_EventQueue_nextEvent(
        blpapi_EventQueue_t *eventQueue, int timeout);

BLPAPI_EXPORT
int blpapi_EventQueue_purge(blpapi_EventQueue_t *eventQueue);

BLPAPI_EXPORT
int blpapi_EventQueue_tryNextEvent(
        blpapi_EventQueue_t *eventQueue, blpapi_Event_t **eventPointer);

BLPAPI_EXPORT
blpapi_MessageIterator_t *blpapi_MessageIterator_create(
        const blpapi_Event_t *event);

BLPAPI_EXPORT
void blpapi_MessageIterator_destroy(blpapi_MessageIterator_t *iterator);

BLPAPI_EXPORT
int blpapi_MessageIterator_next(
        blpapi_MessageIterator_t *iterator, blpapi_Message_t **result);

BLPAPI_EXPORT
int blpapi_MessageIterator_addRef(const blpapi_MessageIterator_t *iterator);

#ifdef __cplusplus
}

#include <cassert>
#include <utility>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_event
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 *     A single event resulting from a subscription or a request.
 *
 *     Event objects are created by the API and passed to the
 *     application either through a registered EventHandler or
 *     EventQueue or returned from the Session::nextEvent()
 *     method. Event objects contain Message objects which can be
 *     accessed using a MessageIterator.
 *
 *     The Event object is a handle to an event. The event is the
 *     basic unit of work provided to applications. Each Event object
 *     consists of an EventType attribute and zero or more Message
 *     objects. The underlying event data including the messages is
 *     reference counted - as long as at least one Event object still
 *     exists then the underlying data will not be freed.
 */
/*!
 * See \ref blpapi_event
 */
class Event {

    blpapi_Event_t *d_impl_p;

  public:
    /// The possible types of event
    enum EventType {
        ADMIN = BLPAPI_EVENTTYPE_ADMIN,
        ///< Admin event
        SESSION_STATUS = BLPAPI_EVENTTYPE_SESSION_STATUS,
        ///< Status updates for a session.
        SUBSCRIPTION_STATUS = BLPAPI_EVENTTYPE_SUBSCRIPTION_STATUS,
        ///< Status updates for a subscription.
        REQUEST_STATUS = BLPAPI_EVENTTYPE_REQUEST_STATUS,
        ///< Status updates for a request.
        RESPONSE = BLPAPI_EVENTTYPE_RESPONSE,
        ///< The final (possibly only) response to a request.
        PARTIAL_RESPONSE = BLPAPI_EVENTTYPE_PARTIAL_RESPONSE,
        ///< A partial response to a request.
        SUBSCRIPTION_DATA = BLPAPI_EVENTTYPE_SUBSCRIPTION_DATA,
        ///< Data updates resulting from a subscription.
        SERVICE_STATUS = BLPAPI_EVENTTYPE_SERVICE_STATUS,
        ///< Status updates for a service.
        TIMEOUT = BLPAPI_EVENTTYPE_TIMEOUT,
        ///< An Event returned from Session::nextEvent() if it timed out.
        AUTHORIZATION_STATUS = BLPAPI_EVENTTYPE_AUTHORIZATION_STATUS,
        ///< Status updates for user authorization.
        RESOLUTION_STATUS = BLPAPI_EVENTTYPE_RESOLUTION_STATUS,
        ///< Status updates for a resolution operation.
        TOPIC_STATUS = BLPAPI_EVENTTYPE_TOPIC_STATUS,
        ///< Status updates about topics for service providers.
        TOKEN_STATUS = BLPAPI_EVENTTYPE_TOKEN_STATUS,
        ///< Status updates for a generate token request.
        REQUEST = BLPAPI_EVENTTYPE_REQUEST,
        ///< %Request event. Provided to ProviderSession only.
        UNKNOWN = -1
    };

    /*!
     * An input iterator that iterates the messages in an <code>Event</code>
     * sequentially. It only guarantees validity for single pass
     * algorithms which pass through an iterator position once at
     * most. Once an iterator has been incremented, all copies of its
     * previous value may be invalidated.
     *
     * Changes to the `Event` invalidate any iterator obtained from it.
     */
    class iterator {
        // DATA
        blpapi_MessageIterator_t *d_impl_p;
        Message d_currentMessage;

      public:
        // TYPES
        using difference_type = std::ptrdiff_t;
        using value_type = Message;
        using pointer = Message *;
        using reference = Message&;
        using iterator_category = std::input_iterator_tag;

        // CREATORS
        iterator();
        /*!< Construct an empty iterator. */

        iterator(const Event& event);
        /*!<
         * Construct an iterator to iterate the messages in the specified
         * <code>event</code>.
         */

        iterator(const iterator& original);
        /*!<
         * Construct an iterator with the same value as the `original`
         * iterator.  Note that the iterator is a single-pass input iterator,
         * incrementing one of the two copies will impact the other copy.
         */

        ~iterator();

        // MANIPULATORS
        iterator& operator=(const iterator& original);
        /*!<
         * Assign the value of the `original` iterator to this iterator.
         * Note that the iterator is a single-pass input iterator, incrementing
         * one of the two copies will impact the other copy.
         */

        iterator& operator++();
        /*!<
         * Iterate over the next message in the event. Note that this operation
         * is relatively expensive as it will *decode* the next message in the
         * event.  Returns a reference to this iterator.
         */

        iterator operator++(int);
        /*!<
         * Iterate over the next message in the event and return a copy of the
         * original value of this iterator.  Note that this operation is
         * relatively expensive as it will *decode* the next message in the
         * event.  Also note that this is a single-pass input iterator,
         * incremeting one of the two copies will impact the other iterator.
         */

        void swap(iterator& other);
        /*!<
         * Swap the contents of `this` iterator and the `other` iterator.
         */

        // ACCESSORS
        const Message& operator*() const noexcept;
        const Message *operator->() const noexcept;

        // FRIENDS
        friend bool operator==(const iterator& lhs, const iterator& rhs);
    };

    Event();
    /*!<
     *     Construct an uninitialized Event. The only valid operations
     *     on an uninitialized Event are assignment, isValid() and
     *     destruction.
     */

    Event(blpapi_Event_t *handle);

    Event(const Event& original);
    /*!<
     *     Copy constructor. This performs a shallow copy, increasing
     *     the reference count on the actual data underlying this
     *     handle.
     */

    ~Event();
    /*!<
     *     Destructor. If this is the last reference to this Event
     *     then the underlying data and Iterators into the Event are
     *     invalidated, but Message objects remain valid.
     */

    Event& operator=(const Event& rhs);
    /*!<
     *     Assignment operator. This performs a shallow assignment,
     *     increasing the reference count on the actual data
     *     underlying this handle.
     */

    EventType eventType() const;
    /*!<
     *     Return the type of messages contained by this Event.
     */

    bool isValid() const;
    /*!<
     *     Return true if this Event is a valid event.
     */

    blpapi_Event_t *impl() const;

    iterator begin() const;
    iterator end() const;
};

// FREE OPERATORS
bool operator==(const Event::iterator& lhs, const Event::iterator& rhs);
/*!<
 * Return true if the specified <code>lhs</code> and <code>rhs</code> are the
 * same iterator, or both are end iterators.
 */

bool operator!=(const Event::iterator& lhs, const Event::iterator& rhs);
/*!<
 * Return true if the specified <code>lhs</code> and <code>rhs</code> are not
 * equal.
 */

/*!
 *     A construct used to handle replies to request synchronously.
 *
 *     An EventQueue can be supplied when using Session::sendRequest()
 *     and Session::sendAuthorizationRequest() methods.
 *
 *     When a request is submitted an application can either handle
 *     the responses asynchronously as they arrive or use an
 *     EventQueue to handle all responses for a given request or
 *     requests synchronously. The EventQueue will only deliver
 *     responses to the request(s) it is associated with.
 */
/*!
 * See \ref blpapi_event
 */
class EventQueue {

    blpapi_EventQueue_t *d_handle_p;

  public:
    EventQueue();
    /*!<
     *     Construct an empty event queue.
     */

    virtual ~EventQueue();
    /*!<
     *     Destroy this event queue and cancel any pending request
     *     that are linked to this queue.
     */

    virtual Event nextEvent(int timeout = 0);
    /*!<
     * Returns the next Event available from the EventQueue. If the specified
     * <code>timeout</code> is zero this will wait forever for the next event.
     * If the specified <code>timeout</code> is non zero then if no Event is
     * available within the specified <code>timeout</code> in milliseconds an
     * Event with a type() of TIMEOUT will be returned.
     */

    virtual int tryNextEvent(Event *event);
    /*!<
     *     If the EventQueue is non-empty, load the next Event available
     *     into event and return 0 indicating success. If the EventQueue is
     *     empty, return a non-zero value with no effect on event or the
     *     the state of EventQueue. This method never blocks.
     */

    virtual void purge();
    /*!<
     *     Purges any Event objects in this EventQueue which have not
     *     been processed and cancel any pending requests linked to
     *     this EventQueue. The EventQueue can subsequently be
     *     re-used for a subsequent request.
     */

    blpapi_EventQueue_t *handle() const;
};

/*!
 *     An iterator over the Message objects within an Event.
 *
 *     MessageIterator objects are used to process the individual
 *     Message objects in an Event received in an EventHandler, from
 *     EventQueue::nextEvent() or from Session::nextEvent().
 *
 *     This class is used to iterate over each message in an
 *     Event. Changes to the Event invalidate the iterator. The user must
 *     ensure that the Event this iterator is created for is not destroyed
 *     before the iterator.
 */
/*!
 * See \ref blpapi_event
 */
class MessageIterator {

    blpapi_MessageIterator_t *d_impl_p;
    blpapi_Message_t *d_current_p;

  public:
    MessageIterator(const MessageIterator&) = delete;
    MessageIterator& operator=(const MessageIterator&) = delete;

    MessageIterator(const Event& event);
    /*!<
     *     Construct a forward iterator to iterate over the message in
     *     the specified <code>event</code> object. The MessageIterator is
     *     created in a state where next() must be called to advance
     *     it to the first item.
     */

    ~MessageIterator();
    /*!<
     *     Destructor.
     */

    bool next();
    /*!<
     *     Attempts to advance this MessageIterator to the next Message in this
     *     Event. Returns true on success, and false if there are no more
     *     messages. After next() returns true, isValid() will return true
     *     until the subsequent call to next(). After next() returns false,
     *     isValid() will always returns false.
     */

    bool isValid() const;
    /*!<
     *     Returns true if this iterator is currently positioned on a
     *     valid Message.  Returns false otherwise.
     */

    Message message(bool createClonable = false) const;
    /*!<
     * Returns the Message at the current position of this iterator. If the
     * specified <code>createClonable</code> flag is set, the internal handle
     * of the message returned is added a reference and the message can outlive
     * the call to next(). If the <code>createClonable</code> flag is set to
     * false, the use of message outside the scope of the iterator or after the
     * next() call is undefined. The behavior is undefined if isValid() returns
     * false.
     */
};

void swap(Event::iterator& lhs, Event::iterator& rhs);
//!< Swap the contents of the `lhs` and `rhs` iterators.

/** @} */
/** @} */

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

// -----------
// class Event
// -----------

inline Event::Event()
    : d_impl_p(0)
{
}

inline Event::Event(blpapi_Event_t *handle)
    : d_impl_p(handle)
{
}

inline Event::Event(const Event& original)
    : d_impl_p(original.d_impl_p)
{
    if (d_impl_p) {
        blpapi_Event_addRef(d_impl_p);
    }
}

inline Event::~Event()
{
    if (d_impl_p) {
        blpapi_Event_release(d_impl_p);
    }
}

inline Event& Event::operator=(const Event& rhs)
{
    using std::swap;

    Event tmp(rhs);
    swap(tmp.d_impl_p, d_impl_p);

    return *this;
}

inline Event::EventType Event::eventType() const
{
    return (EventType)blpapi_Event_eventType(d_impl_p);
}

inline bool Event::isValid() const { return d_impl_p ? true : false; }

inline blpapi_Event_t *Event::impl() const { return d_impl_p; }

inline Event::iterator Event::begin() const { return iterator(*this); }

inline Event::iterator Event::end() const { return iterator(); }

// ----------------
// class EventQueue
// ----------------

inline EventQueue::EventQueue() { d_handle_p = blpapi_EventQueue_create(); }

inline EventQueue::~EventQueue() { blpapi_EventQueue_destroy(d_handle_p); }

inline Event EventQueue::nextEvent(int timeout)
{
    return blpapi_EventQueue_nextEvent(d_handle_p, timeout);
}

inline int EventQueue::tryNextEvent(Event *event)
{
    assert(event);

    blpapi_Event_t *impl = 0;
    int ret = blpapi_EventQueue_tryNextEvent(d_handle_p, &impl);
    if (0 == ret) {
        *event = Event(impl);
    }
    return ret;
}

inline void EventQueue::purge() { blpapi_EventQueue_purge(d_handle_p); }

inline blpapi_EventQueue_t *EventQueue::handle() const { return d_handle_p; }

// ---------------------
// class MessageIterator
// ---------------------

inline MessageIterator::MessageIterator(const Event& event)
    : d_impl_p(nullptr)
    , d_current_p(nullptr)
{
    d_impl_p = blpapi_MessageIterator_create(event.impl());
}

inline MessageIterator::~MessageIterator()
{
    blpapi_MessageIterator_destroy(d_impl_p);
}

inline bool MessageIterator::next()
{
    return !blpapi_MessageIterator_next(d_impl_p, &d_current_p);
}

inline bool MessageIterator::isValid() const
{
    return d_current_p ? true : false;
}

inline Message MessageIterator::message(bool createClonable) const
{
    if (createClonable) {
        BLPAPI_CALL_MESSAGE_ADDREF(d_current_p);
    }
    return Message(d_current_p, createClonable);
}

// --------------------------
// class Event::iterator
// --------------------------

inline Event::iterator::iterator()
    : d_impl_p(nullptr)
    , d_currentMessage(nullptr)
{
}

inline Event::iterator::iterator(const Event& event)
    : iterator()
{
    if (event.impl()) {
        d_impl_p = blpapi_MessageIterator_create(event.impl());
        ++(*this);
    }
}

inline Event::iterator::iterator(const iterator& original)
    : d_impl_p(original.d_impl_p)
    , d_currentMessage(original.d_currentMessage)
{
    if (d_impl_p) {
        BLPAPI_CALL(blpapi_MessageIterator_addRef)(d_impl_p);
    }
}

inline Event::iterator::~iterator()
{
    blpapi_MessageIterator_destroy(d_impl_p);
}

inline Event::iterator& Event::iterator::operator=(const iterator& original)
{
    auto copy(original);
    copy.swap(*this);
    return *this;
}

inline const Message& Event::iterator::operator*() const noexcept
{
    return d_currentMessage;
}

inline const Message *Event::iterator::operator->() const noexcept
{
    return &d_currentMessage;
}

inline Event::iterator& Event::iterator::operator++()
{
    d_currentMessage = Message(nullptr);

    blpapi_Message_t *nextMessage = nullptr;
    blpapi_MessageIterator_next(d_impl_p, &nextMessage);
    d_currentMessage = Message(nextMessage);

    return *this;
}

inline Event::iterator Event::iterator::operator++(int)
{
    auto copy = *this;
    ++(*this);
    return copy;
}

inline void Event::iterator::swap(iterator& other)
{
    using std::swap;
    swap(d_impl_p, other.d_impl_p);
    swap(d_currentMessage, other.d_currentMessage);
}

} // close namespace blpapi

inline bool blpapi::operator==(
        Event::iterator const& lhs, Event::iterator const& rhs)
{
    if (&lhs == &rhs) {
        return true;
    }

    if (lhs.d_impl_p == rhs.d_impl_p
            && lhs.d_currentMessage.impl() == rhs.d_currentMessage.impl()) {
        return true;
    }

    const bool lend = !lhs.d_impl_p || !lhs.d_currentMessage.impl();
    const bool rend = !rhs.d_impl_p || !rhs.d_currentMessage.impl();

    return lend && rend;
}

inline bool blpapi::operator!=(
        Event::iterator const& lhs, Event::iterator const& rhs)
{
    return !(lhs == rhs);
}

inline void blpapi::swap(Event::iterator& lhs, Event::iterator& rhs)
{
    lhs.swap(rhs);
}

} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_EVENT
