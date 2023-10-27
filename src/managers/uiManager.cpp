#include "uiManager.h"

#include <string>
#include "raylib.h"

#include "uiComponents/button.h"

namespace Asteroids {
	namespace UiManager {
		static const int FONT_SIZE = 30;
		static const int SCREEN_MARGIN = 40;
		static const int SPACING_MARGIN = 20;
		static const int PAUSE_BUTTON_WIDTH = 50;
		static const int PAUSE_BUTTON_HEIGHT = 50;

		static Buttons::Button pauseButton;

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
		}

		void drawUI(int totalPoints, int lives) {
			std::string totalPointsString = "Total points: " + std::to_string(totalPoints);
			std::string livesString = "Lives: " + std::to_string(lives);

			DrawText(totalPointsString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN, FONT_SIZE, WHITE);
			DrawText(livesString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN + FONT_SIZE + SPACING_MARGIN, FONT_SIZE, WHITE);

			Buttons::drawButton(pauseButton);
		}

		void updateUI(bool &isPaused) {
			Buttons::updateButton(pauseButton);

			if (pauseButton.isClicked) {
				isPaused = true;
			}
		}
	}
}
