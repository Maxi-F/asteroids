#pragma once
#include "raylib.h"

namespace Asteroids {
	namespace Buttons {
		struct Button {
			Rectangle insideRectangle;
			Rectangle outsideRectangle;
			Color insideColor;
			Color focusColor;
			Color outsideColor;
			bool isHovered = false;
			bool isClicked = false;
		};

		void drawButton(Button button);
		void drawCenteredTextInButton(Button button, const char* text);
		void updateButton(Button &button);
		Button createButton(Rectangle rectangle);
	}
}
