#include "screenManager.h"

#include "screens/menu.h"
#include "screens/gameplay.h"
#include "assets/sfxManager.h"

namespace Asteroids {
	namespace ScreensManager {
		static Screens actualScreen;

		void initManager() {
			actualScreen = Screens::MENU;

			SfxManager::playMusic(SfxManager::MENU);
			initMenu();
		}

		void changeScreenTo(Screens screen) {
			actualScreen = screen;
			SfxManager::stopAllMusic();

			switch (actualScreen) {
				case Screens::MENU:
					initMenu();
					SfxManager::playMusic(SfxManager::MENU);
					break;
				case Screens::GAMEPLAY:
					Gameplay::initGameplay();
					SfxManager::playMusic(SfxManager::GAMEPLAY);
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
					SfxManager::updateMusic(SfxManager::MENU);
					break;
				case Screens::CREDITS:
					break;
				case Screens::RULES:
					break;
				case Screens::GAMEPLAY:
					Gameplay::updateGameplay();
					SfxManager::updateMusic(SfxManager::GAMEPLAY);
					break;
			};

			shouldClose = shouldClose || WindowShouldClose();
		};
	}
}