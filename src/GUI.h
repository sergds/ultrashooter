#include <string>
#include <cmath>

// Простенькая "Библиотека" Для GUI
namespace GUI {
    // Рисовать кнопку
    bool Button(float x, float y, float fontsize = 30.f, std::string label = "Button");
    // Рисовать кнопку в центре оси X
    bool ButtonCenter(float y, float fontsize = 30.f, std::string label = "Button");
    // Текст, который перемещается как по волнам
    void WavyLabelCenter(float y, std::string text = "GUI::WavyLabel");
}