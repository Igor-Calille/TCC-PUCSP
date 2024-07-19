/* Copyright 2022. Bloomberg Finance L.P.
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

/** \file blpapi_socks5config.h */
/** \defgroup blpapi_socks5config Component blpapi_socks5config
\brief Provide description of Socks5 proxy.
\file blpapi_socks5config.h
\brief Provide description of Socks5 proxy.
*/

#ifndef INCLUDED_BLPAPI_SOCKS5CONFIG
#define INCLUDED_BLPAPI_SOCKS5CONFIG

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_socks5config
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provides a description of Socks5 proxy necessary to reach one or more
 * destination hosts.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Socks5Config</td>
 * <td>A description of Socks5 proxy</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a Socks5 proxy.
 */

/** @} */
/** @} */

#include <blpapi_call.h>
#include <blpapi_defs.h>
#include <blpapi_exception.h>
#include <blpapi_streamproxy.h>
#include <blpapi_types.h>

#ifdef __cplusplus

extern "C" {
#endif
BLPAPI_EXPORT
blpapi_Socks5Config_t *blpapi_Socks5Config_create(
        const char *hostname, size_t hostname_size, unsigned short port);

BLPAPI_EXPORT
int blpapi_Socks5Config_copy(blpapi_Socks5Config_t **socks5Config,
        blpapi_Socks5Config_t *srcSocks5Config);

BLPAPI_EXPORT
void blpapi_Socks5Config_destroy(blpapi_Socks5Config_t *socks5Config);

BLPAPI_EXPORT
int blpapi_Socks5Config_print(blpapi_Socks5Config_t *socks5Config,
        blpapi_StreamWriter_t streamWriter,
        void *userStream,
        int indentLevel,
        int spacesPerLevel);
#ifdef __cplusplus
}

#include <algorithm>
#include <string>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_socks5config
 * @{
 */

namespace BloombergLP {
namespace blpapi {

class SessionOptions;

/*!
 * This class provides a description of Socks5 proxy necessary to reach
 * one or more destination hosts.
 */
/*!
 * See \ref blpapi_socks5config
 */
class Socks5Config {

    blpapi_Socks5Config_t *d_handle;
    // Handle to the internal representation.

  public:
    Socks5Config();
    Socks5Config(const Socks5Config&);
    Socks5Config& operator=(const Socks5Config&);

    Socks5Config(const std::string& hostName, unsigned short port);
    /*!<
     * Constructs a `Socks5Config` object using the specified
     * `hostName` and the specified `port`.
     * Exception is thrown if an empty `hostName` is provided.
     */

    ~Socks5Config();
    /*!<
     * Destructor.
     */

    std::ostream& print(
            std::ostream& stream, int indentLevel, int spacesPerLevel) const;

    //! \cond INTERNAL
    blpapi_Socks5Config_t *impl() const;
    /*!<
     * For internal use only. Returns internal `handle`.
     */
    //! \endcond
};

/** @} */
/** @} */

inline Socks5Config::Socks5Config()
    : d_handle(0)
{
}

inline Socks5Config::Socks5Config(const Socks5Config& socks5Config)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(blpapi_Socks5Config_copy)(
            &d_handle, socks5Config.d_handle));
}

inline Socks5Config& Socks5Config::operator=(const Socks5Config& socks5Config)
{
    Socks5Config copy(socks5Config);
    std::swap(d_handle, copy.d_handle);
    return *this;
}

inline std::ostream& Socks5Config::print(std::ostream& stream,
        int indentLevel = 0,
        int spacesPerLevel = 4) const
{
    BLPAPI_CALL(blpapi_Socks5Config_print)
    (d_handle,
            StreamProxyOstream::writeToStream,
            &stream,
            indentLevel,
            spacesPerLevel);
    return stream;
}

std::ostream& operator<<(
        std::ostream& stream, const Socks5Config& socks5Config);

inline Socks5Config::Socks5Config(
        const std::string& hostname, unsigned short port)
{
    d_handle = BLPAPI_CALL(blpapi_Socks5Config_create)(
            hostname.c_str(), hostname.size(), port);
}

inline Socks5Config::~Socks5Config()
{
    BLPAPI_CALL_UNCHECKED(blpapi_Socks5Config_destroy)(d_handle);
}

inline blpapi_Socks5Config_t *Socks5Config::impl() const { return d_handle; }

inline std::ostream& operator<<(
        std::ostream& stream, const Socks5Config& socks5Config)
{
    socks5Config.print(stream, 0, -1);
    return stream;
}

} // end namespace blpapi
} // end namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_SOCKS5CONFIG
