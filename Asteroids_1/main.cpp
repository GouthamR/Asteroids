//#include <SFML/Graphics.hpp>

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);

//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }

//        window.clear();
//        window.draw(shape);
//        window.display();
//    }

//    return 0;
//}



#include <iostream>
using namespace std;

#include "circleobject.h"
#include "world.h"

int main ()
{
    CircleObject circle1(0, 0, 5);
    CircleObject circle2(5, 0, 5);

    cout << circle1 << "\t" << circle2 << endl;

    World world(2);
    world.add(&circle1);
    world.add(&circle2);

    world.handleAllCollisions();

    cout << circle1 << "\t" << circle2 << endl;

    return 0;
}

