#include "uiManager.h"

#include <string>
#include "raylib.h"

#include "uiComponents/button.h"
#include "utils/math.h"
#include "managers/asteroidsManager.h"
#include "managers/bulletManager.h"
#include "managers/powerupsManager.h"

namespace Asteroids {
	namespace UiManager {
		static const int FONT_SIZE = 30;
		static const int SCREEN_MARGIN = 40;
		static const int SPACING_MARGIN = 20;
		static const int PAUSE_BUTTON_WIDTH = 50;
		static const int PAUSE_BUTTON_HEIGHT = 50;
		static const int RESUME_BUTTON_WIDTH = 200;
		static const int RESUME_BUTTON_HEIGHT = 50;

		static Buttons::Button pauseButton;
		static Buttons::Button resumeButton;

		static void drawPause() {
			Buttons::drawButton(resumeButton);
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
					getHalf(static_cast<float>(GetScreenHeight())) - getHalf(static_cast<float>(RESUME_BUTTON_HEIGHT)),
					RESUME_BUTTON_WIDTH,
					RESUME_BUTTON_HEIGHT
				},
				LIGHTGRAY,
				GRAY,
				DARKGRAY
			);
		}

		void drawUI(int totalPoints, int lives, bool isPaused) {
			std::string totalPointsString = "Total points: " + std::to_string(totalPoints);
			std::string livesString = "Lives: " + std::to_string(lives);

			DrawText(totalPointsString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN, FONT_SIZE, WHITE);
			DrawText(livesString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN + FONT_SIZE + SPACING_MARGIN, FONT_SIZE, WHITE);

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

				if (resumeButton.isClicked) {
					isPaused = false;

					AsteroidsManager::unpauseTimers();
					BulletManager::unpauseTimers();
					PowerupsManager::unpauseTimers();
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
