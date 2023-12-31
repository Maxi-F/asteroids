#include "asteroidsManager.h"

#include <vector>

#include "raylib.h"

#include "assets/sfxManager.h"
#include "entities/asteroid.h"
#include "managers/pointsManager.h"
#include "managers/powerupsManager.h"

namespace Asteroids {
	namespace AsteroidsManager {
		static const int MAX_MINIMUM_ASTEROID_SPAWNS = 8;
		static const int MAX_MAXIMUM_ASTEROID_SPAWNS = 10;
		static const float MINIMUM_SPAWN_TIMER = 2.0f;
		static const int START_MINIMUM_ASTEROID_SPAWNS = 2;
		static const int START_MAXIMUM_ASTEROID_SPAWNS = 4;
		static const float START_SPAWN_TIMER = 5.0f;

		static float spawnTimer = START_SPAWN_TIMER;
		static int minAsteroidSpawns = START_MINIMUM_ASTEROID_SPAWNS;
		static int maxAsteroidSpawns = START_MAXIMUM_ASTEROID_SPAWNS;

		static Timer::Timer asteroidSpawnTimer;
		static std::vector<Asteroid::Asteroid> asteroids;

		static void divideOrRemoveAsteroids(Spaceship::Ship ship) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (asteroids[i].shouldDivide) {
					if (!Asteroid::isIndivisible(asteroids[i])) {
						asteroids.push_back(Asteroid::createDividedAsteroidFrom(asteroids[i], true));
						asteroids.push_back(Asteroid::createDividedAsteroidFrom(asteroids[i], false));
					}
					else {
						PointsManager::addPoint(asteroids[i], ship);
						PowerupsManager::addPowerUp(asteroids[i]);
					}
					asteroids.erase(asteroids.begin() + i);
				}
			}
		}

		static SfxManager::SfxName getRandomCollisionSound() {
			const int COLLISION_SOUNDS_COUNT = 2;
			int collisionSound = GetRandomValue(1, COLLISION_SOUNDS_COUNT);

			switch (collisionSound) {
				case 1:
					return SfxManager::BULLET_COLLISION_1;
				case 2:
					return SfxManager::BULLET_COLLISION_2;
				default:
					return SfxManager::BULLET_COLLISION_1;
			}
		}

		static void createAsteroids(Spaceship::Ship ship) {
			if (Timer::timerDone(asteroidSpawnTimer)) {
				int asteroidsToSpawn = GetRandomValue(minAsteroidSpawns, maxAsteroidSpawns);

				for (int i = 0; i < asteroidsToSpawn; i++) {
					Asteroid::AsteroidType type = static_cast<Asteroid::AsteroidType>(
						GetRandomValue(1, static_cast<int>(Asteroid::AsteroidType::TYPES_QUANTITY)) - 1
						);

					asteroids.push_back(Asteroid::createAsteroid(type, { ship.position, ship.shipRadius * 3 }));
				}

				minAsteroidSpawns = static_cast<int>(
					MathUtils::clamp(
						static_cast<float>(minAsteroidSpawns + 1),
						static_cast<float>(minAsteroidSpawns),
						static_cast<float>(MAX_MINIMUM_ASTEROID_SPAWNS)
					));
				maxAsteroidSpawns = static_cast<int>(
					MathUtils::clamp(
						static_cast<float>(maxAsteroidSpawns + 1),
						static_cast<float>(maxAsteroidSpawns),
						static_cast<float>(MAX_MAXIMUM_ASTEROID_SPAWNS)
					));

				if (minAsteroidSpawns == MAX_MINIMUM_ASTEROID_SPAWNS && maxAsteroidSpawns == MAX_MAXIMUM_ASTEROID_SPAWNS) {
					spawnTimer = MathUtils::clamp(spawnTimer - 0.5f, spawnTimer, MINIMUM_SPAWN_TIMER);
				}

				Timer::startTimer(&asteroidSpawnTimer, spawnTimer);
			}
		};

		static void checkShipCollisions(Spaceship::Ship ship) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (MathUtils::checkCircleCollision({ ship.position, ship.shipRadius }, { asteroids[i].position, asteroids[i].radius })) {
					SfxManager::playSound(SfxManager::SHIELD_ASTEROID_COLLISION, true);
					asteroids[i].shouldDivide = true;
				}
			}
		}

		void initManager() {
			// This will spawn asteroids at the start of the game
			Timer::startTimer(&asteroidSpawnTimer, 0.0f);
			asteroids.clear();

			minAsteroidSpawns = START_MINIMUM_ASTEROID_SPAWNS;
			maxAsteroidSpawns = START_MAXIMUM_ASTEROID_SPAWNS;
			spawnTimer = START_SPAWN_TIMER;
		}

		void updateAsteroids(Spaceship::Ship ship) {
			createAsteroids(ship);
			
			if (PowerupsManager::isPowerUpActive(PowerUp::SHIELD)) {
				checkShipCollisions(ship);
			}

			for (size_t i = 0; i < asteroids.size(); i++) {
				Asteroid::updateAsteroid(asteroids[i]);
			}

			divideOrRemoveAsteroids(ship);
		};

		void checkCollissionsWith(Bullets::Bullet& bullet) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (MathUtils::checkCircleCollision({ bullet.position, bullet.radius }, { asteroids[i].position, asteroids[i].radius })) {
					SfxManager::playSound(getRandomCollisionSound(), true);
					asteroids[i].shouldDivide = true;
					bullet.shouldRemove = true;
				}
			}
		}
		
		bool isPlayerCollidingWithAsteroid(Spaceship::Ship ship) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (MathUtils::checkCircleCollision({ ship.position, ship.shipRadius }, { asteroids[i].position, asteroids[i].radius })) {
					return true;
				}
			}
			return false;
		}

		void drawAsteroids() {
			for (size_t i = 0; i < asteroids.size(); i++) {
				Asteroid::drawAsteroid(asteroids[i]);
			}
		};

		void pauseTimers() {
			Timer::pauseTimer(&asteroidSpawnTimer);
		}

		void unpauseTimers() {
			Timer::unPauseTimer(&asteroidSpawnTimer);
		}
	}
}
