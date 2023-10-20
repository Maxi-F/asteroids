#pragma once

#include "entities/bullet.h"

namespace Asteroids {
	namespace AsteroidsManager {
		void initManager();
		void updateAsteroids();
		void checkCollissionsWith(Bullets::Bullet &bullet);
		void drawAsteroids();
	}
}
