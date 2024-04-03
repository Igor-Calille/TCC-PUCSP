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

/** \file blpapi_exception.h */
/** \defgroup blpapi_exception Component blpapi_exception
\brief Defines Exceptions that can be thrown by the blpapi library.
\file blpapi_exception.h
\brief Defines Exceptions that can be thrown by the blpapi library.
*/

#ifndef INCLUDED_BLPAPI_EXCEPTION
#define INCLUDED_BLPAPI_EXCEPTION

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_exception
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Defines Exceptions that can be thrown by the blpapi library.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi_ErrorInfo</td>
 * <td>C struct to get more info on error</td>
 * </tr>
 * <tr>
 * <td>blpapi::Exception</td>
 * <td>Base class from all exceptions</td>
 * </tr>
 * <tr>
 * <td>blpapi::DuplicateCorrelationIdException</td>
 * <td>Duplicate CorrelationId exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::InvalidStateException</td>
 * <td>Invalid state exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::InvalidArgumentException</td>
 * <td>Invalid argument exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::InvalidConversionException</td>
 * <td>Invalid conversion exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::IndexOutOfRangeException</td>
 * <td>Index out of range exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::FieldNotFoundException</td>
 * <td>Field not found exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::NotFoundException</td>
 * <td>Not present exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::UnknownErrorException</td>
 * <td>Unknown error exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::UnsupportedOperationException</td>
 * <td>Unsupported operation exception</td>
 * </tr>
 * <tr>
 * <td>blpapi::ExceptionUtil</td>
 * <td>Internal exception generating class</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This file defines various exceptions that blpapi can throw.
 * \par
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_ERROR
#include <blpapi_error.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_exception
 * @{
 */
struct blpapi_ErrorInfo {
    int exceptionClass;
    char description[256];
};

typedef struct blpapi_ErrorInfo blpapi_ErrorInfo_t;

BLPAPI_EXPORT
int blpapi_getErrorInfo(blpapi_ErrorInfo_t *buffer, int errorCode);

#ifdef __cplusplus
} // extern "C"

/** @} */
/** @} */

#ifndef INCLUDED_EXCEPTION
#include <exception>
#define INCLUDED_EXCEPTION
#endif

#ifndef INCLUDED_STRING
#include <string>
#define INCLUDED_STRING
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_exception
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 *     This class defines a base exception for blpapi operations.  Objects of
 *     this class contain the error description for the exception.
 */
/*!
 * See \ref blpapi_exception
 */
class Exception : public std::exception {

    const std::string d_description;

  private:
    // NOT IMPLEMENTED
    Exception& operator=(const Exception&); // = delete

  public:
    // CREATORS
    explicit Exception(const std::string& description);
    /*!<
     *     Create an exception object initialized with the specified
     *     <code>description</code>.
     */

    // ACCESSORS
    const std::string& description() const throw();
    /*!<
     *     Return the error description supplied at construction.
     */

    virtual const char *what() const throw();
    /*!<
     *     Return the error description supplied at construction as a
     *     null-terminated character sequence.
     */

    virtual ~Exception() throw();
    /*!<
     *     Destroy this object.
     */
};

/*!
 * The class defines an exception for non unique
 * <code>blpapi::CorrelationId</code>.
 */
/*!
 * See \ref blpapi_exception
 */
class DuplicateCorrelationIdException : public Exception {
  public:
    // CREATORS
    explicit DuplicateCorrelationIdException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception for calling methods on an object that is not
 * in a valid state.
 */
/*!
 * See \ref blpapi_exception
 */
class InvalidStateException : public Exception {
  public:
    // CREATORS
    explicit InvalidStateException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception for invalid arguments on method invocations.
 */
/*!
 * See \ref blpapi_exception
 */
class InvalidArgumentException : public Exception {
  public:
    // CREATORS
    explicit InvalidArgumentException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception for invalid conversion of data.
 */
/*!
 * See \ref blpapi_exception
 */
class InvalidConversionException : public Exception {
  public:
    // CREATORS
    explicit InvalidConversionException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception to capture the error when an invalid index
 * is used for an operation that needs index.
 */
/*!
 * See \ref blpapi_exception
 */
class IndexOutOfRangeException : public Exception {
  public:
    // CREATORS
    explicit IndexOutOfRangeException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * \deprecated This exception is not used.
 *
 * This class defines an exception to capture the error when an invalid field
 * is used for operation.
 */
/*!
 * See \ref blpapi_exception
 */
class FieldNotFoundException : public Exception {
  public:
    // CREATORS
    explicit FieldNotFoundException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception for errors that do not fall in any
 * predefined category.
 */
/*!
 * See \ref blpapi_exception
 */
class UnknownErrorException : public Exception {
  public:
    // CREATORS
    explicit UnknownErrorException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception for unsupported operations.
 */
/*!
 * See \ref blpapi_exception
 */
class UnsupportedOperationException : public Exception {
  public:
    // CREATORS
    explicit UnsupportedOperationException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class defines an exception to capture the error when an item is not
 * found for an operation.
 */
/*!
 * See \ref blpapi_exception
 */
class NotFoundException : public Exception {
  public:
    // CREATORS
    explicit NotFoundException(const std::string& description);
    /*!<
     * Create an exception object initialized with the specified
     * <code>description</code>.
     */
};

/*!
 * This class provides a namespace for utility functions that convert C-style
 * error codes to <code>blpapi::Exception</code> objects.
 */
/*!
 * See \ref blpapi_exception
 */
class ExceptionUtil {

  private:
    static void throwException(int errorCode);
    /*!<
     * Throw the appropriate exception for the specified
     * <code>errorCode</code>.
     */

  public:
    static void throwOnError(int errorCode);
    /*!<
     * Throw the appropriate exception for the specified <code>errorCode</code>
     * if the errorCode is not 0.
     */
};

/** @} */
/** @} */

// ============================================================================
//                        INLINE FUNCTION DEFINITIONS
// ============================================================================

// ---------------
// class Exception
// ---------------

inline Exception::Exception(const std::string& newDescription)
    : d_description(newDescription)
{
}

inline Exception::~Exception() throw() { }

inline const std::string& Exception::description() const throw()
{
    return d_description;
}

inline const char *Exception::what() const throw()
{
    return description().c_str();
}

// -------------------------------------
// class DuplicateCorrelationIdException
// -------------------------------------

inline DuplicateCorrelationIdException::DuplicateCorrelationIdException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// ---------------------------
// class InvalidStateException
// ---------------------------

inline InvalidStateException::InvalidStateException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// ------------------------------
// class InvalidArgumentException
// ------------------------------

inline InvalidArgumentException::InvalidArgumentException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// --------------------------------
// class InvalidConversionException
// --------------------------------

inline InvalidConversionException::InvalidConversionException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// ------------------------------
// class IndexOutOfRangeException
// ------------------------------

inline IndexOutOfRangeException::IndexOutOfRangeException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// ----------------------------
// class FieldNotFoundException
// ----------------------------

inline FieldNotFoundException::FieldNotFoundException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// ---------------------------
// class UnknownErrorException
// ---------------------------

inline UnknownErrorException::UnknownErrorException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// -----------------------------------
// class UnsupportedOperationException
// -----------------------------------

inline UnsupportedOperationException::UnsupportedOperationException(
        const std::string& newDescription)
    : Exception(newDescription)
{
}

// -----------------------
// class NotFoundException
// -----------------------

inline NotFoundException::NotFoundException(const std::string& newDescription)
    : Exception(newDescription)
{
}

// -------------------
// class ExceptionUtil
// -------------------

inline void ExceptionUtil::throwException(int errorCode)
{
    const char *description = blpapi_getLastErrorDescription(errorCode);
    if (!description) {
        description = "Unknown";
    }

    if (BLPAPI_ERROR_DUPLICATE_CORRELATIONID == errorCode) {
        throw DuplicateCorrelationIdException(description);
    }

    switch (BLPAPI_RESULTCLASS(errorCode))
    case BLPAPI_INVALIDSTATE_CLASS: {
        throw InvalidStateException(description);
    case BLPAPI_INVALIDARG_CLASS:
        throw InvalidArgumentException(description);
    case BLPAPI_CNVERROR_CLASS:
        throw InvalidConversionException(description);
    case BLPAPI_BOUNDSERROR_CLASS:
        throw IndexOutOfRangeException(description);
    case BLPAPI_FLDNOTFOUND_CLASS:
        throw FieldNotFoundException(description);
    case BLPAPI_UNSUPPORTED_CLASS:
        throw UnsupportedOperationException(description);
    case BLPAPI_NOTFOUND_CLASS:
        throw NotFoundException(description);
    default:
        throw Exception(description);
    }
}

inline void ExceptionUtil::throwOnError(int errorCode)
{
    if (errorCode) {
        throwException(errorCode);
    }
}

} // close namespace blpapi {
} // close namespace BloombergLP {

#endif

#endif // #ifndef INCLUDED_BLPAPI_EXCEPTION
