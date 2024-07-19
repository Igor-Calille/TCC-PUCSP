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

/** \file blpapi_logging.h */
/** \defgroup blpapi_logging Component blpapi_logging
\brief Provide a C call to register a call back for logging
\file blpapi_logging.h
\brief Provide a C call to register a call back for logging
*/

#ifndef INCLUDED_BLPAPI_LOGGING
#define INCLUDED_BLPAPI_LOGGING

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_logging
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a C call to register a call back for logging
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="2"> \par Description: </A>
 *  This component provides a C function that is used to
 * register a callback for logging
 * \par
 * \par
 * <A NAME="usage"></A>
 * <A NAME="description.usage"></A>
 * <A NAME="2.1"> \par Usage: </A>
 * To use the call back a function needs to be created with the same definition
 * of blpapi_Logging_Func_t.
 * The callback will be called for all the log messages that have severity
 * greater than or equal to the specified <code>thresholdSeverity</code>.
 * A callback can be registered multiple number of times but only the last
 * registered callback will be used.
 * Registering with a <code>NULL</code> callback will de-register the callback.
\code
 extern "C" {
 void myLoggerCallback(blpapi_UInt64_t    threadId,
                       int                severity,
                       blpapi_Datetime_t  timestamp,
                       const char        *category,
                       const char        *message)
 {
     if (severity == blpapi_Logging_SEVERITY_FATAL) {
         // Do some logic for abort here
     }
     std::cout << severity << "-->" << message << std::endl;
 }
\endcode
 * This callback needs to be registered with the library as
\code
 int main()  {
     // ....
     blpapi_Logging_registerCallback(myLoggerCallback,
                                     blpapi_Logging_SEVERITY_TRACE);
     // ....
 }
\endcode
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DATETIME
#include <blpapi_datetime.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*blpapi_Logging_Func_t)(blpapi_UInt64_t threadId,
        int severity,
        blpapi_Datetime_t timestamp,
        const char *category,
        const char *message);
/*!<
 * Provide a type definition for the callback that will be called when a
 * message is logged.  The specified <code>threadId</code> is the id of the
 * calling thread.  The specified <code>severity</code> is the severity of the
 * log message whose value is defined by the type
 * <code>blpapi_Logging_Severity_t</code>.  The specified
 * <code>timestamp</code> is the date and time the message is logged.  The
 * specified <code>category</code> identifies the source of the logged message.
 * The specified <code>message</code> is the actual log message text.
 */

BLPAPI_EXPORT
int blpapi_Logging_registerCallback(blpapi_Logging_Func_t callback,
        blpapi_Logging_Severity_t thresholdSeverity);
/*!<
 * Register the specified <code>callback</code> that will be called for all log
 * messages with severity greater than or equal to the specified
 * <code>thresholdSeverity</code>.  The callback needs to be registered before
 * the start of all sessions.  If this function is called multiple times, only
 * the last registered callback will take effect.  Registering with a
 * <code>NULL</code> callback will de-register the callback.
 * <code>0</code> is returned if callback is registered and a non-zero
 * otherwise.
 */

BLPAPI_EXPORT
void blpapi_Logging_logTestMessage(blpapi_Logging_Severity_t severity);
/*!<
 * Log a test message at the specified <code>severity</code>.  Note that this
 * function is intended for testing of the logging configuration only.
 */

#ifdef __cplusplus
}

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_logging
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * This utility <code>struct</code> provides a namespace for functions to test
 * the logging configuration.
 */
/*!
 * See \ref blpapi_logging
 */
struct Logging {

    struct Severity {
        /// Enumeration used to specify different logging severity levels.
        enum Type {

            e_off = blpapi_Logging_SEVERITY_OFF, ///< OFF
            e_fatal = blpapi_Logging_SEVERITY_FATAL, ///< FATAL
            e_error = blpapi_Logging_SEVERITY_ERROR, ///< ERROR
            e_warn = blpapi_Logging_SEVERITY_WARN, ///< WARN
            e_info = blpapi_Logging_SEVERITY_INFO, ///< INFO
            e_debug = blpapi_Logging_SEVERITY_DEBUG, ///< DEBUG
            e_trace = blpapi_Logging_SEVERITY_TRACE ///< TRACE
        };
    };

    // CLASS METHODS
    static void logTestMessage(Severity::Type severity);
    /*!<
     * Log a test message with the specified <code>severity</code>.  Note that
     * this function is intended for testing of the logging configuration only.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// --------------
// struct Logging
// --------------

// CLASS METHODS
inline void Logging::logTestMessage(Severity::Type severity)
{
    BLPAPI_CALL(blpapi_Logging_logTestMessage)
    (static_cast<blpapi_Logging_Severity_t>(severity));
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif

#endif
