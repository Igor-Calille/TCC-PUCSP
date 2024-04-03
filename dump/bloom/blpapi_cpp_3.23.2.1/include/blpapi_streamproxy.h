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

/** \file blpapi_streamproxy.h */
/** \defgroup blpapi_streamproxy Component blpapi_streamproxy
\brief A signature for callback on print and default C++ implementation
\file blpapi_streamproxy.h
\brief A signature for callback on print and default C++ implementation
*/

#ifndef INCLUDED_BLPAPI_STREAMPROXY
#define INCLUDED_BLPAPI_STREAMPROXY

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_streamproxy
 * @{
 * <A NAME="purpose"></A>
 * <A NAME="1"> \par Purpose: </A>
 * A signature for callback on print and default C++ implementation
 * \par
 * \par
 * <A NAME="description"></A>
 * <A NAME="2"> \par Description: </A>
 *
 * This file defines <code>blpapi_StreamWriter_t</code> a function pointer
 * type. The user of the C API need to specify a callback of above type which
 * will be called on xxx_print(...) with the formatted data. For C++ API, a
 * default callback is specified which writes data to the stream specified in
 * xxx::print
 */
/** @} */
/** @} */

typedef int (*blpapi_StreamWriter_t)(
        const char *data, int length, void *stream);

#ifdef __cplusplus

#include <cassert>
#include <ostream>

/** \addtogroup blpapi
 * @{
 */
/** \addtogroup blpapi_streamproxy
 * @{
 */

namespace BloombergLP {
namespace blpapi {

inline int OstreamWriter(const char *data, int length, void *stream);
/*!<
 * \deprecated Use StreamProxyOstream::writeToStream instead.
 */

struct StreamProxyOstream {

    static int writeToStream(const char *data, int length, void *stream);
    /*!<
     * Format, to the specified <code>stream</code>, which must be a pointer to
     * a <code>std::ostream</code>, the specified <code>length</code> bytes of
     * the specified <code>data</code>.
     */
};

/** @} */
/** @} */

//=============================================================================
//                           INLINE FUNCTION DEFINITIONS
//=============================================================================

inline int StreamProxyOstream::writeToStream(
        const char *data, int length, void *stream)
{
    assert(stream);

    reinterpret_cast<std::ostream *>(stream)->write(data, length);
    return 0;
}

inline int OstreamWriter(const char *data, int length, void *stream)
{
    return StreamProxyOstream::writeToStream(data, length, stream);
}

} // close namespace blpapi
} // close namespace BloombergLP

#endif // #ifdef __cplusplus
#endif // #ifndef INCLUDED_BLPAPI_STREAMPROXY
