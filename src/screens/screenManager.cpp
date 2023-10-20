#include "screenManager.h"

#include "screens/menu.h"
#include "screens/gameplay.h"

namespace Asteroids {
	namespace ScreensManager {
		static Screens actualScreen;

		void initManager() {
			actualScreen = Screens::MENU;

			initMenu();
		}

		void changeScreenTo(Screens screen) {
			actualScreen = screen;

			switch (actualScreen) {
				case Screens::MENU:
					initMenu();
					break;
				case Screens::GAMEPLAY:
					Gameplay::initGameplay();
					break;
				case Screens::CREDITS:
					break;
				case Screens::RULES:
					break;
			}
		}

		void drawScreen() {
			switch (actualScreen) {
				case Screens::MENU:
					drawMenu();
					break;
				case Screens::CREDITS:
					break;
				case Screens::RULES:
					break;
				case Screens::GAMEPLAY:
					Gameplay::drawGameplay();
					break;
			};
		}

		void updateScreen(bool& shouldClose) {
			switch (actualScreen) {
				case Screens::MENU:
					checkMenuInputAndCollision(shouldClose);
					break;
				case Screens::CREDITS:
					break;
				case Screens::RULES:
					break;
				case Screens::GAMEPLAY:
					Gameplay::updateGameplay();
					break;
			};

			shouldClose = shouldClose || WindowShouldClose();
		};
	}
}