#include "powerupsManager.h"

#include <vector>

#include "utils/math.h"
#include "assets/sfxManager.h"

namespace Asteroids {
	namespace PowerupsManager {
		struct ActivePowerUp {
			PowerUp::PowerUpType powerUpType;
			Timer::Timer lifetimeTimer;
			bool isActive = false;
		};

		static const int POWER_UPS_COUNT = 3;
		static const double POWER_UP_DISAPPEARING_IN_SECONDS = 2.0;
		static std::vector<PowerUp::PowerUp> powerUpsInMap;
		static ActivePowerUp activePowerUps[POWER_UPS_COUNT];

		static SfxManager::SfxName getActivationSound(PowerUp::PowerUpType type) {
			switch (type) {
				case PowerUp::MULTI_BULLET:
					return SfxManager::BULLETS_POWER_UP_ACTIVATION;
				case PowerUp::MORE_POINTS:
					return SfxManager::POINTS_POWER_UP_ACTIVATION;
				case PowerUp::SHIELD:
					return SfxManager::SHIELD_POWER_UP_ACTIVATION;
				default:
					return SfxManager::BULLETS_POWER_UP_ACTIVATION;
			}
		}

		static SfxManager::SfxName getDeactivationSound(PowerUp::PowerUpType type) {
			switch (type) {
			case PowerUp::MULTI_BULLET:
				return SfxManager::BULLETS_POWER_UP_DEACTIVATION;
			case PowerUp::MORE_POINTS:
				return SfxManager::POINTS_POWER_UP_DEACTIVATION;
			case PowerUp::SHIELD:
				return SfxManager::SHIELD_POWER_UP_DEACTIVATION;
			default:
				return SfxManager::BULLETS_POWER_UP_DEACTIVATION;
			}
		}

		static bool shouldAddPowerUp() {
			const float POWER_UP_SPAWN_PROBABILITY = 0.1f;

			return GetRandomValue(1, static_cast<int>(1 / POWER_UP_SPAWN_PROBABILITY)) == 1;
		}

		static void activatePowerup(PowerUp::PowerUp powerUp) {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				if (activePowerUps[i].powerUpType == powerUp.powerUpType) {
					SfxManager::playSound(getActivationSound(powerUp.powerUpType), true);
					Timer::startTimer(&activePowerUps[i].lifetimeTimer, powerUp.lifetime);
					activePowerUps[i].isActive = true;
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
			if (shouldAddPowerUp()) {
				powerUpsInMap.push_back(PowerUp::createPowerUp(asteroid.position));
			}
		}

		void updatePowerups(Spaceship::Ship& ship) {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				if (activePowerUps[i].isActive && Timer::timerDone(activePowerUps[i].lifetimeTimer)) {
					SfxManager::playSound(getDeactivationSound(activePowerUps[i].powerUpType), true);
					activePowerUps[i].isActive = false;
				}
			}

			for (size_t i = 0; i < powerUpsInMap.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { powerUpsInMap[i].position, powerUpsInMap[i].radius })) {
					activatePowerup(powerUpsInMap[i]);
					powerUpsInMap.erase(powerUpsInMap.begin() + i);
				} else if (Timer::timerDone(powerUpsInMap[i].lifetimeInMapTimer)) {
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
					return !activePowerUps[i].lifetimeTimer.paused && !Timer::timerDone(activePowerUps[i].lifetimeTimer);
				}
			}
			return false;
		};

		bool isPowerUpDisappearing(PowerUp::PowerUpType powerUpType) {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				if (activePowerUps[i].powerUpType == powerUpType) {
					return Timer::isTimeLeftLessThan(activePowerUps[i].lifetimeTimer, POWER_UP_DISAPPEARING_IN_SECONDS);
				}
			}
			return false;
		};

		void pauseTimers() {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				Timer::pauseTimer(&activePowerUps[i].lifetimeTimer);
			}

			for (size_t i = 0; i < powerUpsInMap.size(); i++) {
				PowerUp::pauseTimer(powerUpsInMap[i]);
			}
		};

		void unpauseTimers() {
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				Timer::unPauseTimer(&activePowerUps[i].lifetimeTimer);
			}

			for (size_t i = 0; i < powerUpsInMap.size(); i++) {
				PowerUp::unpauseTimer(powerUpsInMap[i]);
			}
		};
	}
}
