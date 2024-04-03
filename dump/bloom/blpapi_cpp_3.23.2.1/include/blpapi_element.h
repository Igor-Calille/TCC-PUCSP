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

/** \file blpapi_element.h */
/** \defgroup blpapi_element Component blpapi_element
\brief Provide a representation of an item in a message.
\file blpapi_element.h
\brief Provide a representation of an item in a message.
*/

#ifndef INCLUDED_BLPAPI_ELEMENT
#define INCLUDED_BLPAPI_ELEMENT

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_element
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a representation of an item in a message.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Element</td>
 * <td>Represents an item in a message</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a representation of an item in a
 * <code>Message</code>.
 */
/** @} */
/** @} */

#include <blpapi_call.h>
#include <blpapi_datetime.h>
#include <blpapi_defs.h>
#include <blpapi_name.h>
#include <blpapi_schema.h>
#include <blpapi_streamproxy.h>
#include <blpapi_types.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT blpapi_Name_t *blpapi_Element_name(
        const blpapi_Element_t *element);

BLPAPI_EXPORT const char *blpapi_Element_nameString(
        const blpapi_Element_t *element);

BLPAPI_EXPORT blpapi_SchemaElementDefinition_t *blpapi_Element_definition(
        const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_datatype(const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_isComplexType(
        const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_isArray(const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_isReadOnly(const blpapi_Element_t *element);

BLPAPI_EXPORT size_t blpapi_Element_numValues(const blpapi_Element_t *element);

BLPAPI_EXPORT size_t blpapi_Element_numElements(
        const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_isNullValue(
        const blpapi_Element_t *element, size_t position);

BLPAPI_EXPORT int blpapi_Element_isNull(const blpapi_Element_t *element);

BLPAPI_EXPORT int blpapi_Element_print(const blpapi_Element_t *element,
        blpapi_StreamWriter_t streamWriter,
        void *stream,
        int level,
        int spacesPerLevel);

BLPAPI_EXPORT
int blpapi_Element_getElementAt(const blpapi_Element_t *element,
        blpapi_Element_t **result,
        size_t position);

BLPAPI_EXPORT
int blpapi_Element_getElement(const blpapi_Element_t *element,
        blpapi_Element_t **result,
        const char *nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Element_hasElement(const blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
int blpapi_Element_hasElementEx(const blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        int excludeNullElements,
        int reserved);

BLPAPI_EXPORT
int blpapi_Element_getValueAsBool(
        const blpapi_Element_t *element, blpapi_Bool_t *buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsChar(
        const blpapi_Element_t *element, blpapi_Char_t *buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsInt32(
        const blpapi_Element_t *element, blpapi_Int32_t *buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsInt64(
        const blpapi_Element_t *element, blpapi_Int64_t *buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsFloat32(const blpapi_Element_t *element,
        blpapi_Float32_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsFloat64(const blpapi_Element_t *element,
        blpapi_Float64_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsString(
        const blpapi_Element_t *element, const char **buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsDatetime(const blpapi_Element_t *element,
        blpapi_Datetime_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsHighPrecisionDatetime(
        const blpapi_Element_t *element,
        blpapi_HighPrecisionDatetime_t *buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsElement(const blpapi_Element_t *element,
        blpapi_Element_t **buffer,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsName(
        const blpapi_Element_t *element, blpapi_Name_t **buffer, size_t index);

BLPAPI_EXPORT
int blpapi_Element_getValueAsBytes(const blpapi_Element_t *element,
        const char **buffer,
        size_t *length,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_getChoice(
        const blpapi_Element_t *element, blpapi_Element_t **result);

BLPAPI_EXPORT
int blpapi_Element_setValueBool(
        blpapi_Element_t *element, blpapi_Bool_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueChar(
        blpapi_Element_t *element, blpapi_Char_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueInt32(
        blpapi_Element_t *element, blpapi_Int32_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueInt64(
        blpapi_Element_t *element, blpapi_Int64_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFloat32(
        blpapi_Element_t *element, blpapi_Float32_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFloat64(
        blpapi_Element_t *element, blpapi_Float64_t value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueString(
        blpapi_Element_t *element, const char *value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueDatetime(blpapi_Element_t *element,
        const blpapi_Datetime_t *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueHighPrecisionDatetime(blpapi_Element_t *element,
        const blpapi_HighPrecisionDatetime_t *value,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueBytes(blpapi_Element_t *element,
        const char *value,
        size_t length,
        size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFromElement(
        blpapi_Element_t *element, blpapi_Element_t *value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setValueFromName(
        blpapi_Element_t *element, const blpapi_Name_t *value, size_t index);

BLPAPI_EXPORT
int blpapi_Element_setElementBool(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Bool_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementChar(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Char_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementInt32(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Int32_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementInt64(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Int64_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementFloat32(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Float32_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementFloat64(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Float64_t value);

BLPAPI_EXPORT
int blpapi_Element_setElementString(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        const char *value);

BLPAPI_EXPORT
int blpapi_Element_setElementDatetime(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        const blpapi_Datetime_t *value);

BLPAPI_EXPORT
int blpapi_Element_setElementHighPrecisionDatetime(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        const blpapi_HighPrecisionDatetime_t *value);

BLPAPI_EXPORT
int blpapi_Element_setElementBytes(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        const char *value,
        size_t length);

BLPAPI_EXPORT
int blpapi_Element_setElementFromField(blpapi_Element_t *element,
        const char *nameString,
        const blpapi_Name_t *name,
        blpapi_Element_t *sourcebuffer);

BLPAPI_EXPORT
int blpapi_Element_setElementFromName(blpapi_Element_t *element,
        const char *elementName,
        const blpapi_Name_t *name,
        const blpapi_Name_t *buffer);

BLPAPI_EXPORT
int blpapi_Element_appendElement(
        blpapi_Element_t *element, blpapi_Element_t **appendedElement);

BLPAPI_EXPORT
int blpapi_Element_setChoice(blpapi_Element_t *element,
        blpapi_Element_t **resultElement,
        const char *nameCstr,
        const blpapi_Name_t *name,
        size_t index);

#ifdef __cplusplus
}

#include <blpapi_exception.h>

#include <cassert>
#include <string>
#include <type_traits>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_element
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * Element represents an item in a message.
 *
 * An Element can represent: a single value of any data type supported by
 * the Bloomberg API; an array of values; a sequence or a choice.
 *
 * The value(s) in an Element can be queried in a number of ways. For an
 * Element which represents a single value or an array of values use the
 * getValueAs() functions or getValueAsBool() etc. For an Element which
 * represents a sequence or choice use getElementAsBool() etc. In addition,
 * for choices and sequences, hasElement() and getElement() are useful.
 *
 * This example shows how to access the value of a scalar element
 * <code>s</code> as a floating point number:
 *
 * \code
 * float f = s.getValueAsFloat32();
 * \endcode
 *
 * Similarly, this example shows how to retrieve the third value in an
 * array element <code>a</code>, as a floating pointer number:
 *
 * \code
 * float f = a.getValueAsFloat32(2);
 * \endcode
 *
 * Use numValues() to determine the number of values available. For single
 * values, it will return either 0 or 1. For arrays it will return the actual
 * number of values in the array.
 *
 * To retrieve values from a complex element types (sequences and choices) use
 * the getElementAs...() family of methods. This example shows how to get the
 * value of the element <code>city</code> in the sequence element
 * <code>address</code>:
 *
 * \code
 * static const Name k_city { "city" };
 * const char* city = address.getElementAsString(k_city);
 * \endcode
 *
 * The value(s) of an Element can be set in a number of ways. For an Element
 * which represents a single value or an array of values use the setValue() or
 * appendValue() functions. For an element which represents a sequence or a
 * choice use the setElement() functions.
 *
 * This example shows how to set the value of an Element <code>s</code> from an
 * integer:
 *
 * \code
 * Int32 value=5;
 * s.setValue(value);
 * \endcode
 *
 * This example shows how to append an integer a value to an array element
 * <code>a</code>:
 *
 * \code
 * Int32 value=5;
 * s.appendValue(value);
 * \endcode
 *
 * To set values in a complex element (a sequence or a choice) use the
 * setElement() family of functions. This example shows how to set the value of
 * the element <code>city</code> in the sequence element <code>address</code>
 * to a string.
 *
 * \code
 * static const Name k_city { "city" };
 * Element address;
 * ...
 * address.setElement(k_city, "New York");
 * \endcode
 *
 * The API will convert data types as long as there is no loss of precision
 * involved. So:
 *
 * - A BOOL can be returned as bool, char, Int32, Int64, Float32, Float64,
 *   std::string (the string will be "true" or "false")
 *
 * - A BOOL can be set from bool, std::string (if it has a value of "y", "n",
 *   "yes", "no", "true" or "false")
 *
 * - A CHAR can be returned as char, Int32, Int64, Float32, Float64,
 *   std::string
 *
 * - A CHAR can be set from char
 *
 * - An INT32 can be returned as Int32, Int64, Float64, std::string
 *
 * - An INT32 can be set from char, Int32, Int64 if the value is in Int32
 *   range.
 *
 * - An INT64 can be returned as Int64, std::string
 *
 * - An INT64 can be set from char, Int32, Int64
 *
 * - A FLOAT32 can be returned as Float32, Float64, std::string
 *
 * - A FLOAT32 can be set from char
 *
 * - A FLOAT64 can be returned as Float64, std::string
 *
 * - A FLOAT64 can be set from char, Int32, Float32
 *
 * - A STRING can be returned as std::string, Name
 *
 * - A STRING can be set from bool (the string will be set to "true" or
 * "false"), char, Int32, Int64, Float32, Float64, Name
 *
 * - A DATETIME can be returned as Datetime
 *
 * - A DATETIME can be set from Datetime
 *
 * - A BYTEARRAY can be set from a type that represents a contiguous sequence
 *   of bytes and returned as blpapi::Bytes.
 */
/*!
 * See \ref blpapi_element
 */
class Element {

    blpapi_Element_t *d_handle_p;

  public:
    Element();
    /*!<
     * Create an uninitialized Element. The only valid operations to
     * perform on an uninitialized Element are assignment, isValid() and
     * destruction.
     */

    Element(blpapi_Element_t *element);

    // MANIPULATORS

    void rebind(blpapi_Element_t *element);

    void setElement(const char *name, bool value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, char value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, Int32 value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, Int64 value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, Float32 value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, Float64 value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, const Datetime& value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, const char *value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined unless <code>name</code> is a
     * valid null-terminated string.
     */

    void setElement(const char *name, const Name& value);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element.
     * An exception is also thrown if the specified Element's type is not an
     * enumeration type, or if <code>value</code> does not refer to a constant
     * in the enumeration type of the specified Element. The behavior of this
     * function is undefined unless <code>name</code> is a valid
     * null-terminated string.
     */

    void setElement(const Name& name, bool value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, char value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, Int32 value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, Int64 value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, Float32 value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, Float64 value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, const Datetime& value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, const char *value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized.
     */

    void setElement(const Name& name, const std::string& value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> cannot
     * be initialized from the type of the specified <code>value</code>. The
     * behavior of this function is undefined if <code>name</code> is
     * uninitialized. The behaviour is undefined if the specified
     * <code>value</code> contains embedded zero-characters.
     */

    void setElement(const Name& name, const Name& value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element.
     * An exception is also thrown if the specified Element's type is not an
     * enumeration type, or if <code>value</code> does not refer to a constant
     * in the enumeration type of the specified Element. The behavior of this
     * function is undefined if <code>name</code> is uninitialized.
     */

    void setElement(const Name& name, const void *value, size_t length);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code> and
     * <code>length</code> in bytes. An exception is thrown if the specified
     * <code>name</code> is not valid for this Element, or if the Element
     * identified by the specified <code>name</code> does not have the data
     * type <code>BYTEARRAY</code>. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    template <typename BYTES,
            typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type
            = true>
    void setElement(const Name& name, const BYTES& value);
    /*!<
     * Set the specified element <code>name</code> within this sequence or
     * choice Element to the specified <code>value</code>. An exception is
     * thrown if the specified <code>name</code> is not valid for this Element,
     * or if the Element identified by the specified <code>name</code> does not
     * have the data type <code>BYTEARRAY</code>. The behavior of this function
     * is undefined if <code>name</code> is uninitialized. This function
     * accepts any <code>BYTES</code> that provides <code>const
     * BYTES::value_type * BYTES::data() const</code> method, does not provide
     * <code>BYTES::c_str()</code> method and <code>sizeof(BYTES::value_type)
     * == 1</code>, for example <code>std::vector\<char\></code>. The behaviour
     * of this function is undefined unless <code>data()</code> returns a
     * pointer to a contiguous block of memory.
     */

    void setValue(bool value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(char value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(Int32 value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(Int64 value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(Float32 value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(Float64 value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(const Datetime& value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(const char *value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>.
     */

    void setValue(const std::string& value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType means it cannot be initialized from an instance
     * of the supplied <code>value</code>. An exception is thrown if
     * <code>index \>= numValues()</code>. The behaviour is undefined if the
     * specified <code>value</code> contains embedded zero-characters.
     */

    void setValue(const Name& valueName, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>valueName</code>. An exception is thrown
     * if this element's datatype is not an enumeration type, or if
     * <code>valueName</code> does not refer to a constant in the enumeration
     * type of this element. An exception is also thrown if <code>index \>=
     * numValues()</code>.
     */

    void setValue(const void *value, size_t length, size_t index);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code> and <code>length</code> in
     * bytes. An exception is thrown if this Element's DataType is not
     * <code>BYTEARRAY</code>. An exception is also thrown if <code>index \>=
     * numValues()</code>.
     */

    template <typename BYTES,
            typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type
            = true>
    void setValue(const BYTES& value, size_t index = 0);
    /*!<
     * Set the value of the specified <code>index</code>th entry in this
     * Element to the specified <code>value</code>. An exception is thrown if
     * this Element's DataType is not <code>BYTEARRAY</code>. An exception is
     * also thrown if <code>index \>= numValues()</code>. This function accepts
     * any <code>BYTES</code> that provides <code>const BYTES::value_type *
     * BYTES::data() const</code> method, does not provide
     * <code>BYTES::c_str()</code> method and <code>sizeof(BYTES::value_type)
     * == 1</code>, for example <code>std::vector\<char\></code>. The behaviour
     * of this function is undefined unless <code>data()</code> returns a
     * pointer to a contiguous block of memory.
     */

    void appendValue(bool value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(char value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(Int32 value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(Int64 value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(Float32 value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(Float64 value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(const Datetime& value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(const char *value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    void appendValue(const std::string& value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this Element's DataType means it
     * cannot be initialized from an instance of the supplied
     * <code>value</code>, or if the current size of this Element
     * (<code>numValues()</code>) is equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>. The behaviour is undefined
     * if the specified <code>value</code> contains embedded
     * zero-characters.
     */

    void appendValue(const Name& value);
    /*!<
     * Appends the specified <code>value</code> to this Element as the last
     * element. An exception is thrown if this element's datatype is not an
     * enumeration type, or if <code>value</code> does not refer to a
     * constant in the enumeration type of this element. An exception is also
     * thrown if the current size of this Element (<code>numValues()</code>) is
     * equal to the maximum defined by
     * <code>elementDefinition().maxValues()</code>.
     */

    Element appendElement();
    /*!<
     * If this Element is an array of sequence or choice Elements, then
     * append an element to this element and return the appended element;
     * otherwise an exception is thrown.
     */

    Element setChoice(const char *selectionName);
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If <code>datatype() == DataType::CHOICE</code> and the specified
     * <code>selectionName</code> is valid for this Element, then set the
     * active Element to the one specified by <code>selectionName</code> and
     * return it; otherwise an exception is thrown.
     */

    Element setChoice(const Name& selectionName);
    /*!<
     * If <code>datatype() == DataType::CHOICE</code> and the specified
     * <code>selectionName</code> is value for this Element, then set the
     * active Element to the one specified by <code>selectionName</code> and
     * return it; otherwise an exception is thrown.
     */

    blpapi_Element_t *handle();

    // ACCESSORS

    Name name() const;
    /*!<
     * If this Element is part of a sequence or choice Element then return
     * the Name of this Element within the sequence or choice Element that
     * owns it. If this Element is not part of a sequence Element (that is
     * it is an entire Request or Message) then return the Name of the
     * Request or Message.
     */

    int datatype() const;
    /*!<
     * Return the basic data type used to represent a value in this
     * element as an integer specified by the
     * <code>blpapi_DataType_t</code> enumeration defined in
     * <code>blpapi_types.h</code>.
     */

    bool isComplexType() const;
    /*!<
     * Return true if the DataType is either SEQUENCE or CHOICE and the
     * element is not an array element.  Return false otherwise.
     */

    bool isArray() const;
    /*!<
     * Return true if <code>elementDefinition().maxValues() \> 1</code> or
     * <code>elementDefinition().maxValues() == UNBOUNDED</code>, and false
     * otherwise.
     */

    bool isNull() const;
    /*!<
     * Return true if this element has a null value, and false otherwise.
     */

    bool isReadOnly() const;
    /*!<
     * Return true if this element cannot be modified, and false otherwise.
     */

    SchemaElementDefinition elementDefinition() const;
    /*!<
     * Return a reference to the read-only element definition object that
     * defines the properties of this elements value.
     */

    size_t numValues() const;
    /*!<
     * Return the number of values contained by this element. The number of
     * values is 0 if <code>isNull()</code> returns true, and no greater
     * than 1 if <code>isComplexType()</code> returns true. The value returned
     * will always be in the range defined by
     * <code>elementDefinition().minValues()</code> and
     * <code>elementDefinition().maxValues()</code>.
     */

    size_t numElements() const;
    /*!<
     * Return the number of elements contained by this element.  The number
     * of elements is 0 if <code>isComplex()</code> returns false, and no
     * greater than 1 if the Datatype is CHOICE; if the DataType is SEQUENCE
     * this may return any number (including 0).
     */

    bool isValid() const;
    /*!<
     * Return true if this Element is valid. An Element created using the
     * default constructor is not valid until it has had a value assigned
     * to it.
     */

    bool isNullValue(size_t position = 0) const;
    /*!<
     * Return true if the value of the sub-element at the specified
     * <code>position</code> in a sequence or choice element is a null
     * value. An exception is thrown if <code>position \>=
     * numElements()</code>.
     */

    bool hasElement(const char *name, bool excludeNullElements = false) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * Return true if this Element is a choice or sequence
     * (<code>isComplexType() == true</code>) and it contains an Element
     * with the specified <code>name</code>.
     */

    bool hasElement(const Name& name, bool excludeNullElements = false) const;
    /*!<
     * Return true if this Element is a choice or sequence
     * (<code>isComplexType() == true</code>) and it contains an Element
     * with the specified <code>name</code>.
     */

    int getValueAs(bool *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(char *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Int32 *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Int64 *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Float32 *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Float64 *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Datetime *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>. Note that this function will not necessarily set all
     * fields of <code>*result</code> -- callers should check
     * <code>result-\>hasParts(...)</code> or <code>result-\>parts()</code>
     * before accessing the fields of <code>result</code>.
     */

    int getValueAs(std::string *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Bytes *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element is not
     * `DataType.BYTEARRAY or if <code>numValues() \<= index</code>.
     */

    int getValueAs(Element *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element cannot be
     * converted to the type of <code>result</code> or if <code>numValues() \<=
     * index</code>.
     */

    int getValueAs(Name *result, size_t index = 0) const;
    /*!<
     * Set the specified <code>result</code> to the value of the specified
     * <code>index</code>th entry in this Element and return 0. An error
     * (non-zero) is returned if the DataType of this Element is not of type
     * enumeration or if <code>numValues() \<= index</code>.
     */

    bool getValueAsBool(size_t index = 0) const;
    /*!<
     * Return the specified <code>index</code>th entry in the Element as a
     * bool. An exception is thrown if the DataType of this Element cannot be
     * converted to bool or if <code>numValues() \<= index</code>.
     */

    char getValueAsChar(size_t index = 0) const;
    /*!<
     * Return the specified <code>index</code>th entry in the Element as a
     * char. An exception is thrown if the DataType of this Element cannot be
     * converted to char or if <code>numValues() \<= index</code>.
     */

    Int32 getValueAsInt32(size_t index = 0) const;
    /*!<
     * Return the specified <code>index</code>th entry in the Element as a
     * Int32. An exception is thrown if the DataType of this Element cannot be
     * converted to Int32 or if <code>numValues() \<= index</code>.
     */

    Int64 getValueAsInt64(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * Int64. An exception is thrown if the DataType of this Element cannot be
     * converted to Int64 or if <code>numValues() \<= index</code>.
     */

    Float32 getValueAsFloat32(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * Float32. An exception is thrown if the DataType of this Element cannot
     * be converted to Float32 or if <code>numValues() \<= index</code>.
     */

    Float64 getValueAsFloat64(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * Float64. An exception is thrown if the DataType of this Element cannot
     * be converted to Float64 or if <code>numValues() \<= index</code>.
     */

    Datetime getValueAsDatetime(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * Datetime. An exception is thrown if the DataType of this Element cannot
     * be converted to Datetime or if <code>numValues() \<= index</code>. Note
     * that this function will not necessarily set all fields of the returned
     * value -- callers should check <code>rv.hasParts(...)</code> or
     * <code>rv.parts()</code> before accessing the fields of the returned
     * value <code>rv</code>.
     */

    const char *getValueAsString(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * pointer to a null-terminated string. An exception is thrown if the
     * DataType of this Element cannot be converted to a null-terminated string
     * or if <code>numValues() \<= index</code>. The pointer returned remains
     * valid until this Element is destroyed.
     */

    Bytes getValueAsBytes(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as
     * Bytes. An exception is thrown if the DataType of this Element is not
     * `DataType.BYTEARRAY` or if <code>numValues() \<= index</code>.
     * The pointer returned remains valid until this Element is destroyed.
     */

    Element getValueAsElement(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as
     * an Element. An exception is thrown if the DataType of this Element
     * cannot be converted to an Element or if <code>numValues() \<=
     * index</code>.
     */

    Name getValueAsName(size_t index = 0) const;
    /*!<
     * Returns the specified <code>index</code>th entry in the Element as a
     * Name. An exception is thrown if the DataType of this Element is not of
     * type enumeration or if <code>numValues() \<= index</code>.
     */

    int getElement(Element *result, const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> then
     * load that element into the specified <code>result</code> and return 0;
     * otherwise, return an error (non-zero). The behavior of this function is
     * undefined unless <code>name</code> is a valid null-terminated string.
     */

    int getElement(Element *result, const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> then
     * load that element into the specified <code>result</code> and return 0;
     * otherwise, return an error (non-zero). The behavior of this function is
     * undefined if <code>name</code> is uninitialized.
     */

    int getElement(Element *result, size_t position) const;
    /*!<
     * If this Element is either a sequence or a choice and
     * <code>numElements()</code> is greater than the specified
     * <code>position</code>, then load the element at <code>position</code>
     * into the specified <code>result</code> and return 0; otherwise return an
     * error (non-zero).
     */

    Element getElement(size_t position) const;
    /*!<
     * If this Element is either a sequence or a choice and
     * <code>numElements()</code> is greater than the specified
     * <code>position</code> return the <code>position</code>th element.
     * Otherwise, an exception is thrown.
     */

    Element getElement(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code>, then
     * return that Element. Otherwise, an exception is thrown. The behavior of
     * this function is undefined if <code>name</code> is uninitialized.
     */

    Element getElement(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code>, then
     * return that Element. Otherwise, an exception is thrown. The behavior of
     * this function is undefined unless <code>name</code> is a valid
     * null-terminated string.
     */

    bool getElementAsBool(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a bool then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    bool getElementAsBool(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a bool then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    char getElementAsChar(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a char then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    char getElementAsChar(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a char then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Int32 getElementAsInt32(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as an Int32 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    Int32 getElementAsInt32(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as an Int32 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Int64 getElementAsInt64(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as an Int64 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    Int64 getElementAsInt64(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as an Int64 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Float32 getElementAsFloat32(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Float32 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    Float32 getElementAsFloat32(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Float32 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Float64 getElementAsFloat64(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Float64 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    Float64 getElementAsFloat64(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Float64 then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Datetime getElementAsDatetime(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Datetime then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string. Note
     * this function will not necessarily set all fields of the returned value
     * -- callers should check <code>rv.hasParts(...)</code> or
     * <code>rv.parts()</code> before accessing the fields of the returned
     * value <code>rv</code>.
     */

    Datetime getElementAsDatetime(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as Datetime then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized. Note that this function will
     * not necessarily set all fields of the returned value -- callers should
     * check <code>rv.hasParts(...)</code> or <code>rv.parts()</code>
     * before accessing the fields of the returned value <code>rv</code>.
     */

    const char *getElementAsString(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a null-terminated string then a pointer to a string
     * is returned. The pointer remains valid until this Element is destroyed.
     * Otherwise an exception is thrown. The behavior of this function is
     * undefined unless <code>name</code> is a valid null-terminated string.
     */

    const char *getElementAsString(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a null-terminated string then a pointer to a string
     * is returned. The pointer remains valid until this Element is destroyed.
     * Otherwise an exception is thrown. The behavior of this function is
     * undefined if <code>name</code> is uninitialized.
     */

    Bytes getElementAsBytes(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which can be
     * returned as a byte array, then a byte array struct is returned. The
     * pointer remains valid until this Element is destroyed.  Otherwise an
     * exception is thrown. The behavior of this function is undefined if
     * <code>name</code> is uninitialized.
     */

    Name getElementAsName(const char *name) const;
    /*!<
     * \deprecated Use the form that takes Name instead of const char*.
     *
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Name then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * unless <code>name</code> is a valid null-terminated string.
     */

    Name getElementAsName(const Name& name) const;
    /*!<
     * If this Element is either a sequence or a choice and contains a
     * valid Element identified by the specified <code>name</code> which
     * can be returned as a Name then its value is returned. Otherwise an
     * exception is thrown. The behavior of this function is undefined
     * if <code>name</code> is uninitialized.
     */

    Element getChoice() const;
    /*!<
     * Return the selection name of this element if this element is a
     * "choice" element. Otherwise, an exception is thrown.
     */

    const blpapi_Element_t *handle() const;

    std::ostream& print(
            std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
    /*!<
     * Format this Element to the specified output <code>stream</code> at
     * the (absolute value of) the optionally specified indentation
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

// FREE OPERATORS
std::ostream& operator<<(std::ostream& stream, const Element& element);
/*!<
 * Write the value of the specified <code>element</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified, can change without notice, and is logically
 * equivalent to:
 *
 * \code
 * print(stream, 0, -1);
 * \endcode
 */

// ============================================================================
//                      INLINE AND TEMPLATE FUNCTION IMPLEMENTATIONS
// ============================================================================

// -------------
// class Element
// -------------

inline Element::Element()
    : d_handle_p(0)
{
}

inline Element::Element(blpapi_Element_t *newHandle)
    : d_handle_p(newHandle)
{
}

inline void Element::rebind(blpapi_Element_t *element)
{
    d_handle_p = element;
}

inline void Element::setElement(const char *elementName, bool value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementBool(
            d_handle_p, elementName, 0, value ? 1 : 0));
}

inline void Element::setElement(const char *elementName, char value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementChar(d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, Int32 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt32(d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, Int64 value)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setElementInt64(d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, Float32 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFloat32(
            d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, Float64 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFloat64(
            d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, const Datetime& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_ELEMENT_SETELEMENTHIGHPRECISIONDATETIME(d_handle_p,
                    elementName,
                    0,
                    &value.rawHighPrecisionValue()));
}

inline void Element::setElement(const char *elementName, const char *value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementString(
            d_handle_p, elementName, 0, value));
}

inline void Element::setElement(const char *elementName, const Name& value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFromName(
            d_handle_p, elementName, 0, value.impl()));
}

inline void Element::setElement(const Name& elementName, bool value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementBool(
            d_handle_p, 0, elementName.impl(), value ? 1 : 0));
}

inline void Element::setElement(const Name& elementName, char value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementChar(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(const Name& elementName, Int32 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementInt32(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(const Name& elementName, Int64 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementInt64(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(const Name& elementName, Float32 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFloat32(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(const Name& elementName, Float64 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFloat64(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(const Name& elementName, const Datetime& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_ELEMENT_SETELEMENTHIGHPRECISIONDATETIME(d_handle_p,
                    0,
                    elementName.impl(),
                    &value.rawHighPrecisionValue()));
}

inline void Element::setElement(const Name& elementName, const char *value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementString(
            d_handle_p, 0, elementName.impl(), value));
}

inline void Element::setElement(
        const Name& elementName, const std::string& value)
{
    setElement(elementName, value.c_str());
}

inline void Element::setElement(const Name& elementName, const Name& value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setElementFromName(
            d_handle_p, 0, elementName.impl(), value.impl()));
}

inline void Element::setElement(
        const Name& elementName, const void *value, size_t length)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL(blpapi_Element_setElementBytes)(d_handle_p,
                    0,
                    elementName.impl(),
                    reinterpret_cast<const char *>(value),
                    length));
}

template <typename BYTES,
        typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type>
inline void Element::setElement(const Name& elementName, const BYTES& value)
{
    setElement(elementName, value.data(), value.size());
}

inline void Element::setValue(bool value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueBool(d_handle_p, value, index));
}

inline void Element::setValue(char value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueChar(d_handle_p, value, index));
}

inline void Element::setValue(Int32 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt32(d_handle_p, value, index));
}

inline void Element::setValue(Int64 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueInt64(d_handle_p, value, index));
}

inline void Element::setValue(Float32 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueFloat32(d_handle_p, value, index));
}

inline void Element::setValue(Float64 value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueFloat64(d_handle_p, value, index));
}

inline void Element::setValue(const Datetime& value, size_t index)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_ELEMENT_SETVALUEHIGHPRECISIONDATETIME(
                    d_handle_p, &value.rawHighPrecisionValue(), index));
}

inline void Element::setValue(const char *value, size_t index)
{
    ExceptionUtil::throwOnError(
            blpapi_Element_setValueString(d_handle_p, value, index));
}

inline void Element::setValue(const std::string& value, size_t index)
{
    setValue(value.c_str(), index);
}

inline void Element::setValue(const Name& valueName, size_t index)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueFromName(
            d_handle_p, valueName.impl(), index));
}

inline void Element::setValue(const void *value, size_t length, size_t index)
{
    ExceptionUtil::throwOnError(BLPAPI_CALL(blpapi_Element_setValueBytes)(
            d_handle_p, reinterpret_cast<const char *>(value), length, index));
}

template <typename BYTES,
        typename std::enable_if<IsByteSequence<BYTES>::value, bool>::type>
inline void Element::setValue(const BYTES& value, size_t index)
{
    setValue(value.data(), value.size(), index);
}

inline void Element::appendValue(bool value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueBool(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(char value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueChar(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Int32 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueInt32(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Int64 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueInt64(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Float32 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueFloat32(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(Float64 value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueFloat64(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const Datetime& value)
{
    ExceptionUtil::throwOnError(
            BLPAPI_CALL_ELEMENT_SETVALUEHIGHPRECISIONDATETIME(d_handle_p,
                    &value.rawHighPrecisionValue(),
                    BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const char *value)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueString(
            d_handle_p, value, BLPAPI_ELEMENT_INDEX_END));
}

inline void Element::appendValue(const std::string& value)
{
    appendValue(value.c_str());
}

inline void Element::appendValue(const Name& valueName)
{
    ExceptionUtil::throwOnError(blpapi_Element_setValueFromName(
            d_handle_p, valueName.impl(), BLPAPI_ELEMENT_INDEX_END));
}

inline Element Element::appendElement()
{
    blpapi_Element_t *appendedElement = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_appendElement(d_handle_p, &appendedElement));
    return Element(appendedElement);
}

inline Element Element::setChoice(const char *selectionName)
{
    blpapi_Element_t *resultElement = 0;
    ExceptionUtil::throwOnError(blpapi_Element_setChoice(
            d_handle_p, &resultElement, selectionName, 0, 0));
    return Element(resultElement);
}

inline Element Element::setChoice(const Name& selectionName)
{
    blpapi_Element_t *resultElement = 0;
    ExceptionUtil::throwOnError(blpapi_Element_setChoice(
            d_handle_p, &resultElement, 0, selectionName.impl(), 0));
    return Element(resultElement);
}

inline blpapi_Element_t *Element::handle() { return d_handle_p; }

inline Name Element::name() const { return blpapi_Element_name(d_handle_p); }

inline int Element::getElement(Element *element, const char *nameString) const
{
    assert(element);

    blpapi_Element_t *fldt = 0;
    int rc = blpapi_Element_getElement(d_handle_p, &fldt, nameString, 0);
    if (!rc) {
        element->rebind(fldt);
    }

    return rc;
}

inline int Element::getElement(Element *element, const Name& elementName) const
{
    assert(element);

    blpapi_Element_t *fldt = 0;
    int rc = blpapi_Element_getElement(
            d_handle_p, &fldt, 0, elementName.impl());
    if (!rc) {
        element->rebind(fldt);
    }

    return rc;
}

inline int Element::getElement(Element *element, size_t position) const
{
    assert(element);

    blpapi_Element_t *fldt = 0;
    int rc = blpapi_Element_getElementAt(d_handle_p, &fldt, position);
    if (!rc) {
        element->rebind(fldt);
    }

    return rc;
}

inline int Element::datatype() const
{
    return blpapi_Element_datatype(d_handle_p);
}

inline bool Element::isComplexType() const
{
    return blpapi_Element_isComplexType(d_handle_p) ? true : false;
}

inline bool Element::isArray() const
{
    return blpapi_Element_isArray(d_handle_p) ? true : false;
}

inline bool Element::isNull() const
{
    return blpapi_Element_isNull(d_handle_p) ? true : false;
}

inline bool Element::isReadOnly() const
{
    return blpapi_Element_isReadOnly(d_handle_p) ? true : false;
}

inline SchemaElementDefinition Element::elementDefinition() const
{
    return blpapi_Element_definition(d_handle_p);
}

inline size_t Element::numValues() const
{
    return blpapi_Element_numValues(d_handle_p);
}

inline size_t Element::numElements() const
{
    return blpapi_Element_numElements(d_handle_p);
}

inline bool Element::isValid() const { return d_handle_p ? true : false; }

inline bool Element::isNullValue(size_t position) const
{
    int rc = blpapi_Element_isNullValue(d_handle_p, position);
    if (rc != 0 && rc != 1) {
        ExceptionUtil::throwOnError(rc);
    }
    return rc ? true : false;
}

inline bool Element::hasElement(
        const char *nameString, bool excludeNullElements) const
{
    if (excludeNullElements) {
        return (blpapi_Element_hasElementEx(
                        d_handle_p, nameString, 0, excludeNullElements, 0)
                        ? true
                        : false);
    }
    return blpapi_Element_hasElement(d_handle_p, nameString, 0) ? true : false;
}

inline bool Element::hasElement(
        const Name& elementName, bool excludeNullElements) const
{
    if (excludeNullElements) {
        return (blpapi_Element_hasElementEx(d_handle_p,
                        0,
                        elementName.impl(),
                        excludeNullElements,
                        0)
                        ? true
                        : false);
    }
    return blpapi_Element_hasElement(d_handle_p, 0, elementName.impl())
            ? true
            : false;
}

inline Element Element::getElement(const Name& elementName) const
{
    blpapi_Element_t *fldt = 0;
    ExceptionUtil::throwOnError(blpapi_Element_getElement(
            d_handle_p, &fldt, 0, elementName.impl()));
    return Element(fldt);
}

inline Element Element::getElement(const char *elementName) const
{
    blpapi_Element_t *fldt = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_getElement(d_handle_p, &fldt, elementName, 0));
    return Element(fldt);
}

inline Element Element::getElement(size_t position) const
{
    blpapi_Element_t *element = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_getElementAt(d_handle_p, &element, position));
    return Element(element);
}

inline int Element::getValueAs(bool *buffer, size_t index) const
{
    assert(buffer);

    blpapi_Bool_t tmp = false;

    int res = blpapi_Element_getValueAsBool(d_handle_p, &tmp, index);
    *buffer = tmp ? true : false;
    return res;
}

inline int Element::getValueAs(char *buffer, size_t index) const
{
    return blpapi_Element_getValueAsChar(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Int32 *buffer, size_t index) const
{
    return blpapi_Element_getValueAsInt32(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Int64 *buffer, size_t index) const
{
    return blpapi_Element_getValueAsInt64(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Float32 *buffer, size_t index) const
{
    return blpapi_Element_getValueAsFloat32(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Float64 *buffer, size_t index) const
{
    return blpapi_Element_getValueAsFloat64(d_handle_p, buffer, index);
}

inline int Element::getValueAs(Datetime *buffer, size_t index) const
{
    BLPAPI_CALL_ELEMENT_GETVALUEASHIGHPRECISIONDATETIME(
            d_handle_p, buffer, index);
}

inline int Element::getValueAs(std::string *result, size_t index) const
{
    assert(result);

    const char *buffer = 0;
    int rc = blpapi_Element_getValueAsString(d_handle_p, &buffer, index);
    if (!rc) {
        *result = buffer;
    }
    return rc;
}

inline int Element::getValueAs(Bytes *result, size_t index) const
{
    assert(result);

    const char *buffer = 0;
    size_t length = 0;
    const int rc = BLPAPI_CALL(blpapi_Element_getValueAsBytes)(
            d_handle_p, &buffer, &length, index);
    if (!rc) {
        result->assign(buffer, length);
    }
    return rc;
}

inline int Element::getValueAs(Element *buffer, size_t index) const
{
    assert(buffer);

    return blpapi_Element_getValueAsElement(
            d_handle_p, &buffer->d_handle_p, index);
}

inline int Element::getValueAs(Name *buffer, size_t index) const
{
    assert(buffer);

    blpapi_Name_t *tmpName = 0;
    int res = blpapi_Element_getValueAsName(d_handle_p, &tmpName, index);
    if (!res) {
        *buffer = Name(tmpName);
    }
    return res;
}

inline bool Element::getValueAsBool(size_t index) const
{
    bool value = false;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline char Element::getValueAsChar(size_t index) const
{
    char value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Int32 Element::getValueAsInt32(size_t index) const
{
    Int32 value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Int64 Element::getValueAsInt64(size_t index) const
{
    Int64 value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Float32 Element::getValueAsFloat32(size_t index) const
{
    Float32 value = 0.0;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Float64 Element::getValueAsFloat64(size_t index) const
{
    Float64 value = 0.0;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Datetime Element::getValueAsDatetime(size_t index) const
{
    Datetime value;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline const char *Element::getValueAsString(size_t index) const
{
    const char *tmpStringBuffer = 0;
    ExceptionUtil::throwOnError(blpapi_Element_getValueAsString(
            d_handle_p, &tmpStringBuffer, index));
    return tmpStringBuffer;
}

inline Bytes Element::getValueAsBytes(size_t index) const
{
    Bytes value;
    ExceptionUtil::throwOnError(getValueAs(&value, index));
    return value;
}

inline Element Element::getValueAsElement(size_t index) const
{
    blpapi_Element_t *element = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_getValueAsElement(d_handle_p, &element, index));
    return Element(element);
}

inline Name Element::getValueAsName(size_t index) const
{
    blpapi_Name_t *nameValue = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_getValueAsName(d_handle_p, &nameValue, index));
    return nameValue;
}

inline Element Element::getChoice() const
{
    blpapi_Element_t *element = 0;
    ExceptionUtil::throwOnError(
            blpapi_Element_getChoice(d_handle_p, &element));
    return Element(element);
}

inline bool Element::getElementAsBool(const char *elementName) const
{
    return getElement(elementName).getValueAsBool();
}

inline bool Element::getElementAsBool(const Name& elementName) const
{
    return getElement(elementName).getValueAsBool();
}

inline char Element::getElementAsChar(const char *elementName) const
{
    return getElement(elementName).getValueAsChar();
}

inline char Element::getElementAsChar(const Name& elementName) const
{
    return getElement(elementName).getValueAsChar();
}

inline Int32 Element::getElementAsInt32(const char *elementName) const
{
    return getElement(elementName).getValueAsInt32();
}

inline Int32 Element::getElementAsInt32(const Name& elementName) const
{
    return getElement(elementName).getValueAsInt32();
}

inline Int64 Element::getElementAsInt64(const char *elementName) const
{
    return getElement(elementName).getValueAsInt64();
}

inline Int64 Element::getElementAsInt64(const Name& elementName) const
{
    return getElement(elementName).getValueAsInt64();
}

inline Float32 Element::getElementAsFloat32(const char *elementName) const
{
    return getElement(elementName).getValueAsFloat32();
}

inline Float32 Element::getElementAsFloat32(const Name& elementName) const
{
    return getElement(elementName).getValueAsFloat32();
}

inline Float64 Element::getElementAsFloat64(const char *elementName) const
{
    return getElement(elementName).getValueAsFloat64();
}

inline Float64 Element::getElementAsFloat64(const Name& elementName) const
{
    return getElement(elementName).getValueAsFloat64();
}

inline Datetime Element::getElementAsDatetime(const char *elementName) const
{
    return getElement(elementName).getValueAsDatetime();
}

inline Datetime Element::getElementAsDatetime(const Name& elementName) const
{
    return getElement(elementName).getValueAsDatetime();
}

inline const char *Element::getElementAsString(const char *elementName) const
{
    return getElement(elementName).getValueAsString();
}

inline const char *Element::getElementAsString(const Name& elementName) const
{
    return getElement(elementName).getValueAsString();
}

inline Bytes Element::getElementAsBytes(const Name& elementName) const
{
    return getElement(elementName).getValueAsBytes();
}

inline Name Element::getElementAsName(const char *elementName) const
{
    return getElement(elementName).getValueAsName();
}

inline Name Element::getElementAsName(const Name& elementName) const
{
    return getElement(elementName).getValueAsName();
}

inline const blpapi_Element_t *Element::handle() const { return d_handle_p; }

inline std::ostream& Element::print(
        std::ostream& stream, int level, int spacesPerLevel) const
{
    blpapi_Element_print(d_handle_p,
            StreamProxyOstream::writeToStream,
            &stream,
            level,
            spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const Element& element)
{
    element.print(stream, 0, -1);
    return stream;
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_ELEMENT
