#include <SFML/Network.hpp>
#include <Logger/Logger.hpp>

Logger logger;

sf::TcpSocket  arduino;
sf::IpAddress  ip(10,27,29,100);
unsigned short port = 1025;

int main(){
    logger.log("Choose a mode: ");
    logger.log("0. Solid White");
    logger.log("1. Marquee");
    logger.log("2. Color Cycle");
    logger.log("3. Pew");
    logger.log("4. Rainbow Dance Party");
    logger.log("5. Storm Spirit");
    logger.logNoEndl("Make your selection by typing the number: ");

    int selection = -1;
    std::cin >> selection;

    arduino.connect(ip, port);

    char data;
    data = (char) selection;
    arduino.send(&data, sizeof(data));

    arduino.disconnect();
}
