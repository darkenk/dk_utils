#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <algorithm>
#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <utility>
#include "noncopyable.hpp"

template<typename T>
class ObserverSubject;

template<typename E>
class ObserverEvent
{
public:
    virtual ~ObserverEvent() {}
    E getType() {
        return mType;
    }

protected:
    E mType;
};

template<typename Event>
class ObserverSubject : NonCopyable
{
public:
    using Token = unsigned int;
    using ObserverFn = std::function<void(ObserverEvent<Event>&)>;
    virtual ~ObserverSubject() = default;

    void notify(ObserverEvent<Event>& oe) {
        auto& vec = mObservers[oe.getType()];
        auto size = vec.size();
        auto it = std::begin(vec);
        while (it != std::end(vec)) {
            it->fn(oe);
            if (size == vec.size()) {
                it++;
            }
        }
    }

    Token registerObserver(const Event& event, ObserverFn&& observer) {
        static Token t = 0;
        t++;
        mObservers[event].push_back(TokenFunction(t, std::forward<ObserverFn>(observer)));
        return t;
    }

    void unregisterObserver(Token token) {
        for (auto& it : mObservers) {
            auto& vec = it.second;
            vec.erase(std::remove_if(std::begin(vec), std::end(vec),
                                     [token](TokenFunction& tf) { return token == tf.token; }),
                             std::end(vec));
        }
    }

private:
    struct TokenFunction {
        TokenFunction(Token t, ObserverFn f) : token(t), fn(f) {}
        Token token;
        ObserverFn fn;
    };
    std::map<Event, std::vector<TokenFunction>> mObservers;

};

#endif  // OBSERVER_HPP
