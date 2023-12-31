#pragma once
#include <string>

#include "raylib.h"

#include "uiComponents/button.h"

namespace Asteroids {
	namespace Menu {
		enum Option {
			PLAY,
			READ_RULES,
			READ_CREDITS,
			EXIT,
			OPTIONS_QUANTITY
		};

		struct MenuOption {
			Option option;
			std::string text;
			Buttons::Button optionButton;
		};

		void initMenu();
		void drawMenu();
		void checkMenuInputAndCollision(bool& shouldClose);
	}
}
