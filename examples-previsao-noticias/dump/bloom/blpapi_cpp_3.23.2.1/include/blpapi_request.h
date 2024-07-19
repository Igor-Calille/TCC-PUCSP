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

/** \file blpapi_request.h */
/** \defgroup blpapi_request Component blpapi_request
\brief Defines a request which can be sent for a service.
\file blpapi_request.h
\brief Defines a request which can be sent for a service.
*/

#ifndef INCLUDED_BLPAPI_REQUEST
#define INCLUDED_BLPAPI_REQUEST

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_request
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Defines a request which can be sent for a service.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Request</td>
 * <td>a request for a particular service</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This file defines a <code>Request</code>. A generic Request object is
 * created for a service using Service::createRequest() and sent over a session
 * using Session::sendRequest().
 */
/** @} */
/** @} */

#include <blpapi_correlationid.h>
#include <blpapi_defs.h>
#include <blpapi_element.h>
#include <blpapi_exception.h>
#include <blpapi_types.h>

struct blpapi_Request;
typedef struct blpapi_Request blpapi_Request_t;

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
void blpapi_Request_destroy(blpapi_Request_t *request);

BLPAPI_EXPORT
blpapi_Element_t *blpapi_Request_elements(blpapi_Request_t *request);

BLPAPI_EXPORT
void blpapi_Request_setPreferredRoute(
        blpapi_Request_t *request, blpapi_CorrelationId_t *correlationId);

BLPAPI_EXPORT
int blpapi_Request_getRequestId(
        const blpapi_Request_t *request, const char **requestId);

#ifdef __cplusplus
}

#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <string>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_request
 * @{
 */

namespace BloombergLP {
namespace blpapi {

class RequestRef;

/*!
 * A single request to a single service.
 *
 * Request objects are created using Service::createRequest() or
 * Service::createAuthorizationRequest(). They are used with
 * Session::sendRequest() or Session::sendAuthorizationRequest().
 *
 * The Request object contains the parameters for a single request to a single
 * service. Once a Request has been created its fields can be populated
 * directly using the convenience functions set() and append() functions or
 * using the Element interface on the Element returned by asElement().
 *
 * The schema for the Request can be queried using the Element interface on the
 * Element returned by asElement().
 *
 * Request objects cannot be duplicated. Copying a Request causes the original
 * Request to become invalid. The API provides support for common idioms which
 * require a normal copy constructor. For example, you can write the following
 * code.
 * \code
 * Request request(service.createRequest("operationName"));
 * \endcode
 * However, if you write this <code>requestOne</code> will become invalid and
 * unusable.
 * \code
 * Request requestOne(service.createRequest("operationName"));
 * Request requestTwo(requestOne);
 * // At this point requestOne is no longer valid
 * \endcode
 * This should be written as follows.
 * \code
 * Request requestOne(service.createRequest("operationName"));
 * Request requestTwo(service.createRequest("operationName"));
 * \endcode
 */
/*!
 * See \ref blpapi_request
 */
class Request {

    blpapi_Request_t *d_handle;
    Element d_elements;

    /*!  not implemented */
    Request& operator=(const Request& rhs);

  public:
    explicit Request(blpapi_Request_t *handle);

    Request(RequestRef src);
    Request(Request& src);
    /*!<
     * Initialize a Request from the specified non-const <code>src</code>.
     * After this the <code>src</code> Request is invalid.
     */

    ~Request();
    /*!<
     * Destructor.
     */

    operator RequestRef();

    void set(const char *name, bool value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, char value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, Int32 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, Int64 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, Float32 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, Float64 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, const Datetime& value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const char *name, const char *value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, bool value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, char value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, Int32 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, Int64 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, Float32 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, Float64 value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, const Datetime& value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, const char *value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, const std::string& value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void set(const Name& name, const void *value, std::size_t length);
    /*!<
     * Equivalent to asElement().set(name, value, length).
     */

    template <typename BYTES,
            typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type
            = true>
    void set(const Name& name, const BYTES& value);
    /*!<
     * Equivalent to asElement().set(name, value).
     */

    void append(const char *name, bool value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, char value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, Int32 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, Int64 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, Float32 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, Float64 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, const Datetime& value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const char *name, const char *value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, bool value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, char value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, Int32 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, Int64 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, Float32 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, Float64 value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, const Datetime& value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, const char *value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    void append(const Name& name, const std::string& value);
    /*!<
     * Equivalent to asElement().append(name, value).
     */

    Element asElement();
    /*!<
     * Returns the contents of this request as a modifiable Element.
     */

    Element getElement(const char *name);
    /*!<
     * Equivalent to asElement().getElement(name).
     */

    Element getElement(const Name& name);
    /*!<
     * Equivalent to asElement().getElement(name).
     */

    const Element getElement(const char *name) const;
    /*!<
     * Equivalent to asElement().getElement(name).
     */

    const Element getElement(const Name& name) const;
    /*!<
     * Equivalent to asElement().getElement(name).
     */

    const Element asElement() const;
    /*!<
     * Returns the contents of this request as a read-only Element.
     */

    const char *getRequestId() const;
    /*!<
     * Return a pointer offering unmodifiable access to the request's id if one
     * exists, otherwise return null.
     *
     * If there are issues with this request, the request id can be reported to
     * Bloomberg for troubleshooting purposes.
     *
     * Note that request id is not the same as correlation id and should not be
     * used for correlation purposes.
     */

    blpapi_Request_t *handle() const;

    std::ostream& print(
            std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
    /*!<
     * Format this Request to the specified output <code>stream</code> at the
     * (absolute value of) the optionally specified indentation
     * <code>level</code> and return a reference to <code>stream</code>. If
     * <code>level</code> is specified, optionally specify
     * <code>spacesPerLevel</code>, the number of spaces per indentation level
     * for this and all of its nested objects. If <code>level</code> is
     * negative, suppress indentation of the first line. If
     * <code>spacesPerLevel</code> is negative, format the entire output on one
     * line, suppressing all but the initial indentation (as governed by
     * <code>level</code>).
     */
};

/** @} */
/** @} */

std::ostream& operator<<(std::ostream& stream, const Request& request);
/*!<
 * Write the value of the specified <code>request</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified, can change without notice, and is logically
 * equivalent to:
\code
  print(stream, 0, -1);
\endcode
 */

class RequestRef {
    Request *d_request_p;

  public:
    RequestRef(Request *request_p);
    Request *ptr() const;
    Request *operator->() const;
};

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

// -------------
// class Request
// -------------

inline Request::Request(blpapi_Request_t *newHandle)
{
    d_handle = newHandle;
    if (newHandle) {
        d_elements.rebind(blpapi_Request_elements(newHandle));
    }
}

inline Request::Request(RequestRef ref)
{
    Request *src = ref.ptr();
    assert(src);
    d_handle = src->d_handle;
    d_elements = src->d_elements;
    src->d_handle = 0;
    src->d_elements.rebind(0);
}

inline Request::Request(Request& src)
{
    d_handle = src.d_handle;
    d_elements = src.d_elements;
    src.d_handle = 0;
    src.d_elements.rebind(0);
}

inline Request::~Request()
{
    if (d_handle) {
        blpapi_Request_destroy(d_handle);
    }
}

inline Request::operator RequestRef() { return this; }

inline void Request::set(const char *element, bool value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, char value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, Int32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, Int64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, Float32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, Float64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, const Datetime& value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const char *element, const char *value)
{
    d_elements.setElement(element, value);
}

inline void Request::append(const char *element, bool value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, char value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, Int32 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, Int64 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, Float32 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, Float64 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, const Datetime& value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const char *element, const char *value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::set(const Name& element, bool value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, char value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Int32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Int64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Float32 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, Float64 value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, const Datetime& value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, const char *value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(const Name& element, const std::string& value)
{
    d_elements.setElement(element, value);
}

inline void Request::set(
        const Name& element, const void *value, std::size_t length)
{
    d_elements.setElement(element, value, length);
}

template <typename BYTES,
        typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type>
inline void Request::set(const Name& element, const BYTES& value)
{
    d_elements.setElement(element, value);
}

inline void Request::append(const Name& element, bool value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, char value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, Int32 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, Int64 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, Float32 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, Float64 value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, const Datetime& value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, const char *value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline void Request::append(const Name& element, const std::string& value)
{
    Element namedElement = d_elements.getElement(element);
    namedElement.appendValue(value);
}

inline Element Request::getElement(const char *name)
{
    return d_elements.getElement(name);
}

inline Element Request::getElement(const Name& name)
{
    return d_elements.getElement(name);
}

inline Element Request::asElement() { return d_elements; }

inline const Element Request::getElement(const char *name) const
{
    return d_elements.getElement(name);
}

inline const Element Request::getElement(const Name& name) const
{
    return d_elements.getElement(name);
}

inline const Element Request::asElement() const { return d_elements; }

inline const char *Request::getRequestId() const
{
    const char *requestId = 0;
    BLPAPI_CALL(blpapi_Request_getRequestId)(d_handle, &requestId);
    return requestId;
}

inline blpapi_Request_t *Request::handle() const { return d_handle; }

inline std::ostream& Request::print(
        std::ostream& stream, int level, int spacesPerLevel) const
{
    return d_elements.print(stream, level, spacesPerLevel);
}

inline std::ostream& operator<<(std::ostream& stream, const Request& request)
{
    return request.print(stream, 0, -1);
}
// ----------------
// class RequestRef
// ----------------

inline RequestRef::RequestRef(Request *request)
    : d_request_p(request)
{
}

inline Request *RequestRef::ptr() const { return this->d_request_p; }

inline Request *RequestRef::operator->() const { return this->d_request_p; }

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_REQUEST
