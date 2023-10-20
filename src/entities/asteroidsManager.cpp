#include "asteroidsManager.h"

#include "raylib.h"
#include <vector>

#include "entities/asteroid.h"
#include "utils/timer.h"

namespace Asteroids {
	namespace AsteroidsManager {
		static const float SPAWN_TIMER = 5.0f;
		static const int MIN_ASTEROID_SPAWNS = 2;
		static const int MAX_ASTEROID_SPAWNS = 6;

		static Timer::Timer asteroidSpawnTimer;
		static std::vector<Asteroid::Asteroid> asteroids;

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
		}

		void updateAsteroids() {
			createAsteroids();
			for (size_t i = 0; i < asteroids.size(); i++) {
				Asteroid::updateAsteroid(asteroids[i]);
			}
		};
		
		void drawAsteroids() {
			for (size_t i = 0; i < asteroids.size(); i++) {
				Asteroid::drawAsteroid(asteroids[i]);
			}
		};
	}
}