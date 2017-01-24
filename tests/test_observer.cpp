#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "observer.hpp"

using namespace std;
using testing::Ref;
using testing::Invoke;

enum TestEvents {
    DUMMY,
    UNREGISTER
};

using OE = ObserverEvent<TestEvents>;
using OS = ObserverSubject<TestEvents>;

class DummyEvent : public OE
{
public:
    DummyEvent() {
        mType = TestEvents::DUMMY;
    }
};

class UnregisterEvent : public OE
{
public:
    UnregisterEvent(OS& os, OS::Token t): token(t), subject(os) {
        mType = TestEvents::UNREGISTER;
    }
    OS::Token token;
    OS& subject;
};

class MockObserver
{
public:
    MOCK_METHOD1(notify, void(OE&));
};

void unregisterWhileNotify(OE& evt) {
    UnregisterEvent& ue = dynamic_cast<UnregisterEvent&>(evt);
    ue.subject.unregisterObserver(ue.token);
}

TEST(Observer, simple_register) {
    OS os;
    MockObserver mo;
    os.registerObserver(TestEvents::DUMMY, std::bind(&MockObserver::notify, &mo, std::placeholders::_1));
    DummyEvent evt;
    EXPECT_CALL(mo, notify(Ref(evt)));
    os.notify(evt);
}

TEST(Observer, unregister) {
    OS os;
    MockObserver mo;
    auto fn = std::bind(&MockObserver::notify, &mo, std::placeholders::_1);
    auto t = os.registerObserver(TestEvents::DUMMY, fn);
    DummyEvent evt;
    EXPECT_CALL(mo, notify(Ref(evt))).Times(1);
    os.notify(evt);
    os.unregisterObserver(t);
    EXPECT_CALL(mo, notify(Ref(evt))).Times(0);
    os.notify(evt);
}

TEST(Observer, unregister_while_notify)
{
    OS os;
    MockObserver mo;
    auto t = os.registerObserver(TestEvents::UNREGISTER, unregisterWhileNotify);
    UnregisterEvent ue(os, t);
    EXPECT_NO_FATAL_FAILURE(os.notify(ue));
}
