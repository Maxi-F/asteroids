#pragma once

#include "entities/bullet.h"

namespace Asteroids {
	namespace BulletManager {
		void initManager();
		void addBullet(Bullets::Bullet bullet);
		void updateBullets();
		void drawBullets();
		void pauseTimers();
		void unpauseTimers();
	}
}
