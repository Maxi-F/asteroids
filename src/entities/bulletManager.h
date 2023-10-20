#pragma once

#include "bullet.h"

namespace Asteroids {
	namespace BulletManager {
		void initManager();
		void addBullet(Bullets::Bullet bullet);
		void updateBullets();
		void drawBullets();
	}
}
