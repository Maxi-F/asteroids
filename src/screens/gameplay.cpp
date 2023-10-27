#include "gameplay.h"

#include "entities/spaceship.h"
#include "managers/bulletManager.h"
#include "managers/asteroidsManager.h"
#include "managers/pointsManager.h"
#include "managers/screenManager.h"
#include "managers/uiManager.h"

namespace Asteroids {
	namespace Gameplay {
		struct GameplayEntities {
			Spaceship::Ship spaceship;
			int totalPoints = 0;
			int lives = 3;
			bool isPaused = false;
		};

		static GameplayEntities gameplayEntities;

		static void initManagers() {
			AsteroidsManager::initManager();
			BulletManager::initManager();
			PointsManager::init();
			UiManager::initUI();
		}

		void initGameplay() {
			gameplayEntities = {
				Spaceship::createSpaceship(),
				0,
				3
			};
			initManagers();
		}

		void updateGameplay() {
			UiManager::updateUI(gameplayEntities.isPaused);
			Spaceship::updateSpaceship(gameplayEntities.spaceship);
			BulletManager::updateBullets();
			AsteroidsManager::updateAsteroids(gameplayEntities.spaceship);
			PointsManager::updatePoints(gameplayEntities.spaceship, gameplayEntities.totalPoints);

			if (AsteroidsManager::isPlayerCollidingWithAsteroid(gameplayEntities.spaceship)) {
				gameplayEntities.lives -= 1;
				
				if (gameplayEntities.lives <= 0) {
					ScreensManager::changeScreenTo(ScreensManager::Screens::MENU);
				}
				else {
					initManagers();
					Spaceship::restartSpaceship(gameplayEntities.spaceship);
				}
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
