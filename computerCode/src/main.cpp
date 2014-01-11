#include <Logger/Logger.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "main.hpp"

Logger logger;

sf::RectangleShape rect1(sf::Vector2f(200,200));
sf::RectangleShape rect2(sf::Vector2f(200,200));
sf::RectangleShape rect3(sf::Vector2f(200,200));
sf::RectangleShape rect4(sf::Vector2f(200,200));
sf::RenderWindow   window;
sf::TcpSocket      arduino;
sf::IpAddress      ip(10,27,29,100);
unsigned short     port = 1025;

Mode currentMode = SolidWhite;

int main(){

    logger.logNoEndl("Setting up window...");
    window.create(sf::VideoMode(430,430), "GL");
    logger.continueln(" done!");

    logger.logNoEndl("Setting up variables...");

    rect1.setFillColor(sf::Color(200,200,200));
    rect1.setOutlineColor(sf::Color(0,0,0));
    rect1.setOutlineThickness(-2);
    rect1.setPosition(10,10);

    rect2.setFillColor(sf::Color(200,200,200));
    rect2.setOutlineColor(sf::Color(0,0,0));
    rect2.setOutlineThickness(-2);
    rect2.setPosition(220,10);

    rect3.setFillColor(sf::Color(200,200,200));
    rect3.setOutlineColor(sf::Color(0,0,0));
    rect3.setOutlineThickness(-2);
    rect3.setPosition(10,220);

    rect4.setFillColor(sf::Color(200,200,200));
    rect4.setOutlineColor(sf::Color(0,0,0));
    rect4.setOutlineThickness(-2);
    rect4.setPosition(220,220);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")){
        logger.log(Logger::LogType::Error, "Arial font not found. Cannot continue...");
        return 1;
    }

    sf::Text label1("Solid White", font);
    label1.setColor(sf::Color::Black);
    label1.setPosition(rect1.getPosition().x + rect1.getSize().x / 2 - label1.getLocalBounds().width / 2, rect1.getPosition().y + rect1.getSize().y / 2 - label1.getLocalBounds().height / 2 - 10);

    sf::Text label2("Marquee", font);
    label2.setColor(sf::Color::Black);
    label2.setPosition(rect2.getPosition().x + rect2.getSize().x / 2 - label2.getLocalBounds().width / 2, rect2.getPosition().y + rect2.getSize().y / 2 - label2.getLocalBounds().height / 2 - 10);

    sf::Text label3("Color Cycle", font);
    label3.setColor(sf::Color::Black);
    label3.setPosition(rect3.getPosition().x + rect3.getSize().x / 2 - label3.getLocalBounds().width / 2, rect3.getPosition().y + rect3.getSize().y / 2 - label3.getLocalBounds().height / 2 - 10);

    sf::Text label4("Pew", font);
    label4.setColor(sf::Color::Black);
    label4.setPosition(rect4.getPosition().x + rect4.getSize().x / 2 - label4.getLocalBounds().width / 2, rect4.getPosition().y + rect4.getSize().y / 2 - label4.getLocalBounds().height / 2 - 10);


    unsigned short r = 0,
                   g = 0,
                   b = 0;

    logger.continueln(" done!");

    logger.log("Running until told to stop.");
    bool running = true;
    while(running){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                running = false;
            } else if (event.type == sf::Event::MouseMoved){
                doMouseMove();
            } else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased){
                doMouseButton(event.mouseButton.button);
            }
        }
        window.clear(sf::Color::White);
        window.draw(rect1);
        window.draw(rect2);
        window.draw(rect3);
        window.draw(rect4);
        window.draw(label1);
        window.draw(label2);
        window.draw(label3);
        window.draw(label4);
        window.display();
    }

    logger.log("Closing...");
}

void doMouseMove(){
    if (rect1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) rect1.setFillColor(sf::Color(100,100,100));
    } else {
        rect1.setFillColor(sf::Color(200,200,200));
    }

    if (rect2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) rect2.setFillColor(sf::Color(100,100,100));
    } else {
        rect2.setFillColor(sf::Color(200,200,200));
    }

    if (rect3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) rect3.setFillColor(sf::Color(100,100,100));
    } else {
        rect3.setFillColor(sf::Color(200,200,200));
    }

    if (rect4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) rect4.setFillColor(sf::Color(100,100,100));
    } else {
        rect4.setFillColor(sf::Color(200,200,200));
    }
}

void doMouseButton(sf::Mouse::Button button){
    if (button == sf::Mouse::Button::Left){
        if (rect1.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                rect1.setFillColor(sf::Color::Yellow);
                doSwitchMode(Mode::SolidWhite);
            } else {
                rect1.setFillColor(sf::Color(100,100,100));
            }
        } else {
            rect1.setFillColor(sf::Color(200,200,200));
        }

        if (rect2.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                rect2.setFillColor(sf::Color::Yellow);
                doSwitchMode(Mode::Marquee);
            } else {
                rect2.setFillColor(sf::Color(100,100,100));
            }
        } else {
            rect2.setFillColor(sf::Color(200,200,200));
        }

        if (rect3.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                rect3.setFillColor(sf::Color::Yellow);
                doSwitchMode(Mode::ColorCycle);
            } else {
                rect3.setFillColor(sf::Color(100,100,100));
            }
        } else {
            rect3.setFillColor(sf::Color(200,200,200));
        }

        if (rect4.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)){
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                rect4.setFillColor(sf::Color::Yellow);
                doSwitchMode(Mode::Pew);
            } else {
                rect4.setFillColor(sf::Color(100,100,100));
            }
        } else {
            rect4.setFillColor(sf::Color(200,200,200));
        }
    }
}

void doSwitchMode(Mode mode){
    arduino.connect(ip, port);

    if (mode != currentMode){
        currentMode = mode;

        char data;
        switch (mode){
            case Mode::SolidWhite: data = (char) 0;
                                   break;
            case Mode::Marquee:    data = (char) 1;
                                   break;
            case Mode::ColorCycle: data = (char) 2;
                                   break;
            case Mode::Pew:        data = (char) 3;
                                   break;
            default: break;
        }

        char* dataPointer = &data;
        arduino.send(dataPointer, sizeof(data));
        logger.log("Sent ", (int) data);
    }

    arduino.disconnect();

}
