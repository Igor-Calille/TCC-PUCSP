/* Copyright 2021, Bloomberg Finance L.P.
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
#ifndef INCLUDED_CATEGORIZEDFIELDSEARCHREQUESTS
#define INCLUDED_CATEGORIZEDFIELDSEARCHREQUESTS

#include <blpapi_element.h>
#include <blpapi_event.h>
#include <blpapi_message.h>
#include <blpapi_request.h>
#include <blpapi_service.h>

#include <iostream>
#include <string>

#include <snippets/apiflds/ApiFieldsRequestUtils.h>

using namespace BloombergLP;
using blpapi::Element;
using blpapi::Event;
using blpapi::Message;
using blpapi::Name;
using blpapi::Request;
using blpapi::Service;

struct CategorizedFieldSearchRequests {
    static Request createRequest(const Service& apifldsService);
    static void processResponse(const Event& event);
};

inline Request CategorizedFieldSearchRequests::createRequest(
        const Service& apifldsService)
{
    static const Name k_searchSpec { "searchSpec" };
    static const Name k_exclude { "exclude" };
    static const Name k_fieldType { "fieldType" };
    static const Name k_returnFieldDocumentation {
        "returnFieldDocumentation"
    };

    Request request
            = apifldsService.createRequest("CategorizedFieldSearchRequest");
    request.set(k_searchSpec, "last price");

    Element exclude = request.getElement(k_exclude);
    exclude.setElement(k_fieldType, "Static");

    request.set(k_returnFieldDocumentation, false);

    return request;
}

inline void CategorizedFieldSearchRequests::processResponse(const Event& event)
{
    static const int k_CatNameLen { 40 };
    static const Name k_category { "category" };
    static const Name k_categoryName { "categoryName" };
    static const Name k_categoryId { "categoryId" };
    static const Name k_fieldSearchError { "fieldSearchError" };
    static const Name k_fieldData { "fieldData" };

    for (Message msg : event) {
        if (msg.hasElement(k_fieldSearchError)) {
            msg.print(std::cout);
            continue;
        }

        Element categories = msg.getElement(k_category);
        size_t numCategories = categories.numValues();

        for (size_t catIdx = 0; catIdx < numCategories; ++catIdx) {
            Element category = categories.getValueAsElement(catIdx);
            std::string name = category.getElementAsString(k_categoryName);
            std::string id = category.getElementAsString(k_categoryId);

            std::cout << "\nCategory Name:"
                      << ApiFieldsRequestUtils::padString(name, k_CatNameLen)
                      << "\tId:" << id << "\n";

            ApiFieldsRequestUtils::printHeader();

            Element fields = category.getElement(k_fieldData);
            size_t numValues = fields.numValues();
            for (size_t i = 0; i < numValues; i++) {
                ApiFieldsRequestUtils::printField(fields.getValueAsElement(i));
            }
        }
    }
}

#endif // INCLUDED_CATEGORIZEDFIELDSEARCHREQUESTS
