#include "asteroidsManager.h"

#include "raylib.h"
#include <vector>

#include "entities/asteroid.h"
#include "entities/spaceship.h"
#include "managers/pointsManager.h"
#include "utils/timer.h"
#include "utils/math.h"

namespace Asteroids {
	namespace AsteroidsManager {
		static const float SPAWN_TIMER = 5.0f;
		static const int MIN_ASTEROID_SPAWNS = 2;
		static const int MAX_ASTEROID_SPAWNS = 6;

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
					}
					asteroids.erase(asteroids.begin() + i);
				}
			}
		}

		static void createAsteroids() {
			if (Timer::timerDone(asteroidSpawnTimer)) {
				int asteroidsToSpawn = GetRandomValue(MIN_ASTEROID_SPAWNS, MAX_ASTEROID_SPAWNS);

				for (int i = 0; i < asteroidsToSpawn; i++) {
					Asteroid::AsteroidType type = static_cast<Asteroid::AsteroidType>(
						GetRandomValue(0, static_cast<int>(Asteroid::AsteroidType::TYPES_QUANTITY))
						);

					asteroids.push_back(Asteroid::createAsteroid(type));
				}

				Timer::startTimer(&asteroidSpawnTimer, SPAWN_TIMER);
			}
		};

		void initManager() {
			// This will spawn asteroids at the start of the game
			Timer::startTimer(&asteroidSpawnTimer, 0.0f);
			asteroids.clear();
		}

		void updateAsteroids(Spaceship::Ship ship) {
			createAsteroids();
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
