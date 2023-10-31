#include "screenManager.h"

#include "screens/menu.h"
#include "screens/gameplay.h"
#include "screens/rules.h"
#include "assets/sfxManager.h"

namespace Asteroids {
	namespace ScreensManager {
		static Screens actualScreen;

		void initManager() {
			actualScreen = Screens::MENU;

			SfxManager::playMusic(SfxManager::MENU);
			initMenu();
		}

		void changeScreenTo(Screens screen, bool shouldStopMusic) {
			actualScreen = screen;
			if (shouldStopMusic) {
				SfxManager::stopAllMusic();
			}

			switch (actualScreen) {
				case Screens::MENU:
					initMenu();
					if (shouldStopMusic) {
						SfxManager::playMusic(SfxManager::MENU);
					}
					break;
				case Screens::GAMEPLAY:
					Gameplay::initGameplay();
					SfxManager::playMusic(SfxManager::GAMEPLAY);
					break;
				case Screens::CREDITS:
					break;
				case Screens::RULES:
					Rules::initRules();
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
					Rules::drawRules();
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
					SfxManager::updateMusic(SfxManager::MENU);
					break;
				case Screens::RULES:
					Rules::checkRulesInputAndCollision();
					SfxManager::updateMusic(SfxManager::MENU);
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