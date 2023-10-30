#include "gameplay.h"

#include "entities/spaceship.h"
#include "assets/sfxManager.h"
#include "assets/assetManager.h"
#include "managers/bulletManager.h"
#include "managers/asteroidsManager.h"
#include "managers/pointsManager.h"
#include "managers/screenManager.h"
#include "managers/uiManager.h"
#include "managers/powerupsManager.h"

namespace Asteroids {
	namespace Gameplay {
		struct GameplayEntities {
			Spaceship::Ship spaceship;
			int totalPoints = 0;
			int lives = 3;
			bool isPaused = false;
			bool isDeathPlaying = false;
		};

		static const double DEATH_ANIM_LIFETIME = 2.0;

		Timer::Timer deathTimer;
		static GameplayEntities gameplayEntities;

		static void initManagers() {
			AsteroidsManager::initManager();
			BulletManager::initManager();
			PointsManager::init();
			UiManager::initUI();
			PowerupsManager::initManager();
		}

		void initGameplay() {
			gameplayEntities = {
				Spaceship::createSpaceship(),
				0,
				3
			};
			initManagers();

			SfxManager::playMusic(SfxManager::GAMEPLAY);
		}

		void updateGameplay() {
			UiManager::updateUI(gameplayEntities.isPaused);
			SfxManager::updateMusic(SfxManager::GAMEPLAY);
			if (!gameplayEntities.isPaused && !gameplayEntities.isDeathPlaying) {
				Spaceship::updateSpaceship(gameplayEntities.spaceship);
				BulletManager::updateBullets();
				AsteroidsManager::updateAsteroids(gameplayEntities.spaceship);
				PointsManager::updatePoints(gameplayEntities.spaceship, gameplayEntities.totalPoints);
				PowerupsManager::updatePowerups(gameplayEntities.spaceship);

				if (AsteroidsManager::isPlayerCollidingWithAsteroid(gameplayEntities.spaceship) && !PowerupsManager::isPowerUpActive(PowerUp::SHIELD)) {
					gameplayEntities.lives -= 1;
					SfxManager::stopAllSounds();
					SfxManager::playSound(SfxManager::SHIP_COLLISION, true);

					Timer::startTimer(&deathTimer, DEATH_ANIM_LIFETIME);
					gameplayEntities.isDeathPlaying = true;
				};
			}

			else if (gameplayEntities.isDeathPlaying) {
				if (Timer::timerDone(deathTimer)) {
					
					if (gameplayEntities.lives <= 0) {
						ScreensManager::changeScreenTo(ScreensManager::Screens::MENU);
					}

					gameplayEntities.isDeathPlaying = false;
					initManagers();
					Spaceship::restartSpaceship(gameplayEntities.spaceship);
				}
			}
		}

		void drawGameplay() {
			DrawTextureEx(AssetManager::getTexture(AssetManager::BACKGROUND), { 0, 0 }, 0, 2, WHITE);

			PowerupsManager::drawPowerups();
			BulletManager::drawBullets();
			AsteroidsManager::drawAsteroids();
			Spaceship::drawSpaceship(gameplayEntities.spaceship, gameplayEntities.isDeathPlaying, deathTimer);
			PointsManager::drawPoints();
			UiManager::drawUI(gameplayEntities.totalPoints, gameplayEntities.lives, gameplayEntities.isPaused);
		}
	}
}
