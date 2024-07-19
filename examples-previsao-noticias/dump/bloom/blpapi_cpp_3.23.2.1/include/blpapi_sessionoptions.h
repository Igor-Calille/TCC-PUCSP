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

/** \file blpapi_sessionoptions.h */
/** \defgroup blpapi_sessionoptions Component blpapi_sessionoptions
\brief A common interface shared between publish and consumer sessions.
\file blpapi_sessionoptions.h
\brief A common interface shared between publish and consumer sessions.
*/

#ifndef INCLUDED_BLPAPI_SESSIONOPTIONS
#define INCLUDED_BLPAPI_SESSIONOPTIONS

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_sessionoptions
 * @{
 * \par Outline
 * <UL>
 * <LI><A HREF="#1">Purpose</A></LI>
 * <LI><A HREF="#2">Classes</A></LI>
 * <LI><A HREF="#3">Description</A></LI>
 * <UL>
 * <LI><A HREF="#3.1">Usage</A></LI>
 * </UL>
 * </UL>
 * \par
 * \par
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * A common interface shared between publish and consumer sessions.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::SessionOptions</td>
 * <td>user specified options when creating a session.</td>
 * </tr>
 * </table>
 * \par
 * \sa  blpapi_abstractsession, blpapi_session, blpapi_providersession
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This file defines a <code>SessionOptions</code> class which is used
 * to specify various options during session creation.
 * \par
 * \par
 * \par
 * <A NAME="usage"></A>
 * <A NAME="description.usage"></A>
 * <A NAME="3.1"> \par Usage: </A>
 * The following snippet shows to use the SessionOptions when creating a
 * <code>Session</code>.
\code
 #include <blpapi_session.h>
 SessionOptions sessionOptions;
 sessionOptions.setServerHost("127.0.0.1");
 Session session(sessionOptions);
 if (!session.start()) {
      std::cout << "Failed to start session." << std::endl;
      return;
 }
\endcode
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_CORRELATIONID
#include <blpapi_correlationid.h>
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

#ifndef INCLUDED_BLPAPI_TLSOPTIONS
#include <blpapi_tlsoptions.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#include <blpapi_authoptions.h>
#include <blpapi_error.h>
#include <blpapi_socks5config.h>

#include <stddef.h>

#ifdef __cplusplus

extern "C" {
#endif

BLPAPI_EXPORT
blpapi_SessionOptions_t *blpapi_SessionOptions_create(void);

BLPAPI_EXPORT
blpapi_SessionOptions_t *blpapi_SessionOptions_duplicate(
        const blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
void blpapi_SessionOptions_copy(
        blpapi_SessionOptions_t *lhs, const blpapi_SessionOptions_t *rhs);

BLPAPI_EXPORT
void blpapi_SessionOptions_destroy(blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerHost(
        blpapi_SessionOptions_t *parameters, const char *serverHost);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerPort(
        blpapi_SessionOptions_t *parameters, unsigned short serverPort);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerAddress(blpapi_SessionOptions_t *parameters,
        const char *serverHost,
        unsigned short serverPort,
        size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServerAddressWithProxy(
        blpapi_SessionOptions_t *parameters,
        const char *serverHost,
        unsigned short serverPort,
        const blpapi_Socks5Config_t *socks5Config,
        size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_removeServerAddress(
        blpapi_SessionOptions_t *parameters, size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_setConnectTimeout(
        blpapi_SessionOptions_t *parameters,
        unsigned int timeoutInMilliseconds);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultServices(
        blpapi_SessionOptions_t *parameters, const char *defaultServices);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultSubscriptionService(
        blpapi_SessionOptions_t *parameters, const char *serviceIdentifier);

BLPAPI_EXPORT
void blpapi_SessionOptions_setDefaultTopicPrefix(
        blpapi_SessionOptions_t *parameters, const char *prefix);

BLPAPI_EXPORT
void blpapi_SessionOptions_setAllowMultipleCorrelatorsPerMsg(
        blpapi_SessionOptions_t *parameters,
        int allowMultipleCorrelatorsPerMsg);

BLPAPI_EXPORT
void blpapi_SessionOptions_setClientMode(
        blpapi_SessionOptions_t *parameters, int clientMode);

BLPAPI_EXPORT
void blpapi_SessionOptions_setMaxPendingRequests(
        blpapi_SessionOptions_t *parameters, int maxPendingRequests);

BLPAPI_EXPORT
void blpapi_SessionOptions_setAutoRestartOnDisconnection(
        blpapi_SessionOptions_t *parameters, int autoRestart);

BLPAPI_EXPORT
void blpapi_SessionOptions_setAutoRestart(
        blpapi_SessionOptions_t *parameters, int autoRestart);
BLPAPI_EXPORT
int blpapi_SessionOptions_setSessionIdentityOptions(
        blpapi_SessionOptions_t *parameters,
        const blpapi_AuthOptions_t *authOptions,
        blpapi_CorrelationId_t *cid);

BLPAPI_EXPORT
void blpapi_SessionOptions_setAuthenticationOptions(
        blpapi_SessionOptions_t *parameters, const char *authOptions);

BLPAPI_EXPORT
void blpapi_SessionOptions_setNumStartAttempts(
        blpapi_SessionOptions_t *parameters, int numStartAttempts);

BLPAPI_EXPORT
void blpapi_SessionOptions_setMaxEventQueueSize(
        blpapi_SessionOptions_t *parameters, size_t maxEventQueueSize);

BLPAPI_EXPORT
int blpapi_SessionOptions_setSlowConsumerWarningHiWaterMark(
        blpapi_SessionOptions_t *parameters, float hiWaterMark);

BLPAPI_EXPORT
int blpapi_SessionOptions_setSlowConsumerWarningLoWaterMark(
        blpapi_SessionOptions_t *parameters, float loWaterMark);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultKeepAliveInactivityTime(
        blpapi_SessionOptions_t *parameters, int inactivityMsecs);

BLPAPI_EXPORT
int blpapi_SessionOptions_setDefaultKeepAliveResponseTimeout(
        blpapi_SessionOptions_t *parameters, int timeoutMsecs);

BLPAPI_EXPORT
int blpapi_SessionOptions_setKeepAliveEnabled(
        blpapi_SessionOptions_t *parameters, int isEnabled);

BLPAPI_EXPORT
void blpapi_SessionOptions_setRecordSubscriptionDataReceiveTimes(
        blpapi_SessionOptions_t *parameters, int shouldRecord);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServiceCheckTimeout(
        blpapi_SessionOptions_t *paramaters, int timeoutMsecs);

BLPAPI_EXPORT
int blpapi_SessionOptions_setServiceDownloadTimeout(
        blpapi_SessionOptions_t *paramaters, int timeoutMsecs);

BLPAPI_EXPORT
void blpapi_SessionOptions_setTlsOptions(blpapi_SessionOptions_t *paramaters,
        const blpapi_TlsOptions_t *tlsOptions);

BLPAPI_EXPORT
int blpapi_SessionOptions_setFlushPublishedEventsTimeout(
        blpapi_SessionOptions_t *paramaters, int timeoutMsecs);

BLPAPI_EXPORT
int blpapi_SessionOptions_setBandwidthSaveModeDisabled(
        blpapi_SessionOptions_t *parameters, int disableBandwidthSaveMode);

BLPAPI_EXPORT
const char *blpapi_SessionOptions_serverHost(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
unsigned int blpapi_SessionOptions_serverPort(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_numServerAddresses(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_getServerAddress(blpapi_SessionOptions_t *parameters,
        const char **serverHost,
        unsigned short *serverPort,
        size_t index);

BLPAPI_EXPORT
int blpapi_SessionOptions_getServerAddressWithProxy(
        blpapi_SessionOptions_t *parameters,
        const char **serverHost,
        unsigned short *serverPort,
        const char **socks5Host,
        unsigned short *sock5Port,
        size_t index);

BLPAPI_EXPORT
unsigned int blpapi_SessionOptions_connectTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char *blpapi_SessionOptions_defaultServices(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char *blpapi_SessionOptions_defaultSubscriptionService(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char *blpapi_SessionOptions_defaultTopicPrefix(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_allowMultipleCorrelatorsPerMsg(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_clientMode(blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_maxPendingRequests(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_autoRestartOnDisconnection(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_autoRestart(blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
const char *blpapi_SessionOptions_authenticationOptions(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_numStartAttempts(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
size_t blpapi_SessionOptions_maxEventQueueSize(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
float blpapi_SessionOptions_slowConsumerWarningHiWaterMark(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
float blpapi_SessionOptions_slowConsumerWarningLoWaterMark(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_defaultKeepAliveInactivityTime(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_defaultKeepAliveResponseTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_keepAliveEnabled(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_recordSubscriptionDataReceiveTimes(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_serviceCheckTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_serviceDownloadTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_print(blpapi_SessionOptions_t *parameters,
        blpapi_StreamWriter_t streamWriter,
        void *stream,
        int indentLevel,
        int spacesPerLevel);

BLPAPI_EXPORT
int blpapi_SessionOptions_flushPublishedEventsTimeout(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_bandwidthSaveModeDisabled(
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_setApplicationIdentityKey(
        blpapi_SessionOptions_t *parameters,
        const char *applicationIdentityKey,
        size_t size);
BLPAPI_EXPORT
int blpapi_SessionOptions_applicationIdentityKey(
        const char **applicationIdentityKey,
        size_t *size,
        blpapi_SessionOptions_t *parameters);

BLPAPI_EXPORT
int blpapi_SessionOptions_setSessionName(blpapi_SessionOptions_t *parameters,
        const char *sessionName,
        size_t size);

BLPAPI_EXPORT
int blpapi_SessionOptions_sessionName(const char **sessionName,
        size_t *size,
        blpapi_SessionOptions_t *parameters);

#ifdef __cplusplus
}

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_sessionoptions
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * Contains the options which the user can specify when creating a session.
 *
 * To use non-default options on a Session, create a SessionOptions instance
 * and set the required options and then supply it when creating a Session.
 */
/*!
 * See \ref blpapi_sessionoptions
 */
class SessionOptions {

    blpapi_SessionOptions_t *d_handle_p;

  public:
    /*
     * The possible options for how to connect to the API
     */

    enum ClientMode {
        AUTO = BLPAPI_CLIENTMODE_AUTO,
        ///< Automatic (desktop if available otherwise server)

        DAPI = BLPAPI_CLIENTMODE_DAPI,
        ///< Always connect to the desktop API

        SAPI = BLPAPI_CLIENTMODE_SAPI
        ///< Always connect to the server API
    };

    SessionOptions();
    /*!<
     * Create a SessionOptions with all options set to the standard defaults.
     */

    SessionOptions(const SessionOptions& original);
    /*!<
     * Copy constructor
     */

    ~SessionOptions();
    /*!<
     * Destroy this SessionOptions.
     */

    // MANIPULATORS

    SessionOptions& operator=(const SessionOptions& rhs);
    /*!<
     * Assign to this object the value of the specified <code>rhs</code>
     * object.
     */

    void setServerHost(const char *host);
    /*!<
     * Set the API server host to connect to when using the server API to the
     * specified <code>host</code>, which is a hostname or an IPv4 address
     * (that is, a.b.c.d).  This will update only the first element in the
     * server list.  The default is "127.0.0.1".  Behavior is undefined if the
     * specified <code>host</code> is a <code>nullptr</code> or points to an
     * empty string.
     */

    void setServerPort(unsigned short port);
    /*!<
     * Set the port to connect to when using the server API to the specified
     * <code>port</code>.  This will update only the first element of the
     * server list.  The default port is 8194.
     */

    int setServerAddress(
            const char *serverHost, unsigned short serverPort, size_t index);
    /*!<
     * Set the server address at the specified <code>index</code> in the server
     * list using the specified <code>serverHost</code> and
     * <code>serverPort</code>.  The default is "127.0.0.1:8194".  Behavior is
     * undefined if the specified <code>serverHost</code> is a
     * <code>nullptr</code> or points to an empty string.
     */

    int setServerAddress(const char *serverHost,
            unsigned short serverPort,
            const Socks5Config& socks5Config,
            size_t index);
    /*!<
     * Set the server address at the specified `index` in the server list
     * using the specified `serverHost`, `serverPort`, and `socks5Config`.
     *
     * Behavior is undefined if the specified `serverHost` is a `nullptr`
     * or points to an empty string.
     */

    int removeServerAddress(size_t index);
    /*!<
     * Remove the server address at the specified <code>index</code>.
     */

    void setConnectTimeout(unsigned int timeoutMilliSeconds);
    /*!<
     * Set the connection timeout in milliseconds when connecting to the API.
     * The default is 5000 milliseconds.  Behavior is not defined unless the
     * specified <code>timeoutMilliSeconds</code> is in range of [1 .. 120000]
     * milliseconds
     */

    void setDefaultServices(const char *defaultServices);
    /*!<
     * <strong>DEPRECATED</strong>
     *
     * Set the default service for the session. This function is
     * deprecated; see <code>setDefaultSubscriptionService</code>.
     */

    void setDefaultSubscriptionService(const char *serviceIdentifier);
    /*!<
     * Set the default service for subscriptions which do not specify a
     * subscription server to the specified <code>serviceIdentifier</code>.
     * The behavior is undefined unless <code>serviceIdentifier</code> matches
     * the regular expression
     * <code>^//[-_.a-zA-Z0-9]+/[-_.a-zA-Z0-9]+\$</code>. The default is
     * "//blp/mktdata".  For more information on when this will be used see
     * <code>QUALIFYING SUBSCRIPTION STRINGS</code> section in
     * <code>blpapi_subscriptionlist</code>.
     */

    void setDefaultTopicPrefix(const char *prefix);
    /*!<
     * Set the default topic prefix to be used when a subscription does not
     * specify a prefix to the specified <code>prefix</code>. The default is
     * "/ticker/".  For more information on when this will be used see
     * <code>QUALIFYING SUBSCRIPTION STRINGS</code> section in
     * <code>blpapi_subscriptionlist</code>.
     */

    void setAllowMultipleCorrelatorsPerMsg(
            bool allowMultipleCorrelatorsPerMsg);
    /*!<
     * Set whether the Session is allowed to associate more than one
     * CorrelationId with a Message to the specified
     * <code>allowMultipleCorrelatorsPerMsg</code>.  The default is
     * <code>false</code>.  This means that if you have multiple subscriptions
     * which overlap (that is a particular Message is relevant to all of them)
     * you will be presented with the same message multiple times when you use
     * the MessageIterator, each time with a different CorrelationId.  If you
     * specify <code>true</code> for this then a Message may be presented with
     * multiple CorrelationId's.
     */

    void setClientMode(int clientMode);
    /*!<
     * Set how to connect to the API.  The default is AUTO which will try to
     * connect to the desktop API but fall back to the server API if the
     * desktop is not available.  DAPI always connects to the desktop API and
     * will fail if it is not available.  SAPI always connects to the server
     * API and will fail if it is not available.
     */

    void setMaxPendingRequests(int maxPendingRequests);
    /*!<
     * Set the maximum number of requests which can be pending to the specified
     * <code>maxPendingRequests</code>.  The default is 1024.
     */

    CorrelationId setSessionIdentityOptions(const AuthOptions& authOptions,
            const CorrelationId& correlationId = CorrelationId());
    /*!<
     * Set the specified <code>authOptions</code> as the
     * <code>AuthOptions</code> for the session identity, enabling automatic
     * authorization of the session identity during startup. The optionally
     * specified <code>correlationId</code> is used to identify the messages
     * associated with the session identity.
     *
     * Return the actual <code>CorrelationId</code> that identifies the
     * messages associated with the session identity.
     *
     * The session identity lifetime is tied to the session's lifetime, so it
     * is guaranteed that the session identity will remain authorized during
     * the entire duration of the session. The identity will be authorized
     * before the session starts. The session will terminate if the identity
     * fails to authorize or is revoked.
     *
     * The session identity is used to send requests and make subscriptions if
     * no other identity is provided.
     *
     * By default the session identity is not authorized.
     */

    void setAuthenticationOptions(const char *authOptions);
    /*!<
     * Set the specified <code>authOptions</code> as authentication option.
     */

    void setNumStartAttempts(int numStartAttempts);
    /*!<
     * Set the maximum number of attempts to connect to a server.  This option
     * only has effect when <code>autoRestartOnDisconnection</code> is set to
     * true.  The default is 3.
     */

    void setAutoRestartOnDisconnection(bool autoRestart);
    /*!<
     * Set whether to automatically retry connecting if the connection to a
     * server gets disconnected.  The default is true.  The number of times
     * such a retry is attempted is controlled by numStartAttempts.
     */

    void setMaxEventQueueSize(size_t eventQueueSize);
    /*!<
     * Set the maximum number of outstanding undelivered events per session to
     * the specified <code>eventQueueSize</code>.  All subsequent events
     * delivered over the network will be dropped by the session if the number
     * of outstanding undelivered events is <code>eventQueueSize</code>, the
     * specified threshold.  The default value is 10000.
     */

    void setSlowConsumerWarningHiWaterMark(float hiWaterMark);
    /*!<
     * Set the point at which "slow consumer" events will be generated, using
     * the specified <code>highWaterMark</code> as a fraction of
     * <code>maxEventQueueSize</code>; the default value is 0.75.  A warning
     * event will be generated when the number of outstanding undelivered
     * events passes above <code>hiWaterMark * maxEventQueueSize</code>.  The
     * behavior of the function is undefined unless <code>0.0 \< hiWaterMark
     * \<= 1.0</code>.  Further, at the time that <code>Session.start()</code>
     * is called, it must be the case that
     * <code>slowConsumerWarningLoWaterMark() * maxEventQueueSize()</code> \<
     * <code>slowConsumerWarningHiWaterMark() * maxEventQueueSize()</code>.
     */

    void setSlowConsumerWarningLoWaterMark(float loWaterMark);
    /*!<
     * Set the point at which "slow consumer cleared" events will be generated,
     * using the specified <code>loWaterMark</code> as a fraction of
     * <code>maxEventQueueSize</code>; the default value is 0.5.  A warning
     * cleared event will be generated when the number of outstanding
     * undelivered events drops below <code>loWaterMark *
     * maxEventQueueSize</code>. The behavior of the function is undefined
     * unless <code>0.0 \<= loWaterMark \< 1.0</code>.  Further, at the time
     * that <code>Session.start()</code> is called, it must be the case that
     * <code>slowConsumerWarningLoWaterMark() * maxEventQueueSize()</code> \<
     * <code>slowConsumerWarningHiWaterMark() * maxEventQueueSize()</code>.
     */

    void setDefaultKeepAliveInactivityTime(int inactivityMsecs);
    /*!<
     * Set to the specified <code>inactivityMsecs</code> the amount of time
     * that no traffic can be received on a connection before the ping-based
     * keep-alive mechanism is triggered; if no traffic is received for this
     * duration then a keep-alive ping is sent to the remote end to solicit a
     * response.  If <code>inactivityMsecs == 0</code>, then no keep-alive
     * pings will be sent.  The behavior of this function is undefined unless
     * <code>inactivityMsecs</code> is a non-negative value.  The default value
     * is 20,000 milliseconds.  Note that not all back-end connections provide
     * ping-based keep-alives; this option is ignored by such connections.
     */

    void setDefaultKeepAliveResponseTimeout(int timeoutMsecs);
    /*!<
     * When a keep-alive ping is sent, wait for the specified
     * <code>timeoutMsecs</code> to receive traffic (of any kind) before
     * terminating the connection due to inactivity.  If <code>timeoutMsecs ==
     * 0</code>, then connections are never terminated due to the absence of
     * traffic after a keep-alive ping.  The behavior of this function is
     * undefined unless <code>timeoutMsecs</code> is a non-negative value.  The
     * default value is 5,000 milliseconds.  Note that not all back-end
     * connections provide support for ping-based keep-alives; this option is
     * ignored by such connections.
     */

    void setKeepAliveEnabled(bool isEnabled);
    /*!<
     * If the specified <code>isEnabled</code> is <code>false</code>, then
     * disable all keep-alive mechanisms, both from the client to the server
     * and from the server to the client; otherwise enable keep-alive pings
     * both from the client to the server (as configured by
     * <code>setDefaultKeepAliveInactivityTime</code> and
     * <code>setDefaultKeepAliveResponseTimeout</code> if the connection
     * supports ping-based keep-alives), and from the server to the client as
     * specified by the server configuration.
     */

    void setRecordSubscriptionDataReceiveTimes(bool shouldRecord);
    /*!<
     * Set whether the receipt time (accessed via
     * blpapi::Message::timeReceived) should be recorded for subscription data
     * messages. By default, the receipt time for these messages is not
     * recorded.
     */

    void setServiceCheckTimeout(int timeoutMsecs);
    /*!<
     * Set the timeout, in milliseconds, when opening a service for checking
     * what version of the schema should be downloaded. The behavior is not
     * defined unless <code>timeoutMsecs</code> is a positive value. The
     * default timeout is 120,000 milliseconds.
     */

    void setServiceDownloadTimeout(int timeoutMsecs);
    /*!<
     * Set the timeout, in milliseconds, when opening a service for downloading
     * the service schema. The behavior is not defined unless the specified
     * <code>timeoutMsecs</code> is a positive value. The default timeout is
     * 120,000 milliseconds.
     */

    void setTlsOptions(const TlsOptions& tlsOptions);
    /*!<
     * Set the TLS options to the specified <code>tlsOptions</code>.
     */

    void setFlushPublishedEventsTimeout(int timeoutMsecs);
    /*!<
     * Set the timeout, in milliseconds, for ProviderSession to flush published
     * events before stopping. The behavior is not defined unless the specified
     * <code>timeoutMsecs</code> is a positive value.  The default value is
     * 2000.
     */

    void setBandwidthSaveModeDisabled(bool isDisabled);
    /*!<
     * If the specified <code>isDisabled</code> is <code>true</code>, then
     * disable bandwidth saving measures. The default value is
     * <code>false</code>.
     */

    void setApplicationIdentityKey(const std::string& applicationIdentityKey);
    /*!<
     * Set the application identity key (AIK) which uniquely identifies
     * this application for this session.
     */

    void setSessionName(const std::string& sessionName);
    /*!<
     * Set the session name which can be used to identify the log
     * lines pertaining to the session.
     */

    // ACCESSORS
    const char *serverHost() const;
    /*!<
     * Return a pointer to the value of the server host option in this
     * SessionOptions instance.  The pointer is valid until this SessionOptions
     * is destroyed setServerHost() is called.
     */

    unsigned short serverPort() const;
    /*!<
     * Return the server port that this session connects to.  If more than one
     * server addresses are specified, return the port of the first server
     * address.
     */

    size_t numServerAddresses() const;
    /*!<
     * Return the number of server addresses.
     */

    int getServerAddress(const char **serverHost,
            unsigned short *serverPort,
            size_t index) const;
    /*!<
     * Put the server name and port into <code>serverHost</code> and
     * <code>serverPort</code> indexed by <code>index</code>.  Return 0 if
     * succeeded; otherwise, return non-zero.
     */

    int getServerAddress(const char **serverHost,
            unsigned short *serverPort,
            Socks5Config *socksConfig,
            size_t index) const;
    /*!<
     * Put the server name and port into `serverHost`, `serverPort`, and
     * associated `socksConfig` indexed by `index`. Return 0 if succeeded;
     * otherwise, return non-zero. Behavior is undefined if `serverHost`,
     * `serverPort`, or `socksConfig` is `nullptr`.
     */

    unsigned int connectTimeout() const;
    /*!<
     * Return the value of the connection timeout option in this SessionOptions
     * instance in milliseconds.
     */

    const char *defaultServices() const;
    /*!<
     * Return all default services in one string.
     */

    const char *defaultSubscriptionService() const;
    /*!<
     * Return a pointer to the value of the default subscription service option
     * in this SessionOptions instance.  The pointer is valid until this
     * SessionOptions is destroyed or setDefaultSubscriptionService() is
     * called.
     */

    const char *defaultTopicPrefix() const;
    /*!<
     * Return a pointer to the value of the default topic prefix option in this
     * SessionOptions instance.  The pointer is valid until this SessionOptions
     * is destroyed or setDefaultTopicPrefix() is called.
     */

    bool allowMultipleCorrelatorsPerMsg() const;
    /*!<
     * Return the value of the allow multiple correlators per message option in
     * this SessionOptions instance.
     */

    int clientMode() const;
    /*!<
     * Return the value of the client mode option in this SessionOptions
     * instance.
     */

    int maxPendingRequests() const;
    /*!<
     * Return the value of the maximum pending request option in this
     * SessionOptions instance.
     */

    blpapi_SessionOptions_t *handle() const;
    /*!<
     * Return the handle of the current session options.
     */

    bool autoRestartOnDisconnection() const;
    /*!<
     * Return whether automatically restarting connection if disconnected.
     */

    const char *authenticationOptions() const;
    /*!<
     * Return authentication options in a string.
     */

    int numStartAttempts() const;
    /*!<
     * Return the maximum number of attempts to start a session by connecting a
     * server.
     */

    size_t maxEventQueueSize() const;
    /*!<
     * Return the value of maximum outstanding undelivered events that the
     * session is configured with.
     */

    float slowConsumerWarningHiWaterMark() const;
    /*!<
     * Return the fraction of maxEventQueueSize at which "slow consumer" event
     * will be generated.
     */

    float slowConsumerWarningLoWaterMark() const;
    /*!<
     * Return the fraction of maxEventQueueSize at which "slow consumer
     * cleared" event will be generated.
     */

    int defaultKeepAliveInactivityTime() const;
    /*!<
     * Return the interval (in milliseconds) a connection has to remain
     * inactive (receive no data) before a keep alive probe will be sent.
     */

    int defaultKeepAliveResponseTimeout() const;
    /*!<
     * Return the time (in milliseconds) the library will wait for response to
     * a keep alive probe before declaring it lost.
     */

    bool keepAliveEnabled() const;
    /*!<
     * Return <code>true</code> if the keep-alive mechanism is enabled;
     * otherwise return <code>false</code>.
     */

    bool recordSubscriptionDataReceiveTimes() const;
    /*!<
     * Return whether the receipt time (accessed via
     * blpapi::Message::timeReceived) should be recorded for subscription data
     * messages.
     */

    int serviceCheckTimeout() const;
    /*!<
     * Return the value of the service check timeout option in this
     * SessionOptions instance in milliseconds.
     */

    int serviceDownloadTimeout() const;
    /*!<
     * Return the value of the service download timeout option in this
     * SessionOptions instance in milliseconds.
     */

    int flushPublishedEventsTimeout() const;
    /*!<
     * Return the timeout, in milliseconds, for ProviderSession to flush
     * published events before stopping. The default value is 2000.
     */

    bool bandwidthSaveModeDisabled() const;
    /*!<
     * Return <code>true</code> if bandwidth saving measures have been
     * disabled; otherwise return <code>false</code>.
     */

    std::string applicationIdentityKey();
    /*!<
     * Return the application identity key (AIK) which uniquely identifies
     * this application for this session.
     */

    std::string sessionName();
    /*!<
     * Return the session name.
     */

    std::ostream& print(std::ostream& stream,
            int indentLevel = 0,
            int spacesPerLevel = 4) const;
    /*!<
     * Format this SessionOptions to the specified output <code>stream</code>
     * at the (absolute value of) the optionally specified indentation
     * <code>level</code> and return a reference to <code>stream</code>.  If
     * <code>level</code> is specified, optionally specify
     * <code>spacesPerLevel</code>, the number of spaces per indentation level
     * for this and all of its nested objects.  If <code>level</code> is
     * negative, suppress indentation of the first line.  If
     * <code>spacesPerLevel</code> is negative, format the entire output on one
     * line, suppressing all but the initial indentation (as governed by
     * <code>level</code>).
     */
};

/** @} */
/** @} */

// FREE OPERATORS
std::ostream& operator<<(
        std::ostream& stream, const SessionOptions& sessionOptions);
/*!<
 * Write the value of the specified <code>sessionOptions</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified and can change without notice, and is logically
 * equivalent to:
 * ..
 * print(stream, 0, -1);
 * ..
 */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// --------------------
// class SessionOptions
// --------------------
inline SessionOptions::SessionOptions()
{
    d_handle_p = blpapi_SessionOptions_create();
#if BLPAPI_COMPAT_33X
    blpapi_SessionOptions_setClientMode(
            d_handle_p, BLPAPI_CLIENTMODE_AUTO | BLPAPI_CLIENTMODE_COMPAT_33X);
#endif
}

inline SessionOptions::SessionOptions(const SessionOptions& options)
{
    d_handle_p = blpapi_SessionOptions_duplicate(options.handle());
}

inline SessionOptions::~SessionOptions()
{
    blpapi_SessionOptions_destroy(d_handle_p);
}

inline SessionOptions& SessionOptions::operator=(const SessionOptions& rhs)
{
    blpapi_SessionOptions_copy(this->handle(), rhs.handle());
    return *this;
}

inline void SessionOptions::setServerHost(const char *newServerHost)
{
    blpapi_SessionOptions_setServerHost(d_handle_p, newServerHost);
}

inline void SessionOptions::setServerPort(unsigned short newServerPort)
{
    blpapi_SessionOptions_setServerPort(d_handle_p, newServerPort);
}

inline int SessionOptions::setServerAddress(
        const char *serverHost, unsigned short serverPort, size_t index)
{
    return blpapi_SessionOptions_setServerAddress(
            d_handle_p, serverHost, serverPort, index);
}

inline int SessionOptions::setServerAddress(const char *serverHost,
        unsigned short serverPort,
        const Socks5Config& socks5Config,
        size_t index)
{
    return BLPAPI_CALL(blpapi_SessionOptions_setServerAddressWithProxy)(
            d_handle_p, serverHost, serverPort, socks5Config.impl(), index);
}

inline int SessionOptions::removeServerAddress(size_t index)
{
    return blpapi_SessionOptions_removeServerAddress(d_handle_p, index);
}

inline void SessionOptions::setConnectTimeout(unsigned int timeoutMilliSeconds)
{
    ExceptionUtil::throwOnError(blpapi_SessionOptions_setConnectTimeout(
            d_handle_p, timeoutMilliSeconds));
}

inline void SessionOptions::setDefaultServices(const char *newDefaultServices)
{
    blpapi_SessionOptions_setDefaultServices(d_handle_p, newDefaultServices);
}

inline void SessionOptions::setDefaultSubscriptionService(
        const char *serviceIdentifier)
{
    blpapi_SessionOptions_setDefaultSubscriptionService(
            d_handle_p, serviceIdentifier);
}

inline void SessionOptions::setDefaultTopicPrefix(const char *prefix)
{
    blpapi_SessionOptions_setDefaultTopicPrefix(d_handle_p, prefix);
}

inline void SessionOptions::setAllowMultipleCorrelatorsPerMsg(
        bool newAllowMultipleCorrelatorsPerMsg)
{
    blpapi_SessionOptions_setAllowMultipleCorrelatorsPerMsg(
            d_handle_p, newAllowMultipleCorrelatorsPerMsg);
}

inline void SessionOptions::setClientMode(int newClientMode)
{
#if BLPAPI_COMPAT_33X
    newClientMode |= BLPAPI_CLIENTMODE_COMPAT_33X;
#endif

    blpapi_SessionOptions_setClientMode(d_handle_p, newClientMode);
}

inline void SessionOptions::setMaxPendingRequests(int newMaxPendingRequests)
{
    blpapi_SessionOptions_setMaxPendingRequests(
            d_handle_p, newMaxPendingRequests);
}

inline void SessionOptions::setAutoRestartOnDisconnection(bool autoRestart)
{
    blpapi_SessionOptions_setAutoRestartOnDisconnection(
            d_handle_p, autoRestart ? 1 : 0);
}

inline CorrelationId SessionOptions::setSessionIdentityOptions(
        const AuthOptions& authOptions, const CorrelationId& cid)
{
    blpapi_CorrelationId_t cidHandle = cid.impl();

    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_setSessionIdentityOptions)(
                    d_handle_p, authOptions.handle(), &cidHandle));

    return cidHandle;
}

inline void SessionOptions::setAuthenticationOptions(const char *authOptions)
{
    blpapi_SessionOptions_setAuthenticationOptions(d_handle_p, authOptions);
}

inline void SessionOptions::setNumStartAttempts(int newNumStartAttempts)
{
    blpapi_SessionOptions_setNumStartAttempts(d_handle_p, newNumStartAttempts);
}

inline void SessionOptions::setMaxEventQueueSize(size_t eventQueueSize)
{
    BLPAPI_CALL_SESSIONOPTIONS_SETMAXEVENTQUEUESIZE(
            d_handle_p, eventQueueSize);
}

inline void SessionOptions::setSlowConsumerWarningHiWaterMark(
        float hiWaterMark)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SESSIONOPTIONS_SETSLOWCONSUMERHIWATERMARK(
                    d_handle_p, hiWaterMark));
}

inline void SessionOptions::setSlowConsumerWarningLoWaterMark(
        float loWaterMark)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SESSIONOPTIONS_SETSLOWCONSUMERLOWATERMARK(
                    d_handle_p, loWaterMark));
}

inline void SessionOptions::setDefaultKeepAliveInactivityTime(
        int inactivityTime)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SESSIONOPTIONS_SETDEFAULTKEEPALIVEINACTIVITYTIME(
                    d_handle_p, inactivityTime));
}

inline void SessionOptions::setDefaultKeepAliveResponseTimeout(
        int responseTimeout)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SESSIONOPTIONS_SETDEFAULTKEEPALIVERESPONSETIMEOUT(
                    d_handle_p, responseTimeout));
}

inline void SessionOptions::setKeepAliveEnabled(bool isEnabled)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL_SESSIONOPTIONS_SETKEEPALIVEENABLED(
            d_handle_p, isEnabled));
}

inline void SessionOptions::setRecordSubscriptionDataReceiveTimes(
        bool shouldRecrod)
{
    BLPAPI_CALL_SESSIONOPTION_SETRECORDSUBSCRIPTIONDATARECEIVETIMES(
            d_handle_p, shouldRecrod);
}

inline void SessionOptions::setServiceCheckTimeout(int timeoutMsecs)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_setServiceCheckTimeout)(
                    d_handle_p, timeoutMsecs));
}

inline void SessionOptions::setServiceDownloadTimeout(int timeoutMsecs)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_setServiceDownloadTimeout)(
                    d_handle_p, timeoutMsecs));
}

inline void SessionOptions::setTlsOptions(const TlsOptions& tlsOptions)
{
    BLPAPI_CALL(blpapi_SessionOptions_setTlsOptions)
    (d_handle_p, tlsOptions.handle());
}

inline void SessionOptions::setFlushPublishedEventsTimeout(int timeoutMsecs)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_setFlushPublishedEventsTimeout)(
                    d_handle_p, timeoutMsecs));
}

inline void SessionOptions::setBandwidthSaveModeDisabled(bool isDisabled)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_SESSIONOPTIONS_SETBANDWIDTHSAVEMODEDISABLED(
                    d_handle_p, isDisabled));
}

inline const char *SessionOptions::serverHost() const
{
    return blpapi_SessionOptions_serverHost(d_handle_p);
}

inline unsigned short SessionOptions::serverPort() const
{
    return static_cast<unsigned short>(
            blpapi_SessionOptions_serverPort(d_handle_p));
}

inline size_t SessionOptions::numServerAddresses() const
{
    return static_cast<size_t>(
            blpapi_SessionOptions_numServerAddresses(d_handle_p));
}

inline int SessionOptions::getServerAddress(const char **serverHostOut,
        unsigned short *serverPortOut,
        size_t index) const
{
    return blpapi_SessionOptions_getServerAddress(
            d_handle_p, serverHostOut, serverPortOut, index);
}

inline int SessionOptions::getServerAddress(const char **serverHostOut,
        unsigned short *serverPortOut,
        Socks5Config *socksConfig,
        size_t index) const
{
    const char *socks5ConfigHost = 0;
    unsigned short socks5ConfigPort = 0;
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_SessionOptions_getServerAddressWithProxy)(d_handle_p,
            serverHostOut,
            serverPortOut,
            &socks5ConfigHost,
            &socks5ConfigPort,
            index));

    if (socks5ConfigHost) {
        *socksConfig = Socks5Config(socks5ConfigHost, socks5ConfigPort);
    }

    return 0;
}

inline unsigned int SessionOptions::connectTimeout() const
{
    return blpapi_SessionOptions_connectTimeout(d_handle_p);
}

inline const char *SessionOptions::defaultServices() const
{
    return blpapi_SessionOptions_defaultServices(d_handle_p);
}

inline const char *SessionOptions::defaultSubscriptionService() const
{
    return blpapi_SessionOptions_defaultSubscriptionService(d_handle_p);
}

inline const char *SessionOptions::defaultTopicPrefix() const
{
    return blpapi_SessionOptions_defaultTopicPrefix(d_handle_p);
}

inline bool SessionOptions::allowMultipleCorrelatorsPerMsg() const
{
    return blpapi_SessionOptions_allowMultipleCorrelatorsPerMsg(d_handle_p)
            ? true
            : false;
}

inline int SessionOptions::clientMode() const
{
    return blpapi_SessionOptions_clientMode(d_handle_p);
}

inline int SessionOptions::maxPendingRequests() const
{
    return blpapi_SessionOptions_maxPendingRequests(d_handle_p);
}

inline bool SessionOptions::autoRestartOnDisconnection() const
{
    return blpapi_SessionOptions_autoRestartOnDisconnection(d_handle_p) != 0;
}

inline const char *SessionOptions::authenticationOptions() const
{
    return blpapi_SessionOptions_authenticationOptions(d_handle_p);
}

inline int SessionOptions::numStartAttempts() const
{
    return blpapi_SessionOptions_numStartAttempts(d_handle_p);
}

inline size_t SessionOptions::maxEventQueueSize() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_MAXEVENTQUEUESIZE(d_handle_p);
}

inline float SessionOptions::slowConsumerWarningHiWaterMark() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_SLOWCONSUMERHIWATERMARK(d_handle_p);
}

inline float SessionOptions::slowConsumerWarningLoWaterMark() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_SLOWCONSUMERLOWATERMARK(d_handle_p);
}

inline int SessionOptions::defaultKeepAliveInactivityTime() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_DEFAULTKEEPALIVEINACTIVITYTIME(
            d_handle_p);
}

inline int SessionOptions::defaultKeepAliveResponseTimeout() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_DEFAULTKEEPALIVERESPONSETIMEOUT(
            d_handle_p);
}

inline bool SessionOptions::keepAliveEnabled() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_KEEPALIVEENABLED(d_handle_p) != 0
            ? true
            : false;
}

inline bool SessionOptions::recordSubscriptionDataReceiveTimes() const
{
    return BLPAPI_CALL_SESSIONOPTION_RECORDSUBSCRIPTIONDATARECEIVETIMES(
                   d_handle_p)
            ? true
            : false;
}

inline int SessionOptions::serviceCheckTimeout() const
{
    return BLPAPI_CALL(blpapi_SessionOptions_serviceCheckTimeout)(d_handle_p);
}

inline int SessionOptions::serviceDownloadTimeout() const
{
    return BLPAPI_CALL(blpapi_SessionOptions_serviceDownloadTimeout)(
            d_handle_p);
}

inline int SessionOptions::flushPublishedEventsTimeout() const
{
    return BLPAPI_CALL(blpapi_SessionOptions_flushPublishedEventsTimeout)(
            d_handle_p);
}

inline bool SessionOptions::bandwidthSaveModeDisabled() const
{
    return BLPAPI_CALL_SESSIONOPTIONS_BANDWIDTHSAVEMODEDISABLED(d_handle_p)
                    != 0
            ? true
            : false;
}

inline void SessionOptions::setApplicationIdentityKey(
        const std::string& applicationIdentityKey)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_SessionOptions_setApplicationIdentityKey)(d_handle_p,
            applicationIdentityKey.data(),
            static_cast<int>(applicationIdentityKey.size())));
}

inline std::string SessionOptions::applicationIdentityKey()
{
    const char *apik;
    size_t size;
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_applicationIdentityKey)(
                    &apik, &size, d_handle_p));
    return std::string(apik, size);
}

inline void SessionOptions::setSessionName(const std::string& sessionName)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_SessionOptions_setSessionName)(
                    d_handle_p, sessionName.data(), sessionName.size()));
}

inline std::string SessionOptions::sessionName()
{
    const char *sessionName = nullptr;
    size_t size = 0;
    ExceptionUtil::throwOnError(BLPAPI_CALL(blpapi_SessionOptions_sessionName)(
            &sessionName, &size, d_handle_p));
    return std::string(sessionName, size);
}

inline blpapi_SessionOptions_t *SessionOptions::handle() const
{
    return d_handle_p;
}

inline std::ostream& SessionOptions::print(
        std::ostream& stream, int indentLevel, int spacesPerLevel) const
{
    if (BLPAPI_CALL_AVAILABLE(blpapi_SessionOptions_print)) {
        BLPAPI_CALL(blpapi_SessionOptions_print)
        (d_handle_p,
                StreamProxyOstream::writeToStream,
                &stream,
                indentLevel,
                spacesPerLevel);
    }
    return stream;
}

inline std::ostream& operator<<(
        std::ostream& stream, const SessionOptions& sessionOptions)
{
    return sessionOptions.print(stream, 0, -1);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_SESSIONOPTIONS
