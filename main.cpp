#include <SFML/Graphics.hpp>
#include <unistd.h>

#include <cmath>
#include <iostream>

void drawLine(int x1, int y1, int x2, int y2, sf::RenderWindow &window) {
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	sf::Vertex point(sf::Vector2f(x2, y2), sf::Color::Black);
	window.draw(&point, 1, sf::Points);
	while (x1 != x2 || y1 != y2) {
		sf::Vertex point1(sf::Vector2f(x1, y1), sf::Color::Black);
		window.draw(&point1, 1, sf::Points);
		int error2 = error * 2;
		if (error2 > -deltaY) {
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX) {
			error += deltaX;
			y1 += signY;
		}
	}
	window.display();
}

void drawLineGreen(int x1, int y1, int x2, int y2, sf::RenderWindow &window) {
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	sf::Vertex point(sf::Vector2f(x2, y2), sf::Color::Green);
	window.draw(&point, 1, sf::Points);
	while (x1 != x2 || y1 != y2) {
		sf::Vertex point1(sf::Vector2f(x1, y1), sf::Color::Green);
		window.draw(&point1, 1, sf::Points);
		int error2 = error * 2;
		if (error2 > -deltaY) {
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX) {
			error += deltaX;
			y1 += signY;
		}
	}
}

void drawCircle(int x0, int y0, int radius, sf::RenderWindow &window) {
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		sf::Vertex point(sf::Vector2f(x0 + x, y0 + y), sf::Color::Black);
		sf::Vertex point1(sf::Vector2f(x0 + x, y0 - y), sf::Color::Red);
		sf::Vertex point2(sf::Vector2f(x0 - x, y0 + y), sf::Color::Green);
		sf::Vertex point3(sf::Vector2f(x0 - x, y0 - y), sf::Color::Blue);
		window.draw(&point, 1, sf::Points);
		window.draw(&point1, 1, sf::Points);
		window.draw(&point2, 1, sf::Points);
		window.draw(&point3, 1, sf::Points);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
	window.display();
}

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "HW3");
	window.setFramerateLimit(50);
	std::vector<std::pair<int, int>> vec_points;
	std::vector<std::pair<int, int>> vec_line;
	bool dr = false;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				return 0;
			}
			case sf::Event::MouseButtonPressed: {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (dr) {
						vec_line.push_back(std::make_pair(event.mouseButton.x, event.mouseButton.y));
					} else {
						vec_points.push_back(std::make_pair(event.mouseButton.x, event.mouseButton.y));
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					dr = true;
					auto itend = vec_points.begin();
					vec_points.push_back(std::make_pair(itend->first, itend->second));
				}
			}
			}
		}

		window.clear(sf::Color::White);

		if (vec_points.size() >= 2) {
			auto it0 = vec_points.begin();
			auto it1 = vec_points.begin();
			++it1;
			for (; it1 != vec_points.end(); ++it0, ++it1) {
				drawLineGreen(it0->first, it0->second, it1->first, it1->second, window);
			}
		}
		if (vec_line.size() >= 2) {
			auto it0 = vec_line.begin();
			auto it1 = vec_line.begin();
			++it1;
			for (int i = 0; it1 != vec_line.end(); ++it1, ++it0, ++i) { //std::advance(it0), std::advance(it1, 2)) {
				if (i % 2 == 0) {
					drawLineGreen(it0->first, it0->second, it1->first, it1->second, window);
				}
			}
		}
		window.display();
	}
	return 0;
}
