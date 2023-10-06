#include "menu.h"

#include "constants/dimensions.h"
#include "constants/colors.h"
#include "utils/math.h"

namespace Asteroids {
	static const float OPTION_RECTANGLE_WIDTH = 300.0f;
	static const float OPTION_RECTANGLE_HEIGHT = 40.0f;
	static const int OPTION_FONT_SIZE = 20;
	static const float TOP_MARGIN = 120.0f;
	static const float OPTION_RECTANGLE_MARGIN = 25.0f;
	static const float TITLE_TOP_MARGIN = 40.0f;
	static const int TITLE_FONT_SIZE = 50;

	static MenuOption menuOptions[Option::OPTIONS_QUANTITY];

	static void drawOptionBox(MenuOption option) {
		if (option.isHovered) {
			DrawRectangleRec(option.optionBox, PINK);

			Rectangle insideRectangle = {
				option.optionBox.x + BOX_BORDER_WIDTH,
				option.optionBox.y + BOX_BORDER_WIDTH,
				option.optionBox.width - BOX_BORDER_WIDTH * 2,
				option.optionBox.height - BOX_BORDER_WIDTH * 2,
			};

			DrawRectangleRec(insideRectangle, IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? FOCUS_COLOR : RED);
		}
		else {
			DrawRectangleRec(option.optionBox, RED);
		}
	}

	static void drawOptionText(float yPosition, const char* text) {
		int textLength = MeasureText(text, static_cast<int>(OPTION_FONT_SIZE));
		float screenWidth = static_cast<float>(GetScreenWidth());
		int optionTextPosX = static_cast<int>(getHalf(screenWidth) - getHalf(static_cast<float>(textLength)));
		int optionTextPosY = static_cast<int>(yPosition + getHalf(OPTION_RECTANGLE_HEIGHT) - getHalf(OPTION_FONT_SIZE));

		DrawText(
			text,
			optionTextPosX,
			optionTextPosY,
			static_cast<int>(OPTION_FONT_SIZE),
			WHITE
		);
	}

	static std::string optionToText(Option option) {
		switch (option) {
		case Option::PLAY:
			return "Play";
		case Option::EXIT:
			return "Exit";
		case Option::READ_RULES:
			return "Rules";
		case Option::READ_CREDITS:
			return "Credits";
		default:
			return "";
		}
	}

	static void actionPerMenuOption(Option option, Screens& screen, bool& shouldClose) {
		switch (option) {
		case Option::PLAY:
			screen = Screens::GAMEPLAY;
			break;
		case Option::READ_CREDITS:
			screen = Screens::CREDITS;
			break;
		case Option::READ_RULES:
			screen = Screens::RULES;
			break;
		case Option::EXIT:
			shouldClose = true;
			break;
		}
	}

	void initMenu() {
		for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
			float yPosition = TOP_MARGIN + (OPTION_RECTANGLE_MARGIN + OPTION_RECTANGLE_HEIGHT) * i;
			float screenWidth = static_cast<float>(GetScreenWidth());

			Rectangle optionRectangle = {
			getHalf(screenWidth) - getHalf(OPTION_RECTANGLE_WIDTH),
			yPosition,
			OPTION_RECTANGLE_WIDTH,
			OPTION_RECTANGLE_HEIGHT
			};

			menuOptions[i] = {
				(Option)i,
				optionToText((Option)i),
				false,
				optionRectangle
			};
		}
	}

	void drawMenu() {
		const char* title = "LePong";
		int titleLenght = MeasureText(title, TITLE_FONT_SIZE);
		float screenWidth = static_cast<float>(GetScreenWidth());
		int pongTitlePosX = static_cast<int>(getHalf(screenWidth) - getHalf(static_cast<float>(titleLenght)));

		DrawText("LePong", pongTitlePosX, static_cast<int>(TITLE_TOP_MARGIN), TITLE_FONT_SIZE, WHITE);

		for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
			drawOptionBox(menuOptions[i]);
			drawOptionText(menuOptions[i].optionBox.y, menuOptions[i].text.c_str());
		}
	}

	void checkMenuInputAndCollision(Screens& screen, bool& shouldClose) {
		Vector2 mousePosition = GetMousePosition();

		for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
			if (checkPointToRectangleCollision(menuOptions[i].optionBox, mousePosition)) {
				menuOptions[i].isHovered = true;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					actionPerMenuOption(menuOptions[i].option, screen, shouldClose);
				}
			}
			else {
				menuOptions[i].isHovered = false;
			}
		};

		shouldClose = shouldClose || WindowShouldClose();
	}

}