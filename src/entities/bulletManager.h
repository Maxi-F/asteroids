#pragma once

#include "bullet.h"

namespace Asteroids {
	namespace BulletManager {
		void addBullet(Bullets::Bullet bullet);
		void updateBullets();
		void drawBullets();
		void removeDanglingBullets();
	}
}
