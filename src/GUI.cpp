#include "fix_winapi_conflicts.h"
#include "raylib.h"
#include "GUI.h"
namespace GUI {
    bool Button(float x, float y, float height) {
        Rectangle rec = {x, y, x + 10, y + height};
        DrawRectangleRec(rec, DARKGRAY);
        return false;
    }
};