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

/** \file blpapi_constant.h */
/** \defgroup blpapi_constant Component blpapi_constant
\brief Provide a representation for schema-level enumeration constants.
\file blpapi_constant.h
\brief Provide a representation for schema-level enumeration constants.
*/

#ifndef INCLUDED_BLPAPI_CONSTANT
#define INCLUDED_BLPAPI_CONSTANT

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_constant
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a representation for schema-level enumeration constants.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Constant</td>
 * <td>schema enumeration constant</td>
 * </tr>
 * <tr>
 * <td>blpapi::ConstantList</td>
 * <td>list of schema enumeration constants</td>
 * </tr>
 * </table>
 * \par
 * \sa  blpapi_schema
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component provides a representation of a schema
 * enumeration constant, and a representation for lists of such constants.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

#ifndef INCLUDED_BLPAPI_NAME
#include <blpapi_name.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_DATETIME
#include <blpapi_datetime.h>
#endif

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
void blpapi_Constant_setUserData(blpapi_Constant_t *constant, void *userdata);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_Constant_name(const blpapi_Constant_t *constant);

BLPAPI_EXPORT
const char *blpapi_Constant_description(const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_status(const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_datatype(const blpapi_Constant_t *constant);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsChar(
        const blpapi_Constant_t *constant, blpapi_Char_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsInt32(
        const blpapi_Constant_t *constant, blpapi_Int32_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsInt64(
        const blpapi_Constant_t *constant, blpapi_Int64_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsFloat32(
        const blpapi_Constant_t *constant, blpapi_Float32_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsFloat64(
        const blpapi_Constant_t *constant, blpapi_Float64_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsDatetime(
        const blpapi_Constant_t *constant, blpapi_Datetime_t *buffer);

BLPAPI_EXPORT
int blpapi_Constant_getValueAsString(
        const blpapi_Constant_t *constant, const char **buffer);

BLPAPI_EXPORT
void *blpapi_Constant_userData(const blpapi_Constant_t *constant);

BLPAPI_EXPORT
void blpapi_ConstantList_setUserData(
        blpapi_ConstantList_t *constant, void *userdata);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_ConstantList_name(const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
const char *blpapi_ConstantList_description(const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
int blpapi_ConstantList_numConstants(const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
int blpapi_ConstantList_datatype(const blpapi_ConstantList_t *constant);

BLPAPI_EXPORT
int blpapi_ConstantList_status(const blpapi_ConstantList_t *list);

BLPAPI_EXPORT
blpapi_Constant_t *blpapi_ConstantList_getConstant(
        const blpapi_ConstantList_t *constant,
        const char *nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Constant_t *blpapi_ConstantList_getConstantAt(
        const blpapi_ConstantList_t *constant, size_t index);

BLPAPI_EXPORT
void *blpapi_ConstantList_userData(const blpapi_ConstantList_t *constant);

#ifdef __cplusplus
}

#include <cassert>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_constant
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * Represents the value of a schema enumeration constant.
 *
 * Constants can be any of the following DataTypes: BOOL, CHAR, BYTE, INT32,
 * INT64, FLOAT32, FLOAT64, STRING, DATE, TIME, DATETIME. This class provides
 * access to not only the constant value, but also the symbolic name, the
 * description, and the status of the constant. It also provides an interface
 * for associating arbitrary user-defined data (specified as a
 * <code>void*</code>) with a <code>Constant</code>.
 *
 * <code>Constant</code> objects are read-only, with the exception of a single
 * <code>void*</code> attribute for storing user data.  <code>Constant</code>
 * objects have <em>reference</em> <em>semantics</em> with respect to this user
 * data field: calling <code>c.setUserData(void*)</code> modifies the user data
 * associated with <code>c</code>, as well as that associated with all copies
 * of <code>c</code>. As a result, functions which set or read this field are
 * <em>NOT</em> per-object thread-safe. Clients must synchronize such
 * operations across <em>all</em> <em>copies</em> of an object.
 *
 * Application clients need never create fresh <code>Constant</code> objects
 * directly; applications will typically work with copies of objects returned
 * by other <code>blpapi</code> components.
 */
/*!
 * See \ref blpapi_constant
 */
class Constant {

    blpapi_Constant_t *d_impl_p;

  public:
    Constant(blpapi_Constant_t *handle);
    /*
     * Create a <code>Constant</code> object having the same value as the
     * specified <code>original</code>. Note that this function does
     * <em>not</em> require cross-object thread synchronization, as it does not
     * directly read or modify the <code>userData</code> field.
     */

    void setUserData(void *userData);
    /*!<
     * Set the user data associated with this <code>Constant</code> -- and all
     * copies of this <code>Constant</code> -- to the specified
     * <code>userData</code>. Clients are responsible for synchronizing calls
     * to this function, and to <code>userData()</code>, across all copies of
     * this <code>Constant</code> object.
     */

    Name name() const;
    /*!<
     * Return the symbolic name of this <code>Constant</code>.
     */

    const char *description() const;
    /*!<
     * Return a null-terminated string containing a human-readable description
     * of this <code>Constant</code>. The returned pointer remains valid until
     * this <code>Constant</code> is destroyed.
     */

    int status() const;
    /*!<
     * Return the status, as a <code>SchemaStatus::Value</code>, of this
     * <code>Constant</code>.
     */

    int datatype() const;
    /*!<
     * Return the data type used to represent the value of this constant as an
     * integer specified by the <code>blpapi_DataType_t</code> enumeration
     * defined in <code>blpapi_types.h</code>.
     */

    int getValueAs(char *buffer) const;
    /*!<
     * Load the <code>char</code> value of this <code>Constant</code> into the
     * specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not a <code>char</code> then return a nonzero
     * value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(Int32 *buffer) const;
    /*!<
     * Load the <code>Int32</code> value of this <code>Constant</code> into the
     * specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not an <code>Int32</code> then return a nonzero
     * value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(Int64 *buffer) const;
    /*!<
     * Load the <code>Int64</code> value of this <code>Constant</code> into the
     * specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not an <code>Int64</code> then return a nonzero
     * value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(Float32 *buffer) const;
    /*!<
     * Load the <code>Float32</code> value of this <code>Constant</code> into
     * the specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not a <code>Float32</code> then return a
     * nonzero value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(Float64 *buffer) const;
    /*!<
     * Load the <code>Float64</code> value of this <code>Constant</code> into
     * the specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not a <code>Float64</code> then return a
     * nonzero value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(Datetime *buffer) const;
    /*!<
     * Load the <code>Datetime</code> value of this <code>Constant</code> into
     * the specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not a <code>Datetime</code> then return a
     * nonzero value and leave <code>buffer</code> unchanged.
     */

    int getValueAs(std::string *buffer) const;
    /*!<
     * Load the <code>std::string</code> value of this <code>Constant</code>
     * into the specified <code>buffer</code> and return 0; if this
     * <code>Constant</code> is not a <code>std::string</code> then return a
     * nonzero value and leave <code>buffer</code> unchanged.
     */

    char getValueAsChar() const;
    /*!<
     * Return the value of this object as a <code>char</code>. If the value is
     * not a <code>char</code> an exception is thrown.
     */

    Int32 getValueAsInt32() const;
    /*!<
     * Return the value of this object as an <code>Int32</code>. If the value
     * is not an <code>Int32</code> an exception is thrown.
     */

    Int64 getValueAsInt64() const;
    /*!<
     * Return the value of this object as an <code>Int64</code>. If the value
     * is not an <code>Int64</code> an exception is thrown.
     */

    Float32 getValueAsFloat32() const;
    /*!<
     * Return the value of this object as a <code>Float32</code>. If the value
     * is not a <code>Float32</code> an exception is thrown.
     */

    Float64 getValueAsFloat64() const;
    /*!<
     * Return the value of this object as a <code>Float64</code>. If the value
     * is not a <code>Float64</code> an exception is thrown.
     */

    Datetime getValueAsDatetime() const;
    /*!<
     * Return the value of this object as a <code>Datetime</code>. If the value
     * is not a <code>Datetime</code> an exception is thrown.
     */

    std::string getValueAsString() const;
    /*!<
     * Return the value of this object as a <code>std::string</code>. If the
     * value is not a <code>std::string</code> an exception is thrown.
     */

    void *userData() const;
    /*!<
     * Return the user data associated with this <code>Constant</code>. If no
     * user data has been associated with this <code>Constant</code> then
     * return 0. Clients are responsible for synchronizing calls to this
     * function with calls to <code>setUserData(void*)</code> made on not only
     * this <code>Constant</code>, but also all copies of this
     * <code>Constant</code>. Note that <code>Constant</code> objects have
     * reference semantics: this function will reflect the last value set on
     * <em>any</em> copy of this <code>Constant</code>.
     */

    const blpapi_Constant_t *impl() const;
};

/*!
 * Represents a list schema enumeration constants.
 *
 * As well as the list of <code>Constant</code> objects, this class also
 * provides access to the symbolic name, description, and status of the list as
 * a whole, and provides a facility for associating arbitrary user data (in the
 * form of a <code>void*</code>) with the list. All <code>Constant</code>
 * objects in a <code>ConstantList</code> are of the same DataType.
 *
 * <code>ConstantList</code> objects are read-only, with the exception of a
 * single <code>void*</code> attribute for storing user data.
 * <code>ConstantList</code> objects have <em>reference</em> <em>semantics</em>
 * with respect to this user data field: calling
 * <code>c.setUserData(void*)</code> modifies the user data associated with
 * <code>c</code>, as well as that associated with all copies of
 * <code>c</code>. As a result, functions which set or read this field are
 * <em>NOT</em> per-object thread-safe. Clients must synchronize such
 * operations across <em>all</em> <em>copies</em> of an object.
 *
 * Application clients need never create fresh <code>ConstantList</code>
 * objects directly; applications will typically work with copies of objects
 * returned by other <code>blpapi</code> components.
 */
/*!
 * See \ref blpapi_constant
 */
class ConstantList {

    blpapi_ConstantList_t *d_impl_p;

  public:
    ConstantList(blpapi_ConstantList_t *handle);
    /*
     * Create a <code>ConstantList</code> object having the same value as
     * the specified <code>original</code>. Note that this function does
     * <em>not</em> require cross-object thread synchronization, as it does not
     * directly read or modify the <code>userData</code> field.
     */

    void setUserData(void *userData);
    /*!<
     * Set the user data associated with this <code>ConstantList</code> -- and
     * all copies of this <code>ConstantList</code> -- to the specified
     * <code>userData</code>. Clients are responsible for synchronizing calls
     * to this function, and to <code>userData()</code>, across all copies of
     * this <code>ConstantList</code> object.
     */

    Name name() const;
    /*!<
     * Return the symbolic name of this <code>ConstantList</code>.
     */

    const char *description() const;
    /*!<
     * Return a null-terminated string containing a human-readable description
     * of this <code>ConstantList</code>. The returned pointer remains valid
     * until this <code>ConstantList</code> is destroyed.
     */

    int status() const;
    /*!<
     * Return the status, as a'SchemaStatus::Value', of this
     * <code>ConstantList</code>.
     */

    int numConstants() const;
    /*!<
     * Return the number of <code>Constant</code> objects contained in this
     * <code>ConstantList</code>.
     */

    int datatype() const;
    /*!<
     * Return the data type used to represent the value of this constant as an
     * integer specified by the <code>blpapi_DataType_t</code> enumeration
     * defined in <code>blpapi_types</code>.
     */

    Constant getConstant(const Name& name) const;
    /*!<
     * Return the <code>Constant</code> in this <code>ConstantList</code>
     * identified by the specified <code>name</code>. If this
     * <code>ConstantList</code> does not contain a <code>Constant</code> with
     * the specified <code>name</code> then an exception is thrown.
     */

    Constant getConstant(const char *name) const;
    /*!<
     * Return the <code>Constant</code> in this <code>ConstantList</code>
     * identified by the specified <code>name</code>. If this
     * <code>ConstantList</code> does not contain a <code>Constant</code> with
     * the specified <code>name</code> then an exception is thrown.
     */

    Constant getConstantAt(size_t index) const;
    /*!<
     * Return the <code>Constant</code> at the specified <code>index</code> in
     * this <code>ConstantList</code>. If <code>index</code> is not in the
     * range from 0 to <code>numConstants() - 1</code> then an exception is
     * thrown.
     */

    void *userData() const;
    /*!<
     * Return the user data associated with this <code>ConstantList</code>.  If
     * no user data has been associated with this <code>ConstantList</code>
     * then return 0. Clients are responsible for synchronizing calls to this
     * function with calls to <code>setUserData(void*)</code> made on not only
     * this <code>ConstantList</code>, but also all copies of this
     * <code>ConstantList</code>. Note that <code>ConstantList</code> objects
     * have reference semantics: this function will reflect the last value set
     * on <em>any</em> copy of this <code>ConstantList</code>.
     */

    const blpapi_ConstantList_t *impl() const;
    /*!<
     * Return the internal implementation.
     */
};

/** @} */
/** @} */

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

inline Constant::Constant(blpapi_Constant_t *handle)
    : d_impl_p(handle)
{
}

inline Name Constant::name() const { return blpapi_Constant_name(d_impl_p); }

inline const char *Constant::description() const
{
    return blpapi_Constant_description(d_impl_p);
}

inline int Constant::status() const
{
    return blpapi_Constant_status(d_impl_p);
}

inline int Constant::datatype() const
{
    return blpapi_Constant_datatype(d_impl_p);
}

inline const blpapi_Constant_t *Constant::impl() const { return d_impl_p; }

inline int Constant::getValueAs(char *buffer) const
{
    return blpapi_Constant_getValueAsChar(d_impl_p, buffer);
}

inline int Constant::getValueAs(Int32 *buffer) const
{
    return blpapi_Constant_getValueAsInt32(d_impl_p, buffer);
}

inline int Constant::getValueAs(Int64 *buffer) const
{
    return blpapi_Constant_getValueAsInt64(d_impl_p, buffer);
}

inline int Constant::getValueAs(Float32 *buffer) const
{
    return blpapi_Constant_getValueAsFloat32(d_impl_p, buffer);
}

inline int Constant::getValueAs(Float64 *buffer) const
{
    return blpapi_Constant_getValueAsFloat64(d_impl_p, buffer);
}

inline int Constant::getValueAs(Datetime *buffer) const
{
    assert(buffer);

    return blpapi_Constant_getValueAsDatetime(d_impl_p, &buffer->rawValue());
}

inline int Constant::getValueAs(std::string *result) const
{
    const char *buffer = 0;
    int rc = blpapi_Constant_getValueAsString(d_impl_p, &buffer);
    if (!rc) {
        *result = buffer;
    }
    return rc;
}

inline char Constant::getValueAsChar() const
{
    char value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int32 Constant::getValueAsInt32() const
{
    int value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Int64 Constant::getValueAsInt64() const
{
    Int64 value = 0;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline float Constant::getValueAsFloat32() const
{
    Float32 value = 0.0;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline double Constant::getValueAsFloat64() const
{
    Float64 value = 0.0;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline Datetime Constant::getValueAsDatetime() const
{
    Datetime value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline std::string Constant::getValueAsString() const
{
    std::string value;
    ExceptionUtil::throwOnError(getValueAs(&value));
    return value;
}

inline void Constant::setUserData(void *newUserData)
{
    blpapi_Constant_setUserData(d_impl_p, newUserData);
}

inline void *Constant::userData() const
{
    return blpapi_Constant_userData(d_impl_p);
}

inline ConstantList::ConstantList(blpapi_ConstantList_t *handle)
    : d_impl_p(handle)
{
}

inline Name ConstantList::name() const
{
    return blpapi_ConstantList_name(d_impl_p);
}

inline const char *ConstantList::description() const
{
    return blpapi_ConstantList_description(d_impl_p);
}

inline int ConstantList::status() const
{
    return blpapi_ConstantList_status(d_impl_p);
}

inline int ConstantList::datatype() const
{
    return blpapi_ConstantList_datatype(d_impl_p);
}

inline int ConstantList::numConstants() const
{
    return blpapi_ConstantList_numConstants(d_impl_p);
}

inline Constant ConstantList::getConstant(const Name& constantName) const
{
    return blpapi_ConstantList_getConstant(d_impl_p, 0, constantName.impl());
}

inline Constant ConstantList::getConstant(const char *nameString) const
{
    return blpapi_ConstantList_getConstant(d_impl_p, nameString, 0);
}

inline Constant ConstantList::getConstantAt(size_t index) const
{
    return blpapi_ConstantList_getConstantAt(d_impl_p, index);
}

inline const blpapi_ConstantList_t *ConstantList::impl() const
{
    return d_impl_p;
}

inline void ConstantList::setUserData(void *newUserData)
{
    blpapi_ConstantList_setUserData(d_impl_p, newUserData);
}

inline void *ConstantList::userData() const
{
    return blpapi_ConstantList_userData(d_impl_p);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifndef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_CONSTANT
