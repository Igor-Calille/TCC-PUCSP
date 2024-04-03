/* Copyright 2019. Bloomberg Finance L.P.
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

/** \file blpapi_messageformatter.h */
/** \defgroup blpapi_messageformatter Component blpapi_messageformatter
\brief Format messages for publishing
\file blpapi_messageformatter.h
\brief Format messages for publishing
*/

#ifndef INCLUDED_BLPAPI_MESSAGEFORMATTER
#define INCLUDED_BLPAPI_MESSAGEFORMATTER

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_messageformatter
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Format messages for publishing
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::test::MessageFormatter</td>
 * <td>A Mechanism to format messages.</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component formats messages.
 * \par
 * \par
 * <A NAME="limitations"></A>
 * <A NAME="description.limitations"></A>
 * <A NAME="3.1"> \par Limitations: </A>
 * Currently, the JSON and XML formatting methods have some known limitations.
 * \par
 * The parsers can not differentiate complex field types
 * (sequences, choices, arrays) that are empty with complex field types that
 * are missing / null. These fields are dropped and absent in the message
 * contents.
 * \par
 * Enumerations of type "Datetime", or any "Datetime" element with timezone
 * offset or sub-microsecond precision (e.g. nanoseconds) are not supported.
 */
/** @} */
/** @} */

#include <blpapi_call.h>
#include <blpapi_defs.h>
#include <blpapi_event.h>
#include <blpapi_topic.h>
#include <blpapi_types.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueBool(blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        blpapi_Bool_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueChar(blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        char value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueInt32(blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        blpapi_Int32_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueInt64(blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        blpapi_Int64_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueFloat32(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        blpapi_Float32_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueFloat64(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        blpapi_Float64_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueDatetime(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        const blpapi_Datetime_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueHighPrecisionDatetime(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        const blpapi_HighPrecisionDatetime_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueString(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        const char *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueFromName(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        const blpapi_Name_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueBytes(blpapi_MessageFormatter_t *formatter,
        const blpapi_Name_t *typeName,
        const char *value,
        size_t length);

BLPAPI_EXPORT
int blpapi_MessageFormatter_setValueNull(
        blpapi_MessageFormatter_t *formatter, const blpapi_Name_t *typeName);

BLPAPI_EXPORT
int blpapi_MessageFormatter_pushElement(
        blpapi_MessageFormatter_t *formatter, const blpapi_Name_t *typeName);

BLPAPI_EXPORT
int blpapi_MessageFormatter_popElement(blpapi_MessageFormatter_t *formatter);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueBool(
        blpapi_MessageFormatter_t *formatter, blpapi_Bool_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueChar(
        blpapi_MessageFormatter_t *formatter, char value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueInt32(
        blpapi_MessageFormatter_t *formatter, blpapi_Int32_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueInt64(
        blpapi_MessageFormatter_t *formatter, blpapi_Int64_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueFloat32(
        blpapi_MessageFormatter_t *formatter, blpapi_Float32_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueFloat64(
        blpapi_MessageFormatter_t *formatter, blpapi_Float64_t value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueDatetime(
        blpapi_MessageFormatter_t *formatter, const blpapi_Datetime_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueHighPrecisionDatetime(
        blpapi_MessageFormatter_t *formatter,
        const blpapi_HighPrecisionDatetime_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueString(
        blpapi_MessageFormatter_t *formatter, const char *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendValueFromName(
        blpapi_MessageFormatter_t *formatter, const blpapi_Name_t *value);

BLPAPI_EXPORT
int blpapi_MessageFormatter_appendElement(
        blpapi_MessageFormatter_t *formatter);

BLPAPI_EXPORT
int blpapi_MessageFormatter_FormatMessageJson(
        blpapi_MessageFormatter_t *formatter, const char *message);

BLPAPI_EXPORT
int blpapi_MessageFormatter_FormatMessageXml(
        blpapi_MessageFormatter_t *formatter, const char *message);

BLPAPI_EXPORT
int blpapi_MessageFormatter_copy(blpapi_MessageFormatter_t **formatter,
        const blpapi_MessageFormatter_t *original);

BLPAPI_EXPORT
int blpapi_MessageFormatter_assign(
        blpapi_MessageFormatter_t **lhs, const blpapi_MessageFormatter_t *rhs);

BLPAPI_EXPORT
int blpapi_MessageFormatter_destroy(blpapi_MessageFormatter_t *formatter);

#ifdef __cplusplus
} // extern "C"

#include <string>
#include <type_traits>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_messageformatter
 * @{
 */

namespace BloombergLP {
namespace blpapi {
namespace test {

/*!
 * <code>MessageFormatter</code> is used to populate/format a message. It
 * supports writing once only to each field. Attempting to set an already set
 * element will fail.
 *
 * Note that the behavior is undefined if
 * - A message formatted with <code>formatMessageJson()</code> or
 *   <code>formatMessageXml()</code> is further formatted.
 * - A message formatted with <code>set...()</code> or <code>append...()</code>
 *   is further formatted using
 *   <code>formatMessageJson()/formatMessageXml()</code>.
 */
/*!
 * See \ref blpapi_messageformatter
 */
class MessageFormatter {

  private:
    blpapi_MessageFormatter_t *d_handle;

  public:
    // CREATORS
    explicit MessageFormatter(blpapi_MessageFormatter_t *handle);
    /*!<
     * Creates <code>MessageFormatter</code> from <code>handle</code> and
     * takes ownership of the <code>handle</code>.
     */

    MessageFormatter(const MessageFormatter& original);
    /*!<
     * Creates <code>MessageFormatter</code> from <code>original</code>.
     * Changes made by one copy is visible to the other.
     */

    ~MessageFormatter();
    /*!<
     * Destroy this <code>MessageFormatter</code> and release the
     * <code>d_handle</code>.
     */

    // MANIPULATORS
    MessageFormatter& operator=(const MessageFormatter& rhs);
    /*!<
     * Make this <code>MessageFormatter</code> same as <code>rhs</code>.
     */

    void setElement(const Name& name, bool value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, char value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, Int32 value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, Int64 value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, Float32 value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, Float64 value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, const Datetime& value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, const Datetime::HighPrecision& value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, const char *value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message, or if the element identified by <code>name</code>
     * has already been set an exception is thrown. The behavior is undefined
     * unless <code>value</code> is not <code>NULL</code>. Clients wishing to
     * format null values (e.g. for the purpose of cache management) should
     * <em>not</em> use this function; use <code>setElementNull</code> instead.
     */

    void setElement(const Name& name, const std::string& value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message, or if the element identified by <code>name</code>
     * has already been set an exception is thrown. The behaviour is undefined
     * if the specified <code>value</code> contains embedded zero-characters.
     */

    void setElement(const Name& name, const Name& value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown.
     */

    void setElement(const Name& name, const void *value, size_t length);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> and <code>length</code> in bytes in the current
     * message referenced by this <code>MessageFormatter</code>. If the
     * <code>name</code> is invalid for the current message or if the element
     * identified by <code>name</code> has already been set an exception is
     * thrown. The behavior is undefined unless <code>value</code> is not
     * <code>NULL</code> or <code>length</code> is zero. Clients wishing to
     * format null values (e.g. for the purpose of cache management) should
     * <em>not</em> use this function; use <code>setElementNull</code> instead.
     */

    template <typename BYTES,
            typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type
            = true>
    void setElement(const Name& name, const BYTES& value);
    /*!<
     * Set the element with the specified <code>name</code> to the specified
     * <code>value</code> in the current message referenced by this
     * <code>MessageFormatter</code>. If the <code>name</code> is invalid for
     * the current message or if the element identified by <code>name</code>
     * has already been set an exception is thrown. This function accepts any
     * <code>BYTES</code> that provides <code>const BYTES::value_type *
     * BYTES::data() const</code> method, does not provide
     * <code>BYTES::c_str()</code> method and <code>sizeof(BYTES::value_type)
     * == 1</code>, for example <code>std::vector\<char\></code>. The behaviour
     * of this function is undefined unless <code>data()</code> returns a
     * pointer to a contiguous block of memory.
     */

    void setElementNull(const Name& name);
    /*!<
     * Create a null element with the specified <code>name</code>.  Note that
     * whether or not fields containing null values are published to
     * subscribers is dependent upon details of the service and schema
     * configuration.  If the <code>name</code> is invalid for the current
     * message or if the element identified by <code>name</code> has already
     * been set an exception is thrown.
     */

    void pushElement(const Name& name);
    /*!<
     * Change the level at which this <code>MessageFormatter</code> is
     * operating to the specified element <code>name</code>.  The element
     * <code>name</code> must identify either a choice, a sequence or an array
     * at the current level of the schema or the behavior is undefined.  If the
     * <code>name</code> is invalid for the current message or if the element
     * identified by <code>name</code> has already been set an exception is
     * thrown.
     *
     * After this returns, the context of the <code>MessageFormatter</code> is
     * set to the element <code>name</code> in the schema and any calls to
     * <code>setElement()</code> or <code>pushElement()</code> are applied at
     * that level.
     *
     * If <code>name</code> represents an array of scalars then
     * <code>appendValue()</code> must be used to add values.
     *
     * If <code>name</code> represents an array of complex types then
     * <code>appendElement()</code> must be used.
     */

    void popElement();
    /*!<
     * Undo the most recent call to <code>pushElement()</code> or
     * <code>appendElement()</code> on this <code>MessageFormatter</code> and
     * return the context of the <code>MessageFormatter</code> to where it was
     * before the call to <code>pushElement()</code> or
     * <code>appendElement()</code>. Once <code>popElement()</code> has been
     * called it is invalid to attempt to re-visit the same context.
     */

    void appendValue(bool value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating.  Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(char value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(Int32 value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(Int64 value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(Float32 value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(Float64 value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(const Datetime& value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(const Datetime::HighPrecision& value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(const char *value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendValue(const std::string& value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array. The behaviour is
     * undefined if the specified <code>value</code> contains embedded
     * zero-characters.
     */

    void appendValue(const Name& value);
    /*!<
     * Append the specified <code>value</code> to element on which this
     * <code>MessageFormatter</code> is operating. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array.
     */

    void appendElement();
    /*!<
     * Create an element and append it to the array element on which this
     * <code>MessageFormatter</code> is operating on. Throw an exception if the
     * schema of the message is flat or the current element to which
     * <code>value</code> is appended is not an array, a sequence or a choice.
     */

    void formatMessageJson(const char *message);
    /*!<
     * Format the message from its <code>JSON</code> representation.  An
     * exception is thrown if the method fails to format the message.  The
     * behavior is undefined if further formatting is done using this
     * <code>MessageFormatter</code>.
     */

    void formatMessageXml(const char *message);
    /*!<
     * Format the message from its <code>XML</code> representation.  An
     * exception is thrown if the method fails to format the message.  The
     * behavior is undefined if further formatting is done using this
     * <code>MessageFormatter</code>.
     */

    // ACCESSORS
    blpapi_MessageFormatter_t *impl() const;
    /*!<
     * Returns underlying implementation of <code>MessageFormatter</code>.
     * For <em>internal</em> use only.
     */
};

/** @} */
/** @} */

// ============================================================================
//                      INLINE AND TEMPLATE FUNCTION IMPLEMENTATIONS
// ============================================================================

// ----------------------
// class MessageFormatter
// ----------------------

inline MessageFormatter::MessageFormatter(blpapi_MessageFormatter_t *handle)
    : d_handle(handle)
{
}

inline MessageFormatter::~MessageFormatter()
{
    if (d_handle) {
        BLPAPI_CALL_UNCHECKED(blpapi_MessageFormatter_destroy)(d_handle);
    }
}

inline MessageFormatter::MessageFormatter(const MessageFormatter& original)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(blpapi_MessageFormatter_copy)(
            &d_handle, original.impl()));
}

inline MessageFormatter& MessageFormatter::operator=(
        const MessageFormatter& rhs)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(blpapi_MessageFormatter_assign)(
            &d_handle, rhs.impl()));
    return *this;
}

inline void MessageFormatter::setElement(const Name& name, bool value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueBool)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(const Name& name, char value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueChar)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(const Name& name, Int32 value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueInt32)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(const Name& name, Int64 value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueInt64)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(const Name& name, Float32 value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueFloat32)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(const Name& name, Float64 value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueFloat64)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(
        const Name& name, const Datetime& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueDatetime)(
                    d_handle, name.impl(), &value.rawValue()));
}

inline void MessageFormatter::setElement(
        const Name& name, const Datetime::HighPrecision& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueHighPrecisionDatetime)(
                    d_handle, name.impl(), &value));
}

inline void MessageFormatter::setElement(const Name& name, const char *value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueString)(
                    d_handle, name.impl(), value));
}

inline void MessageFormatter::setElement(
        const Name& name, const std::string& value)
{
    setElement(name, value.c_str());
}

inline void MessageFormatter::setElement(const Name& name, const Name& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueFromName)(
                    d_handle, name.impl(), value.impl()));
}

inline void MessageFormatter::setElement(
        const Name& name, const void *value, size_t length)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_setValueBytes)(d_handle,
                    name.impl(),
                    reinterpret_cast<const char *>(value),
                    length));
}

template <typename BYTES,
        typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type>
inline void MessageFormatter::setElement(const Name& name, const BYTES& value)
{
    setElement(name, value.data(), value.size());
}

inline void MessageFormatter::setElementNull(const Name& name)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_setValueNull)(d_handle, name.impl()));
}

inline void MessageFormatter::pushElement(const Name& name)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_pushElement)(d_handle, name.impl()));
}

inline void MessageFormatter::popElement()
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_popElement)(d_handle));
}

inline void MessageFormatter::appendValue(bool value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueBool)(d_handle, value));
}

inline void MessageFormatter::appendValue(char value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueChar)(d_handle, value));
}

inline void MessageFormatter::appendValue(Int32 value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueInt32)(d_handle, value));
}

inline void MessageFormatter::appendValue(Int64 value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueInt64)(d_handle, value));
}

inline void MessageFormatter::appendValue(Float32 value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueFloat32)(d_handle, value));
}

inline void MessageFormatter::appendValue(Float64 value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueFloat64)(d_handle, value));
}

inline void MessageFormatter::appendValue(const Datetime& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_appendValueDatetime)(
                    d_handle, &value.rawValue()));
}

inline void MessageFormatter::appendValue(const Datetime::HighPrecision& value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueHighPrecisionDatetime)(
            d_handle, &value));
}

inline void MessageFormatter::appendValue(const char *value)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_appendValueString)(d_handle, value));
}

inline void MessageFormatter::appendValue(const std::string& value)
{
    appendValue(value.c_str());
}

inline void MessageFormatter::appendValue(const Name& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_appendValueFromName)(
                    d_handle, value.impl()));
}

inline void MessageFormatter::appendElement()
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_MessageFormatter_appendElement)(d_handle));
}

inline blpapi_MessageFormatter_t *MessageFormatter::impl() const
{
    return d_handle;
}

inline void MessageFormatter::formatMessageJson(const char *message)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_FormatMessageJson)(d_handle, message));
}

inline void MessageFormatter::formatMessageXml(const char *message)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(
            blpapi_MessageFormatter_FormatMessageXml)(d_handle, message));
}

} // close namespace test

// *Deprecated*
// Following typedef is provided for backwards compatibility. It will be
// removed in a future release.
typedef test::MessageFormatter MessageFormatter;

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_MESSAGEFORMATTER
