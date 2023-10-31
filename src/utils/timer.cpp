#include "timer.h"

#include "raylib.h"

namespace Asteroids {
    namespace Timer {
        void startTimer(Timer* timer, double lifetime)
        {
            timer->startTime = GetTime();
            timer->lifeTime = lifetime;
            timer->pauseTime = 0;
            timer->paused = false;
        }

        bool timerDone(Timer timer)
        {
            return !timer.paused && GetTime() - timer.startTime >= timer.lifeTime;
        }

        bool isTimeLeftLessThan(Timer timer, double lifetimeLeft) {
            return !timer.paused && GetTime() - timer.startTime >= timer.lifeTime - lifetimeLeft;
        }

        void pauseTimer(Timer* timer) {
            timer->pauseTime = GetTime();
            timer->paused = true;
        }

        void unPauseTimer(Timer* timer) {
            timer->startTime += GetTime() - timer->pauseTime;
            timer->paused = false;
        }

        double getElapsed(Timer timer)
        {
            return GetTime() - timer.startTime;
        }
    }
}
