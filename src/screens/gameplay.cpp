#include "gameplay.h"

#include "entities/spaceship.h"
#include "managers/bulletManager.h"
#include "managers/asteroidsManager.h"
#include "managers/pointsManager.h"
#include "managers/uiManager.h"

namespace Asteroids {
	namespace Gameplay {
		struct GameplayEntities {
			Spaceship::Ship spaceship;
			int totalPoints = 0;
			int lives = 3;
		};

		static GameplayEntities gameplayEntities;

		static void initManagers() {
			AsteroidsManager::initManager();
			BulletManager::initManager();
			PointsManager::init();
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
			AsteroidsManager::updateAsteroids(gameplayEntities.spaceship);
			PointsManager::updatePoints(gameplayEntities.spaceship);

			if (AsteroidsManager::isPlayerCollidingWithAsteroid(gameplayEntities.spaceship)) {
				initManagers();
				Spaceship::restartSpaceship(gameplayEntities.spaceship);
			};
		}

		void drawGameplay() {
			Spaceship::drawSpaceship(gameplayEntities.spaceship);
			BulletManager::drawBullets();
			AsteroidsManager::drawAsteroids();
			PointsManager::drawPoints();
			UiManager::drawUI(gameplayEntities.totalPoints, gameplayEntities.lives);
		}
	}
}
