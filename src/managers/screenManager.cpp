#include "screenManager.h"

#include "screens/menu.h"
#include "screens/gameplay.h"
#include "screens/rules.h"
#include "screens/credits.h"
#include "assets/sfxManager.h"

namespace Asteroids {
	namespace ScreensManager {
		static Screens actualScreen;

		void initManager() {
			actualScreen = Screens::MENU;

			SfxManager::playMusic(SfxManager::MENU);
			Menu::initMenu();
		}

		void changeScreenTo(Screens screen, bool shouldStopMusic) {
			actualScreen = screen;
			if (shouldStopMusic) {
				SfxManager::stopAllMusic();
			}

			switch (actualScreen) {
				case Screens::MENU:
					Menu::initMenu();
					if (shouldStopMusic) {
						SfxManager::playMusic(SfxManager::MENU);
					}
					break;
				case Screens::GAMEPLAY:
					Gameplay::initGameplay();
					SfxManager::playMusic(SfxManager::GAMEPLAY);
					break;
				case Screens::CREDITS:
					Credits::initCredits();
					break;
				case Screens::RULES:
					Rules::initRules();
					break;
			}
		}

		void drawScreen() {
			switch (actualScreen) {
				case Screens::MENU:
					Menu::drawMenu();
					break;
				case Screens::CREDITS:
					Credits::drawCredits();
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
					Menu::checkMenuInputAndCollision(shouldClose);
					SfxManager::updateMusic(SfxManager::MENU);
					break;
				case Screens::CREDITS:
					Credits::checkCreditsInputAndCollision();
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