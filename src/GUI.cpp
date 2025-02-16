#include "fix_winapi_conflicts.h"
#include "globals.h"
#include "raylib.h"
#include "GUI.h"

// Простенькая "Библиотека" Для GUI
namespace GUI {
    // Рисовать кнопку
    bool Button(float x, float y, float fontsize, std::string label) {
        Rectangle rec = {x, y, 10, 10};
        Vector2 text_sz = MeasureTextEx(DefaultFont, label.c_str(), fontsize, 1);
        if (rec.width < text_sz.x + 5 + 4) // Выравнивание X.
            rec.width += text_sz.x - rec.height + 5 + 4; // Если кнопка слишком мелкая для текста, то добавляем ей недостающей ширины с учётом выравнивания.
        if (rec.height < text_sz.y + 4) // Выравнивание Y.
            rec.height += text_sz.y - rec.height + 4 ; // Если кнопка слишком мелкая для текста, то добавляем ей недостающей высоты с учётом выравнивания.
        //DrawRectangleRec(rec, DARKBROWN);
        #ifdef PLATFORM_ANDROID
        if(CheckCollisionPointRec(GetTouchPosition(0), rec)){
        #else
        if(CheckCollisionPointRec(GetMousePosition(), rec)){
        #endif
            DrawRectangleRounded(rec, 1, 10, BROWN);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                return true;
        } else {
            DrawRectangleRounded(rec, 1, 10, DARKBROWN);
        }
        
        DrawTextEx(DefaultFont, label.c_str(), CLITERAL(Vector2){rec.x+4, rec.y+2}, fontsize, 1, WHITE);
        return false;
    }
    // Рисовать кнопку в центре оси X
    bool ButtonCenter(float y, float fontsize, std::string label) {
        Rectangle rec = {0, y, 10, 10};
        Vector2 text_sz = MeasureTextEx(DefaultFont, label.c_str(), fontsize, 1);
        rec.x = ((float)GetRenderWidth() / 2) - text_sz.x / 2; //Минутка Арифметики!
        if (rec.width < text_sz.x + 5 + 4) // Выравнивание X.
            rec.width += text_sz.x - rec.height + 5 + 4; // Если кнопка слишком мелкая для текста, то добавляем ей недостающей ширины с учётом выравнивания.
        if (rec.height < text_sz.y + 4) // Выравнивание Y.
            rec.height += text_sz.y - rec.height + 4 ; // Если кнопка слишком мелкая для текста, то добавляем ей недостающей высоты с учётом выравнивания.
        //DrawRectangleRec(rec, DARKBROWN);
        #ifdef PLATFORM_ANDROID
        if(CheckCollisionPointRec(GetTouchPosition(0), rec)){
        #else
        if(CheckCollisionPointRec(GetMousePosition(), rec)){
        #endif
            DrawRectangleRounded(rec, 1, 10, BROWN);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                return true;
        } else {
            DrawRectangleRounded(rec, 1, 10, DARKBROWN);
        }
        DrawTextEx(DefaultFont, label.c_str(), CLITERAL(Vector2){rec.x+4, rec.y+2}, fontsize, 1, WHITE);
        return false;
    }
    void WavyLabelCenter(float y, std::string text) {
        Vector2 text_sz = MeasureTextEx(DefaultFont, text.c_str(), 50, 1);
        // Нечитаемая жуть!
        DrawTextPro(DefaultFont, text.c_str(), CLITERAL(Vector2){((float)GetRenderWidth() / 2) - text_sz.x / 2, (float)(y + sin(GetTime()) * 4)}, CLITERAL(Vector2){50,0},sin(GetTime()*2), 50, 1, WHITE);
    }
};