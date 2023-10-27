#include "asteroidsManager.h"

#include "raylib.h"
#include <vector>

#include "entities/asteroid.h"
#include "entities/spaceship.h"
#include "managers/pointsManager.h"
#include "managers/powerupsManager.h"
#include "utils/timer.h"
#include "utils/math.h"

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

		static void createAsteroids() {
			if (Timer::timerDone(asteroidSpawnTimer)) {
				int asteroidsToSpawn = GetRandomValue(minAsteroidSpawns, maxAsteroidSpawns);

				for (int i = 0; i < asteroidsToSpawn; i++) {
					Asteroid::AsteroidType type = static_cast<Asteroid::AsteroidType>(
						GetRandomValue(0, static_cast<int>(Asteroid::AsteroidType::TYPES_QUANTITY))
						);

					asteroids.push_back(Asteroid::createAsteroid(type));
				}

				minAsteroidSpawns = static_cast<int>(
					clamp(
						static_cast<float>(minAsteroidSpawns + 1),
						static_cast<float>(minAsteroidSpawns),
						static_cast<float>(MAX_MINIMUM_ASTEROID_SPAWNS)
					));
				maxAsteroidSpawns = static_cast<int>(
					clamp(
						static_cast<float>(maxAsteroidSpawns + 1),
						static_cast<float>(maxAsteroidSpawns),
						static_cast<float>(MAX_MAXIMUM_ASTEROID_SPAWNS)
					));

				if (minAsteroidSpawns == MAX_MINIMUM_ASTEROID_SPAWNS && maxAsteroidSpawns == MAX_MAXIMUM_ASTEROID_SPAWNS) {
					spawnTimer = clamp(spawnTimer - 0.5f, spawnTimer, MINIMUM_SPAWN_TIMER);
				}

				Timer::startTimer(&asteroidSpawnTimer, spawnTimer);
			}
		};

		static void checkShipCollisions(Spaceship::Ship ship) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { asteroids[i].position, asteroids[i].radius })) {
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
			createAsteroids();
			
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
				if (checkCircleCollision({ bullet.position, bullet.radius }, { asteroids[i].position, asteroids[i].radius })) {
					asteroids[i].shouldDivide = true;
					bullet.shouldRemove = true;
				}
			}
		}
		
		bool isPlayerCollidingWithAsteroid(Spaceship::Ship ship) {
			for (size_t i = 0; i < asteroids.size(); i++) {
				if (checkCircleCollision({ ship.position, ship.shipRadius }, { asteroids[i].position, asteroids[i].radius })) {
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
	}
}
