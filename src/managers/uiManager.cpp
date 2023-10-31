#include "uiManager.h"

#include <string>
#include "raylib.h"

#include "uiComponents/button.h"
#include "utils/math.h"
#include "assets/assetManager.h"
#include "assets/fontManager.h"
#include "managers/asteroidsManager.h"
#include "managers/bulletManager.h"
#include "managers/powerupsManager.h"
#include "managers/screenManager.h"

namespace Asteroids {
	namespace UiManager {
		static const int FONT_SIZE = 30;
		static const int SCREEN_MARGIN = 40;
		static const int SPACING_MARGIN = 20;
		static const int PAUSE_BUTTON_WIDTH = 50;
		static const int PAUSE_BUTTON_HEIGHT = 50;
		static const int RESUME_BUTTON_WIDTH = 200;
		static const int RESUME_BUTTON_HEIGHT = 50;
		static const int MENU_BUTTONS_MARGIN = 25;
		static const float SCORE_SPACING = 3.0f;

		static Buttons::Button pauseButton;
		static Buttons::Button resumeButton;
		static Buttons::Button backToMenuButton;

		static void drawPause() {
			Buttons::drawButton(resumeButton);
			Buttons::drawButton(backToMenuButton);
		}

		static void drawPoints(int totalPoints) {
			std::string totalPointsString = "Points: " + std::to_string(totalPoints);

		    FontManager::drawText(
				totalPointsString.c_str(),
				{ static_cast<float>(SCREEN_MARGIN), static_cast<float>(GetScreenHeight() - SCREEN_MARGIN - FONT_SIZE) },
				FONT_SIZE,
				SCORE_SPACING,
				WHITE
			);
		}

		static void drawPowerUps() {
			const int POWER_UPS_COUNT = 3;
			const float SCALE = 0.2f;
			const float SPACING = 20.0f;

			Texture2D emptyPowerTexture = AssetManager::getTexture(AssetManager::EMPTY_POWER_UP);

			PowerUp::PowerUpType powerUps[POWER_UPS_COUNT] = {
				PowerUp::MORE_POINTS,
				PowerUp::MULTI_BULLET,
				PowerUp::SHIELD
			};
			
			for (int i = 0; i < POWER_UPS_COUNT; i++) {
				Vector2 position = { 
					getHalf(static_cast<float>(GetScreenWidth())) - getHalf(emptyPowerTexture.width * SCALE) + (emptyPowerTexture.width * SCALE + SPACING) * (i - 1),
					SCREEN_MARGIN
				};
				
				if (PowerupsManager::isPowerUpActive(powerUps[i])) {
					DrawTextureEx(
						PowerUp::getTexturePerType(powerUps[i]),
						position,
						0,
						SCALE,
						WHITE
					);
				}
				else {
					DrawTextureEx(
						emptyPowerTexture,
						position,
						0,
						SCALE,
						WHITE
					);
				}
			}

			
		};

		static void drawLives(int lives) {
			static const float SCALE = 0.2f;
			Texture2D liveTexture = AssetManager::getTexture(AssetManager::LIFE);

			for (int i = 0; i < lives; i++) {
				DrawTextureEx(
					liveTexture,
					{ static_cast<float>(SCREEN_MARGIN + (liveTexture.width * SCALE + SPACING_MARGIN) * i), static_cast<float>(SCREEN_MARGIN) },
					0,
					SCALE,
					WHITE
				);
			}
		}

		void initUI() {
			pauseButton = Buttons::createButtonWithColors(
				{
					static_cast<float>(GetScreenWidth() - SCREEN_MARGIN - PAUSE_BUTTON_WIDTH),
					SCREEN_MARGIN,
					PAUSE_BUTTON_WIDTH,
					PAUSE_BUTTON_HEIGHT
				},
				LIGHTGRAY,
				GRAY,
				DARKGRAY
			);

			resumeButton = Buttons::createButtonWithColors(
				{
					getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(RESUME_BUTTON_WIDTH)),
					getHalf(static_cast<float>(GetScreenHeight())) - RESUME_BUTTON_HEIGHT - MENU_BUTTONS_MARGIN,
					RESUME_BUTTON_WIDTH,
					RESUME_BUTTON_HEIGHT
				},
				LIGHTGRAY,
				GRAY,
				DARKGRAY
			);

			backToMenuButton = Buttons::createButtonWithColors(
				{
					getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(RESUME_BUTTON_WIDTH)),
					getHalf(static_cast<float>(GetScreenHeight())) + MENU_BUTTONS_MARGIN,
					RESUME_BUTTON_WIDTH,
					RESUME_BUTTON_HEIGHT
				},
				LIGHTGRAY,
				GRAY,
				DARKGRAY
			);
		}

		void drawUI(int totalPoints, int lives, bool isPaused) {
			drawPoints(totalPoints);
			drawLives(lives);
			drawPowerUps();

			Buttons::drawButton(pauseButton);

			if (isPaused) {
				drawPause();
			}
		}

		void updateUI(bool &isPaused) {
			if (isPaused) {
				pauseButton.isClicked = false;
				pauseButton.isHovered = false;

				Buttons::updateButton(resumeButton);
				Buttons::updateButton(backToMenuButton);

				if (resumeButton.isClicked) {
					isPaused = false;

					AsteroidsManager::unpauseTimers();
					BulletManager::unpauseTimers();
					PowerupsManager::unpauseTimers();
				}
				else if (backToMenuButton.isClicked) {
					ScreensManager::changeScreenTo(ScreensManager::MENU, true);
				}
			} 
			else {
				Buttons::updateButton(pauseButton);

				if (pauseButton.isClicked) {
					isPaused = true;
					
					AsteroidsManager::pauseTimers();
					BulletManager::pauseTimers();
					PowerupsManager::pauseTimers();
				}
			}
		}
	}
}
