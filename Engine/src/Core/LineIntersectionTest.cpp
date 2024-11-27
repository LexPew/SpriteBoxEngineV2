#include "Core/EngineTest.h"
#include <SFML/Graphics.hpp>
#include "Maths/Rect.h"

void LineIntersectionTest()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Line Intersection Test");
    Rect rect1(100, 100, 200, 200);
    Line2 line1(Vector2(100, 100), 200, 45);
    Line2 line2(Vector2(100, 300), 200, -45);

    bool isDrawingLine1 = false;
    bool isDrawingLine2 = false;
    bool isMovingRect = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseMoved)
            {
                if (isDrawingLine1)
                {
                    line1.end = Vector2(event.mouseMove.x, event.mouseMove.y);
                }
                else if (isDrawingLine2)
                {
                    line2.end = Vector2(event.mouseMove.x, event.mouseMove.y);
                }
                else if (isMovingRect)
                {
                    rect1.SetPosition(Vector2(event.mouseMove.x, event.mouseMove.y));
                }
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    line1.start = Vector2(event.mouseButton.x, event.mouseButton.y);
                    isDrawingLine1 = true;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    line2.start = Vector2(event.mouseButton.x, event.mouseButton.y);
                    isDrawingLine2 = true;
                }
                else if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    isMovingRect = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    line1.end = Vector2(event.mouseButton.x, event.mouseButton.y);
                    isDrawingLine1 = false;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    line2.end = Vector2(event.mouseButton.x, event.mouseButton.y);
                    isDrawingLine2 = false;
                }
                else if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    isMovingRect = false;
                }
            }
        }

        Vector2 intersection = Line2::LineIntersection(line1, line2);
        Vector2 intersection2 = rect1.RayCastIntersection(line1);
		Vector2 intersection3 = rect1.RayCastIntersection(line2);
        sf::Vertex line1Vertices[] =
        {
            sf::Vertex(sf::Vector2f(line1.start.x, line1.start.y)),
            sf::Vertex(sf::Vector2f(line1.end.x, line1.end.y))
        };

        sf::Vertex line2Vertices[] =
        {
            sf::Vertex(sf::Vector2f(line2.start.x, line2.start.y)),
            sf::Vertex(sf::Vector2f(line2.end.x, line2.end.y))
        };

        sf::RectangleShape rectangle(sf::Vector2f(rect1.GetWidth(), rect1.GetHeight()));
        rectangle.setPosition(rect1.GetOriginPosition().x, rect1.GetOriginPosition().y);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(sf::Color::Green);

        sf::CircleShape intersectionPoint(5);
        intersectionPoint.setFillColor(sf::Color::Red);
        intersectionPoint.setPosition(intersection.x - 5, intersection.y - 5);

        window.clear();
        window.draw(line1Vertices, 2, sf::Lines);
        window.draw(line2Vertices, 2, sf::Lines);
        window.draw(rectangle);
        if (intersection != Vector2::Zero())
        {
            window.draw(intersectionPoint);
        }
		if (intersection2 != Vector2::Zero())
		{
			sf::CircleShape intersectionPoint2(5);
			intersectionPoint2.setFillColor(sf::Color::Blue);
			intersectionPoint2.setPosition(intersection2.x - 5, intersection2.y - 5);
			window.draw(intersectionPoint2);
		}
		if (intersection3 != Vector2::Zero())
		{
			sf::CircleShape intersectionPoint3(5);
			intersectionPoint3.setFillColor(sf::Color::Yellow);
			intersectionPoint3.setPosition(intersection3.x - 5, intersection3.y - 5);
			window.draw(intersectionPoint3);
		}

        window.display();
    }
}