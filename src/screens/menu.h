#pragma once
#include <string>

#include "raylib.h"

#include "screens.h"

namespace Asteroids {
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
		bool isHovered;
		Rectangle optionBox;
	};

	void drawMenu();
	void initMenu();
	void checkMenuInputAndCollision(Screens& screen, bool& shouldClose);
}
