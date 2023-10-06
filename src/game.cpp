#include "game.h"

#include "raylib.h"
#include "screens/screens.h"
#include "screens/menu.h"
#include "constants/dimensions.h"

namespace Asteroids {
    static void close() {
        CloseWindow();
    }

    static void init() {
        InitWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "LePong");

        initMenu();
    }

    static void update(Screens& screen, bool& shouldClose) {
        switch (screen) {
        case Screens::MENU:
            Asteroids::checkMenuInputAndCollision(screen, shouldClose);
            break;
        case Screens::CREDITS:
            break;
        case Screens::RULES:
            break;
        case Screens::GAMEPLAY:
            break;
        };
    }

    static void draw(Screens screen) {
        BeginDrawing();
            GetFontDefault();
            ClearBackground(BLACK);

            switch (screen) {
            case Screens::MENU:
                drawMenu();
                break;
            case Screens::CREDITS:
                break;
            case Screens::RULES:
                break;
            case Screens::GAMEPLAY:
                break;
            };

        EndDrawing();
    }

    void startGame() {
        init();
        Screens screen = Screens::MENU;
        bool shouldClose = false;

        SetExitKey(0);

        while (!shouldClose)
        {
            update(screen, shouldClose);

            draw(screen);
        }

        close();
    }

}
