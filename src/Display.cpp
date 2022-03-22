#include "Display.h"

Display::Display(uint8_t okBtn, uint8_t cancelBtn)
    : Adafruit_SSD1306(128, 64, &Wire, -1),
    okBtn(okBtn),
    cancelBtn(cancelBtn),
    fontSize(2) {
}

bool Display::init() {
    if (!begin(SSD1306_SWITCHCAPVCC, 0x3C))
        return false;
    clearDisplay();
    setCursor(0, 0);
    setTextSize(fontSize);
    setTextColor(SSD1306_WHITE, SSD1306_BLACK);
    drawBitmap(32, 16, logo_bmp, 64, 32, SSD1306_WHITE);
    display();
    delay(2000);
    return true;
}

bool Display::prompt(String msg) {
    reset();
    println(msg);
    println("SW3 -> Yes");
    println("SW2 -> No");
    display();
    while (1) {
        if (digitalRead(okBtn) == LOW)
            return true;
        if (digitalRead(cancelBtn) == LOW)
            return false;
    }
}

void Display::printScn(String msg) {
    reset();
    println(msg);
    display();
}

void Display::reset() {
    clearDisplay();
    setCursor(0, 0);
}
