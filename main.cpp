#include <SFML/Graphics.hpp>
#include <iostream>
#include "math.h"
#define pi 3.14159265359

float timer;

sf::Vertex getVertexFromPoint(sf::Vector2f point)
{
    sf::Vertex vertex;
    vertex.position = sf::Vector2f((3440 / 2) + point.x, (1440 / 2) - 750 + point.y);
    vertex.color = sf::Color((1500 - (point.y + 1500)) / 3000 * 255, 0, (point.y + 1500) / 3000 * 255);
    return vertex;
}

sf::Vector2f getCirclePosition(float angle, sf::Vector2f start, sf::Vector2f end)
{
    sf::Vector2f distance = sf::Vector2f((end - start).x / 2, (end - start).y / 2);
    
    sf::Vector2f center = start + distance;
    
    float theta = atan2f(distance.y, distance.x) / pi * 180 + 180;
    
    float distance1 = sqrtf(distance.x * distance.x + distance.y * distance.y);
    
    float multiply;
    
    float angle2 = angle;
    
    while (angle2 > 45 + 360*cos(timer / 4000))
    {
        angle2 -= 45;
    }
    
    multiply = (45 - (angle2 - 360*cos(timer / 4000))) / 45 * sin(timer / 4000) * sin((angle + timer / 40) / 10);
    
    sf::Vector2f position = center + sf::Vector2f(((distance1 / 2) + (multiply * (distance1 / 2))) * cos((theta + angle) * pi / 180), ((distance1 / 2) + (multiply * (distance1 / 2))) * sin((theta + angle) * pi / 180));
    
    return position;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(3440,1440), "Krapj", sf::Style::Fullscreen);
    
    window.setMouseCursorVisible(false);
    sf::Clock counter;
    
    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear(sf::Color::Black);
        
        std::vector<sf::Vertex> thing = {};
        
        timer = counter.getElapsedTime().asMilliseconds();
        
        for (int ang = 0 + 360*cos(timer / 4000); ang < 360 + 360*cos(timer / 4000); ang += 1)
        {
            thing.push_back(getVertexFromPoint(getCirclePosition(ang, sf::Vector2f(0, 0), sf::Vector2f(0, 1500))));
            thing.push_back(getVertexFromPoint(sf::Vector2f(250 * sin(360*cos(timer / 4000) * pi / 180), 750 + 250 * cos(360*cos(timer / 4000) * pi / 180))));

            thing.push_back(getVertexFromPoint(getCirclePosition(ang, sf::Vector2f(0, 0), sf::Vector2f(0, 1500))));
        }

        thing.push_back(getVertexFromPoint(getCirclePosition(360*cos(timer / 4000), sf::Vector2f(0, 0), sf::Vector2f(0, 1500))));
        
        window.draw(&thing[0], thing.size(), sf::LineStrip);
        
        window.display();
    }
    
    return 0;
}
