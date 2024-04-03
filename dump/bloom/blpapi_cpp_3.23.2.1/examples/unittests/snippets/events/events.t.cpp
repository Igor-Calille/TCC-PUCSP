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

#include <blpapi_name.h>
#include <blpapi_names.h>
#include <blpapi_testutil.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

namespace blp = BloombergLP::blpapi;
namespace blptst = blp::test;

// Following test cases provides an example on how to mock different events
// supported by blpapi-sdk. The code to set up expectation and verification of
// values is omitted from examples tests.

// SESSION STATUS EVENTS
// =====================
//
// Session status events provide notifications about the session and
// connectivity state.  The following tests provide examples of each one of the
// event/messages that the application may expect.
//
// Applications need to handle:
// - 'SessionStarted',
// - 'SessionStartupFailure'
// -  'SessionTerminated'
//
// Applications can safely ignore:
// - 'SessionConnectionUp',
// - 'SessionConnectionDown'
// - 'SessionClusterInfo'
// - 'SessionClusterUpdate'
//
// These events are informational only and applications should not react to
// them.

static const blp::Name k_address { "address" };
static const blp::Name k_appName { "appName" };
static const blp::Name k_applicationId { "applicationId" };
static const blp::Name k_boundTo { "boundTo" };
static const blp::Name k_category { "category" };
static const blp::Name k_compressionStatus { "compressionStatus" };
static const blp::Name k_socks5Proxy { "socks5Proxy" };
static const blp::Name k_dataConnection { "dataConnection" };
static const blp::Name k_description { "description" };
static const blp::Name k_deviceAddress { "deviceAddress" };
static const blp::Name k_encryptionStatus { "encryptionStatus" };
static const blp::Name k_endpoint { "endpoint" };
static const blp::Name k_endpoints { "endpoints" };
static const blp::Name k_endpointsAdded { "endpointsAdded" };
static const blp::Name k_endpointsRemoved { "endpointsRemoved" };
static const blp::Name k_errorCode { "errorCode" };
static const blp::Name k_eventsDropped { "eventsDropped" };
static const blp::Name k_exceptions { "exceptions" };
static const blp::Name k_failureDetails { "failureDetails" };
static const blp::Name k_fieldId { "fieldId" };
static const blp::Name k_id { "id" };
static const blp::Name k_isSolicited { "isSolicited" };
static const blp::Name k_initialEndpoints { "initialEndpoints" };
static const blp::Name k_name { "name" };
static const blp::Name k_numMessagesDropped { "numMessagesDropped" };
static const blp::Name k_publishing { "publishing" };
static const blp::Name k_reason { "reason" };
static const blp::Name k_receivedFrom { "receivedFrom" };
static const blp::Name k_resolvedTopic { "resolvedTopic" };
static const blp::Name k_resubscriptionId { "resubscriptionId" };
static const blp::Name k_seatType { "seatType" };
static const blp::Name k_server { "server" };
static const blp::Name k_serverAdded { "serverAdded" };
static const blp::Name k_serverId { "serverId" };
static const blp::Name k_serverRemoved { "serverRemoved" };
static const blp::Name k_servers { "servers" };
static const blp::Name k_serviceName { "serviceName" };
static const blp::Name k_servicePart { "servicePart" };
static const blp::Name k_source { "source" };
static const blp::Name k_streamIds { "streamIds" };
static const blp::Name k_streams { "streams" };
static const blp::Name k_subcategory { "subcategory" };
static const blp::Name k_topic { "topic" };
static const blp::Name k_topicWithOptions { "topicWithOptions" };
static const blp::Name k_topics { "topics" };
static const blp::Name k_token { "token" };
static const blp::Name k_userName { "userName" };
static const blp::Name k_uuid { "uuid" };

blp::Element getSubElement(const blp::Element& element, const blp::Name& name)
{
    return element.getElement(name);
}

blp::Element getSubElement(const blp::Element element, int i)
{
    return element.getValueAsElement(i);
}

blp::Element elementAt(const blp::Element& element) { return element; }

// Helper function to return a sub-element of an element given path
template <typename First, typename... Ts>
blp::Element elementAt(const blp::Element& element, First f, Ts... args)
{
    blp::Element sub = getSubElement(element, f);
    if (sizeof...(args) > 0) {
        sub = elementAt(sub, args...);
    }
    return sub;
}

// Helper function to return the first message of an event
blp::Element firstMessage(const blp::Event& event)
{
    blp::MessageIterator it(event);
    bool hasMessage = it.next();
    assert(hasMessage);
    return it.message().asElement();
}

// Helper function that validates the common element 'reason'
::testing::AssertionResult validateReasonElement(const blp::Element& root)
{
    blp::Element reason = root.getElement(k_reason);

    const char *source = reason.getElementAsString(k_source);
    if (strcmp("TestUtil", source)) {
        return ::testing::AssertionFailure()
                << "Expected source to be 'TestUtil', actual: " << source;
    }

    int errorCode = reason.getElementAsInt32(k_errorCode);
    if (-1 != errorCode) {
        return ::testing::AssertionFailure()
                << "Expected errorCode to be '-1', actual: " << errorCode;
    }

    const char *category = reason.getElementAsString(k_category);
    if (strcmp("CATEGORY", category)) {
        return ::testing::AssertionFailure()
                << "Expected category to be 'CATEGORY', actual: " << category;
    }

    const char *description = reason.getElementAsString(k_description);
    if (strcmp("for testing", description)) {
        return ::testing::AssertionFailure()
                << "Expected source to be 'for testing', actual: "
                << description;
    }

    const char *subcategory = reason.getElementAsString(k_subcategory);
    if (strcmp("SUBCATEGORY", subcategory)) {
        return ::testing::AssertionFailure()
                << "Expected source to be 'SUBCATEGORY', actual: "
                << subcategory;
    }
    return ::testing::AssertionSuccess();
}

TEST(ExampleEvents, SessionStarted)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionStarted());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"initialEndpoints\": [                     "
                             "       { \"address\": \"12.34.56.78:8194\" },  "
                             "       { \"address\": \"98.76.54.32:8194\" }   "
                             "   ]                                           "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_initialEndpoints, 0, k_address)
                    .getValueAsString());
    EXPECT_STREQ("98.76.54.32:8194",
            elementAt(msg, k_initialEndpoints, 1, k_address)
                    .getValueAsString());
}

TEST(ExampleEvents, SessionStartupFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionStartupFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                            "
                             "   \"reason\": {                             "
                             "       \"source\":      \"TestUtil\",        "
                             "       \"errorCode\":   -1,                  "
                             "       \"category\":    \"CATEGORY\",        "
                             "       \"description\": \"for testing\",     "
                             "       \"subcategory\": \"SUBCATEGORY\"      "
                             "    }                                        "
                             "}                                            ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

TEST(ExampleEvents, SessionTerminated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionTerminated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                            "
                             "   \"reason\": {                             "
                             "       \"source\":      \"TestUtil\",        "
                             "       \"errorCode\":   -1,                  "
                             "       \"category\":    \"CATEGORY\",        "
                             "       \"description\": \"for testing\",     "
                             "       \"subcategory\": \"SUBCATEGORY\"      "
                             "    }                                        "
                             "}                                            ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

TEST(ExampleEvents, SessionConnectionUp)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionConnectionUp());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"server\":            \"12.34.56.78:8194\","
                             "   \"serverId\":          \"ny-hostname\",     "
                             "   \"encryptionStatus\":  \"Clear\",           "
                             "   \"compressionStatus\": \"Uncompressed\",    "
                             "   \"socks5Proxy\":       \"socks5Host:1080\"  "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("12.34.56.78:8194", msg.getElementAsString(k_server));
    EXPECT_STREQ("ny-hostname", msg.getElementAsString(k_serverId));
    EXPECT_STREQ("Clear", msg.getElementAsString(k_encryptionStatus));
    EXPECT_STREQ("Uncompressed", msg.getElementAsString(k_compressionStatus));
    EXPECT_STREQ("socks5Host:1080", msg.getElementAsString(k_socks5Proxy));
}

TEST(ExampleEvents, SessionConnectionDown)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionConnectionDown());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"server\":           \"12.34.56.78:8194\", "
                             "   \"serverId\":         \"ny-hostname\",      "
                             "   \"socks5Proxy\":       \"socks5Host:1080\"  "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("12.34.56.78:8194", msg.getElementAsString(k_server));
    EXPECT_STREQ("ny-hostname", msg.getElementAsString(k_serverId));
    EXPECT_STREQ("socks5Host:1080", msg.getElementAsString(k_socks5Proxy));
}

TEST(ExampleEvents, SessionClusterInfo)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionClusterInfo());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"name\":           \"clustername\",        "
                             "   \"endpoints\": [                            "
                             "       { \"address\": \"12.34.56.78:8194\" },  "
                             "       { \"address\": \"98.76.54.32:8194\" }   "
                             "   ]                                           "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("clustername", elementAt(msg, k_name).getValueAsString());
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_endpoints, 0, k_address).getValueAsString());
    EXPECT_STREQ("98.76.54.32:8194",
            elementAt(msg, k_endpoints, 1, k_address).getValueAsString());
}

TEST(ExampleEvents, SessionClusterUpdate)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SESSION_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::sessionClusterUpdate());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"name\":           \"clustername\",        "
                             "   \"endpointsAdded\": [                       "
                             "       { \"address\": \"12.34.56.78:8194\" }   "
                             "   ],                                          "
                             "   \"endpointsRemoved\": [                     "
                             "       { \"address\": \"98.76.54.32:8194\" }   "
                             "   ]                                           "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("clustername", elementAt(msg, k_name).getValueAsString());
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_endpointsAdded, 0, k_address).getValueAsString());
    EXPECT_STREQ("98.76.54.32:8194",
            elementAt(msg, k_endpointsRemoved, 0, k_address)
                    .getValueAsString());
}

// ============
// ADMIN EVENTS
// ============

TEST(ExampleEvents, SlowConsumerWarning)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::slowConsumerWarning());
    blptst::TestUtil::appendMessage(expectedEvent, schema);
}

TEST(ExampleEvents, SlowConsumerWarningCleared)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::slowConsumerWarningCleared());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"eventsDropped\": 123                      "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_EQ(123, msg.getElementAsInt32(k_eventsDropped));
}

TEST(ExampleEvents, DataLoss)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::dataLoss());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"id\":                 \"id\",             "
                             "   \"source\":             \"Test\",           "
                             "   \"numMessagesDropped\": 12345               "
                             "}                                              ";

    fmtter.formatMessageJson(msgContent);
    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("id", msg.getElementAsString(k_id));
    EXPECT_STREQ("Test", msg.getElementAsString(k_source));
    EXPECT_EQ(12345, msg.getElementAsInt32(k_numMessagesDropped));
}

TEST(ExampleEvents, RequestTemplateAvailable)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::requestTemplateAvailable());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                "
              "    \"boundTo\":  {                              "
              "        \"dataConnection\": [                    "
              "            {                                    "
              "               \"address\": \"12.34.56.78:8194\" "
              "            }                                    "
              "        ]                                        "
              "    }                                            "
              "}                                                ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_boundTo, k_dataConnection, 0, k_address)
                    .getValueAsString());
}

TEST(ExampleEvents, RequestTemplatePending)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::requestTemplatePending());

    blptst::TestUtil::appendMessage(expectedEvent, schema);
}

TEST(ExampleEvents, RequestTemplateTerminated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::ADMIN);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::requestTemplateTerminated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"reason\": {                                 "
              "        \"source\":      \"TestUtil\",            "
              "        \"errorCode\":   -1,                      "
              "        \"category\":    \"CATEGORY\",            "
              "        \"description\": \"for testing\",         "
              "        \"subcategory\": \"SUBCATEGORY\"          "
              "    }                                             "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

// =====================
// SERVICE STATUS EVENTS
// =====================

TEST(ExampleEvents, ServiceOpened)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceOpened());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\"       "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice", msg.getElementAsString(k_serviceName));
}

TEST(ExampleEvents, ServiceOpenFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceOpenFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                            "
                             "   \"reason\": {                             "
                             "       \"source\":      \"TestUtil\",        "
                             "       \"errorCode\":   -1,                  "
                             "       \"category\":    \"CATEGORY\",        "
                             "       \"description\": \"for testing\",     "
                             "       \"subcategory\": \"SUBCATEGORY\"      "
                             "    }                                        "
                             "}                                            ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

TEST(ExampleEvents, ServiceRegistered)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceRegistered());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\"       "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice", msg.getElementAsString(k_serviceName));
}

TEST(ExampleEvents, ServiceRegisterFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceRegisterFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                            "
                             "   \"reason\": {                             "
                             "       \"source\":      \"TestUtil\",        "
                             "       \"errorCode\":   -1,                  "
                             "       \"category\":    \"CATEGORY\",        "
                             "       \"description\": \"for testing\",     "
                             "       \"subcategory\": \"SUBCATEGORY\"      "
                             "    }                                        "
                             "}                                            ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

TEST(ExampleEvents, ServiceDeregistered)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceDeregistered());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\"       "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice", msg.getElementAsString(k_serviceName));
}

TEST(ExampleEvents, ServiceDown)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceDown());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\",      "
                             "   \"servicePart\":  {                         "
                             "       \"publishing\": { }                     "
                             "   },                                          "
                             "   \"endpoint\": \"12.34.56.78\"               "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice",
            elementAt(msg, k_serviceName).getValueAsString());
    EXPECT_STREQ("12.34.56.78", elementAt(msg, k_endpoint).getValueAsString());
    size_t index = 0;
    EXPECT_STREQ("publishing",
            elementAt(msg, k_servicePart).getElement(index).name().string());
}

TEST(ExampleEvents, ServiceUp)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceUp());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\",      "
                             "   \"servicePart\":  {                         "
                             "       \"publishing\": { }                     "
                             "   },                                          "
                             "   \"endpoint\": \"12.34.56.78\"               "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice",
            elementAt(msg, k_serviceName).getValueAsString());
    EXPECT_STREQ("12.34.56.78", elementAt(msg, k_endpoint).getValueAsString());
    size_t index = 0;
    EXPECT_STREQ("publishing",
            elementAt(msg, k_servicePart).getElement(index).name().string());
}

TEST(ExampleEvents, ServiceAvailabilityInfo)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SERVICE_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::serviceAvailabilityInfo());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                              "
                             "   \"serviceName\":  \"//blp/myservice\",      "
                             "   \"serverAdded\":  {                         "
                             "       \"address\": \"12.34.56.78\"            "
                             "   },                                          "
                             "   \"serverRemoved\":  {                       "
                             "       \"address\": \"12.34.56.78\"            "
                             "   },                                          "
                             "   \"servers\": [                              "
                             "       \"12.34.56.78\",                        "
                             "       \"12.34.56.90\"                         "
                             "   ]                                           "
                             "}                                              ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("//blp/myservice",
            elementAt(msg, k_serviceName).getValueAsString());
    EXPECT_STREQ("12.34.56.78",
            elementAt(msg, k_serverAdded, k_address).getValueAsString());
    EXPECT_STREQ("12.34.56.78",
            elementAt(msg, k_serverRemoved, k_address).getValueAsString());
    EXPECT_STREQ("12.34.56.78", elementAt(msg, k_servers).getValueAsString(0));
    EXPECT_STREQ("12.34.56.90", elementAt(msg, k_servers).getValueAsString(1));
}

// ===================
// TOKEN STATUS EVENTS
// ===================

TEST(ExampleEvents, TokenGenerationSuccess)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOKEN_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::tokenGenerationSuccess());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                          "
                             "   \"token\": \"mytoken\"  "
                             "}                          ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytoken", msg.getElementAsString(k_token));
}

TEST(ExampleEvents, TokenGenerationFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOKEN_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::tokenGenerationFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                            "
                             "   \"reason\": {                             "
                             "       \"source\":      \"TestUtil\",        "
                             "       \"errorCode\":   -1,                  "
                             "       \"category\":    \"CATEGORY\",        "
                             "       \"description\": \"for testing\",     "
                             "       \"subcategory\": \"SUBCATEGORY\"      "
                             "    }                                        "
                             "}                                            ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

// ==========================
// SUBSCRIPTION STATUS EVENTS
// ==========================

TEST(ExampleEvents, SubscriptionStarted)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SUBSCRIPTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::subscriptionStarted());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"exceptions\": [                             "
              "        {                                         "
              "            \"fieldId\": \"field\",               "
              "            \"reason\": {                         "
              "                \"source\":      \"TestUtil\",    "
              "                \"errorCode\":   -1,              "
              "                \"category\":    \"CATEGORY\",    "
              "                \"description\": \"for testing\", "
              "                \"subcategory\": \"SUBCATEGORY\"  "
              "            }                                     "
              "        }                                         "
              "    ],                                            "
              "    \"resubscriptionId\": 123,                    "
              "    \"streamIds\":        [                       "
              "        \"123\",                                  "
              "        \"456\"                                   "
              "    ],                                            "
              "    \"receivedFrom\": {                           "
              "         \"address\": \"12.34.56.78:8194\"        "
              "    },                                            "
              "    \"reason\":      \"TestUtil\"                 "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("field",
            elementAt(msg, k_exceptions, 0, k_fieldId).getValueAsString());

    blp::Element reason = elementAt(msg, k_exceptions, 0);
    EXPECT_TRUE(validateReasonElement(reason));

    EXPECT_EQ(123, msg.getElementAsInt32(k_resubscriptionId));
    EXPECT_STREQ("123", msg.getElement(k_streamIds).getValueAsString(0));
    EXPECT_STREQ("456", msg.getElement(k_streamIds).getValueAsString(1));
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_receivedFrom, k_address).getValueAsString());
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, SubscriptionFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SUBSCRIPTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::subscriptionFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"reason\": {                                 "
              "        \"source\":      \"TestUtil\",            "
              "        \"errorCode\":   -1,                      "
              "        \"category\":    \"CATEGORY\",            "
              "        \"description\": \"for testing\",         "
              "        \"subcategory\": \"SUBCATEGORY\"          "
              "    },                                            "
              "    \"failureDetails\": [                         "
              "        {                                         "
              "            \"fieldId\": \"field\",               "
              "            \"reason\": {                         "
              "                \"source\":      \"TestUtil\",    "
              "                \"errorCode\":   -1,              "
              "                \"category\":    \"CATEGORY\",    "
              "                \"description\": \"for testing\", "
              "                \"subcategory\": \"SUBCATEGORY\"  "
              "            }                                     "
              "        }                                         "
              "    ],                                            "
              "    \"resubscriptionId\": 123                     "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));

    blp::Element reason = elementAt(msg, k_failureDetails, 0);
    EXPECT_TRUE(validateReasonElement(reason));

    EXPECT_EQ(123, msg.getElementAsInt32(k_resubscriptionId));
}

TEST(ExampleEvents, SubscriptionStreamsActivated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SUBSCRIPTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::subscriptionStreamsActivated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"streams\": [                                "
              "        {                                         "
              "            \"id\": \"streamId\",                 "
              "            \"endpoint\": {                       "
              "                \"address\": \"12.34.56.78:8194\" "
              "            }                                     "
              "        }                                         "
              "    ],                                            "
              "    \"reason\":  \"TestUtil\"                     "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ(
            "streamId", elementAt(msg, k_streams, 0, k_id).getValueAsString());
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_streams, 0, k_endpoint, k_address)
                    .getValueAsString());
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, SubscriptionStreamsDeactivated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SUBSCRIPTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::subscriptionStreamsDeactivated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"streams\": [                                "
              "        {                                         "
              "            \"id\": \"streamId\",                 "
              "            \"endpoint\": {                       "
              "                \"address\": \"12.34.56.78:8194\" "
              "            }                                     "
              "        }                                         "
              "    ],                                            "
              "    \"reason\":  \"TestUtil\"                     "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ(
            "streamId", elementAt(msg, k_streams, 0, k_id).getValueAsString());
    EXPECT_STREQ("12.34.56.78:8194",
            elementAt(msg, k_streams, 0, k_endpoint, k_address)
                    .getValueAsString());
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, SubscriptionTerminated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::SUBSCRIPTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::subscriptionTerminated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"reason\": {                                 "
              "        \"source\":      \"TestUtil\",            "
              "        \"errorCode\":   -1,                      "
              "        \"category\":    \"CATEGORY\",            "
              "        \"description\": \"for testing\",         "
              "        \"subcategory\": \"SUBCATEGORY\"          "
              "    }                                             "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

// =====================
// REQUEST STATUS EVENTS
// =====================

TEST(ExampleEvents, RequestFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::REQUEST_STATUS);

    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::requestFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"reason\": {                                 "
              "        \"source\":      \"TestUtil\",            "
              "        \"errorCode\":   -1,                      "
              "        \"category\":    \"CATEGORY\",            "
              "        \"description\": \"for testing\",         "
              "        \"subcategory\": \"SUBCATEGORY\"          "
              "    }                                             "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

// ========================
// RESOLUTION STATUS EVENTS
// ========================

TEST(ExampleEvents, ResolutionSuccess)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::RESOLUTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::resolutionSuccess());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                  "
              "   \"resolvedTopic\":  \"//blp/myservice/rtopic\"  "
              "}                                                  ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ(
            "//blp/myservice/rtopic", msg.getElementAsString(k_resolvedTopic));
}

TEST(ExampleEvents, ResolutionFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::RESOLUTION_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::resolutionFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                "
              "    \"reason\": {                                "
              "        \"source\":      \"TestUtil\",           "
              "        \"errorCode\":   -1,                     "
              "        \"category\":    \"CATEGORY\",           "
              "        \"description\": \"for testing\",        "
              "        \"subcategory\": \"SUBCATEGORY\"         "
              "    }                                            "
              "}                                                ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_TRUE(validateReasonElement(msg));
}

// ============================
// PERMISSION STATUS OPERATIONS
// ============================

TEST(ExampleEvents, PermissionRequest)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::REQUEST);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::permissionRequest());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                                 "
              "    \"topics\":        [ \"topic1\", \"topic2\"], "
              "    \"serviceName\":   \"//blp/mytestservice\",   "
              "    \"uuid\":          1234,                      "
              "    \"seatType\":      1234,                      "
              "    \"applicationId\": 1234,                      "
              "    \"userName\":      \"someName\",              "
              "    \"appName\":       \"myAppName\",             "
              "    \"deviceAddress\": \"myDevice\"               "
              "}                                                 ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("topic1", msg.getElement(k_topics).getValueAsString(0));
    EXPECT_STREQ("topic2", msg.getElement(k_topics).getValueAsString(1));
    EXPECT_EQ(1234, msg.getElementAsInt32(k_uuid));
    EXPECT_EQ(1234, msg.getElementAsInt32(k_seatType));
    EXPECT_EQ(1234, msg.getElementAsInt32(k_applicationId));
    EXPECT_STREQ("someName", msg.getElementAsString(k_userName));
    EXPECT_STREQ("myAppName", msg.getElementAsString(k_appName));
    EXPECT_STREQ("myDevice", msg.getElementAsString(k_deviceAddress));
}

TEST(ExampleEvents, PermissionResponse)
{
    // Unlike the other admin messages, 'PermissionResponse' is not delivered
    // to applications by the SDK. It is used by resolvers to respond to
    // incoming 'PermissionRequest' messages. BLPAPI applications are not
    // expected to handle these messages.
    //
    // For testing if an application is publishing 'PermissionResponse'
    // messages with correct values, it is recommended to mock the related
    // `ProviderSession::publish()` method to capture the published events.
    // See the provided testing examples for more detail.
}

// ===================
// TOPIC STATUS EVENTS
// ===================

TEST(ExampleEvents, TopicCreated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicCreated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                               "
              "    \"topic\":       \"mytopic\"                "
              "}                                               ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
}

TEST(ExampleEvents, TopicCreateFailure)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicCreateFailure());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                         "
                             "    \"topic\":       \"mytopic\",         "
                             "    \"reason\": {                         "
                             "        \"source\":      \"TestUtil\",    "
                             "        \"errorCode\":   -1,              "
                             "        \"category\":    \"CATEGORY\",    "
                             "        \"description\": \"for testing\", "
                             "        \"subcategory\": \"SUBCATEGORY\"  "
                             "    }                                     "
                             "}                                         ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));

    EXPECT_TRUE(validateReasonElement(msg));
}

TEST(ExampleEvents, TopicDeleted)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicDeleted());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":       \"mytopic\",             "
                             "    \"reason\":      \"TestUtil\"             "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);

    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, TopicSubscribed)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicSubscribed());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":            \"mytopic\",        "
                             "    \"topicWithOptions\": \"topicwithopts\"   "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);

    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("topicwithopts", msg.getElementAsString(k_topicWithOptions));
}

TEST(ExampleEvents, TopicResubscribed)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicResubscribed());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":            \"mytopic\",        "
                             "    \"topicWithOptions\": \"topicwithopts\",  "
                             "    \"reason\":           \"TestUtil\"        "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);

    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("topicwithopts", msg.getElementAsString(k_topicWithOptions));
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, TopicUnsubscribed)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicUnsubscribed());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":            \"mytopic\",        "
                             "    \"reason\":           \"TestUtil\"        "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);

    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, TopicActivated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicActivated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent
            = "{                                               "
              "    \"topic\":       \"mytopic\"                "
              "}                                               ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
}

TEST(ExampleEvents, TopicDeactivated)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicDeactivated());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":       \"mytopic\",             "
                             "    \"reason\":      \"TestUtil\"             "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("TestUtil", msg.getElementAsString(k_reason));
}

TEST(ExampleEvents, TopicRecap)
{
    blp::Event expectedEvent
            = blptst::TestUtil::createEvent(blp::Event::TOPIC_STATUS);
    const blp::SchemaElementDefinition schema
            = blptst::TestUtil::getAdminMessageDefinition(
                    blp::Names::topicRecap());

    blptst::MessageFormatter fmtter
            = blptst::TestUtil::appendMessage(expectedEvent, schema);

    const char *msgContent = "{                                             "
                             "    \"topic\":       \"mytopic\",             "
                             "    \"isSolicited\": true,                    "
                             "    \"topicWithOptions\": \"topicwithopts\"   "
                             "}                                             ";
    fmtter.formatMessageJson(msgContent);

    blp::Element msg = firstMessage(expectedEvent);
    EXPECT_STREQ("mytopic", msg.getElementAsString(k_topic));
    EXPECT_STREQ("topicwithopts", msg.getElementAsString(k_topicWithOptions));
    EXPECT_TRUE(msg.getElementAsBool(k_isSolicited));
}

int main(int argc, char **argv)
{
    // The following line must be executed to initialize Google Mock (and
    // Google Test) before running the tests.
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
