#include "credits.h"

#include <string>
#include "raylib.h"
// The next preprocessor statements are made to fix
// bugs that arise because raylib and windows.h libs have
// some names that overlap each other.
#if defined(_WIN32)           
	#define NOGDI   
	#define NOUSER
#endif

#include <Windows.h>

#if defined(_WIN32)
	#undef near
	#undef far
#endif

#include "uiComponents/button.h"
#include "assets/assetManager.h"
#include "managers/screenManager.h"
#include "utils/math.h"

namespace Asteroids {
	namespace Credits {
		struct LinkRectangle {
		    Rectangle rectangle;
			LPCWSTR link;
		};
		
		static const float SCREEN_MARGIN = 50.0f;
		static const int BUTTON_WIDTH = 100;
		static const int BUTTON_HEIGHT = 50;

		static const int LINK_RECTANGLE_HEIGHT = 65;
		static const int LINKS_COUNT = 4;

		static Buttons::Button goBackButton;
		static LinkRectangle linkRectangles[LINKS_COUNT];

		void drawCredits() {
			DrawTextureEx(AssetManager::getTexture(AssetManager::CREDITS), { 0.0f, 0.0f }, 0, 1, WHITE);

			Buttons::drawButton(goBackButton);

#ifdef _DEBUG
			for (int i = 0; i < LINKS_COUNT; i++) {
				DrawRectangleRec(linkRectangles[i].rectangle, RED);
			};
#endif // _DEBUG
		};

		void initCredits() {
			const int DEVELOPER_LINK_WIDTH = 250;
			const int ASSETS_LINK_WIDTH = 250;
			const int SFX_LINK_WIDTH = 190;
			const int FONT_LINK_WIDTH = 420;
			const int START_LINK_Y_POSITION = 140;
			const int MARGIN_LINK_Y_POSITION = 100;

			goBackButton = Buttons::createButton(
				{
					SCREEN_MARGIN,
					static_cast<float>(GetScreenHeight() - BUTTON_HEIGHT - SCREEN_MARGIN),
					BUTTON_WIDTH,
					BUTTON_HEIGHT
				}
			);

			Rectangle developerLinkRectangle = {
				getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(DEVELOPER_LINK_WIDTH)),
				START_LINK_Y_POSITION,
				DEVELOPER_LINK_WIDTH,
				LINK_RECTANGLE_HEIGHT
			};

			Rectangle assetsLinkRectangle = {
				getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(ASSETS_LINK_WIDTH)),
				START_LINK_Y_POSITION + MARGIN_LINK_Y_POSITION,
				ASSETS_LINK_WIDTH,
				LINK_RECTANGLE_HEIGHT
			};

			Rectangle sfxLinkRectangle = {
				getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(SFX_LINK_WIDTH)),
				START_LINK_Y_POSITION + MARGIN_LINK_Y_POSITION * 2,
				SFX_LINK_WIDTH,
				LINK_RECTANGLE_HEIGHT
			};

			Rectangle fontLinkRectangle = {
				getHalf(static_cast<float>(GetScreenWidth())) - getHalf(static_cast<float>(FONT_LINK_WIDTH)),
				START_LINK_Y_POSITION + MARGIN_LINK_Y_POSITION * 3,
				FONT_LINK_WIDTH,
				LINK_RECTANGLE_HEIGHT
			};

			LinkRectangle auxLinkRectangles[LINKS_COUNT] = {
				{
					developerLinkRectangle,
					L"https://github.com/Maxi-F/"
				},
				{
					assetsLinkRectangle,
					L"https://google.com"
				},
				{
					sfxLinkRectangle,
					L"https://google.com"
				},
				{
					fontLinkRectangle,
					L"https://fonts.google.com/specimen/VT323"
				}
			};

			for (int i = 0; i < LINKS_COUNT; i++) {
				linkRectangles[i] = auxLinkRectangles[i];
			}
		};
		
		void checkCreditsInputAndCollision() {
			Buttons::updateButton(goBackButton);
			Vector2 mousePosition = GetMousePosition();

			if (goBackButton.isClicked) {
				ScreensManager::changeScreenTo(ScreensManager::MENU, false);
			}

			for (int i = 0; i < LINKS_COUNT; i++) {
				if (checkPointToRectangleCollision(linkRectangles[i].rectangle, mousePosition) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					ShellExecute(0, 0, linkRectangles[i].link, 0, 0, 5);
				}
			}
		};
	}
}