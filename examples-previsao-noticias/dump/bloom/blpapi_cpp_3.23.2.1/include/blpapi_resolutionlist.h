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

/** \file blpapi_resolutionlist.h */
/** \defgroup blpapi_resolutionlist Component blpapi_resolutionlist
\brief Provide a representation of a list of topics.
\file blpapi_resolutionlist.h
\brief Provide a representation of a list of topics.
*/

#ifndef INCLUDED_BLPAPI_RESOLUTIONLIST
#define INCLUDED_BLPAPI_RESOLUTIONLIST

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_resolutionlist
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
 * <td>blpapi::ResolutionList</td>
 * <td>Represents a list of topics</td>
 * </tr>
 * </table>
 * \par
 * \sa  blpapi_event
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a list of topics that require
 * resolution.
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

#include <stddef.h>

struct blpapi_ResolutionList;
typedef struct blpapi_ResolutionList blpapi_ResolutionList_t;

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Element_t *blpapi_ResolutionList_extractAttributeFromResolutionSuccess(
        const blpapi_Message_t *message, const blpapi_Name_t *attribute);

BLPAPI_EXPORT
blpapi_ResolutionList_t *blpapi_ResolutionList_create(
        blpapi_ResolutionList_t *from);

BLPAPI_EXPORT
void blpapi_ResolutionList_destroy(blpapi_ResolutionList_t *list);

BLPAPI_EXPORT
int blpapi_ResolutionList_add(blpapi_ResolutionList_t *list,
        const char *topic,
        const blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_ResolutionList_addFromMessage(blpapi_ResolutionList_t *list,
        const blpapi_Message_t *topic,
        const blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_ResolutionList_addAttribute(
        blpapi_ResolutionList_t *list, const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_ResolutionList_correlationIdAt(const blpapi_ResolutionList_t *list,
        blpapi_CorrelationId_t *result,
        size_t index);

BLPAPI_EXPORT
int blpapi_ResolutionList_topicString(const blpapi_ResolutionList_t *list,
        const char **topic,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_ResolutionList_topicStringAt(
        const blpapi_ResolutionList_t *list, const char **topic, size_t index);

BLPAPI_EXPORT
int blpapi_ResolutionList_status(const blpapi_ResolutionList_t *list,
        int *status,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_ResolutionList_statusAt(
        const blpapi_ResolutionList_t *list, int *status, size_t index);

BLPAPI_EXPORT
int blpapi_ResolutionList_attribute(const blpapi_ResolutionList_t *list,
        blpapi_Element_t **element,
        const blpapi_Name_t *attribute,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_ResolutionList_attributeAt(const blpapi_ResolutionList_t *list,
        blpapi_Element_t **element,
        const blpapi_Name_t *attribute,
        size_t index);

BLPAPI_EXPORT
int blpapi_ResolutionList_message(const blpapi_ResolutionList_t *list,
        blpapi_Message_t **element,
        const blpapi_CorrelationId_t *id);

BLPAPI_EXPORT
int blpapi_ResolutionList_messageAt(const blpapi_ResolutionList_t *list,
        blpapi_Message_t **element,
        size_t index);

BLPAPI_EXPORT
int blpapi_ResolutionList_size(const blpapi_ResolutionList_t *list);

#ifdef __cplusplus
}

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_resolutionlist
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * Contains a list of topics that require resolution.
 *
 * Created from topic strings or from <code>TopicSubscribed</code> messages
 * This is passed to a resolve() call or resolveAsync() call on a
 * <code>ProviderSession</code>. It is updated and returned by the resolve()
 * call.
 */
/*!
 * See \ref blpapi_resolutionlist
 */
class ResolutionList {

    blpapi_ResolutionList_t *d_handle_p;

  public:
    enum Status {
        UNRESOLVED = BLPAPI_RESOLUTIONLIST_UNRESOLVED,
        ///< Not yet resolved.
        RESOLVED = BLPAPI_RESOLUTIONLIST_RESOLVED,
        ///< Resolved successfully.
        RESOLUTION_FAILURE_BAD_SERVICE
        = BLPAPI_RESOLUTIONLIST_RESOLUTION_FAILURE_BAD_SERVICE,
        ///< There is a problem with the resolution service. Contact service
        /// owners.
        /// See ResolutionFailure message for more details.

        RESOLUTION_FAILURE_SERVICE_AUTHORIZATION_FAILED
        = BLPAPI_RESOLUTIONLIST_RESOLUTION_FAILURE_SERVICE_AUTHORIZATION_FAILED,
        ///< Failed to access resolution service.
        /// See ResolutionFailure message for more details.

        RESOLUTION_FAILURE_BAD_TOPIC
        = BLPAPI_RESOLUTIONLIST_RESOLUTION_FAILURE_BAD_TOPIC,
        ///< Either the resolution request irrecoverably failed, or the
        /// resolution service rejected this topic.
        /// See ResolutionFailure message for more details.

        RESOLUTION_FAILURE_TOPIC_AUTHORIZATION_FAILED
        = BLPAPI_RESOLUTIONLIST_RESOLUTION_FAILURE_TOPIC_AUTHORIZATION_FAILED
        ///< Currently unused.
    };

    // CLASS METHODS
    static Element extractAttributeFromResolutionSuccess(
            Message const& message, Name const& attribute);
    /*!<
     * <strong>DEPRECATED</strong>: Attributes are no longer supported.
     *
     * Return the value of the value in the specified <code>message</code>
     * which represents the specified <code>attribute</code>. The
     * <code>message</code> must be a message of type "RESOLUTION_SUCCESS". The
     * <code>attribute</code> should be an attribute that was requested using
     * addAttribute() on the ResolutionList passed to the resolve() or
     * resolveAsync() that caused this RESOLUTION_SUCCESS message. If the
     * <code>attribute</code> is not present an empty Element is returned.
     */

    ResolutionList();
    /*!<
     *     Create an empty ResolutionList.
     */

    ResolutionList(const ResolutionList& original);
    /*!<
     *     Copy constructor.
     */

    virtual ~ResolutionList();
    /*!<
     *     Destroy this ResolutionList.
     */

    // MANIPULATORS

    virtual int add(const char *topic,
            const CorrelationId& correlationId = CorrelationId());
    /*!<
     * Add the specified <code>topic</code> to this list, optionally specifying
     * a <code>correlationId</code>. Returns 0 on success or negative number on
     * failure. After a successful call to add() the status for this entry is
     * UNRESOLVED_TOPIC.
     */

    virtual int add(Message const& topicSubscribedMessage,
            const CorrelationId& correlationId = CorrelationId());
    /*!<
     * Add the topic contained in the specified <code>TopicSubscribed</code>
     * message to this list, optionally specifying a
     * <code>correlationId</code>.  Returns 0 on success or a negative number
     * on failure. After a successful call to add() the status for this entry
     * is UNRESOLVED_TOPIC.
     */

    int addAttribute(const Name& attribute);
    /*!<
     * <strong>DEPRECATED</strong>: Attributes are no longer supported.
     *
     * Add the specified <code>attribute</code> to the list of attributes
     * requested during resolution for each topic in this ResolutionList.
     * Returns 0 on success or a negative number on failure.
     */

    // ACCESSORS

    virtual CorrelationId correlationIdAt(size_t index) const;
    /*!<
     * Returns the CorrelationId of the specified <code>index</code>th entry in
     * this ResolutionList. If <code>index</code> \>= size() an exception is
     * thrown.
     */

    virtual const char *topicString(const CorrelationId& correlationId) const;
    /*!<
     * Returns a pointer to the topic of the entry identified by the specified
     * <code>correlationId</code>. If the <code>correlationId</code> does not
     * identify an entry in this ResolutionList then an exception is thrown.
     */

    virtual const char *topicStringAt(size_t index) const;
    /*!<
     * Returns a pointer to the topic of the specified <code>index</code>th
     * entry. If <code>index</code> \>= size() an exception is thrown.
     */

    virtual int status(const CorrelationId& correlationId) const;
    /*!<
     * Returns the status of the entry in this ResolutionList identified by the
     * specified <code>correlationId</code>. This may be UNRESOLVED, RESOLVED,
     * RESOLUTION_FAILURE_BAD_SERVICE,
     * RESOLUTION_FAILURE_SERVICE_AUTHORIZATION_FAILED
     * RESOLUTION_FAILURE_BAD_TOPIC,
     * RESOLUTION_FAILURE_TOPIC_AUTHORIZATION_FAILED.  If the
     * <code>correlationId</code> does not identify an entry in this
     * ResolutionList then an exception is thrown.
     */

    virtual int statusAt(size_t index) const;
    /*!<
     * Returns the status of the specified <code>index</code>th entry in this
     * ResolutionList. This may be UNRESOLVED, RESOLVED,
     * RESOLUTION_FAILURE_BAD_SERVICE,
     * RESOLUTION_FAILURE_SERVICE_AUTHORIZATION_FAILED
     * RESOLUTION_FAILURE_BAD_TOPIC,
     * RESOLUTION_FAILURE_TOPIC_AUTHORIZATION_FAILED.  If <code>index</code>
     * \>= size() an exception is thrown.
     */

    Element attribute(
            const Name& attribute, const CorrelationId& correlationId) const;
    /*!<
     * <strong>DEPRECATED</strong>: Attributes are no longer supported.
     *
     * Returns the value for the specified <code>attribute</code> of the entry
     * in this ResolutionList identified by the specified
     * <code>correlationId</code>. The Element returned may be empty if the
     * resolution service cannot provide the attribute. If
     * <code>correlationId</code> does not identify an entry in this
     * ResolutionList or if the status of the entry identified by
     * <code>correlationId</code> is not RESOLVED an exception is thrown.
     */

    Element attributeAt(const Name& attribute, size_t index) const;
    /*!<
     * <strong>DEPRECATED</strong>: Attributes are no longer supported.
     *
     * Returns the value for the specified <code>attribute</code> of the
     * specified <code>index</code>th entry in this ResolutionList. The Element
     * returned may be empty if the resolution service cannot provide the
     * attribute. If <code>index</code> \>= size() or if the status of the
     * <code>index</code>th entry is not RESOLVED an exception is thrown.
     */

    virtual Message const message(const CorrelationId& correlationId) const;
    /*!<
     * Returns the value of the message received during resolution of the topic
     * identified by the specified <code>correlationId</code>. If
     * <code>correlationId</code> does not identify an entry in this
     * ResolutionList or if the status of the entry identify by
     * <code>correlationId</code> is not RESOLVED an exception is thrown.
     *
     * The message returned can be used when creating an instance of Topic.
     */

    virtual Message const messageAt(size_t index) const;
    /*!<
     * Returns the value of the message received during resolution of the
     * specified <code>index</code>th entry in this ResolutionList.  If
     * <code>index</code> \>= size() or if the status of the
     * <code>index</code>th entry is not RESOLVED an exception is thrown.
     *
     * The message returned can be used when creating an instance of Topic.
     */

    virtual size_t size() const;
    /*!<
     * Returns the number of entries in this list.
     */

    const blpapi_ResolutionList_t *impl() const;

    blpapi_ResolutionList_t *impl();
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// --------------------
// class ResolutionList
// --------------------

inline Element ResolutionList::extractAttributeFromResolutionSuccess(
        Message const&, Name const&)
{
    ExceptionUtil::throwOnError(BLPAPI_ERROR_UNSUPPORTED_OPERATION);

    // Unreachable code, previous statement throws.
    return Element();
}

inline ResolutionList::ResolutionList()
    : d_handle_p(blpapi_ResolutionList_create(0))
{
}

inline ResolutionList::ResolutionList(const ResolutionList& original)
    : d_handle_p(blpapi_ResolutionList_create(original.d_handle_p))
{
}

inline ResolutionList::~ResolutionList()
{
    blpapi_ResolutionList_destroy(d_handle_p);
}

inline int ResolutionList::add(
        const char *topic, const CorrelationId& correlationId)
{
    return blpapi_ResolutionList_add(d_handle_p, topic, &correlationId.impl());
}

inline int ResolutionList::add(Message const& topicSubscribedMessage,
        const CorrelationId& correlationId)
{
    return blpapi_ResolutionList_addFromMessage(
            d_handle_p, topicSubscribedMessage.impl(), &correlationId.impl());
}

inline int ResolutionList::addAttribute(const Name&)
{
    ExceptionUtil::throwOnError(BLPAPI_ERROR_UNSUPPORTED_OPERATION);

    // Unreachable code, previous statement throws.
    return BLPAPI_ERROR_UNSUPPORTED_OPERATION;
}

inline CorrelationId ResolutionList::correlationIdAt(size_t index) const
{
    blpapi_CorrelationId_t correlationId;
    ExceptionUtil::throwOnError(blpapi_ResolutionList_correlationIdAt(
            d_handle_p, &correlationId, index));

    return CorrelationId(correlationId);
}

inline const char *ResolutionList::topicString(
        const CorrelationId& correlationId) const
{
    const char *topic = 0;
    ExceptionUtil::throwOnError(blpapi_ResolutionList_topicString(
            d_handle_p, &topic, &correlationId.impl()));

    return topic;
}

inline const char *ResolutionList::topicStringAt(size_t index) const
{
    const char *topic = 0;
    ExceptionUtil::throwOnError(
            blpapi_ResolutionList_topicStringAt(d_handle_p, &topic, index));

    return topic;
}

inline int ResolutionList::status(const CorrelationId& correlationId) const
{
    int result = 0;
    ExceptionUtil::throwOnError(blpapi_ResolutionList_status(
            d_handle_p, &result, &correlationId.impl()));

    return result;
}

inline int ResolutionList::statusAt(size_t index) const
{
    int result = 0;
    ExceptionUtil::throwOnError(
            blpapi_ResolutionList_statusAt(d_handle_p, &result, index));

    return result;
}

inline Element ResolutionList::attribute(
        const Name&, const CorrelationId&) const
{
    ExceptionUtil::throwOnError(BLPAPI_ERROR_UNSUPPORTED_OPERATION);

    // Unreachable code, previous statement throws.
    return Element();
}

inline Element ResolutionList::attributeAt(const Name&, size_t) const
{
    ExceptionUtil::throwOnError(BLPAPI_ERROR_UNSUPPORTED_OPERATION);

    // Unreachable code, previous statement throws.
    return Element();
}

inline Message const ResolutionList::message(
        const CorrelationId& correlationId) const
{
    blpapi_Message_t *messageByCid = 0;
    ExceptionUtil::throwOnError(blpapi_ResolutionList_message(
            d_handle_p, &messageByCid, &correlationId.impl()));

    bool makeMessageCopyable = true;
    BLPAPI_CALL_MESSAGE_ADDREF(messageByCid);
    return Message(messageByCid, makeMessageCopyable);
}

inline Message const ResolutionList::messageAt(size_t index) const
{
    blpapi_Message_t *messageByIndex = 0;
    ExceptionUtil::throwOnError(blpapi_ResolutionList_messageAt(
            d_handle_p, &messageByIndex, index));

    bool makeMessageCopyable = true;
    BLPAPI_CALL_MESSAGE_ADDREF(messageByIndex);
    return Message(messageByIndex, makeMessageCopyable);
}

inline size_t ResolutionList::size() const
{
    return static_cast<size_t>(blpapi_ResolutionList_size(d_handle_p));
}

inline const blpapi_ResolutionList_t *ResolutionList::impl() const
{
    return d_handle_p;
}

inline blpapi_ResolutionList_t *ResolutionList::impl() { return d_handle_p; }

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_RESOLUTIONLIST
