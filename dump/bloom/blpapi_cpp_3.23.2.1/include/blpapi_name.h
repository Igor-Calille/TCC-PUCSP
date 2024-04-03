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

/** \file blpapi_name.h */
/** \defgroup blpapi_name Component blpapi_name
\brief Provide a representation of strings for use as container keys.
\file blpapi_name.h
\brief Provide a representation of strings for use as container keys.
*/

#ifndef INCLUDED_BLPAPI_NAME
#define INCLUDED_BLPAPI_NAME

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_name
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide a representation of strings for use as container keys.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::Name</td>
 * <td>constant string in an efficient form for use as container keys</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component implements a representation of a string which is
 * efficient for use as a key in a container (constant-time hashing and
 * ordering operations using the standard "intern string" technique).
 */
/** @} */
/** @} */

#include <blpapi_defs.h>
#include <blpapi_types.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
blpapi_Name_t *blpapi_Name_create(const char *nameString);

BLPAPI_EXPORT
void blpapi_Name_destroy(blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_Name_duplicate(const blpapi_Name_t *src);

BLPAPI_EXPORT
int blpapi_Name_equalsStr(const blpapi_Name_t *name, const char *string);

BLPAPI_EXPORT
const char *blpapi_Name_string(const blpapi_Name_t *name);

BLPAPI_EXPORT
size_t blpapi_Name_length(const blpapi_Name_t *name);

BLPAPI_EXPORT
blpapi_Name_t *blpapi_Name_findName(const char *nameString);

#ifdef __cplusplus
}

#include <cstring> // for strcmp
#include <iostream>
#include <utility> // for swap

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_name
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!  <code>Name</code> represents a string in a form which provides O(1)
 * hashing and comparison, independent of the string length.
 *
 * <code>Name</code> objects are used to identify and access the classes which
 * define a schema - <code>SchemaTypeDefinition</code>,
 * <code>SchemaElementDefinition</code>, <code>Constant</code>, and
 * <code>ConstantList</code>.  They are also used to access the values in
 * <code>Element</code> objects and <code>Message</code> objects.
 *
 * The <code>Name</code> class is an efficient substitute for a string when
 * used as a key, providing constant-time hashing and comparison.  Two
 * <code>Name</code> objects constructed from strings for which
 * <code>strcmp()</code> would return 0 will always compare equal.
 *
 * The ordering of <code>Name</code> objects (as defined by
 * <code>operator\<(Name,Name)</code>) is consistent during a particular
 * instance of a single application. However, the ordering is not lexical and
 * is not necessarily consistent with the ordering of the same
 * <code>Name</code> objects in any other process.
 *
 * <strong><code>Name</code></strong> <strong>objects</strong>
 * <strong>should</strong> <strong>be</strong> <strong>initialized</strong>
 * <strong>once</strong> <strong>and</strong> <strong>then</strong>
 * <strong>reused</strong>.  Creating a <code>Name</code> object from a
 * <code>const char*</code> involves a search in a container requiring multiple
 * string comparison operations.
 *
 * Note: Each <code>Name</code> instance refers to an entry in a global static
 * table. <code>Name</code> instances for identical strings will refer to the
 * same data. There is no provision for removing entries from the static table
 * so <code>Name</code> objects should be used only when the set of input
 * strings is bounded.
 *
 * For example, creating a <code>Name</code> for every possible field name and
 * type in a data model is reasonable (in fact, the API will do this whenever
 * it receives schema information).  Converting sequence numbers from incoming
 * messages to strings and creating a <code>Name</code> from each one of those
 * strings, however, will cause the static table to grow in an unbounded
 * manner, and is tantamount to a memory leak.
 */
/*!
 * See \ref blpapi_name
 */
class Name {

    blpapi_Name_t *d_impl_p;

  public:
    // CLASS METHODS

    static Name findName(const char *nameString);
    /*!<
     * If a <code>Name</code> already exists which matches the specified
     * <code>nameString</code>, then return a copy of that <code>Name</code>;
     * otherwise return a <code>Name</code> which will compare equal to a
     * <code>Name</code> created using the default constructor. The behavior is
     * undefined if <code>nameString</code> does not point to a null-terminated
     * string.
     */

    static bool hasName(const char *nameString);
    /*!<
     * Return <code>true</code> if a <code>Name</code> has been created which
     * matches the specified <code>nameString</code>; otherwise return
     * <code>false</code>. The behavior is undefined if <code>nameString</code>
     * does not point to a null-terminated string.
     */

    Name();
    /*!<
     * Construct an uninitialized <code>Name</code>. An uninitialized
     * <code>Name</code> can be assigned to, destroyed, or tested for equality.
     * The behavior for all other operations is undefined.
     */

    Name(blpapi_Name_t *handle);

    Name(const Name& original);
    /*!<
     * Create a <code>Name</code> object having the same value as the specified
     * <code>original</code>.
     */

    explicit Name(const char *nameString);
    /*!<
     * Construct a <code>Name</code> from the specified
     * <code>nameString</code>. The behavior is undefined unless
     * <code>nameString</code> is a null-terminated string. Note that any
     * null-terminated string can be specified, including an empty string. Note
     * also that constructing a <code>Name</code> from a <code>const char
     * *</code> is a relatively expensive operation. If a <code>Name</code>
     * will be used repeatedly it is preferable to create it once and re-use
     * (or copy) the object.
     */

    ~Name();
    /*!<
     * Destroy this object.
     */

    // MANIPULATORS

    Name& operator=(const Name& rhs);
    /*!<
     * Assign to this object the value of the specified <code>rhs</code>,
     * and return a reference to this modifiable object.
     */

    // ACCESSORS

    const char *string() const;
    /*!<
     * Return a pointer to the null-terminated string value of this
     * <code>Name</code>. The pointer returned will be valid at least until
     * main() exits.
     */

    size_t length() const;
    /*!<
     * Return the length of the string value of this <code>Name</code>,
     * (excluding a terminating null). Note that <code>name.length()</code> is
     * logically equivalent to <code>strlen(name.string())</code>, however the
     * former is potentially more efficient.
     */

    size_t hash() const;
    /*!<
     * Return an integral value such that for two <code>Name</code> objects
     * <code>a</code> and <code>b</code>, if <code>a == b</code> then
     * <code>a.hash() == b.hash()</code>, and if <code>a != b</code> then it is
     * unlikely that <code>a.hash() == b.hash()</code>.
     */

    blpapi_Name_t *impl() const;
};

/** @} */
/** @} */

// FREE OPERATORS
bool operator==(const Name& lhs, const Name& rhs);
/*!<
 * Return true if the specified <code>lhs</code> and <code>rhs</code> name
 * objects have the same value, and false otherwise. Two <code>Name</code>
 * objects <code>a</code> and <code>b</code> have the same value if and only if
 * <code>strcmp(a.string(), b.string()) == 0</code>.
 */

bool operator!=(const Name& lhs, const Name& rhs);
/*!<
 * Return false if the specified <code>lhs</code> and <code>rhs</code> name
 * objects have the same value, and true otherwise. Two <code>Name</code>
 * objects <code>a</code> and <code>b</code> have the same value if and only if
 * <code>strcmp(a.string(), b.string()) == 0</code>.  Note that <code>lhs !=
 * rhs</code> is equivalent to <code>!(lhs==rhs)</code>.
 */

bool operator==(const Name& lhs, const char *rhs);
/*!<
 * Return true if the specified <code>lhs</code> and <code>rhs</code> have the
 * same value, and false otherwise. A <code>Name</code> object <code>a</code>
 * and a null-terminated string <code>b</code> have the same value if and only
 * if <code>strcmp(a.string(), b) == 0</code>. The behavior is undefined unless
 * <code>rhs</code> is a null-terminated string.
 */

bool operator!=(const Name& lhs, const char *rhs);
/*!<
 * Return false if the specified <code>lhs</code> and <code>rhs</code> have the
 * same value, and true otherwise. A <code>Name</code> object <code>a</code>
 * and a null-terminated string <code>b</code> have the same value if and only
 * if <code>strcmp(a.string(), b) == 0</code>. The behavior is undefined unless
 * <code>rhs</code> is a null-terminated string.
 */

bool operator==(const char *lhs, const Name& rhs);
/*!<
 * Return true if the specified <code>lhs</code> and <code>rhs</code> have the
 * same value, and false otherwise. A <code>Name</code> object <code>a</code>
 * and a null-terminated string <code>b</code> have the same value if and only
 * if <code>strcmp(a.string(), b) == 0</code>. The behavior is undefined unless
 * <code>lhs</code> is a null-terminated string.
 */

bool operator!=(const char *lhs, const Name& rhs);
/*!<
 * Return false if the specified <code>lhs</code> and <code>rhs</code> have the
 * same value, and true otherwise. A <code>Name</code> object <code>a</code>
 * and a null-terminated string <code>b</code> have the same value if and only
 * if <code>strcmp(a.string(), b) == 0</code>. The behavior is undefined unless
 * <code>lhs</code> is a null-terminated string.
 */

bool operator<(const Name& lhs, const Name& rhs);
/*!<
 * Return <code>true</code> if the specified <code>lhs</code> is ordered before
 * the specified <code>rhs</code>, and <code>false</code> otherwise. The
 * ordering used is stable within the lifetime of a single process and is
 * compatible with <code>operator==(const Name\&, const Name\&)</code>, however
 * this order is neither guaranteed to be consistent across different processes
 * (including repeated runs of the same process), nor guaranteed to be lexical
 * (i.e. compatible with <code>strcmp</code>).
 */

bool operator<=(const Name& lhs, const Name& rhs);
/*!<
 * Return <code>false</code> if the specified <code>rhs</code> is ordered
 * before the specified <code>lhs</code>, and <code>true</code> otherwise. The
 * ordering used is stable within the lifetime of a single process and is
 * compatible with <code>operator==(const Name\&, const Name\&)</code>, however
 * this order is neither guaranteed to be consistent across different processes
 * (including repeated runs of the same process), nor guaranteed to be lexical
 * (i.e. compatible with <code>strcmp</code>).
 */

bool operator>(const Name& lhs, const Name& rhs);
/*!<
 * Return <code>true</code> if the specified <code>rhs</code> is ordered before
 * the specified <code>lhs</code>, and <code>false</code> otherwise. The
 * ordering used is stable within the lifetime of a single process and is
 * compatible with <code>operator==(const Name\&, const Name\&)</code>, however
 * this order is neither guaranteed to be consistent across different processes
 * (including repeated runs of the same process), nor guaranteed to be lexical
 * (i.e. compatible with <code>strcmp</code>).
 */

bool operator>=(const Name& lhs, const Name& rhs);
/*!<
 * Return <code>false</code> if the specified <code>lhs</code> is ordered
 * before the specified <code>rhs</code>, and <code>true</code> otherwise. The
 * ordering used is stable within the lifetime of a single process and is
 * compatible with <code>operator==(const Name\&, const Name\&)</code>, however
 * this order is neither guaranteed to be consistent across different processes
 * (including repeated runs of the same process), nor guaranteed to be lexical
 * (i.e. compatible with <code>strcmp</code>).
 */

std::ostream& operator<<(std::ostream& stream, const Name& name);
/*!<
 * Write the value of the specified <code>name</code> object to the specified
 * output <code>stream</code>, and return a reference to <code>stream</code>.
 * Note that this human-readable format is not fully specified and can change
 * without notice.
 */

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

// ----------
// class Name
// ----------

inline Name::Name(blpapi_Name_t *handle)
    : d_impl_p(handle)
{
}

inline Name::Name()
    : d_impl_p(0)
{
}

inline Name::Name(const Name& original)
    : d_impl_p(blpapi_Name_duplicate(original.d_impl_p))
{
}

inline Name::Name(const char *nameString)
{
    d_impl_p = blpapi_Name_create(nameString);
}

inline Name::~Name()
{
    if (d_impl_p) {
        blpapi_Name_destroy(d_impl_p);
    }
}

inline Name& Name::operator=(const Name& rhs)
{
    using std::swap;

    Name tmp(rhs);
    swap(tmp.d_impl_p, d_impl_p);
    return *this;
}

inline const char *Name::string() const
{
    return blpapi_Name_string(d_impl_p);
}

inline size_t Name::length() const { return blpapi_Name_length(d_impl_p); }

inline blpapi_Name_t *Name::impl() const { return d_impl_p; }

inline Name Name::findName(const char *nameString)
{
    return Name(blpapi_Name_findName(nameString));
}

inline bool Name::hasName(const char *nameString)
{
    return blpapi_Name_findName(nameString) ? true : false;
}

inline size_t Name::hash() const { return reinterpret_cast<size_t>(impl()); }

} // close namespace blpapi

inline bool blpapi::operator==(const Name& lhs, const Name& rhs)
{
    return (lhs.impl() == rhs.impl());
}

inline bool blpapi::operator!=(const Name& lhs, const Name& rhs)
{
    return !(lhs == rhs);
}

inline bool blpapi::operator==(const Name& lhs, const char *rhs)
{
    return blpapi_Name_equalsStr(lhs.impl(), rhs) != 0;
}

inline bool blpapi::operator!=(const Name& lhs, const char *rhs)
{
    return !(lhs == rhs);
}

inline bool blpapi::operator==(const char *lhs, const Name& rhs)
{
    return rhs == lhs;
}

inline bool blpapi::operator!=(const char *lhs, const Name& rhs)
{
    return !(rhs == lhs);
}

inline bool blpapi::operator<(const Name& lhs, const Name& rhs)
{
    return lhs.impl() < rhs.impl();
}

inline bool blpapi::operator<=(const Name& lhs, const Name& rhs)
{
    return !(rhs < lhs);
}

inline bool blpapi::operator>(const Name& lhs, const Name& rhs)
{
    return rhs < lhs;
}

inline bool blpapi::operator>=(const Name& lhs, const Name& rhs)
{
    return !(lhs < rhs);
}

inline std::ostream& blpapi::operator<<(std::ostream& stream, const Name& name)
{
    return stream << name.string();
}

} // close namespace BloombergLP

#endif // __cplusplus

#endif // #ifndef INCLUDED_BLPAPI_NAME
