#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <algorithm>
#include <memory>
#include <vector>
#include "noncopyable.hpp"

template<typename T>
class ObserverSubject;

template<typename T>
class Observer : NonCopyable
{
public:
    virtual ~Observer() = default;
    virtual void notify(ObserverSubject<T>& object) = 0;
};

template<typename T>
class ObserverSubject : NonCopyable
{
public:
    using ObserverPtr = std::shared_ptr<Observer<T>>;
    virtual ~ObserverSubject() = default;

    void notify() {
        for (auto o : mObservers) {
            o->notify(*this);
        }
    }

    void registerObserver(ObserverPtr observer) {
        if (mObservers.end() == std::find(mObservers.begin(), mObservers.end(), observer)) {
            mObservers.push_back(observer);
        }
    }

    void unregisterObserver(const ObserverPtr& observer) {
        mObservers.erase(std::remove_if(mObservers.begin(), mObservers.end(),
                                        [observer](ObserverPtr& o) {
                                            return observer.get() == o.get();
                                        }),
                         mObservers.end());
    }

private:
    std::vector<ObserverPtr> mObservers;
};

#endif  // OBSERVER_HPP
