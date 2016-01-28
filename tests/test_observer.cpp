#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "dk_utils/observer.hpp"

using namespace std;
using testing::Ref;

class Mock {};

class MockObserver : public Observer<Mock>
{
public:
    MOCK_METHOD1(notify, void(ObserverSubject<Mock>& object));
};

TEST(Observer, simple_register) {
    auto observer = make_shared<MockObserver>();
    ObserverSubject<Mock> os;
    os.registerObserver(observer);
    EXPECT_CALL(*observer, notify(Ref(os)));
    os.notify();
}

TEST(Observer, prohibit_double_register) {
    auto observer = make_shared<MockObserver>();
    ObserverSubject<Mock> os;
    os.registerObserver(observer);
    os.registerObserver(observer);
    EXPECT_CALL(*observer, notify(Ref(os))).Times(1);
    os.notify();
}

TEST(Observer, unregister) {
    auto observer = make_shared<MockObserver>();
    ObserverSubject<Mock> os;
    os.registerObserver(observer);
    EXPECT_CALL(*observer, notify(Ref(os))).Times(1);
    os.notify();
    os.unregisterObserver(observer);
    EXPECT_CALL(*observer, notify(Ref(os))).Times(0);
    os.notify();
}
