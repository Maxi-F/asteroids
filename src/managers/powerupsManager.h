#pragma once

#include "entities/spaceship.h"
#include "entities/powerUp.h"
#include "entities/asteroid.h"

namespace Asteroids {
	namespace PowerupsManager {
		void initManager();
		void addPowerUp(Asteroid::Asteroid asteroid);
		void updatePowerups(Spaceship::Ship &ship);
		void drawPowerups();
		bool isPowerUpActive(PowerUp::PowerUpType powerUpType);
	}
}
