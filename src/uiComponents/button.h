#pragma once
#include "raylib.h"

namespace Asteroids {
	struct Button {
		Rectangle insideRectangle;
		Rectangle outsideRectangle;
		Color insideColor;
		Color focusColor;
		Color outsideColor;
		bool isHovered;
	};

	void drawButton(Button button);
}
