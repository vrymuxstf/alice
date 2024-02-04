#pragma once

namespace alice {
    template<class T>
    static T &Singleton() {
        static T instance;
        return instance;
    }
}