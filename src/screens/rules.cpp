#include "rules.h"

#include "raylib.h"

#include "assets/assetManager.h"
#include "managers/screenManager.h"
#include "uiComponents/button.h"

namespace Asteroids {
	namespace Rules {
		static const float SCREEN_MARGIN = 50.0f;
		static const int BUTTON_WIDTH = 100;
		static const int BUTTON_HEIGHT = 50;

		static Buttons::Button goBackButton;

		void drawRules() {
			DrawTextureEx(AssetManager::getTexture(AssetManager::RULES), { 0.0f, 0.0f }, 0, 1, WHITE);
			Buttons::drawButton(goBackButton);
		};

		void initRules() {
			goBackButton = Buttons::createButton(
				{
					SCREEN_MARGIN,
					static_cast<float>(GetScreenHeight() - BUTTON_HEIGHT - SCREEN_MARGIN),
					BUTTON_WIDTH,
					BUTTON_HEIGHT
				}
			);
		};
		void checkRulesInputAndCollision() {
			Buttons::updateButton(goBackButton);

			if (goBackButton.isClicked) {
				ScreensManager::changeScreenTo(ScreensManager::MENU, false);
			}
		};
	}
}