#include "bulletManager.h"

#include <vector>
#include <iostream>

namespace Asteroids {
	namespace BulletManager {
		static std::vector<Bullets::Bullet> bullets;

		void addBullet(Bullets::Bullet bullet) {
			std::cout << bullets.size() << std::endl;
			bullets.push_back(bullet);
		}

		void updateBullets() {
			for (size_t i = 0; i < bullets.size(); i++) {
				Bullets::updateBullet(bullets[i]);
			}
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