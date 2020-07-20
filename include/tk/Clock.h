#pragma once

#include <chrono>

namespace tk {

    using Duration = std::chrono::duration<double>;

    using namespace std::chrono_literals;

    class Clock {
    public:
        Duration getElapsedTime() const { return SystemClock::now() - time_; }

        void reset() { time_ = SystemClock::now(); }

    private:
        using SystemClock = std::chrono::system_clock;

        std::chrono::time_point<SystemClock> time_{SystemClock::now()};
    };


}