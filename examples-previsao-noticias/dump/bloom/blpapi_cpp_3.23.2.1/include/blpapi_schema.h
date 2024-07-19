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

/** \file blpapi_schema.h */
/** \defgroup blpapi_schema Component blpapi_schema
\brief Provide a representation of a schema describing structured messages
\file blpapi_schema.h
\brief Provide a representation of a schema describing structured messages
*/

#ifndef INCLUDED_BLPAPI_SCHEMA
#define INCLUDED_BLPAPI_SCHEMA

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_schema
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a representation of a schema describing structured messages
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::SchemaStatus</td>
 * <td>the version status of a schema</td>
 * </tr>
 * <tr>
 * <td>blpapi::SchemaTypeDefinition</td>
 * <td>definitions of schema types</td>
 * </tr>
 * <tr>
 * <td>blpapi::SchemaElementDefinition</td>
 * <td>definitions of message elements</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component provides types for representing schemata which
 * describe structured messages. Such schemata consist of two distinct kinds of
 * definitions: "type" definitions (represented by
 * <code>SchemaTypeDefinition</code> objects) declare types than can be used
 * within other definitions (of both kinds); an "element" definition defines a
 * specific field by associating a field identifier with a particular type, as
 * well as the number of values of that type that are permitted to be
 * associated with that identifier.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CONSTANT
#include <blpapi_constant.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_BLPAPI_EXCEPTION
#include <blpapi_exception.h>
#endif

#ifndef INCLUDED_BLPAPI_NAME
#include <blpapi_name.h>
#endif

#ifndef INCLUDED_BLPAPI_STREAMPROXY
#include <blpapi_streamproxy.h>
#endif

#ifndef INCLUDED_BLPAPI_TYPES
#include <blpapi_types.h>
#endif

typedef void *blpapi_SchemaTypeDefinition_t;

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Name_t *blpapi_SchemaElementDefinition_name(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
const char *blpapi_SchemaElementDefinition_description(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
int blpapi_SchemaElementDefinition_status(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_SchemaTypeDefinition_t *blpapi_SchemaElementDefinition_type(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_numAlternateNames(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_SchemaElementDefinition_getAlternateName(
        const blpapi_SchemaElementDefinition_t *field, size_t index);

//   -- NOT USED or IMPLEMENTED: removing
// BLPAPI_EXPORT
// size_t blpapi_SchemaElementDefinition_numNames(
//         const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_minValues(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
size_t blpapi_SchemaElementDefinition_maxValues(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
int blpapi_SchemaElementDefinition_print(
        const blpapi_SchemaElementDefinition_t *element,
        blpapi_StreamWriter_t streamWriter,
        void *userStream,
        int level,
        int spacesPerLevel);

BLPAPI_EXPORT
void blpapi_SchemaElementDefinition_setUserData(
        blpapi_SchemaElementDefinition_t *field, void *userdata);

BLPAPI_EXPORT
void *blpapi_SchemaElementDefinition_userData(
        const blpapi_SchemaElementDefinition_t *field);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_SchemaTypeDefinition_name(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
const char *blpapi_SchemaTypeDefinition_description(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_status(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_datatype(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isComplexType(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isSimpleType(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isEnumerationType(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isComplex(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isSimple(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_isEnumeration(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
size_t blpapi_SchemaTypeDefinition_numElementDefinitions(
        const blpapi_SchemaTypeDefinition_t *type);

BLPAPI_EXPORT
blpapi_SchemaElementDefinition_t *
blpapi_SchemaTypeDefinition_getElementDefinition(
        const blpapi_SchemaTypeDefinition_t *type,
        const char *nameString,
        const blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_SchemaElementDefinition_t *
blpapi_SchemaTypeDefinition_getElementDefinitionAt(
        const blpapi_SchemaTypeDefinition_t *type, size_t index);

BLPAPI_EXPORT
int blpapi_SchemaTypeDefinition_print(
        const blpapi_SchemaTypeDefinition_t *element,
        blpapi_StreamWriter_t streamWriter,
        void *userStream,
        int level,
        int spacesPerLevel);

BLPAPI_EXPORT
void blpapi_SchemaTypeDefinition_setUserData(
        blpapi_SchemaTypeDefinition_t *element, void *userdata);

BLPAPI_EXPORT
void *blpapi_SchemaTypeDefinition_userData(
        const blpapi_SchemaTypeDefinition_t *element);

BLPAPI_EXPORT
blpapi_ConstantList_t *blpapi_SchemaTypeDefinition_enumeration(
        const blpapi_SchemaTypeDefinition_t *element);

#ifdef __cplusplus
}

#ifndef INCLUDED_IOSFWD
#include <iosfwd>
#define INCLUDED_IOSFWD
#endif

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_schema
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 * This <code>struct</code> provides a namespace for enumerating the possible
 * deprecation statuses of a schema element or type.
 */
/*!
 * See \ref blpapi_schema
 */
struct SchemaStatus {

    enum Value {
        ACTIVE = BLPAPI_STATUS_ACTIVE,
        ///< This item is current and may appear in Messages

        DEPRECATED = BLPAPI_STATUS_DEPRECATED,
        ///< This item is current and may appear in Messages but will be
        /// removed in due course

        INACTIVE = BLPAPI_STATUS_INACTIVE,
        ///< This item is not current and will not appear in Messages

        PENDING_DEPRECATION = BLPAPI_STATUS_PENDING_DEPRECATION
        ///< This item is expected to be deprecated in the future; clients are
        /// advised to migrate away from use of this item
    };
};

class SchemaTypeDefinition;

/*!
 * This class implements the definition of an individual field within a schema
 * type. An element is defined by an identifier/name, a type, and the number of
 * values of that type that may be associated with the identifier/name. In
 * addition, this class offers access to metadata providing a description and
 * deprecation status for the field. Finally,
 * <code>SchemaElementDefinition</code> provides an interface for associating
 * arbitrary user-defined data (specified as a <code>void*</code>) with an
 * element definition.
 *
 * <code>SchemaElementDefinition</code> objects are returned by
 * <code>Service</code> and <code>Operation</code> objects to define the
 * content of requests, replies and events. The
 * <code>SchemaTypeDefinition</code> returned by
 * <code>SchemaElementDefinition::typeDefinition()</code> may itself provide
 * access to <code>SchemaElementDefinition</code> objects when the schema
 * contains nested elements. (See the <code>SchemaTypeDefinition</code>
 * documentation for more information on complex types.)
 *
 * An optional element has <code>minValues() == 0</code>.
 *
 * A mandatory element has <code>minValues() \>= 1</code>.
 *
 * An element that must contain a single value has <code>minValues() ==
 * maxValues() == 1</code>.
 *
 * An element containing an array has <code>maxValues() \> 1</code>.
 *
 * An element with no upper limit on the number of values has <code>maxValues()
 * == UNBOUNDED</code>.
 *
 * <code>SchemaElementDefinition</code> objects are read-only, with the
 * exception of a single <code>void*</code> attribute for storing user data.
 * <code>SchemaElementDefinition</code> objects have <em>reference</em>
 * <em>semantics</em> with respect to this user data field: calling
 * <code>c.setUserData(void*)</code> modifies the user data associated with
 * <code>c</code>, as well as that associated with all copies of
 * <code>c</code>. As a result, functions which set or read this attribute are
 * <em>NOT</em> per-object thread-safe. Clients must synchronize such
 * operations across <em>all</em> <em>copies</em> of an object.
 *
 * Application clients need never create fresh
 * <code>SchemaElementDefinition</code> objects directly; applications will
 * typically work with copies of objects returned by other <code>blpapi</code>
 * components.
 */
/*!
 * See \ref blpapi_schema
 */
class SchemaElementDefinition {

    blpapi_SchemaElementDefinition_t *d_impl_p;

  public:
    /*
     * Constants used in the SchemaElementDefinition interface.
     */

    enum {
        UNBOUNDED = BLPAPI_ELEMENTDEFINITION_UNBOUNDED
        ///< Indicates an array has an unbounded number of values
    };

    SchemaElementDefinition(blpapi_SchemaElementDefinition_t *handle);

    ~SchemaElementDefinition();
    /*!<
     * Destroy this object.
     */

    void setUserData(void *userData);
    /*!<
     * Set the user data associated with this
     * <code>SchemaElementDefinition</code> -- and all copies of this
     * <code>SchemaElementDefinition</code> -- to the specified
     * <code>userData</code>. Clients are responsible for synchronizing calls
     * to this function, and to <code>userData()</code>, across all copies of
     * this <code>SchemaElementDefinition</code> object.
     */

    Name name() const;
    /*!<
     * Return the name identifying this element within its containing
     * structure/type.
     */

    const char *description() const;
    /*!<
     * Return a null-terminated string containing a human-readable description
     * of this element. This pointer is valid until this
     * <code>SchemaElementDefinition</code> is destroyed.
     */

    int status() const;
    /*!<
     * Return the deprecation status, as a <code>SchemaStatus::Value</code>, of
     * this element.
     */

    const SchemaTypeDefinition typeDefinition() const;
    /*!<
     * Return the type of values contained in this element.
     */

    size_t minValues() const;
    /*!<
     * Return the minimum number of occurrences of this element. This value is
     * always greater than or equal to zero.
     */

    size_t maxValues() const;
    /*!<
     * Return the maximum number of occurrences of this element. This value is
     * always greater than or equal to one.
     */

    size_t numAlternateNames() const;
    /*!<
     * Return the number of alternate names for this element.
     */

    Name getAlternateName(size_t index) const;
    /*!<
     * Return the specified <code>index</code>th alternate name for this
     * element. If <code>index \>=numAlternateNames()</code> an exception is
     * thrown.
     */

    void *userData() const;
    /*!<
     * Return the user data associated with this
     * <code>SchemaElementDefinition</code>. If no user data has been
     * associated with this <code>SchemaElementDefinition</code> then return 0.
     * Clients are responsible for synchronizing calls to this function with
     * calls to <code>setUserData(void*)</code> made on not only this
     * <code>SchemaElementDefinition</code>, but also all copies of this
     * <code>SchemaElementDefinition</code>. Note that
     * <code>SchemaElementDefinition</code> objects have reference semantics:
     * this function will reflect the last value set on <em>any</em> copy of
     * this <code>SchemaElementDefinition</code>.
     */

    std::ostream& print(
            std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
    /*!<
     * Format this SchemaElementDefinition to the specified output
     * <code>stream</code> at the (absolute value of) the optionally specified
     * indentation <code>level</code> and return a reference to
     * <code>stream</code>. If <code>level</code> is specified, optionally
     * specify <code>spacesPerLevel</code>, the number of spaces per
     * indentation level for this and all of its nested objects. If
     * <code>level</code> is negative, suppress indentation of the first line.
     * If <code>spacesPerLevel</code> is negative, format the entire output on
     * one line, suppressing all but the initial indentation (as governed by
     * <code>level</code>).
     */

    blpapi_SchemaElementDefinition_t *impl() const;
};

/*!
 * This class implements a representation of a "type" that can be used within a
 * schema, including both simple atomic types (integers, dates, strings, etc.)
 * as well as "complex" types defined a sequences of or choice among a
 * collection (named) elements, each of which is in turn described by another
 * type. In addition to accessors for the type's structure, this class also
 * offers access to metadata providing a description and deprecation status for
 * the type. Finally, <code>SchemaTypeDefinition</code> provides an interface
 * for associating arbitrary user-defined data (specified as a
 * <code>void*</code>) with a type definition.
 *
 * Each <code>SchemaElementDefinition</code> object is associated with a single
 * <code>SchemaTypeDefinition</code>; one <code>SchemaTypeDefinition</code> may
 * be used by zero, one, or many <code>SchemaElementDefinition</code> objects.
 *
 * <code>SchemaTypeDefinition</code> objects are read-only, with the exception
 * of a single <code>void*</code> attribute for storing user data.
 * <code>SchemaTypeDefinition</code> objects have <em>reference</em>
 * <em>semantics</em> with respect to this user data field: calling
 * <code>c.setUserData(void*)</code> modifies the user data associated with
 * <code>c</code>, as well as that associated with all copies of
 * <code>c</code>. As a result, functions which set or read this attribute are
 * <em>NOT</em> per-object thread-safe. Clients must synchronize such
 * operations across <em>all</em> <em>copies</em> of an object.
 *
 * Application clients need never create fresh
 * <code>SchemaTypeDefinition</code> objects directly; applications will
 * typically work with copies of objects returned by other <code>blpapi</code>
 * components.
 */
/*!
 * See \ref blpapi_schema
 */
class SchemaTypeDefinition {

    blpapi_SchemaTypeDefinition_t *d_impl_p;

  public:
    SchemaTypeDefinition(blpapi_SchemaTypeDefinition_t *handle);

    ~SchemaTypeDefinition();
    /*!<
     *     Destroy this object.
     */

    // MANIPULATORS

    void setUserData(void *userData);
    /*!<
     * Set the user data associated with this <code>SchemaTypeDefinition</code>
     * -- and all copies of this <code>SchemaTypeDefinition</code> -- to the
     *  specified <code>userData</code>. Clients are responsible for
     *  synchronizing calls to this function, and to <code>userData()</code>,
     *  across all copies of this <code>SchemaTypeDefinition</code> object.
     */

    // ACCESSORS

    int datatype() const;
    /*!<
     * Return the <code>DataType</code> of this
     * <code>SchemaTypeDefinition</code> as an integer specified by the
     * <code>blpapi_DataType_t</code> enumeration defined in
     * <code>blpapi_types.h</code>.
     */

    Name name() const;
    /*!<
     * Return the name of this <code>SchemaTypeDefinition</code>.
     */

    const char *description() const;
    /*!<
     * Return a null-terminated string which contains a human readable
     * description of this <code>SchemaTypeDefinition</code>. The returned
     * pointer remains valid until this <code>SchemaTypeDefinition</code> is
     * destroyed.
     */

    int status() const;
    /*!<
     * Return the deprecation status, as a <code>SchemaStatus::Value</code>, of
     * this <code>SchemaTypeDefinition</code>.
     */

    size_t numElementDefinitions() const;
    /*!<
     * Return the number of <code>SchemaElementDefinition</code> objects
     * contained by this <code>SchemaTypeDefinition</code>. If this
     * <code>SchemaTypeDefinition</code> is neither a choice nor a sequence
     * this will return 0.
     */

    bool isComplexType() const;
    /*!<
     * Return <code>true</code> if this <code>SchemaTypeDefinition</code>
     * represents a sequence or choice type.
     */

    bool isSimpleType() const;
    /*!<
     * Return <code>true</code> if this <code>SchemaTypeDefinition</code>
     * represents neither a sequence nor a choice type.
     */

    bool isEnumerationType() const;
    /*!<
     * Return <code>true</code> if this <code>SchemaTypeDefinition</code>
     * represents an enumeration type.
     */

    bool hasElementDefinition(const Name& name) const;
    /*!<
     * Return <code>true</code> if this <code>SchemaTypeDefinition</code>
     * contains an element with the specified <code>name</code>; otherwise
     * returns <code>false</code>.
     */

    bool hasElementDefinition(const char *name) const;
    /*!<
     * Return <code>true</code> if this <code>SchemaTypeDefinition</code>
     * contains an element with the specified <code>name</code>; otherwise
     * returns <code>false</code>.
     */

    SchemaElementDefinition getElementDefinition(const Name& name) const;
    /*!<
     * Return the definition of the element identified by the specified
     * <code>name</code>. If <code>hasElementDefinition(name) != true</code>
     * then an exception is thrown.
     */

    SchemaElementDefinition getElementDefinition(const char *nameString) const;
    /*!<
     * Return the definition of the element identified by the specified
     * <code>nameString</code>. If <code>hasElementDefinition(nameString) !=
     * true</code> then an exception is thrown.
     */

    SchemaElementDefinition getElementDefinition(size_t index) const;
    /*!<
     * Return the definition of the element a the specified <code>index</code>
     * in the sequence of elements. If <code>index \>=
     * numElementDefinitions()</code> an exception is thrown.
     */

    const ConstantList enumeration() const;
    /*!<
     * Return a <code>ConstantList</code> containing all possible values of the
     * enumeration defined by this type. The behavior of this function is
     * undefined unless <code>isEnumerationType() == true</code>.
     */

    void *userData() const;
    /*!<
     * Return the user data associated with this
     * <code>SchemaTypeDefinition</code>. If no user data has been associated
     * with this <code>SchemaTypeDefinition</code> then return 0. Clients are
     * responsible for synchronizing calls to this function with calls to
     * <code>setUserData(void*)</code> made on not only this
     * <code>SchemaTypeDefinition</code>, but also all copies of this
     * <code>SchemaTypeDefinition</code>. Note that
     * <code>SchemaTypeDefinition</code> objects have reference semantics: this
     * function will reflect the last value set on <em>any</em> copy of this
     * <code>SchemaTypeDefinition</code>.
     */

    std::ostream& print(
            std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
    /*!<
     * Format this SchemaTypeDefinition to the specified output
     * <code>stream</code> at the (absolute value of) the optionally specified
     * indentation <code>level</code> and return a reference to
     * <code>stream</code>. If <code>level</code> is specified, optionally
     * specify <code>spacesPerLevel</code>, the number of spaces per
     * indentation level for this and all of its nested objects. If
     * <code>level</code> is negative, suppress indentation of the first line.
     * If <code>spacesPerLevel</code> is negative, format the entire output on
     * one line, suppressing all but the initial indentation (as governed by
     * <code>level</code>).
     */
};

/** @} */
/** @} */

// FREE OPERATORS

std::ostream& operator<<(
        std::ostream& stream, const SchemaElementDefinition& element);
/*!<
 * Write the value of the specified <code>element</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified, can change without notice, and is logically
 * equivalent to:
 \code
  print(stream, 0, -1);
\endcode
 */

std::ostream& operator<<(
        std::ostream& stream, const SchemaTypeDefinition& typeDef);
/*!<
 * Write the value of the specified <code>typeDef</code> object to the
 * specified output <code>stream</code> in a single-line format, and return a
 * reference to <code>stream</code>.  If <code>stream</code> is not valid on
 * entry, this operation has no effect.  Note that this human-readable format
 * is not fully specified, can change without notice, and is logically
 * equivalent to:
\code
  print(stream, 0, -1);
\endcode
 */

// ============================================================================
//                      INLINE FUNCTION DEFINITIONS
// ============================================================================

// -----------------------------
// class SchemaElementDefinition
// -----------------------------

inline SchemaElementDefinition::SchemaElementDefinition(
        blpapi_SchemaElementDefinition_t *handle)
    : d_impl_p(handle)
{
}

inline SchemaElementDefinition::~SchemaElementDefinition() { }

inline Name SchemaElementDefinition::name() const
{
    return Name(blpapi_SchemaElementDefinition_name(d_impl_p));
}

inline const char *SchemaElementDefinition::description() const
{
    return blpapi_SchemaElementDefinition_description(d_impl_p);
}

inline int SchemaElementDefinition::status() const
{
    return blpapi_SchemaElementDefinition_status(d_impl_p);
}

inline const SchemaTypeDefinition
SchemaElementDefinition::typeDefinition() const
{
    return blpapi_SchemaElementDefinition_type(d_impl_p);
}

inline size_t SchemaElementDefinition::minValues() const
{
    return blpapi_SchemaElementDefinition_minValues(d_impl_p);
}

inline size_t SchemaElementDefinition::maxValues() const
{
    return blpapi_SchemaElementDefinition_maxValues(d_impl_p);
}

inline size_t SchemaElementDefinition::numAlternateNames() const
{
    return blpapi_SchemaElementDefinition_numAlternateNames(d_impl_p);
}

inline Name SchemaElementDefinition::getAlternateName(size_t index) const
{
    blpapi_Name_t *alternateName
            = blpapi_SchemaElementDefinition_getAlternateName(d_impl_p, index);
    if (alternateName == 0) {
        ExceptionUtil::throwOnError(BLPAPI_ERROR_INDEX_OUT_OF_RANGE);
    }
    return alternateName;
}

inline std::ostream& SchemaElementDefinition::print(
        std::ostream& stream, int level, int spacesPerLevel) const
{
    blpapi_SchemaElementDefinition_print(d_impl_p,
            StreamProxyOstream::writeToStream,
            &stream,
            level,
            spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(
        std::ostream& stream, const SchemaElementDefinition& element)
{
    element.print(stream, 0, -1);
    return stream;
}

inline void SchemaElementDefinition::setUserData(void *newUserData)
{
    blpapi_SchemaElementDefinition_setUserData(d_impl_p, newUserData);
}

inline void *SchemaElementDefinition::userData() const
{
    return blpapi_SchemaElementDefinition_userData(d_impl_p);
}

inline blpapi_SchemaElementDefinition_t *SchemaElementDefinition::impl() const
{
    return d_impl_p;
}
// --------------------------
// class SchemaTypeDefinition
// --------------------------

inline SchemaTypeDefinition::SchemaTypeDefinition(
        blpapi_SchemaTypeDefinition_t *handle)
    : d_impl_p(handle)
{
}

inline SchemaTypeDefinition::~SchemaTypeDefinition() { }

inline int SchemaTypeDefinition::datatype() const
{
    return blpapi_SchemaTypeDefinition_datatype(d_impl_p);
}

inline Name SchemaTypeDefinition::name() const
{
    return blpapi_SchemaTypeDefinition_name(d_impl_p);
}

inline const char *SchemaTypeDefinition::description() const
{
    return blpapi_SchemaTypeDefinition_description(d_impl_p);
}

inline int SchemaTypeDefinition::status() const
{
    return blpapi_SchemaTypeDefinition_status(d_impl_p);
}

inline size_t SchemaTypeDefinition::numElementDefinitions() const
{
    return blpapi_SchemaTypeDefinition_numElementDefinitions(d_impl_p);
}

inline bool SchemaTypeDefinition::hasElementDefinition(
        const Name& elementName) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinition(
                   d_impl_p, 0, elementName.impl())
            ? true
            : false;
}

inline bool SchemaTypeDefinition::hasElementDefinition(
        const char *nameString) const
{
    return blpapi_SchemaTypeDefinition_getElementDefinition(
                   d_impl_p, nameString, 0)
            ? true
            : false;
}

inline SchemaElementDefinition SchemaTypeDefinition::getElementDefinition(
        const Name& elementName) const
{
    blpapi_SchemaElementDefinition_t *def
            = blpapi_SchemaTypeDefinition_getElementDefinition(
                    d_impl_p, 0, elementName.impl());
    if (def == 0) {
        ExceptionUtil::throwOnError(BLPAPI_ERROR_ITEM_NOT_FOUND);
    }
    return def;
}

inline SchemaElementDefinition SchemaTypeDefinition::getElementDefinition(
        const char *nameString) const
{
    blpapi_SchemaElementDefinition_t *def
            = blpapi_SchemaTypeDefinition_getElementDefinition(
                    d_impl_p, nameString, 0);
    if (def == 0) {
        ExceptionUtil::throwOnError(BLPAPI_ERROR_ITEM_NOT_FOUND);
    }
    return def;
}

inline SchemaElementDefinition SchemaTypeDefinition::getElementDefinition(
        size_t index) const
{
    blpapi_SchemaElementDefinition_t *def
            = blpapi_SchemaTypeDefinition_getElementDefinitionAt(
                    d_impl_p, index);
    if (def == 0) {
        ExceptionUtil::throwOnError(BLPAPI_ERROR_INDEX_OUT_OF_RANGE);
    }
    return def;
}

inline bool SchemaTypeDefinition::isComplexType() const
{
    return blpapi_SchemaTypeDefinition_isComplexType(d_impl_p) ? true : false;
}

inline bool SchemaTypeDefinition::isSimpleType() const
{
    return blpapi_SchemaTypeDefinition_isSimpleType(d_impl_p) ? true : false;
}

inline bool SchemaTypeDefinition::isEnumerationType() const
{
    return blpapi_SchemaTypeDefinition_isEnumerationType(d_impl_p) ? true
                                                                   : false;
}

inline std::ostream& SchemaTypeDefinition::print(
        std::ostream& stream, int level, int spacesPerLevel) const
{
    blpapi_SchemaTypeDefinition_print(d_impl_p,
            StreamProxyOstream::writeToStream,
            &stream,
            level,
            spacesPerLevel);
    return stream;
}

inline std::ostream& operator<<(
        std::ostream& stream, const SchemaTypeDefinition& typeDef)
{
    typeDef.print(stream, 0, -1);
    return stream;
}

inline void SchemaTypeDefinition::setUserData(void *newUserData)
{
    blpapi_SchemaTypeDefinition_setUserData(d_impl_p, newUserData);
}

inline void *SchemaTypeDefinition::userData() const
{
    return blpapi_SchemaTypeDefinition_userData(d_impl_p);
}

inline const ConstantList SchemaTypeDefinition::enumeration() const
{
    return blpapi_SchemaTypeDefinition_enumeration(d_impl_p);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_SCHEMA
