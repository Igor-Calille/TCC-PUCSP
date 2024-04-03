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

/** \file blpapi_versioninfo.h */
/** \defgroup blpapi_versioninfo Component blpapi_versioninfo
\brief Provide BLPAPI SDK library version information.
\file blpapi_versioninfo.h
\brief Provide BLPAPI SDK library version information.
*/

#ifndef INCLUDED_BLPAPI_VERSIONINFO
#define INCLUDED_BLPAPI_VERSIONINFO

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_versioninfo
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide BLPAPI SDK library version information.
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::VersionInfo</td>
 * <td>basic BLPAPI SDK library version attribute class</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 * This component provides access to the BLPAPI SDK library version
 * information.  Each version of the BLPAPI library is identified by four
 * integers: major, minor, patch, and build.
 * \par
 * The current major version is 3; there is no guarantee of compatibility
 * between different major versions.
 * \par
 * Differences in minor version numbers indicate significant feature additions.
 * Standard distributions of the BLPAPI have minor version numbers below 128,
 * and higher minor numbers are expected to provide APIs that are a superset of
 * the APIs provided by lower minor version numbers; i.e. all functionality and
 * interfaces supported by BLPAPI 3.7 is also provided by BLPAPI 3.8, while the
 * inverse is not typically true. (Bloomberg occasionally distributes library
 * versions with version numbers above 127; consult the release information
 * distributed with these libraries to determine interoperability with other
 * minor versions.)
 * \par
 * Increments to patch numbers indicate performance or stability enhancements
 * to the library.
 * \par
 * Build numbers typically do not carry any information about the library
 * version's functionality, but can be used along with the other parts of the
 * build number to uniquely identity a precise library binary version (e.g. for
 * the purpose of code signing and auditing).
 * \par
 * \par
 * <A NAME="usage"></A>
 * <A NAME="description.usage"></A>
 * <A NAME="3.1"> \par Usage: </A>
 * \par
 * <A NAME="c++_usage"></A>
 * <A NAME="usage.c++_usage"></A>
 * <A NAME="description.usage.c++_usage"></A>
 * <A NAME="3.1.1"> \par C++ usage: </A>
 * This example logs the BLPAPI version in order to make the logs analysis more
 * productive:
\code
  blpapi::VersionInfo blpapiVersion;
  // Client log the library version for reference and future debugging
  log("BLPAPI version: %d.%d.%d.%d",
      blpapiVersion.majorVersion(),
      blpapiVersion.minorVersion(),
      blpapiVersion.patchVersion(),
      blpapiVersion.buildVersion());
\endcode
 * \par
 * \par
 * <A NAME="c_usage"></A>
 * <A NAME="usage.c_usage"></A>
 * <A NAME="description.usage.c_usage"></A>
 * <A NAME="3.1.2"> \par C usage: </A>
 * This example logs the BLPAPI version in order to make the logs analysis more
 * productive:
\code
  int majorVersion, minorVersion, patchVersion, buildVersion;
  blpapi_getVersionInfo(&majorVersion, &minorVersion, &patchVersion,
      &buildVersion);
  // Client log the library version for reference and future debugging
  log("BLPAPI version: %d.%d.%d.%d", majorVersion, minorVersion,
      patchVersion, buildVersion);
\endcode
 * \par
 * \par
 * This example shows how to use the API backward compatibility macros
 * BLPAPI_SDK_VERSION and BLPAPI_MAKE_VERSION (see blpapi_dispatchtbl.h):
\code
  #if BLPAPI_SDK_VERSION >= BLPAPI_MAKE_VERSION(3, 3, 7)
      // Do version 3.3.7 specific stuff here (e.g. adding functions with old
      // signature to an array so a client code that was compiled with
      // version 3.3.7 will still be able to run using the new version.
      ...
  #elif BLPAPI_SDK_VERSION ...
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

#ifndef INCLUDED_BLPAPI_VERSIONMACROS
#include <blpapi_versionmacros.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

BLPAPI_EXPORT
void blpapi_getVersionInfo(int *majorVersion,
        int *minorVersion,
        int *patchVersion,
        int *buildVersion);
/*!<
 * Initialize the 4 parameters with the current release version information
 * which include the following version parts: Major, Minor, Patch, and
 * Build.
 */

BLPAPI_EXPORT
const char *blpapi_getVersionIdentifier(void);
/*!<
 * Return a null-terminated sequence of printable ascii characters (with
 * values from 0x20 to 0x7e, inclusive) identifying the version of the
 * blpapi runtime library.  The lifetime of the returned string is
 * guaranteed until the end of `main()` (but is <em>not</em> necessarily usable
 * during the C++ static destruction phase).
 */

#ifdef __cplusplus
}

#include <ostream>
#include <sstream>
#include <string>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_versioninfo
 * @{
 */

namespace BloombergLP {
namespace blpapi {

/*!
 *     This attribute class holds the four integer components of a BLPAPI
 *     version number, provides factory methods to obtain such version numbers
 *     for both the headers used at compile time and the library loaded at run
 *     time, and provides a static function to obtain an opaque version
 *     identifier string for use by Bloomberg support.
 */
/*!
 * See \ref blpapi_versioninfo
 */
class VersionInfo {

  private:
    /*!  BLPAPI SDK library major version */
    int d_major;
    /*!  BLPAPI SDK library minor version */
    int d_minor;
    /*!  BLPAPI SDK library patch version */
    int d_patch;
    /*!  BLPAPI SDK library build version */
    int d_build;

    VersionInfo(int major, int minor, int patch, int build);
    /*!<
     * Create a <code>VersionInfo</code> object containing the specified
     * <code>major</code>, <code>minor</code>, <code>patch</code>, and
     * <code>build</code> numbers.
     */

  public:
    // CREATORS
    static VersionInfo headerVersion();
    /*!<
     * Return a <code>VersionInfo</code> object containing the version of the
     * BLPAPI headers against which the client application was compiled.  Note
     * that the version of the BLPAPI library loaded at runtime may be
     * different than the version of the headers against which the code was
     * compiled.
     */

    static VersionInfo runtimeVersion();
    /*!<
     * Return a <code>VersionInfo</code> object containing the version of the
     * BLPAPI runtime library that is currently running.  Note that the version
     * of the BLPAPI library loaded at runtime may be different than the
     * version of the headers against which the code was compiled.
     */

    VersionInfo();
    /*!<
     * This function is a synonym for
     * <code>VersionInfo::runtimeVersion()</code>. DEPRECATED
     */

    // ACCESSORS
    int majorVersion() const;
    /*!<
     *     Return the major version number.
     */
    int minorVersion() const;
    /*!<
     *     Return the minor version number.
     */
    int patchVersion() const;
    /*!<
     *     Return the patch version number.
     */
    int buildVersion() const;
    /*!<
     *     Return the build version number.
     */

    static std::string versionIdentifier();
    /*!<
     *     Return a string containing a sequence of printable ascii characters
     *     (with values from 0x20 to 0x7e, inclusive) identifying the version
     *     of the blpapi runtime library.  The format of this string is
     *     unspecified.
     */
};

/** @} */
/** @} */

std::ostream& operator<<(std::ostream& stream, const VersionInfo& rhs);
/*!<
 * Output the specified <code>rhs</code> to the specified <code>stream</code>
 * in a human-readable format.  Note that the exact details of this format are
 * not specified and may be differ between different library versions.
 */

//=============================================================================
//                         INLINE FUNCTION DEFINITIONS
//=============================================================================

// -----------------
// class VersionInfo
// -----------------
// CREATORS
inline VersionInfo::VersionInfo(int major, int minor, int patch, int build)
    : d_major(major)
    , d_minor(minor)
    , d_patch(patch)
    , d_build(build)
{
}

inline VersionInfo VersionInfo::headerVersion()
{
    return VersionInfo(BLPAPI_VERSION_MAJOR,
            BLPAPI_VERSION_MINOR,
            BLPAPI_VERSION_PATCH,
            BLPAPI_VERSION_BUILD);
}

inline VersionInfo VersionInfo::runtimeVersion()
{
    int major, minor, patch, build;
    blpapi_getVersionInfo(&major, &minor, &patch, &build);
    return VersionInfo(major, minor, patch, build);
}

inline VersionInfo::VersionInfo()
{
    blpapi_getVersionInfo(&d_major, &d_minor, &d_patch, &d_build);
}

// ACCESSORS
inline int VersionInfo::majorVersion() const { return d_major; }

inline int VersionInfo::minorVersion() const { return d_minor; }

inline int VersionInfo::patchVersion() const { return d_patch; }

inline int VersionInfo::buildVersion() const { return d_build; }

inline std::string VersionInfo::versionIdentifier()
{
    std::ostringstream oss;
    oss << "blpapi-cpp; headers " << headerVersion() << "; runtime "
        << runtimeVersion();
    return oss.str();
}

inline std::ostream& operator<<(std::ostream& stream, const VersionInfo& rhs)
{
    return stream << rhs.majorVersion() << '.' << rhs.minorVersion() << '.'
                  << rhs.patchVersion() << '.' << rhs.buildVersion();
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // ifdef __cplusplus

#endif // INCLUDED_BLPAPI_VERSIONINFO
