#pragma once

namespace Asteroids {
	namespace Timer {
		struct Timer {
			double startTime;
			double lifeTime;
			double pauseTime;
			bool paused;
		};

		void startTimer(Timer* timer, double lifeTime);
		bool timerDone(Timer timer);
		void pauseTimer(Timer* timer);
		void unPauseTimer(Timer* timer);
		double getElapsed(Timer timer);
		bool isTimeLeftLessThan(Timer timer, double lifetimeLeft);
		bool isMillisecondLessThan(Timer timer, double ms);
	}
}
