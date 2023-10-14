#include "button.h"

#include "raylib.h"

#include "utils/math.h"
#include "constants/dimensions.h"
#include "constants/colors.h"

namespace Asteroids {
	namespace Buttons {
		static const int BUTTON_TEXT_FONT_SIZE = 20;

		void drawButton(Button button) {
			if (button.isHovered) {
				DrawRectangleRec(button.outsideRectangle, button.outsideColor);

				DrawRectangleRec(button.insideRectangle, IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? button.focusColor : button.insideColor);
			}
			else {
				DrawRectangleRec(button.outsideRectangle, button.insideColor);
			}
		}

		void drawCenteredTextInButton(Button button, const char* text) {
			int textLength = MeasureText(text, static_cast<int>(BUTTON_TEXT_FONT_SIZE));
			float screenWidth = static_cast<float>(GetScreenWidth());
			int optionTextPosX = static_cast<int>(getHalf(screenWidth) - getHalf(static_cast<float>(textLength)));
			int optionTextPosY = static_cast<int>(button.outsideRectangle.y + getHalf(button.outsideRectangle.height) - getHalf(BUTTON_TEXT_FONT_SIZE));

			DrawText(
				text,
				optionTextPosX,
				optionTextPosY,
				static_cast<int>(BUTTON_TEXT_FONT_SIZE),
				WHITE
			);
		}

		void updateButton(Button& button) {
			Vector2 mousePosition = GetMousePosition();

			if (checkPointToRectangleCollision(button.outsideRectangle, mousePosition)) {
				button.isHovered = true;

				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
					button.isClicked = true;
				}
			}
			else {
				button.isHovered = false;
			}
		}

		Button createButton(Rectangle rectangle) {
			Rectangle insideRectangle = {
				rectangle.x + BOX_BORDER_WIDTH,
				rectangle.y + BOX_BORDER_WIDTH,
				rectangle.width - BOX_BORDER_WIDTH * 2,
				rectangle.height - BOX_BORDER_WIDTH * 2,
			};

			return {
				insideRectangle,
				rectangle,
				RED,
				FOCUS_COLOR,
				PINK
			};
		}
	}
}