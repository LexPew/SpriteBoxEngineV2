#include <iostream>

#include "Core/EngineTest.h"
#include <SFML/Graphics.hpp>
#include "Maths/Rect.h"


void LineIntersectionTest()
{
    std::vector<Line2> lines;
    std::vector<Vector2> intersections;
    std::vector<Rect> rects;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Multi Line Intersection Test");

    bool drawingRay = false;
    Vector2 lastMousePosition{ 0,0 };

    while (window.isOpen())
    {
        sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (drawingRay)
					{
						drawingRay = false;
					}
                    else
                    {
                        drawingRay = true;
                        Line2 line;
                        line.start = lastMousePosition;
                        lines.push_back(line);
                    }


				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					
					Rect rect(0,0,40,40);
					rect.SetPosition(lastMousePosition - Vector2(20,20));
					rects.push_back(rect);
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				lastMousePosition = Vector2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

				if (!lines.empty() && drawingRay)
				{

					lines.back().end = Vector2(lastMousePosition.x, lastMousePosition.y);
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::R)
				{
					lines.clear();
					rects.clear();
					
				}
			}
		}

    window.clear(sf::Color::White);

    for (auto& line : lines)
    {
        sf::Vertex lineVertices[] =
        {
            sf::Vertex(sf::Vector2f(line.start.x, line.start.y)),
            sf::Vertex(sf::Vector2f(line.end.x, line.end.y))
        };
        lineVertices[0].color = sf::Color::Red;
        lineVertices[1].color = sf::Color::Green;
        window.draw(lineVertices, 2, sf::Lines);
    }
    for (auto& rect : rects)
    {
        sf::RectangleShape rectangle(sf::Vector2f(rect.GetWidth(), rect.GetHeight()));
        rectangle.setPosition(rect.GetOriginPosition().x, rect.GetOriginPosition().y);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineThickness(1);
        rectangle.setOutlineColor(sf::Color::Green);
        window.draw(rectangle);
    }

	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = i + 1; j < lines.size(); j++)
		{
			Vector2 intersection = Line2::LineIntersection(lines[i], lines[j]);
			if (intersection != Vector2::Zero())
			{
				intersections.push_back(intersection);
			}
		}
	}
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = 0; j < rects.size(); j++)
		{
			Vector2 intersection = rects[j].RayCastIntersection(lines[i]);
			if (intersection != Vector2::Zero())
			{
				intersections.push_back(intersection);
			}
		}
	}
	for (auto& intersection : intersections)
	{
		sf::CircleShape intersectionPoint(5);
		intersectionPoint.setFillColor(sf::Color::Red);
		intersectionPoint.setOutlineThickness(2);
		intersectionPoint.setOutlineColor(sf::Color::Black);
		intersectionPoint.setPosition(intersection.x - 5, intersection.y - 5);
		window.draw(intersectionPoint);
	}

	intersections.clear();

    window.display();
	}

}
