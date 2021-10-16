#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <cmath>

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

void drawLineWhite(int x1, int y1, int x2, int y2, sf::RenderWindow &window) {
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	sf::Vertex point(sf::Vector2f(x2, y2), sf::Color::White);
	window.draw(&point, 1, sf::Points);
	while (x1 != x2 || y1 != y2) {
		sf::Vertex point1(sf::Vector2f(x1, y1), sf::Color::White);
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
	sf::RenderWindow window(sf::VideoMode(500, 500), "HW 2");
	double alf = 0;
	const int x0 = 250;
	const int y0 = 250;
	const int radius = 99;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);
		drawCircle(250, 250, 100, window);
		drawLine(x0, y0, x0 + radius * cos(alf), y0 + radius * sin(alf), window);
		sleep(1);
		drawLineWhite(x0, y0, x0 + radius * cos(alf), y0 + radius * sin(alf), window);
		alf += M_PI / 180 * 6;
		window.display();
	}
	return 0;
}
