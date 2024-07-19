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

/** \file blpapi_providersession.h */
/** \defgroup blpapi_providersession Component blpapi_providersession
\brief Provide a session that can be used for providing services
\file blpapi_providersession.h
\brief Provide a session that can be used for providing services
*/

#ifndef INCLUDED_BLPAPI_PROVIDERSESSION
#define INCLUDED_BLPAPI_PROVIDERSESSION

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_providersession
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a session that can be used for providing services
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::ProviderSession</td>
 * <td>Session with providing(publishing) services.</td>
 * </tr>
 * <tr>
 * <td>blpapi::ProviderEventHandler</td>
 * <td>Event handler for ProviderSession</td>
 * </tr>
 * <tr>
 * <td>blpapi::ServiceRegistrationOptions</td>
 * <td>Container holding registration options.</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  ProviderSession inherits from AbstractSession. In addition to
 * AbstractSession functionality, ProviderSession provides functions that are
 * needed to support publishing like <code>registerService</code>,
 * <code>createTopics</code> and <code>publish</code>.
 * \par
 * \par
 * <A NAME="topic_life_cycle"></A> <A NAME="description.topic_life_cycle"></A>
 * <A NAME="3.1"> \par Topic Life Cycle: </A>
 * A provider wishing to publish subscription data must explicitly open each
 * topic on which they publish using <code>ProviderSession::createTopics</code>
 * (or <code>ProviderSession::createTopicsAsync</code>). Creating a topic
 * prepares the distribution and caching infrastructure for new data associated
 * with the topic's resolved identifier. (Note that several different topics
 * could resolve to the same ID.) Independent of a topic's creation status is
 * its subscription status, i.e. whether there are subscribers ready to receive
 * the data published. A topic that is both created and subscribed is
 * <em>activated</em>.
 * \par
 * There are two models for managing topic creation: broadcast and
 * interactive. Broadcast publishers proactively call
 * <code>ProviderSession::createTopic*</code> for each topic on which they
 * intend to publish, while interactive publishers wait to receive a
 * <code>TopicSubscribed</code> message (within an <code>Event</code> of type
 * <code>Event::TOPIC_STATUS</code>) before calling
 * <code>ProviderSession::createTopic*</code> in response. Topics are resolved
 * before they are created---it is possible that multiple different topic
 * strings will map to the same underlying topic. See below for the behavior of
 * the SDK when the same topic is created multiple times.
 * \par
 * For applications using multiple broadcast publishers with the same priority
 * for the same service in the same group, successfully calling
 * <code>createTopic*</code> in a publisher does not mean that the topic will
 * be subscribed or activated as the infrastructure can select a different
 * publisher for the subscription.  That is, there's no guarantee of
 * <code>TopicSubscribed</code> and <code>TopicActivated</code> events
 * following <code>TopicCreated</code>. All broadcast publisher instances in
 * the same publisher group should call <code>createTopic*</code> for the same
 * topics and be able to handle <code>TopicSubscribed</code> before
 * <code>TopicCreated</code> is received.
 * \par
 * After <code>ProviderSession::createTopic*</code> is called, the publisher
 * will receive a <code>TopicCreated</code> message (within an
 * <code>Event::TOPIC_STATUS</code> event), and when there is at least one
 * subscriber to the topic the publisher will then receive a
 * <code>TopicActivated</code> message (also within an
 * <code>Event::TOPIC_STATUS</code> event). As subscribers come and go,
 * additional <code>TopicSubscribed</code>, <code>TopicActivated</code>,
 * <code>TopicUnsubscribed</code>, and <code>TopicDeactivated</code> messages
 * may be received by the publisher. A <code>Topic</code> object can be
 * retrieved from each of these messages using the
 * <code>ProviderSession::getTopic</code> method, and this object can be used
 * for subsequent calls to <code>EventFormatter::appendMessage</code> and
 * <code>ProviderSession::deleteTopic</code>. In the case that the same
 * resolved topic is created multiple times by a publisher using different
 * names, it is unspecified which of those names will be returned by
 * <code>Message::topicName</code> for these (or other) messages.
 * \par
 * If a publisher no longer intends to publish data on a topic, it can call
 * <code>ProviderSession::deleteTopic*</code> to free the internal caching and
 * distribution resources associated with the topic. When a resolved topic has
 * been deleted the same number of times that it has been created, a
 * <code>TopicDeleted</code> message will be delivered, preceded by
 * <code>TopicDeactivated</code> message. Existing subscriptions are not
 * affected and the publisher can call
 * <code>ProviderSession::createTopic*</code> to recreate the topic and proceed
 * publishing.
 * \par
 * If a topic is no longer supported, the publisher can call
 * <code>ProviderSession::terminateSubscriptionsOnTopics()</code> to terminate
 * all existing subscriptions and delete the topics.  Subscribers will be
 * delivered a <code>SubscriptionTerminated</code> message indicating that the
 * subscription has been terminated.
 * \par
 * Deregistering a service forces unsubscribes and deletes all topics
 * associated with that service on the publisher. The subscriptions will fail
 * over to another publisher if one is available.
 * \par
 * Note that <code>TopicActivated</code> and <code>TopicDeactivated</code>
 * messages are entirely redundant with <code>TopicCreated</code>,
 * <code>TopicSubscribed</code>, <code>TopicDeleted</code>, and
 * <code>TopicUnsubscribed</code> messages, and are provided only for the
 * convenience of publishers that do not maintain per-topic state.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_ABSTRACTSESSION
#include <blpapi_abstractsession.h>
#endif

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_CORRELATIONID
#include <blpapi_correlationid.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_EVENT
#include <blpapi_event.h>
#endif

#ifndef INCLUDED_BLPAPI_EVENTDISPATCHER
#include <blpapi_eventdispatcher.h>
#endif

#ifndef INCLUDED_BLPAPI_IDENTITY
#include <blpapi_identity.h>
#endif

#ifndef INCLUDED_BLPAPI_REQUEST
#include <blpapi_request.h>
#endif

#ifndef INCLUDED_BLPAPI_RESOLUTIONLIST
#include <blpapi_resolutionlist.h>
#endif

#ifndef INCLUDED_BLPAPI_SERVICE
#include <blpapi_service.h>
#endif

#ifndef INCLUDED_BLPAPI_SESSIONOPTIONS
#include <blpapi_sessionoptions.h>
#endif

#ifndef INCLUDED_BLPAPI_SUBSCRIPTIONLIST
#include <blpapi_subscriptionlist.h>
#endif

#ifndef INCLUDED_BLPAPI_TOPIC
#include <blpapi_topic.h>
#endif

#ifndef INCLUDED_BLPAPI_TOPICLIST
#include <blpapi_topiclist.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct blpapi_ServiceRegistrationOptions;
typedef struct blpapi_ServiceRegistrationOptions
        blpapi_ServiceRegistrationOptions_t;

typedef void (*blpapi_ProviderEventHandler_t)(blpapi_Event_t *event,
        blpapi_ProviderSession_t *session,
        void *userData);

BLPAPI_EXPORT
blpapi_ProviderSession_t *blpapi_ProviderSession_create(
        blpapi_SessionOptions_t *parameters,
        blpapi_ProviderEventHandler_t handler,
        blpapi_EventDispatcher_t *dispatcher,
        void *userData);

BLPAPI_EXPORT
void blpapi_ProviderSession_destroy(blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_start(blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_startAsync(blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_stop(blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_stopAsync(blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_nextEvent(blpapi_ProviderSession_t *session,
        blpapi_Event_t **eventPointer,
        unsigned int timeoutInMilliseconds);

BLPAPI_EXPORT
int blpapi_ProviderSession_tryNextEvent(
        blpapi_ProviderSession_t *session, blpapi_Event_t **eventPointer);

BLPAPI_EXPORT
int blpapi_ProviderSession_registerService(blpapi_ProviderSession_t *session,
        const char *serviceName,
        const blpapi_Identity_t *identity,
        blpapi_ServiceRegistrationOptions_t *registrationOptions);

BLPAPI_EXPORT
int blpapi_ProviderSession_activateSubServiceCodeRange(
        blpapi_ProviderSession_t *session,
        const char *serviceName,
        int begin,
        int end,
        int priority);

BLPAPI_EXPORT
int blpapi_ProviderSession_deactivateSubServiceCodeRange(
        blpapi_ProviderSession_t *session,
        const char *serviceName,
        int begin,
        int end);

BLPAPI_EXPORT
int blpapi_ProviderSession_registerServiceAsync(
        blpapi_ProviderSession_t *session,
        const char *serviceName,
        const blpapi_Identity_t *identity,
        blpapi_CorrelationId_t *correlationId,
        blpapi_ServiceRegistrationOptions_t *registrationOptions);

BLPAPI_EXPORT
int blpapi_ProviderSession_deregisterService(
        blpapi_ProviderSession_t *session, const char *serviceName);

BLPAPI_EXPORT
int blpapi_ProviderSession_resolve(blpapi_ProviderSession_t *session,
        blpapi_ResolutionList_t *resolutionList,
        int resolveMode,
        const blpapi_Identity_t *identity);

BLPAPI_EXPORT
int blpapi_ProviderSession_resolveAsync(blpapi_ProviderSession_t *session,
        const blpapi_ResolutionList_t *resolutionList,
        int resolveMode,
        const blpapi_Identity_t *identity);

BLPAPI_EXPORT
int blpapi_ProviderSession_createTopics(blpapi_ProviderSession_t *session,
        blpapi_TopicList_t *topicList,
        int resolveMode,
        const blpapi_Identity_t *identity);

BLPAPI_EXPORT
int blpapi_ProviderSession_createTopicsAsync(blpapi_ProviderSession_t *session,
        const blpapi_TopicList_t *topicList,
        int resolveMode,
        const blpapi_Identity_t *identity);

BLPAPI_EXPORT
int blpapi_ProviderSession_getTopic(blpapi_ProviderSession_t *session,
        const blpapi_Message_t *message,
        blpapi_Topic_t **topic);

BLPAPI_EXPORT
int blpapi_ProviderSession_createTopic(blpapi_ProviderSession_t *session,
        const blpapi_Message_t *message,
        blpapi_Topic_t **topic);

BLPAPI_EXPORT
int blpapi_ProviderSession_createServiceStatusTopic(
        blpapi_ProviderSession_t *session,
        const blpapi_Service_t *service,
        blpapi_Topic_t **topic);

BLPAPI_EXPORT
int blpapi_ProviderSession_deleteTopics(blpapi_ProviderSession_t *session,
        const blpapi_Topic_t **topics,
        size_t numTopics);

BLPAPI_EXPORT
int blpapi_ProviderSession_terminateSubscriptionsOnTopics(
        blpapi_ProviderSession_t *session,
        const blpapi_Topic_t **topics,
        size_t numTopics,
        const char *message);

BLPAPI_EXPORT
int blpapi_ProviderSession_publish(
        blpapi_ProviderSession_t *session, blpapi_Event_t *event);

BLPAPI_EXPORT
int blpapi_ProviderSession_sendResponse(blpapi_ProviderSession_t *session,
        blpapi_Event_t *event,
        int isPartialResponse);

BLPAPI_EXPORT
blpapi_AbstractSession_t *blpapi_ProviderSession_getAbstractSession(
        blpapi_ProviderSession_t *session);

BLPAPI_EXPORT
int blpapi_ProviderSession_flushPublishedEvents(
        blpapi_ProviderSession_t *session, int *allFlushed, int timeoutMsecs);

// ServiceRegistrationOptions

BLPAPI_EXPORT
blpapi_ServiceRegistrationOptions_t *blpapi_ServiceRegistrationOptions_create(
        void);

BLPAPI_EXPORT
blpapi_ServiceRegistrationOptions_t *
blpapi_ServiceRegistrationOptions_duplicate(
        const blpapi_ServiceRegistrationOptions_t *parameters);

BLPAPI_EXPORT
void blpapi_ServiceRegistrationOptions_destroy(
        blpapi_ServiceRegistrationOptions_t *parameters);

BLPAPI_EXPORT
void blpapi_ServiceRegistrationOptions_copy(
        blpapi_ServiceRegistrationOptions_t *lhs,
        const blpapi_ServiceRegistrationOptions_t *rhs);

// SUBSERVICE CODES
BLPAPI_EXPORT
int blpapi_ServiceRegistrationOptions_addActiveSubServiceCodeRange(
        blpapi_ServiceRegistrationOptions_t *parameters,
        int start,
        int end,
        int priority);

BLPAPI_EXPORT
void blpapi_ServiceRegistrationOptions_removeAllActiveSubServiceCodeRanges(
        blpapi_ServiceRegistrationOptions_t *parameters);

BLPAPI_EXPORT
void blpapi_ServiceRegistrationOptions_setGroupId(
        blpapi_ServiceRegistrationOptions_t *parameters,
        const char *groupId,
        unsigned int groupIdLength);

BLPAPI_EXPORT
int blpapi_ServiceRegistrationOptions_setServicePriority(
        blpapi_ServiceRegistrationOptions_t *parameters, int priority);

BLPAPI_EXPORT
void blpapi_ServiceRegistrationOptions_setPartsToRegister(
        blpapi_ServiceRegistrationOptions_t *parameters, int parts);

BLPAPI_EXPORT
int blpapi_ServiceRegistrationOptions_getGroupId(
        blpapi_ServiceRegistrationOptions_t *parameters,
        char *groupdIdBuffer,
        int *groupIdLength);

BLPAPI_EXPORT
int blpapi_ServiceRegistrationOptions_getServicePriority(
        blpapi_ServiceRegistrationOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_ServiceRegistrationOptions_getPartsToRegister(
        blpapi_ServiceRegistrationOptions_t *parameters);

#ifdef __cplusplus
}

#include <cassert>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_providersession
 * @{
 */

namespace BloombergLP {
namespace blpapi {

//! \cond INTERNAL
extern "C" inline void blpapi_providerEventHandlerAdapter(
        blpapi_Event_t *event,
        blpapi_ProviderSession_t *session,
        void *userData);
//! \endcond

class ProviderSession;
// ==========================
// class ProviderEventHandler
// ==========================

class ProviderEventHandler {
  public:
    virtual ~ProviderEventHandler() { }

    virtual bool processEvent(const Event& event, ProviderSession *session)
            = 0;
    /*!<
     * An implementation of <code>processEvent</code> should process the
     * specified <code>event</code> which originates from the specified
     * <code>session</code>. The return value is ignored.
     *
     * If the application wishes to further process the <code>messages</code>
     * in the <code>event</code> after returning from the
     * <code>processEvent()</code> call, the application must make a copy of
     * the <code>event</code> to ensure the underlying data is not freed.
     */
};

/*!
 * Contains the options which the user can specify when registering a service.
 *
 * To use non-default options to registerService, create a
 * ServiceRegistrationOptions instance and set the desired options and then
 * supply it when using the registerService interface.
 */
/*!
 * See \ref blpapi_providersession
 */
class ServiceRegistrationOptions {

    blpapi_ServiceRegistrationOptions_t *d_handle_p;

  public:
    /// Constants for specifying the priority to register services.
    ///
    /// Service providers can use any non-negative value as a priority
    /// for more granular control.
    enum ServiceRegistrationPriority {
        PRIORITY_LOW = BLPAPI_SERVICEREGISTRATIONOPTIONS_PRIORITY_LOW,
        ///< Low priority (`0`)
        PRIORITY_MEDIUM = BLPAPI_SERVICEREGISTRATIONOPTIONS_PRIORITY_MEDIUM,
        ///< Medium priority (`INT_MAX/2`)
        PRIORITY_HIGH = BLPAPI_SERVICEREGISTRATIONOPTIONS_PRIORITY_HIGH
        ///< High priority (`INT_MAX`)
    };

    /// Constants for specifying which part(s) of a service should be
    /// registered
    enum RegistrationParts {

        PART_PUBLISHING = BLPAPI_REGISTRATIONPARTS_PUBLISHING,
        ///< register to receive subscribe and unsubscribe messages

        PART_OPERATIONS = BLPAPI_REGISTRATIONPARTS_OPERATIONS,
        ///< register to receive the request types corresponding to each
        /// "operation" defined in the service metadata

        PART_SUBSCRIBER_RESOLUTION
        = BLPAPI_REGISTRATIONPARTS_SUBSCRIBER_RESOLUTION,
        ///< register to receive resolution requests (with message type
        /// <code>PermissionRequest</code>) from subscribers

        PART_PUBLISHER_RESOLUTION
        = BLPAPI_REGISTRATIONPARTS_PUBLISHER_RESOLUTION,
        ///< register to receive resolution requests (with message type
        /// <code>PermissionRequest</code>) from publishers (via
        /// <code>ProviderSession::createTopics</code>)

        PART_DEFAULT = BLPAPI_REGISTRATIONPARTS_DEFAULT
        ///< register the parts of the service implied by options
        /// specified in the service metadata
    };

    ServiceRegistrationOptions();
    /*!<
     *     Create ServiceRegistrationOptions with default options.
     */

    ServiceRegistrationOptions(const ServiceRegistrationOptions& original);
    /*!<
     *     Copy Constructor
     */

    ~ServiceRegistrationOptions();
    /*!<
     *     Destroy this ServiceRegistrationOptions.
     */

    ServiceRegistrationOptions& operator=(
            const ServiceRegistrationOptions& rhs);
    /*!<
     * Assign to this object the value of the specified <code>rhs</code>
     * object.
     */

    void setGroupId(const char *groupId, unsigned int groupIdLength);
    /*!<
     * Set the Group ID for the service to be registered to the specified char
     * array beginning at groupId with size groupIdLength.  If groupIdLength \>
     * MAX_GROUP_ID_SIZE (=64) only the first MAX_GROUP_ID_SIZE chars are
     * considered as Group Id.  Publishers with the same group id are treated
     * as equivalent and will participate in load balancing given the same
     * priority.  Publishers with different group ids provide different subsets
     * of the data and subscriptions will be established with one publisher
     * from each group.
     */

    int setServicePriority(int priority);
    /*!<
     * Set the priority with which a service will be registered to the
     * specified <code>priority</code>, where numerically greater values of
     * <code>priority</code> indicate higher priorities. The behavior is
     * undefined unless <code>priority</code> is non-negative. Note that while
     * the values of <code>enum ServiceRegistrationPriority</code> are suitable
     * for use here, any non-negative <code>priority</code> is acceptable.
     *
     * By default, a service will be registered with priority
     * <code>ServiceRegistrationPriority::PRIORITY_HIGH</code>.
     *
     * Note that this has no effect for resolution services.
     */

    void setPartsToRegister(int parts);
    /*!<
     * Set the parts of the service to be registered to the specified
     * <code>parts</code>, which must be a bitwise-or of the options provided
     * in <code>RegistrationParts</code>, above.  This option defaults to
     * <code>RegistrationParts::PARTS_DEFAULT</code>.
     */

    void addActiveSubServiceCodeRange(int begin, int end, int priority);
    /*!<
     * Advertise the service to be registered to receive, with the specified
     * <code>priority</code>, subscriptions that the resolver has mapped to a
     * service code between the specified <code>begin</code> and the specified
     * <code>end</code> values, inclusive. Numerically greater values of
     * <code>priority</code> indicate higher priorities. The behavior of this
     * function is undefined unless <code>0 \<= begin \<= end \< (1 \<\<
     * 24)</code>, and <code>priority</code> is non-negative.
     */

    void removeAllActiveSubServiceCodeRanges();
    /*!<
     * Remove all previously added sub-service code ranges.
     */

    int getGroupId(char *groupId, int *groupIdLength) const;
    /*!<
     * Copy the previously specified groupId at the memory location specified
     * by groupId and the set the size of the groupId returned at
     * groupIdLength. A Non-zero value indicates an error.  The behavior is
     * undefined if there is not enough space to copy the group Id to the
     * specified buffer.  Note that the groupId is not null terminated and
     * buffer for groupId needs to be at most MAX_GROUP_ID_SIZE.
     */

    int getServicePriority() const;
    /*!<
     * Return the priority with which a service will be registered.
     *
     * Note that the priority is used for both the publishing part and the
     * operations part. it is not supported for resolution part.
     */

    int getPartsToRegister() const;
    /*!<
     * Return the parts of the service to be registered.  See
     * <code>RegistrationParts</code>, above for additional details.
     */

    //! \cond INTERNAL
    blpapi_ServiceRegistrationOptions_t *handle() const;
    //! \endcond
};

/*!
 * This class provides a session that can be used for providing services.
 *
 * It inherits from AbstractSession. In addition to the AbstractSession
 * functionality a ProviderSession provides the following functions to
 * applications.
 *
 * A provider can register to provide services using
 * <code>ProviderSession::registerService*</code>. Before registering to
 * provide a service the provider must have established its identity. Then the
 * provider can create topics and publish events on topics. It can also get
 * requests from the event queue and send responses back.
 *
 * After users have registered a service they will start receiving subscription
 * requests (<code>TopicSubscribed</code> message in <code>TOPIC_STATUS</code>)
 * for topics which belong to the service. If the resolver has specified
 * <code>subServiceCode</code> for topics in <code>PermissionResponse</code>,
 * then only providers who have activated the <code>subServiceCode</code> will
 * get the subscription request. Where multiple providers have registered the
 * same service and sub-service code (if any), the provider that registered the
 * highest priority for the sub-service code will receive subscription
 * requests; if multiple providers have registered the same sub-service code
 * with the same priority (or the resolver did not set a sub-service code for
 * the subscription), the subscription request will be routed to one of the
 * providers with the highest service priority.
 */
/*!
 * See \ref blpapi_providersession
 */
class ProviderSession : public AbstractSession {

  public:
    typedef ::BloombergLP::blpapi::ProviderEventHandler EventHandler;

  private:
    blpapi_ProviderSession_t *d_handle_p;
    EventHandler *d_eventHandler_p;

  private:
    friend void blpapi_providerEventHandlerAdapter(blpapi_Event_t *event,
            blpapi_ProviderSession_t *session,
            void *userData);

    void dispatchEvent(const Event& event);

  private:
    // NOT IMPLEMENTED
    ProviderSession(const ProviderSession&);
    ProviderSession& operator=(const ProviderSession&);

  public:
    enum ResolveMode {
        AUTO_REGISTER_SERVICES = BLPAPI_RESOLVEMODE_AUTO_REGISTER_SERVICES,
        ///< Try to register services found in ResolutionList if necessary.
        DONT_REGISTER_SERVICES = BLPAPI_RESOLVEMODE_DONT_REGISTER_SERVICES
        ///< Fail to resolve a topic if the service has not already been
        /// registered.
    };

    explicit ProviderSession(const SessionOptions& options = SessionOptions(),
            EventHandler *eventHandler = 0,
            EventDispatcher *eventDispatcher = 0);
    /*!<
     * Construct a Session using the optionally specified <code>options</code>,
     * the optionally specified <code>eventHandler</code>, and the optionally
     * specified <code>eventDispatcher</code>.
     *
     * See the SessionOptions documentation for details on what can be
     * specified in the <code>options</code>.
     *
     * If <code>eventHandler</code> is not null then this Session will operate
     * in asynchronous mode; otherwise, the Session will operate in synchronous
     * mode.
     *
     * If <code>eventDispatcher</code> is null and a not null
     * <code>eventHandler</code> is provided, then the Session will create an
     * EventDispatcher for this Session which will use a single thread for
     * dispatching events. For more control over event dispatching a specific
     * instance of EventDispatcher can be supplied. This can be used to share a
     * single EventDispatcher amongst multiple Session objects.
     *
     * If an <code>eventDispatcher</code> is supplied which uses more than one
     * thread the Session will ensure that events which should be ordered are
     * passed to callbacks in a correct order. For example, partial response to
     * a request or updates to a single subscription.
     *
     * The behavior is undefined if <code>eventHandler</code> is null and the
     * <code>eventDispatcher</code> is not null.
     *
     * Each EventDispatcher uses its own thread or pool of threads so if you
     * want to ensure that a session which receives very large messages and
     * takes a long time to process them does not delay a session that receives
     * small messages and processes each one very quickly then give each one a
     * separate EventDispatcher.
     */

    //! \cond INTERNAL
    explicit ProviderSession(blpapi_ProviderSession_t *handle);
    //! \endcond

    virtual ~ProviderSession();
    /*!<
     *     Destructor.
     */

    // MANIPULATORS
    virtual bool start();
    /*!<
     *     \copydoc AbstractSession::start
     */

    virtual bool startAsync();
    /*!<
     *     \copydoc  AbstractSession::startAsync()
     */

    virtual void stop();
    /*!<
     *     \copydoc AbstractSession::stop()
     */

    virtual void stopAsync();
    /*!<
     *     \copydoc AbstractSession::stopAsync
     */

    virtual Event nextEvent(int timeout = 0);
    /*!<
     *     \copydoc AbstractSession::nextEvent
     */

    virtual int tryNextEvent(Event *event);
    /*!<
     *     \copydoc  AbstractSession::tryNextEvent()
     */

    virtual bool registerService(const char *serviceName,
            const Identity& providerIdentity = Identity(),
            const ServiceRegistrationOptions& registrationOptions
            = ServiceRegistrationOptions());
    /*!<
     * Attempt to register the service identified by the specified
     * <code>serviceName</code> and block until the service is either
     * registered successfully or has failed to be registered. The optionally
     * specified <code>providerIdentity</code> is used to verify permissions to
     * provide the service being registered. The optionally specified
     * <code>registrationOptions</code> is used to specify the group ID and
     * service priority of the service being registered.  Returns
     * <code>true</code> if the service is registered successfully and
     * <code>false</code> if the service cannot be registered successfully.
     *
     * The <code>serviceName</code> must be a full qualified service name.
     * That is it must be of the form
     * <code>//\<namespace\>/\<local-name\></code>.
     *
     * This function does not return until a SERVICE_STATUS event has been
     * generated. Note that if the session was created in asynchronous mode,
     * the event may be processed before the function returns.
     *
     * When <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual void activateSubServiceCodeRange(
            const char *serviceName, int begin, int end, int priority);
    /*!<
     * Register to receive, with the specified <code>priority</code>,
     * subscriptions for the specified <code>service</code> that the resolver
     * has mapped to a service code between the specified <code>begin</code>
     * and the specified <code>end</code> values, inclusive. Numerically
     * greater values of <code>priority</code> indicate higher priorities.
     * The behavior of this function is undefined unless <code>service</code>
     * has already been successfully registered, <code>0 \<= begin \<= end \<
     * (1 \<\< 24)</code>, and <code>priority</code> is non-negative.
     */

    virtual void deactivateSubServiceCodeRange(
            const char *serviceName, int begin, int end);
    /*!<
     * De-register to receive subscriptions for the specified
     * <code>service</code> that the resolver has mapped to a service code
     * between the specified <code>begin</code> and the specified
     * <code>end</code> values, inclusive. The behavior of this function is
     * undefined unless <code>service</code> has already been successfully
     * registered and <code>0 \<= begin \<= end \< (1 \<\< 24)</code>.
     */

    virtual CorrelationId registerServiceAsync(const char *serviceName,
            const Identity& providerIdentity = Identity(),
            const CorrelationId& correlationId = CorrelationId(),
            const ServiceRegistrationOptions& registrationOptions
            = ServiceRegistrationOptions());
    /*!<
     * Begin the process of registering the service identified by the specified
     * <code>serviceName</code> and return immediately. The optionally
     * specified <code>providerIdentity</code> is used to verify permissions to
     * provide the service being registered. The optionally specified
     * <code>correlationId</code> is used to identify <code>Message</code>
     * objects generated as a result of this call. Return the actual
     * <code>CorrelationId</code> object that will identify
     * <code>Message</code> objects. The optionally specified
     * <code>registrationOptions</code> is used to specify the group ID and
     * service priority of the service being registered.
     *
     * The <code>serviceName</code> must be a full qualified service name.
     * That is it must be of the form
     * <code>//\<namespace\>/\<local-name\></code>.
     *
     * The application must monitor events for a SERVICE_STATUS Event which
     * will be generated once the service has been successfully registered or
     * registration has failed.
     *
     * When <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual bool deregisterService(const char *serviceName);
    /*!<
     * Deregister the service, including all registered parts, identified by
     * the specified <code>serviceName</code>. The identity in the service
     * registration is reused to verify permissions for deregistration.  If the
     * service is not registered nor in pending registration, return false;
     * return true otherwise. If the service is in pending registration, cancel
     * the pending registration. If the service is registered, send a
     * deregistration request; generate TOPIC_STATUS events containing a
     * TopicUnsubscribed message for each subscribed topic, a TopicDeactivated
     * message for each active topic and a TopicDeleted for each created topic;
     * generate REQUEST_STATUS events containing a RequestFailure message for
     * each pending incoming request; and generate a SERVICE_STATUS Event
     * containing a ServiceDeregistered message. All published events on topics
     * created on this service will be ignored after this method returns.
     */

    virtual void resolve(ResolutionList *resolutionList,
            ResolveMode resolveMode = DONT_REGISTER_SERVICES,
            const Identity& providerIdentity = Identity());
    /*!<
     * Resolves the topics in the specified <code>resolutionList</code> and
     * updates the <code>resolutionList</code> with the results of the
     * resolution process. If the specified <code>resolveMode</code> is
     * ResolveMode::DONT_REGISTER_SERVICES (the default) then all the services
     * referenced in the topics in the <code>resolutionList</code> must already
     * have been registered using registerService(). If
     * <code>resolveMode</code> is ResolveMode::AUTO_REGISTER_SERVICES then the
     * specified <code>providerIdentity</code> should be supplied and
     * ProviderSession will automatically attempt to register any services
     * reference in the topics in the <code>resolutionList</code> that have not
     * already been registered. Once resolve() returns each entry in the
     * <code>resolutionList</code> will have been updated with a new status.
     *
     * Before resolve() returns one or more RESOLUTION_STATUS events and,
     * if <code>resolveMode</code> is ResolveMode::AUTO_REGISTER_SERVICES, zero
     * or more SERVICE_STATUS events are generated. If this is an asynchronous
     * ProviderSession then these Events may be processed by the processed by
     * the EventHandler before resolve() has returned.
     *
     * If <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual void resolveAsync(const ResolutionList& resolutionList,
            ResolveMode resolveMode = DONT_REGISTER_SERVICES,
            const Identity& providerIdentity = Identity());
    /*!<
     * Begin the resolution of the topics in the specified
     * <code>resolutionList</code>. If the specified <code>resolveMode</code>
     * is ResolveMode::DONT_REGISTER_SERVICES (the default) then all the
     * services referenced in the topics in the <code>resolutionList</code>
     * must already have been registered using registerService(). If
     * <code>resolveMode</code> is ResolveMode::AUTO_REGISTER_SERVICES then the
     * specified <code>providerIdentity</code> should be supplied and
     * ProviderSession will automatically attempt to register any services
     * reference in the topics in the <code>resolutionList</code> that have not
     * already been registered.
     *
     * One or more RESOLUTION_STATUS events will be delivered with the results
     * of the resolution. These events may be generated before or after
     * resolve() returns. If ResolveMode::AUTO_REGISTER_SERVICES is specified
     * SERVICE_STATUS events may also be generated before or after resolve()
     * returns.
     *
     * If <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual Topic getTopic(const Message& message);
    /*!<
     * Finds a previously created Topic object based on the specified
     * <code>message</code>. The <code>message</code> must be one of the
     * following types: TopicCreated, TopicActivated, TopicDeactivated,
     * TopicSubscribed, TopicUnsubscribed, TopicRecap.  If the
     * <code>message</code> is not valid then invoking isValid() on the
     * returned Topic will return false.
     */

    virtual Topic createServiceStatusTopic(const Service& service);
    /*!<
     * Creates a Service Status Topic which is to be used to provide service
     * status. On success invoking isValid() on the returned Topic will return
     * false.
     */

    virtual void publish(const Event& event);
    /*!<
     * Publish messages contained in the specified <code>event</code>.
     */

    virtual void sendResponse(
            const Event& event, bool isPartialResponse = false);
    /*!<
     * Send the response event for previously received request.  If
     * `isPartialResponse` is `false`, cleans up all the internal state
     * associated with the request.
     */

    virtual void createTopics(TopicList *topicList,
            ResolveMode resolveMode = DONT_REGISTER_SERVICES,
            const Identity& providerIdentity = Identity());
    /*!<
     * Creates the topics in the specified <code>topicList</code> and updates
     * the <code>topicList</code> with the results of the creation process. If
     * service needs to be registered, <code>providerIdentity</code> should be
     * supplied.  Once a call to this function returns, each entry in the
     * <code>topicList</code> will have been updated with a new topic creation
     * status.
     *
     * Before createTopics() returns one or more RESOLUTION_STATUS events, zero
     * or more SERVICE_STATUS events and one or more TOPIC_STATUS events are
     * generated.  If this is an asynchronous ProviderSession then these Events
     * may be processed by the registered EventHandler before createTopics()
     * has returned.
     *
     * If <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual void createTopicsAsync(const TopicList& topicList,
            ResolveMode resolveMode = DONT_REGISTER_SERVICES,
            const Identity& providerIdentity = Identity());
    /*!<
     * Creates the topics in the specified <code>topicList</code> and updates
     * the <code>topicList</code> with the results of the creation process. If
     * service needs to be registered, <code>providerIdentity</code> should be
     * supplied.
     *
     * One or more RESOLUTION_STATUS events, zero or more SERVICE_STATUS events
     * and one or more TOPIC_STATUS events are generated.  If this is an
     * asynchronous ProviderSession then these Events may be processed by the
     * registered EventHandler before createTopics() has returned.
     *
     * If <code>providerIdentity</code> is not provided, the session identity
     * will be used if it has been authorized.
     */

    virtual void deleteTopic(const Topic& topic);
    /*!<
     * Remove one reference from the specified <code>topic</code>.  If the
     * number of times this function,
     * <code>terminateSubscriptionsOnTopic</code>,
     * <code>updateResolvedTopics</code> or
     * <code>requireNewPermissionCheck</code> are called is the same as the
     * number of times <code>topic</code> was created by
     * <code>createTopics</code>, then <code>topic</code> is deleted: a
     * <code>TopicDeleted</code> message is delivered, preceded by
     * <code>TopicDeactivated</code> message (See \ref topic_life_cycle "Topic
     * Life Cycle" for additional details).  The behavior of this function is
     * undefined if <code>topic</code> has already been deleted.  Further, the
     * behavior is undefined if a provider attempts to publish a message on a
     * deleted topic.
     */

    virtual void deleteTopics(const std::vector<Topic>& topics);
    /*!<
     * Delete each topic in the specified <code>topics</code>. See
     * <code>deleteTopic(const Topic&)</code> for additional details.
     */

    virtual void deleteTopics(const Topic *topics, size_t numTopics);
    /*!<
     * Delete the first <code>numTopics</code> elements of the specified
     * <code>topics</code> array. See <code>deleteTopic(const Topic&)</code>
     * for additional details.
     */

    virtual void terminateSubscriptionsOnTopic(
            const Topic& topic, const char *message = 0);
    /*!<
     * Delete the specified <code>topic</code> (See <code>deleteTopic(const
     * Topic&)</code> for additional details).  Furthermore, proactively
     * terminate all current subscriptions on <code>topic</code>.  The
     * optionally specified <code>message</code> can be used to convey
     * additional information to subscribers regarding the termination.  This
     * message is contained in the <code>description</code> of
     * <code>reason</code> in a <code>SubscriptionTerminated</code> message.
     */

    virtual void terminateSubscriptionsOnTopics(
            const std::vector<Topic>& topics, const char *message = 0);
    /*!<
     * Terminate subscriptions on each topic in the specified
     * <code>topics</code>. See <code>terminateSubscriptionsOnTopic(const
     * Topic&, const char* message)</code> for additional details.
     */

    virtual void terminateSubscriptionsOnTopics(
            const Topic *topics, size_t numTopics, const char *message = 0);
    /*!<
     * Terminate subscriptions on the first <code>numTopics</code> topics in
     * the specified <code>topics</code>.  See
     * <code>terminateSubscriptionsOnTopic(const Topic&, const char*
     * message)</code> for additional details.
     */

    virtual bool flushPublishedEvents(int timeoutMsecs);
    /*!<
     * Wait at most <code>timeoutMsecs</code> milliseconds for all the
     * published events to be sent through the underlying channel. The method
     * returns either as soon as all the published events have been sent out or
     * when it has waited <code>timeoutMs</code> milliseconds. Return true if
     * all the published events have been sent; false otherwise. The behavior
     * is undefined unless the specified <code>timeoutMsecs</code> is a
     * non-negative value. When <code>timeoutMsecs</code> is 0, the method
     * checks if all the published events have been sent and returns without
     * waiting.
     */

    //! \cond INTERNAL
    blpapi_ProviderSession_t *handle() const;
    /*!<
     * Return the handle to this provider session
     */
    //! \endcond

    //! \name DEPRECATED
    virtual Topic createTopic(const Message& message);
    /*!<
     * \deprecated Use `createTopics` or `createTopicsAsync` instead.
     *
     * Create a topic from the specified <code>message</code>, which must be of
     * type <code>ResolutionSuccess</code>.
     */
};

/** @} */
/** @} */

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

// ---------------------
// class ProviderSession
// ---------------------

inline ProviderSession::ProviderSession(const SessionOptions& parameters,
        EventHandler *handler,
        EventDispatcher *dispatcher)
    : d_eventHandler_p(handler)
{
    if (dispatcher && !handler) {
        throw InvalidArgumentException(
                "Event dispatcher provided without handler.");
    }
    d_handle_p = blpapi_ProviderSession_create(parameters.handle(),
            handler ? &blpapi_providerEventHandlerAdapter : 0,
            dispatcher ? dispatcher->impl() : 0,
            this);
    initAbstractSessionHandle(
            blpapi_ProviderSession_getAbstractSession(d_handle_p));
}

inline ProviderSession::ProviderSession(blpapi_ProviderSession_t *newHandle)
    : d_handle_p(newHandle)
{
    initAbstractSessionHandle(
            blpapi_ProviderSession_getAbstractSession(d_handle_p));
}

inline ProviderSession::~ProviderSession()
{
    blpapi_ProviderSession_destroy(d_handle_p);
}

inline bool ProviderSession::start()
{
    return blpapi_ProviderSession_start(d_handle_p) ? false : true;
}

inline bool ProviderSession::startAsync()
{
    return blpapi_ProviderSession_startAsync(d_handle_p) ? false : true;
}

inline void ProviderSession::stop()
{
    blpapi_ProviderSession_stop(d_handle_p);
}

inline void ProviderSession::stopAsync()
{
    blpapi_ProviderSession_stopAsync(d_handle_p);
}

inline Event ProviderSession::nextEvent(int timeout)
{
    if (timeout < 0) {
        throw InvalidArgumentException("Timeout must be >= 0.");
    }

    blpapi_Event_t *event = 0;
    ExceptionUtil::throwOnError(blpapi_ProviderSession_nextEvent(
            d_handle_p, &event, static_cast<unsigned>(timeout)));
    return Event(event);
}

inline int ProviderSession::tryNextEvent(Event *event)
{
    assert(event);

    blpapi_Event_t *impl = 0;
    int ret = blpapi_ProviderSession_tryNextEvent(d_handle_p, &impl);
    if (0 == ret) {
        *event = Event(impl);
    }
    return ret;
}

inline bool ProviderSession::registerService(const char *serviceName,
        const Identity& identity,
        const ServiceRegistrationOptions& registrationOptions)
{
    return blpapi_ProviderSession_registerService(d_handle_p,
                   serviceName,
                   identity.handle(),
                   registrationOptions.handle())
            ? false
            : true;
}

inline void ProviderSession::activateSubServiceCodeRange(
        const char *serviceName, int begin, int end, int priority)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_PROVIDERSESSION_ACTIVATESUBSERVICECODERANGE(
                    d_handle_p, serviceName, begin, end, priority));
}

inline void ProviderSession::deactivateSubServiceCodeRange(
        const char *serviceName, int begin, int end)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_PROVIDERSESSION_DEACTIVATESUBSERVICECODERANGE(
                    d_handle_p, serviceName, begin, end));
}

inline CorrelationId ProviderSession::registerServiceAsync(
        const char *serviceName,
        const Identity& identity,
        const CorrelationId& correlationId,
        const ServiceRegistrationOptions& registrationOptions)
{
    blpapi_CorrelationId_t retv = correlationId.impl();
    ExceptionUtil::throwOnError(
            blpapi_ProviderSession_registerServiceAsync(d_handle_p,
                    serviceName,
                    identity.handle(),
                    &retv,
                    registrationOptions.handle()));

    return retv;
}

inline bool ProviderSession::deregisterService(const char *serviceName)
{
    return BLPAPI_CALL_PROVIDERSESSION_DEREGISTERSERVICE(
                   d_handle_p, serviceName)
                    == 0
            ? true
            : false;
}

inline void ProviderSession::resolve(ResolutionList *resolutionList,
        ResolveMode resolveMode,
        const Identity& identity)
{
    assert(resolutionList);

    ExceptionUtil::throwOnError(blpapi_ProviderSession_resolve(d_handle_p,
            resolutionList->impl(),
            resolveMode,
            identity.handle()));
    return;
}

inline void ProviderSession::resolveAsync(const ResolutionList& resolutionList,
        ResolveMode resolveMode,
        const Identity& identity)
{
    ExceptionUtil::throwOnError(blpapi_ProviderSession_resolveAsync(d_handle_p,
            resolutionList.impl(),
            resolveMode,
            identity.handle()));
    return;
}

inline Topic ProviderSession::createTopic(const Message& message)
{
    blpapi_Topic_t *topic = 0;
    ExceptionUtil::throwOnError(blpapi_ProviderSession_createTopic(
            d_handle_p, message.impl(), &topic));

    return Topic(topic);
}

inline Topic ProviderSession::getTopic(const Message& message)
{
    blpapi_Topic_t *topic = 0;
    ExceptionUtil::throwOnError(blpapi_ProviderSession_getTopic(
            d_handle_p, message.impl(), &topic));

    return Topic(topic);
}

inline Topic ProviderSession::createServiceStatusTopic(const Service& service)
{
    blpapi_Topic_t *topic = 0;
    ExceptionUtil::throwOnError(
            blpapi_ProviderSession_createServiceStatusTopic(
                    d_handle_p, service.handle(), &topic));

    return Topic(topic);
}

inline void ProviderSession::createTopics(TopicList *topicList,
        ResolveMode resolveMode,
        const Identity& identity)
{
    assert(topicList);

    ExceptionUtil::throwOnError(blpapi_ProviderSession_createTopics(
            d_handle_p, topicList->impl(), resolveMode, identity.handle()));
    return;
}

inline void ProviderSession::createTopicsAsync(const TopicList& topicList,
        ResolveMode resolveMode,
        const Identity& identity)
{
    ExceptionUtil::throwOnError(blpapi_ProviderSession_createTopicsAsync(
            d_handle_p, topicList.impl(), resolveMode, identity.handle()));
    return;
}

inline void ProviderSession::deleteTopic(const Topic& topic)
{
    const blpapi_Topic_t *topicImpl = topic.impl();
    ExceptionUtil::throwOnError(BLPAPI_CALL_PROVIDERSESSION_DELETETOPICS(
            d_handle_p, &topicImpl, 1));
}

inline void ProviderSession::deleteTopics(const std::vector<Topic>& topics)
{
    if (topics.size() == 0) {
        return;
    }
    std::vector<const blpapi_Topic_t *> topicImplList;
    topicImplList.reserve(topics.size());
    for (std::vector<Topic>::const_iterator it = topics.begin();
            it != topics.end();
            ++it) {
        topicImplList.push_back(it->impl());
    }
    ExceptionUtil::throwOnError(BLPAPI_CALL_PROVIDERSESSION_DELETETOPICS(
            d_handle_p, &topicImplList[0], topicImplList.size()));
}

inline void ProviderSession::deleteTopics(
        const Topic *topics, size_t numTopics)
{
    if (numTopics == 0) {
        return;
    }

    assert(topics);

    std::vector<const blpapi_Topic_t *> topicImplList;
    topicImplList.reserve(numTopics);
    for (size_t i = 0; i < numTopics; ++i) {
        topicImplList.push_back(topics[i].impl());
    }
    ExceptionUtil::throwOnError(BLPAPI_CALL_PROVIDERSESSION_DELETETOPICS(
            d_handle_p, &topicImplList[0], topicImplList.size()));
}

inline void ProviderSession::terminateSubscriptionsOnTopic(
        const Topic& topic, const char *message)
{
    const blpapi_Topic_t *topicImpl = topic.impl();
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_PROVIDERSESSION_TERMINATESUBSCRIPTIONSONTOPICS(
                    d_handle_p, &topicImpl, 1, message));
}

inline void ProviderSession::terminateSubscriptionsOnTopics(
        const std::vector<Topic>& topics, const char *message)
{
    if (topics.empty()) {
        return;
    }
    terminateSubscriptionsOnTopics(&topics.front(), topics.size(), message);
}

inline void ProviderSession::terminateSubscriptionsOnTopics(
        const Topic *topics, size_t numTopics, const char *message)
{
    if (numTopics == 0) {
        return;
    }

    assert(topics);

    std::vector<const blpapi_Topic_t *> topicImplList;
    topicImplList.reserve(numTopics);
    for (size_t i = 0; i < numTopics; ++i) {
        topicImplList.push_back(topics[i].impl());
    }
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_PROVIDERSESSION_TERMINATESUBSCRIPTIONSONTOPICS(
                    d_handle_p,
                    &topicImplList[0],
                    topicImplList.size(),
                    message));
}

inline void ProviderSession::publish(const Event& event)
{
    ExceptionUtil::throwOnError(
            blpapi_ProviderSession_publish(d_handle_p, event.impl()));
    return;
}

inline void ProviderSession::sendResponse(
        const Event& event, bool isPartialResponse)
{
    ExceptionUtil::throwOnError(blpapi_ProviderSession_sendResponse(
            d_handle_p, event.impl(), isPartialResponse));
    return;
}

inline blpapi_ProviderSession_t *ProviderSession::handle() const
{
    return d_handle_p;
}

inline void ProviderSession::dispatchEvent(const Event& event)
{
    assert(d_eventHandler_p);

    d_eventHandler_p->processEvent(event, this);
}

inline bool ProviderSession::flushPublishedEvents(int timeoutMsecs)
{
    int allFlushed = 0;
    int rc = BLPAPI_CALL(blpapi_ProviderSession_flushPublishedEvents)(
            d_handle_p, &allFlushed, timeoutMsecs);
    if (rc != 0) {
        ExceptionUtil::throwOnError(rc);
    }
    return allFlushed ? true : false;
}

// --------------------------------
// class ServiceRegistrationOptions
// --------------------------------

inline ServiceRegistrationOptions::ServiceRegistrationOptions()
{
    d_handle_p = blpapi_ServiceRegistrationOptions_create();
}

inline ServiceRegistrationOptions::ServiceRegistrationOptions(
        const ServiceRegistrationOptions& original)
{
    d_handle_p
            = blpapi_ServiceRegistrationOptions_duplicate(original.handle());
}

inline ServiceRegistrationOptions::~ServiceRegistrationOptions()
{
    blpapi_ServiceRegistrationOptions_destroy(d_handle_p);
}

inline ServiceRegistrationOptions& ServiceRegistrationOptions::operator=(
        const ServiceRegistrationOptions& rhs)
{
    blpapi_ServiceRegistrationOptions_copy(this->handle(), rhs.handle());
    return *this;
}

// SUBSERVICE CODES
inline void ServiceRegistrationOptions::addActiveSubServiceCodeRange(
        int begin, int end, int priority)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SERVICEREGISTRATIONOPTIONS_ADDACTIVATESUBSERVICECODERANGE(
                    d_handle_p, begin, end, priority));
}

inline void ServiceRegistrationOptions::removeAllActiveSubServiceCodeRanges()
{
    BLPAPI_CALL_SERVICEREGISTRATIONOPTIONS_REMOVEALLACTIVESUBSERVICECODERANGES(
            d_handle_p);
}

inline void ServiceRegistrationOptions::setGroupId(
        const char *groupId, unsigned int groupIdLength)
{
    blpapi_ServiceRegistrationOptions_setGroupId(
            d_handle_p, groupId, groupIdLength);
}

inline int ServiceRegistrationOptions::setServicePriority(int priority)
{
    return blpapi_ServiceRegistrationOptions_setServicePriority(
            d_handle_p, priority);
}

inline void ServiceRegistrationOptions::setPartsToRegister(int parts)
{
    BLPAPI_CALL_SERVICEREGISTRATIONOPTIONS_SETPARTSTOREGISTER(
            d_handle_p, parts);
}

inline int ServiceRegistrationOptions::getGroupId(
        char *groupIdBuffer, int *groupIdLength) const
{
    return blpapi_ServiceRegistrationOptions_getGroupId(
            d_handle_p, groupIdBuffer, groupIdLength);
}

inline int ServiceRegistrationOptions::getServicePriority() const
{
    return blpapi_ServiceRegistrationOptions_getServicePriority(d_handle_p);
}

inline int ServiceRegistrationOptions::getPartsToRegister() const
{
    return BLPAPI_CALL_SERVICEREGISTRATIONOPTIONS_GETPARTSTOREGISTER(
            d_handle_p);
}

inline blpapi_ServiceRegistrationOptions_t *
ServiceRegistrationOptions::handle() const
{
    return d_handle_p;
}

// --------------------------
// class ProviderEventHandler
// --------------------------

//! \cond INTERNAL
extern "C" inline void blpapi_providerEventHandlerAdapter(
        blpapi_Event_t *event, blpapi_ProviderSession_t *, void *userData)
{
    assert(userData);

    reinterpret_cast<ProviderSession *>(userData)->dispatchEvent(Event(event));
}
//! \endcond

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_PROVIDERSESSION
