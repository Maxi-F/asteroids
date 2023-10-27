#include "powerupsManager.h"

#include <vector>

#include "utils/math.h"

namespace Asteroids {
	namespace PowerupsManager {
		struct ActivePowerUp {
			PowerUp::PowerUpType powerUpType;
			Timer::Timer lifetimeTimer;
		};

		static const int POWER_UPS_COUNT = 3;
		static std::vector<PowerUp::PowerUp> powerUpsInMap;
		static ActivePowerUp activePowerUps[POWER_UPS_COUNT];

		static void activatePowerup(PowerUp::PowerUp powerUp) {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				if (activePowerUps[i].powerUpType == powerUp.powerUpType) {
					Timer::startTimer(&activePowerUps[i].lifetimeTimer, powerUp.lifetime);
				}
			}
		}

		void initManager() {
			powerUpsInMap.clear();
			
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				activePowerUps[i].powerUpType = static_cast<PowerUp::PowerUpType>(i);
				Timer::startTimer(&activePowerUps[i].lifetimeTimer, 0.0);
			}
		};

		void addPowerUp(Asteroid::Asteroid asteroid) {
			powerUpsInMap.push_back(PowerUp::createPowerUp(asteroid.position));
		}

		void updatePowerups(Spaceship::Ship& ship) {
			for (size_t i = 0; i < powerUpsInMap.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { powerUpsInMap[i].position, powerUpsInMap[i].radius })) {
					activatePowerup(powerUpsInMap[i]);
					powerUpsInMap.erase(powerUpsInMap.begin() + i);
				}
			}
		};

		void drawPowerups() {
			for (size_t i = 0; i < powerUpsInMap.size(); i++) {
				PowerUp::drawPowerUp(powerUpsInMap[i]);
			}
		};
		
		bool isPowerUpActive(PowerUp::PowerUpType powerUpType) {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				if (activePowerUps[i].powerUpType == powerUpType) {
					return !Timer::timerDone(activePowerUps[i].lifetimeTimer);
				}
			}
			return false;
		};
	}
}
