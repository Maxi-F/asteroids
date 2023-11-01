#pragma once
#include "entities/bullet.h"
#include "entities/spaceship.h"

namespace Asteroids {
	namespace AsteroidsManager {
		void initManager();
		void updateAsteroids(Spaceship::Ship ship);
		void checkCollissionsWith(Bullets::Bullet &bullet);
		bool isPlayerCollidingWithAsteroid(Spaceship::Ship ship);
		void drawAsteroids();
		void pauseTimers();
		void unpauseTimers();
	}
}
