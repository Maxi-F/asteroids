#pragma once

namespace Asteroids {
	namespace ScreensManager {
        enum Screens {
            GAMEPLAY = 0,
            MENU,
            RULES,
            CREDITS
        };

        void initManager();
        void changeScreenTo(Screens screen);
        void drawScreen();
        void updateScreen(bool& shouldClose);
	}
}
