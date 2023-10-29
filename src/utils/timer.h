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
		double getElapsed(Timer timer);
		void pauseTimer(Timer* timer);
		void unPauseTimer(Timer* timer);
		bool isTimeLeftLessThan(Timer timer, double lifetimeLeft);
	}
}
