#ifndef MAIN_HPP
#define MAIN_HPP

enum Mode {
    SolidWhite,
    Marquee,
    ColorCycle,
    Pew
};

int main();
void doMouseMove();
void doMouseButton(sf::Mouse::Button button);
void doSwitchMode(Mode mode);

#endif
