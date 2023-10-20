#include "gameplay.h"

#include "entities/spaceship.h"
#include "entities/bulletManager.h"
#include "entities/asteroidsManager.h"

namespace Asteroids {
	namespace Gameplay {
		struct GameplayEntities {
			Spaceship::Ship spaceship;
		};

		static GameplayEntities gameplayEntities;

		static void initManagers() {
			AsteroidsManager::initManager();
			BulletManager::initManager();
		}

		void initGameplay() {
			gameplayEntities = {
				Spaceship::createSpaceship()
			};
			initManagers();
		}

		void updateGameplay() {
			Spaceship::updateSpaceship(gameplayEntities.spaceship);
			BulletManager::updateBullets();
			AsteroidsManager::updateAsteroids();

			if (AsteroidsManager::isPlayerCollidingWithAsteroid(gameplayEntities.spaceship)) {
				initManagers();
				Spaceship::restartSpaceship(gameplayEntities.spaceship);
			};
		}

		void drawGameplay() {
			Spaceship::drawSpaceship(gameplayEntities.spaceship);
			BulletManager::drawBullets();
			AsteroidsManager::drawAsteroids();
		}
	}
}
