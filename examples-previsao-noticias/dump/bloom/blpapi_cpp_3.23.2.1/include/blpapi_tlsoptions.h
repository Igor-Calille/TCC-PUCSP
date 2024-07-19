/* Copyright 2016. Bloomberg Finance L.P.
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

/** \file blpapi_tlsoptions.h */
/** \defgroup blpapi_tlsoptions Component blpapi_tlsoptions
\brief Maintain client credentials and trust material.
\file blpapi_tlsoptions.h
\brief Maintain client credentials and trust material.
*/

#ifndef INCLUDED_BLPAPI_TLSOPTIONS
#define INCLUDED_BLPAPI_TLSOPTIONS

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_tlsoptions
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Maintain client credentials and trust material.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::TlsOptions</td>
 * <td>user specified TLS options.</td>
 * </tr>
 * </table>
 * \par
 * \sa  blpapi_sessionoptions
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  TlsOptions instances maintain client credentials and
 * trust material used by a session to establish secure mutually authenticated
 * connections to endpoints.
 * \par
 * The client credentials comprise an encrypted private key with a client
 * certificate. The trust material comprises one or more certificates.
 * \par
 * TlsOptions objects are created using the methods
 * <code>TlsOptions::createFromBlobs</code> and
<code>TlsOptions::createFromFiles</code>; both accept
 * the DER encoded client credentials in PKCS\#12 format and the DER encoded
 * trusted material in PKCS\#7 format.
 * \par
 * \par
 * \par
 * <A NAME="usage"></A>
 * <A NAME="description.usage"></A>
 * <A NAME="3.1"> \par Usage: </A>
 * The following snippet shows to use the TlsOptions when creating a
 * <code>SessionOptions</code>.
\code{.cpp}
 blpapi::TlsOptions tlsOptionsFromFiles
     = blpapi::TlsOptions::createFromFiles("client",
                                           "mypassword",
                                           "trusted");
 tlsOptionsFromFiles.setTlsHandshakeTimeoutMs(123456);
 SessionOptions sessionOptions1;
 sessionOptions1.setTlsOptions(tlsOptionsFromFiles);

 std::string credentials  = getCredentials();
 std::string password     = getPassword();
 std::string trustedCerts = getCerts();
 blpapi::TlsOptions tlsOptionsFromBlobs
     = blpapi::TlsOptions::createFromBlobs(credentials.data(),
                                           credentials.size(),
                                           password.c_str(),
                                           trustedCerts.data(),
                                           trustedCerts.size());
 tlsOptionsFromBlobs.setCrlFetchTimeoutMs(234567);
 SessionOptions sessionOptions2;
 sessionOptions2.setTlsOptions(tlsOptionsFromBlobs);
\endcode
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_TlsOptions_t *blpapi_TlsOptions_create(void);

BLPAPI_EXPORT
blpapi_TlsOptions_t *blpapi_TlsOptions_duplicate(
        const blpapi_TlsOptions_t *parameters);

BLPAPI_EXPORT
void blpapi_TlsOptions_copy(
        blpapi_TlsOptions_t *lhs, const blpapi_TlsOptions_t *rhs);

BLPAPI_EXPORT
void blpapi_TlsOptions_destroy(blpapi_TlsOptions_t *parameters);

BLPAPI_EXPORT
blpapi_TlsOptions_t *blpapi_TlsOptions_createFromFiles(
        const char *clientCredentialsFileName,
        const char *clientCredentialsPassword,
        const char *trustedCertificatesFileName);

BLPAPI_EXPORT
blpapi_TlsOptions_t *blpapi_TlsOptions_createFromBlobs(
        const char *clientCredentialsRawData,
        int clientCredentialsRawDataLength,
        const char *clientCredentialsPassword,
        const char *trustedCertificatesRawData,
        int trustedCertificatesRawDataLength);

BLPAPI_EXPORT
void blpapi_TlsOptions_setTlsHandshakeTimeoutMs(
        blpapi_TlsOptions_t *paramaters, int tlsHandshakeTimeoutMs);

BLPAPI_EXPORT
void blpapi_TlsOptions_setCrlFetchTimeoutMs(
        blpapi_TlsOptions_t *paramaters, int crlFetchTimeoutMs);

#ifdef __cplusplus
}

#include <cassert>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_tlsoptions
 * @{
 */

namespace BloombergLP {
namespace blpapi {

// ================
// class TlsOptions
// ================

/*!
 * Contains the user specified TLS options.
 *
 * To enable SSL connections, create a TlsOptions object using the methods
 * <code>TlsOptions::createFromBlobs</code> and
 * <code>TlsOptions::createFromFiles</code>.
 */
/*!
 * See \ref blpapi_tlsoptions
 */
class TlsOptions {

  private:
    blpapi_TlsOptions_t *d_handle_p;

    explicit TlsOptions(blpapi_TlsOptions_t *handle);
    /*!<
     * Create a TlsOptions from the specified <code>handle</code>.
     */

  public:
    TlsOptions();
    /*!<
     * Create a TlsOptions with all TLS options with no certificate
     * information.
     */

    TlsOptions(const TlsOptions&);
    /*!<
     * Copy constructor
     */

    ~TlsOptions();
    /*!<
     * Destroy this TlsOptions.
     */

    // MANIPULATORS

    TlsOptions& operator=(const TlsOptions& rhs);
    /*!<
     * Assign to this object the value of the specified <code>rhs</code>
     * object.
     */

    static TlsOptions createFromFiles(const char *clientCredentialsFileName,
            const char *clientCredentialsPassword,
            const char *trustedCertificatesFileName);
    /*!<
     * Creates a TlsOptions using a DER encoded client credentials in PKCS\#12
     * format and DER encoded trust material in PKCS\#7 format from the
     * specified files.
     */

    static TlsOptions createFromBlobs(const char *clientCredentialsRawData,
            int clientCredentialsRawDataLength,
            const char *clientCredentialsPassword,
            const char *trustedCertificatesRawData,
            int trustedCertificatesRawDataLength);
    /*!<
     * Create a TlsOptions using DER encoded client credentials in PKCS\#12
     * format and DER encoded trust material in PKCS\#7 format from the
     * specified raw data.
     */

    void setTlsHandshakeTimeoutMs(int tlsHandshakeTimeoutMs);
    /*!<
     * Set the TLS handshake timeout to the specified
     * <code>tlsHandshakeTimeoutMs</code>. The default is 10,000 milliseconds.
     * The TLS handshake timeout will be set to the default if the specified
     * <code>tlsHandshakeTimeoutMs</code> is not positive.
     */

    void setCrlFetchTimeoutMs(int crlFetchTimeoutMs);
    /*!<
     * Set the CRL fetch timeout to the specified
     * <code>crlFetchTimeoutMs</code>. The default is 20,000 milliseconds.  The
     * TLS handshake timeout will be set to the default if the specified
     * <code>crlFetchTimeoutMs</code> is not positive.
     */

    // ACCESSORS

    blpapi_TlsOptions_t *handle() const;
    /*!<
     * Return the handle of the current TLS options.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// ----------------
// class TlsOptions
// ----------------
inline TlsOptions::TlsOptions(blpapi_TlsOptions_t *handle)
    : d_handle_p(handle)
{
    assert(d_handle_p);
}

inline TlsOptions::TlsOptions()
{
    d_handle_p = BLPAPI_CALL(blpapi_TlsOptions_create)();
}

inline TlsOptions::TlsOptions(const TlsOptions& options)
{
    d_handle_p = BLPAPI_CALL(blpapi_TlsOptions_duplicate)(options.handle());
}

inline TlsOptions::~TlsOptions()
{
    BLPAPI_CALL_UNCHECKED(blpapi_TlsOptions_destroy)(d_handle_p);
}

inline TlsOptions& TlsOptions::operator=(const TlsOptions& rhs)
{
    BLPAPI_CALL(blpapi_TlsOptions_copy)(this->handle(), rhs.handle());
    return *this;
}

inline TlsOptions TlsOptions::createFromFiles(
        const char *clientCredentialsFileName,
        const char *clientCredentialsPassword,
        const char *trustedCertificatesFileName)
{
    blpapi_TlsOptions_t *handle = BLPAPI_CALL(
            blpapi_TlsOptions_createFromFiles)(clientCredentialsFileName,
            clientCredentialsPassword,
            trustedCertificatesFileName);
    return TlsOptions(handle);
}

inline TlsOptions TlsOptions::createFromBlobs(
        const char *clientCredentialsRawData,
        int clientCredentialsRawDataLength,
        const char *clientCredentialsPassword,
        const char *trustedCertificatesRawData,
        int trustedCertificatesRawDataLength)
{
    blpapi_TlsOptions_t *handle = BLPAPI_CALL(
            blpapi_TlsOptions_createFromBlobs)(clientCredentialsRawData,
            clientCredentialsRawDataLength,
            clientCredentialsPassword,
            trustedCertificatesRawData,
            trustedCertificatesRawDataLength);
    return TlsOptions(handle);
}

inline void TlsOptions::setTlsHandshakeTimeoutMs(int tlsHandshakeTimeoutMs)
{
    BLPAPI_CALL(blpapi_TlsOptions_setTlsHandshakeTimeoutMs)
    (d_handle_p, tlsHandshakeTimeoutMs);
}

inline void TlsOptions::setCrlFetchTimeoutMs(int crlFetchTimeoutMs)
{
    BLPAPI_CALL(blpapi_TlsOptions_setCrlFetchTimeoutMs)
    (d_handle_p, crlFetchTimeoutMs);
}

inline blpapi_TlsOptions_t *TlsOptions::handle() const { return d_handle_p; }

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_TLSOPTIONS
