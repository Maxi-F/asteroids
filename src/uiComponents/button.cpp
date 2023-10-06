#include "button.h"

namespace Asteroids {
	void drawButton(Button button) {
		if (button.isHovered) {
			DrawRectangleRec(button.outsideRectangle, button.outsideColor);

			DrawRectangleRec(button.insideRectangle, IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? button.focusColor : button.insideColor);
		}
		else {
			DrawRectangleRec(button.outsideRectangle, button.insideColor);
		}
	}
}