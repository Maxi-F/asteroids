#include "bulletManager.h"

#include <vector>
#include <iostream>

#include "utils/timer.h"

namespace Asteroids {
	namespace BulletManager {
		static std::vector<Bullets::Bullet> bullets;
		static Timer::Timer bulletTimer;
		static const double TIME_BETWEEN_BULLETS = 0.3;

		void initBulletManager() {
			Timer::startTimer(&bulletTimer, TIME_BETWEEN_BULLETS);
		}

		void addBullet(Bullets::Bullet bullet) {
			if (Timer::timerDone(bulletTimer)) {
				bullets.push_back(bullet);
				Timer::startTimer(&bulletTimer, TIME_BETWEEN_BULLETS);
			}
		}

		void updateBullets() {
			for (size_t i = 0; i < bullets.size(); i++) {
				Bullets::updateBullet(bullets[i]);
			}
			removeDanglingBullets();
		}

		void drawBullets() {
			for (size_t i = 0; i < bullets.size(); i++) {
				Bullets::drawBullet(bullets[i]);
			}
		}

		void removeDanglingBullets() {
			for (size_t i = 0; i < bullets.size(); i++) {
				if (bullets[i].shouldRemove) {
					bullets.erase(bullets.begin() + i);
				}
			}
		}
	}
}