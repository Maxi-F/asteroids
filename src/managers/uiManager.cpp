#include "uiManager.h"

#include <string>
#include "raylib.h"

namespace Asteroids {
	namespace UiManager {
		static const int FONT_SIZE = 30;
		static const int SCREEN_MARGIN = 40;
		static const int SPACING_MARGIN = 20;

		void drawUI(int totalPoints, int lives) {
			std::string totalPointsString = "Total points: " + std::to_string(totalPoints);
			std::string livesString = "Lives: " + std::to_string(lives);

			DrawText(totalPointsString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN, FONT_SIZE, WHITE);
			DrawText(livesString.c_str(), SCREEN_MARGIN, SCREEN_MARGIN + FONT_SIZE + SPACING_MARGIN, FONT_SIZE, WHITE);
		}
	}
}
