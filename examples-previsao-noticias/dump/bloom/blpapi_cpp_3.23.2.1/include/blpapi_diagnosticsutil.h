/* Copyright 2013. Bloomberg Finance L.P.
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

/** \file blpapi_diagnosticsutil.h */
/** \defgroup blpapi_diagnosticsutil Component blpapi_diagnosticsutil
\brief Provide api to access diagnostics information on the blpapi library
\file blpapi_diagnosticsutil.h
\brief Provide api to access diagnostics information on the blpapi library
*/

#ifndef INCLUDED_BLPAPI_DIAGNOSTICSUTIL
#define INCLUDED_BLPAPI_DIAGNOSTICSUTIL

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_diagnosticsutil
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * Provide api to access diagnostics information on the blpapi library
 * \par
 * \par
 * <A NAME="classes"></A>
 * <A NAME="2"> \par Classes: </A>
 * <table>
 * <tr>
 * <td>blpapi::DiagnosticsUtil</td>
 * <td>collection of diagnostics information functions</td>
 * </tr>
 * </table>
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="3"> \par Description: </A>
 *  This component provide a collection of functions which give
 * access to various sets of diagnostics information on the <code>blpapi</code>
 * library.
 */
/** @} */
/** @} */

#ifndef INCLUDED_BLPAPI_CALL
#include <blpapi_call.h>
#endif

#ifndef INCLUDED_BLPAPI_DEFS
#include <blpapi_defs.h>
#endif

#ifndef INCLUDED_STDDEF
#include <stddef.h>
#define INCLUDED_STDDEF
#endif

#ifdef __cplusplus
extern "C" {
#endif

BLPAPI_EXPORT
int blpapi_DiagnosticsUtil_memoryInfo(char *buffer, size_t bufferLength);

#ifdef __cplusplus
}

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_diagnosticsutil
 * @{
 */

namespace BloombergLP {
namespace blpapi {

class DiagnosticsUtil {
  public:
    static int memoryInfo(char *buffer, size_t bufferLength);
    /*!<
     * Load into the specified <code>buffer</code> up to the specified
     * <code>bufferLength</code> characters of a null-terminated string
     * describing the <code>blpapi</code> library's memory usage; the format of
     * the string is platform-specific.  On success, return the number of
     * characters required to output the entire string, not including the null
     * terminator; otherwise return a negative value.  Note that if the value
     * returned from this function is greater than or equal to
     * <code>bufferLength</code> then the output is truncated and is
     * <em>not</em> null-terminated.
     */
};

inline int DiagnosticsUtil::memoryInfo(char *buffer, size_t bufferLength)
{
    BLPAPI_CALL_DIAGNOSTICSUTIL_MEMORYINFO(buffer, bufferLength);
}

}
}

/** @} */
/** @} */

#endif

#endif
