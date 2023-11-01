#include "youlost.h"

#include <string>

#include "raylib.h"

#include "assets/assetManager.h"
#include "managers/screenManager.h"
#include "managers/gameManager.h"
#include "assets/fontManager.h"
#include "utils/screen.h"
#include "utils/math.h"
#include "uiComponents/button.h"

namespace Asteroids {
	namespace YouLost {
		static const int BUTTON_SPACING = 20;
		static const int BUTTON_WIDTH = 300;
		static const int BUTTON_HEIGHT = 60;
		static const float TITLE_FONT_SIZE = 42.0f;
		static const float TITLE_SPACING = 3.0f;
		static const float POINTS_FONT_SIZE = 36.0f;
		static const float POINTS_SPACING = 3.0f;
		static const float POINTS_MARGIN = 25.0f;
		static const float TOP_SCREEN_MARGIN = 60.0f;
		static const float SCREEN_MARGIN = 120.0f;

		Buttons::Button backToMenuButton;
		Buttons::Button playAgainButton;

		void drawYouLost() {
			Vector2 screenDimensions = { ScreenUtils::getScreenWidth(), ScreenUtils::getScreenHeight() };

			DrawTextureEx(AssetManager::getTexture(AssetManager::BACKGROUND), { 0.0f, 0.0f }, 0, 2, WHITE);

			Texture2D youLostTexture = AssetManager::getTexture(AssetManager::YOU_LOST);

			DrawTextureEx(
				youLostTexture,
				{ MathUtils::getHalf(screenDimensions.x) - MathUtils::getHalf(static_cast<float>(youLostTexture.width)), TOP_SCREEN_MARGIN },
				0,
				1,
				WHITE
			);
			
			Buttons::drawButton(backToMenuButton);
			Buttons::drawCenteredTextInButton(backToMenuButton, "BACK TO MENU");

			Buttons::drawButton(playAgainButton);
			Buttons::drawCenteredTextInButton(playAgainButton, "PLAY AGAIN");

			std::string highScoreString = "High Score: " + std::to_string(GameManager::getHighScore());
			const char* highScoreText = highScoreString.c_str();
			Vector2 highScoreSize = FontManager::measureText(highScoreText, POINTS_FONT_SIZE, POINTS_SPACING);
			FontManager::drawText(
				highScoreText,
				{
					MathUtils::getHalf(screenDimensions.x) - MathUtils::getHalf(highScoreSize.x),
					screenDimensions.y - SCREEN_MARGIN - highScoreSize.y
				},
				POINTS_FONT_SIZE,
				POINTS_SPACING,
				WHITE
			);

			std::string lastPointsString = "Points: " + std::to_string(GameManager::getLastScore());
			const char* lastPointsText = lastPointsString.c_str();
			Vector2 lastPointsSize = FontManager::measureText(lastPointsText, POINTS_FONT_SIZE, POINTS_SPACING);
			FontManager::drawText(
				lastPointsText,
				{
					MathUtils::getHalf(screenDimensions.x) - MathUtils::getHalf(lastPointsSize.x),
					screenDimensions.y - SCREEN_MARGIN - highScoreSize.y - POINTS_MARGIN - lastPointsSize.y
				},
				POINTS_FONT_SIZE,
				POINTS_SPACING,
				WHITE
			);
		};
		
		void initYouLost() {
			Vector2 screenDimensions = { ScreenUtils::getScreenWidth(), ScreenUtils::getScreenHeight() };

			backToMenuButton = Buttons::createButton({
				MathUtils::getHalf(screenDimensions.x) - MathUtils::getHalf(static_cast<float>(BUTTON_WIDTH)),
				MathUtils::getHalf(screenDimensions.y) + MathUtils::getHalf(static_cast<float>(BUTTON_HEIGHT)) + BUTTON_SPACING,
				BUTTON_WIDTH,
				BUTTON_HEIGHT
			});

			playAgainButton = Buttons::createButton({
				MathUtils::getHalf(screenDimensions.x) - MathUtils::getHalf(static_cast<float>(BUTTON_WIDTH)),
				MathUtils::getHalf(screenDimensions.y) - MathUtils::getHalf(static_cast<float>(BUTTON_HEIGHT)) - BUTTON_SPACING,
				BUTTON_WIDTH,
				BUTTON_HEIGHT
			});
		};
		
		void checkYouLostInputsAndCollision() {
			Buttons::updateButton(backToMenuButton);
			Buttons::updateButton(playAgainButton);

			if (backToMenuButton.isClicked) {
				ScreensManager::changeScreenTo(ScreensManager::MENU, false);
			}
			else if (playAgainButton.isClicked) {
				ScreensManager::changeScreenTo(ScreensManager::GAMEPLAY, false);
			}
		};
	}
};
