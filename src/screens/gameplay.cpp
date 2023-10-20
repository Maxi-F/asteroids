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

		void initGameplay() {
			gameplayEntities = {
				Spaceship::createSpaceship()
			};

			AsteroidsManager::initManager();
		}

		void updateGameplay() {
			Spaceship::updateSpaceship(gameplayEntities.spaceship);
			BulletManager::updateBullets();
			AsteroidsManager::updateAsteroids();
		}

		void drawGameplay() {
			Spaceship::drawSpaceship(gameplayEntities.spaceship);
			BulletManager::drawBullets();
			AsteroidsManager::drawAsteroids();
		}
	}
}
