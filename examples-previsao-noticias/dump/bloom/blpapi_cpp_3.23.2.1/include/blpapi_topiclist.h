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

/** \file blpapi_topiclist.h */
/** \defgroup blpapi_topiclist Component blpapi_topiclist
\brief Provide a representation of a list of topics.
\file blpapi_topiclist.h
\brief Provide a representation of a list of topics.
*/

#ifndef INCLUDED_BLPAPI_TOPICLIST
#define INCLUDED_BLPAPI_TOPICLIST

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_topiclist
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a representation of a list of topics.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::TopicList</td>
 * <td>Represents a list of topics</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a list of topics which require
 * topic creation.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#ifndef INCLUDED_BLPAPI_CORRELATIONID
#include <blpapi_correlationid.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_ELEMENT
#include <blpapi_element.h>
#endif

#ifndef INCLUDED_BLPAPI_NAME
#include <blpapi_name.h>
#endif

#ifndef INCLUDED_BLPAPI_MESSAGE
#include <blpapi_message.h>
#endif

#ifndef INCLUDED_BLPAPI_RESOLUTIONLIST
#include <blpapi_resolutionlist.h>
#endif

struct blpapi_TopicList;
typedef struct blpapi_TopicList blpapi_TopicList_t;

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_TopicList_t *blpapi_TopicList_create(blpapi_TopicList_t *from);

BLPAPI_EXPORT
void blpapi_TopicList_destroy(blpapi_TopicList_t *list);

BLPAPI_EXPORT
int blpapi_TopicList_add(blpapi_TopicList_t *list,
        const char *topic,
        const blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_TopicList_addFromMessage(blpapi_TopicList_t *list,
        const blpapi_Message_t *topic,
        const blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_TopicList_correlationIdAt(const blpapi_TopicList_t *list,
        blpapi_CorrelationId_t *result,
        size_t index);

BLPAPI_EXPORT
int blpapi_TopicList_topicString(const blpapi_TopicList_t *list,
        const char **topic,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_TopicList_topicStringAt(
        const blpapi_TopicList_t *list, const char **topic, size_t index);

BLPAPI_EXPORT
int blpapi_TopicList_status(const blpapi_TopicList_t *list,
        int *status,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_TopicList_statusAt(
        const blpapi_TopicList_t *list, int *status, size_t index);

BLPAPI_EXPORT
int blpapi_TopicList_message(const blpapi_TopicList_t *list,
        blpapi_Message_t **element,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_TopicList_messageAt(const blpapi_TopicList_t *list,
        blpapi_Message_t **element,
        size_t index);

BLPAPI_EXPORT
int blpapi_TopicList_size(const blpapi_TopicList_t *list);

#ifdef __cplusplus
}

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_topiclist
 * @{
 */

namespace BloombergLP {
namespace blpapi {

class ResolutionList;

/*!
 *     Contains a list of topics which require creation.
 *
 *     Created from topic strings or from TOPIC_SUBSCRIBED or
 *     RESOLUTION_SUCCESS messages.
 *     This is passed to a createTopics() call or createTopicsAsync()
 *     call on a ProviderSession. It is updated and returned by the
 *     createTopics() call.
 */
/*!
 * See \ref blpapi_topiclist
 */
class TopicList {

    blpapi_TopicList_t *d_handle_p;

  public:
    enum Status {
        NOT_CREATED = BLPAPI_TOPICLIST_NOT_CREATED, ///< Not created
        CREATED = BLPAPI_TOPICLIST_CREATED, ///< Created successfully
        FAILURE = BLPAPI_TOPICLIST_FAILURE ///< Topic creation failed
    };

    // CLASS METHODS
    TopicList();
    /*!<
     *     Create an empty TopicList.
     */

    TopicList(const ResolutionList& original);
    /*!<
     *     Create a topic list from ResolutionList.
     *     User has previously resolved topics in ResolutionList
     *     and wants to now createTopics.
     */

    TopicList(const TopicList& original);
    /*!<
     *     Copy constructor.
     */

    virtual ~TopicList();
    /*!<
     *     Destroy this TopicList.
     */

    // MANIPULATORS
    virtual int add(const char *topic,
            const CorrelationId& correlationId = CorrelationId());
    /*!<
     *     Add the specified <code>topic</code> to this list, optionally
     *     specifying a <code>correlationId</code>. Returns 0 on success or
     *     negative number on failure. After a successful call to
     *     add() the status for this entry is NOT_CREATED.
     */

    virtual int add(Message const& message,
            const CorrelationId& correlationId = CorrelationId());
    /*!<
     * Add the topic contained in the specified
     * <code>topicSubscribedMessage</code> or
     * <code>resolutionSuccessMessage</code> to this list, optionally
     * specifying a <code>correlationId</code>. Returns 0 on success or a
     * negative number on failure. After a successful call to add() the status
     * for this entry is NOT_CREATED.
     */

    virtual CorrelationId correlationIdAt(size_t index) const;
    /*!<
     * Returns the CorrelationId of the specified <code>index</code>th entry in
     * this TopicList. If <code>index</code> \>= size() an exception is thrown.
     */

    virtual const char *topicString(const CorrelationId& correlationId) const;
    /*!<
     * Returns a pointer to the topic of the entry identified by the specified
     * <code>correlationId</code>. If the <code>correlationId</code> does not
     * identify an entry in this TopicList then an exception is thrown.
     */

    virtual const char *topicStringAt(size_t index) const;
    /*!<
     *     Returns a pointer to the topic of the specified <code>index</code>th
     *     entry. If <code>index</code> \>= size() an exception is thrown.
     */

    virtual int status(const CorrelationId& correlationId) const;
    /*!<
     *     Returns the status of the entry in this TopicList
     *     identified by the specified <code>correlationId</code>. This may be
     *     NOT_CREATED, CREATED and FAILURE.
     *     If the <code>correlationId</code> does not identify an entry in this
     *     TopicList then an exception is thrown.
     */

    virtual int statusAt(size_t index) const;
    /*!<
     * Returns the status of the specified <code>index</code>th entry in this
     * TopicList. This may be NOT_CREATED, CREATED and FAILURE. If
     * <code>index</code> \>= size() an exception is thrown.
     */

    virtual Message const message(const CorrelationId& correlationId) const;
    /*!<
     * Returns the value of the message received during creation of the topic
     * identified by the specified <code>correlationId</code>. If
     * <code>correlationId</code> does not identify an entry in this TopicList,
     * an exception is thrown.
     *
     * The message returned can be used when creating an instance of Topic.
     */

    virtual Message const messageAt(size_t index) const;
    /*!<
     * Returns the value of the message received during creation of the
     * specified <code>index</code>th entry in this TopicList. If
     * <code>index</code> \>= size(), an exception is thrown.
     *
     * The message returned can be used when creating an instance of Topic.
     */

    virtual size_t size() const;
    /*!<
     * Returns the number of entries in this list.
     */

    const blpapi_TopicList_t *impl() const;

    blpapi_TopicList_t *impl();
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// ---------------
// class TopicList
// ---------------

inline TopicList::TopicList()
    : d_handle_p(blpapi_TopicList_create(0))
{
}

inline TopicList::TopicList(const TopicList& original)
    : d_handle_p(blpapi_TopicList_create(original.d_handle_p))
{
}

inline TopicList::TopicList(const ResolutionList& original)
    : d_handle_p(
            blpapi_TopicList_create(reinterpret_cast<blpapi_TopicList_t *>(
                    const_cast<blpapi_ResolutionList_t *>(original.impl()))))
{
}

inline TopicList::~TopicList() { blpapi_TopicList_destroy(d_handle_p); }

inline int TopicList::add(
        const char *topic, const CorrelationId& correlationId)
{
    return blpapi_TopicList_add(d_handle_p, topic, &correlationId.impl());
}

inline int TopicList::add(
        const Message& newMessage, const CorrelationId& correlationId)
{
    return blpapi_TopicList_addFromMessage(
            d_handle_p, newMessage.impl(), &correlationId.impl());
}

inline CorrelationId TopicList::correlationIdAt(size_t index) const
{
    blpapi_CorrelationId_t correlationId;
    ExceptionUtil::throwOnError(blpapi_TopicList_correlationIdAt(
            d_handle_p, &correlationId, index));

    return CorrelationId(correlationId);
}

inline const char *TopicList::topicString(
        const CorrelationId& correlationId) const
{
    const char *topic = 0;
    ExceptionUtil::throwOnError(blpapi_TopicList_topicString(
            d_handle_p, &topic, &correlationId.impl()));

    return topic;
}

inline const char *TopicList::topicStringAt(size_t index) const
{
    const char *topic = 0;
    ExceptionUtil::throwOnError(
            blpapi_TopicList_topicStringAt(d_handle_p, &topic, index));

    return topic;
}

inline int TopicList::status(const CorrelationId& correlationId) const
{
    int result = 0;
    ExceptionUtil::throwOnError(blpapi_TopicList_status(
            d_handle_p, &result, &correlationId.impl()));

    return result;
}

inline int TopicList::statusAt(size_t index) const
{
    int result = 0;
    ExceptionUtil::throwOnError(
            blpapi_TopicList_statusAt(d_handle_p, &result, index));

    return result;
}

inline Message const TopicList::message(
        const CorrelationId& correlationId) const
{
    blpapi_Message_t *messageByCid = 0;
    ExceptionUtil::throwOnError(blpapi_TopicList_message(
            d_handle_p, &messageByCid, &correlationId.impl()));
    BLPAPI_CALL_MESSAGE_ADDREF(messageByCid);
    return Message(messageByCid, true);
}

inline Message const TopicList::messageAt(size_t index) const
{
    blpapi_Message_t *messageByIndex = 0;
    ExceptionUtil::throwOnError(
            blpapi_TopicList_messageAt(d_handle_p, &messageByIndex, index));

    BLPAPI_CALL_MESSAGE_ADDREF(messageByIndex);
    return Message(messageByIndex, true);
}

inline size_t TopicList::size() const
{
    return static_cast<size_t>(blpapi_TopicList_size(d_handle_p));
}

inline const blpapi_TopicList_t *TopicList::impl() const { return d_handle_p; }

inline blpapi_TopicList_t *TopicList::impl() { return d_handle_p; }

} // close namespace blpapi
} // close namespace BloombergLP

#endif // ifdef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_TOPICLIST
