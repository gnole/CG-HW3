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
	sf::Vertex point(sf::Vector2f(x2, y2), sf::Color::Red);
	window.draw(&point, 1, sf::Points);
	while (x1 != x2 || y1 != y2) {
		sf::Vertex point1(sf::Vector2f(x1, y1), sf::Color::Red);
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

int dot(std::pair<int, int> p0, std::pair<int, int> p1) {
	return p0.first * p1.first + p0.second * p1.second;
}

float max(std::vector<float> t) {
	float maximum = -1000000;
	for (int i = 0; i < t.size(); i++)
		if (t[i] > maximum)
			maximum = t[i];
	return maximum;
}

float min(std::vector<float> t) {
	float minimum = 1000000;
	for (int i = 0; i < t.size(); i++)
		if (t[i] < minimum)
			minimum = t[i];
	return minimum;
}
void cyrusBeck(std::vector<std::pair<int, int>> vertices,
	std::vector<std::pair<int, int>> line, std::vector<std::pair<int, int>> &vec_line_cb) {
	const int n = vertices.size();
	std::pair<int, int> *newPair = new std::pair<int, int>[2];
	std::pair<int, int> *normal = new std::pair<int, int>[n];

	for (int i = 0; i < n; i++) {
		normal[i].second = vertices[(i + 1) % n].first - vertices[i].first;
		normal[i].first = vertices[i].second - vertices[(i + 1) % n].second;
	}
	std::pair<int, int> P1_P0 = std::make_pair(line[1].first - line[0].first,
		line[1].second - line[0].second);

	std::pair<int, int> *P0_PEi = new std::pair<int, int>[n];

	for (int i = 0; i < n; i++) {
		P0_PEi[i].first = vertices[i].first - line[0].first;
		P0_PEi[i].second = vertices[i].second - line[0].second;
	}
	int *numerator = new int[n], *denominator = new int[n];

	for (int i = 0; i < n; i++) {
		numerator[i] = dot(normal[i], P0_PEi[i]);
		denominator[i] = dot(normal[i], P1_P0);
	}

	float *t = new float[n];

	std::vector<float> tE, tL;

	for (int i = 0; i < n; i++) {

		t[i] = (float)(numerator[i]) / (float)(denominator[i]);

		if (denominator[i] > 0)
			tE.push_back(t[i]);
		else
			tL.push_back(t[i]);
	}

	float temp[2];

	tE.push_back(0.f);
	temp[0] = max(tE);
	tL.push_back(1.f);
	temp[1] = min(tL);

	if (temp[0] > temp[1]) {
		newPair[0] = std::make_pair(-1, -1);
		newPair[1] = std::make_pair(-1, -1);
		vec_line_cb.push_back(std::make_pair(newPair[0].first, newPair[0].second));
		vec_line_cb.push_back(std::make_pair(newPair[1].first, newPair[1].second));
	} else {

		newPair[0].first = (float)line[0].first + (float)P1_P0.first * (float)temp[0];
		newPair[0].second = (float)line[0].second + (float)P1_P0.second * (float)temp[0];
		newPair[1].first = (float)line[0].first + (float)P1_P0.first * (float)temp[1];
		newPair[1].second = (float)line[0].second + (float)P1_P0.second * (float)temp[1];
	}
	vec_line_cb.push_back(std::make_pair(newPair[0].first, newPair[0].second));
	vec_line_cb.push_back(std::make_pair(newPair[1].first, newPair[1].second));
}

int main() {
	sf::RenderWindow window(sf::VideoMode(740, 680), "HW3");
	window.setFramerateLimit(50);
	std::vector<std::pair<int, int>> vec_points;
	std::vector<std::pair<int, int>> vec_line;
	std::vector<std::pair<int, int>> vec_line_cb;
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
						vec_line.insert(vec_line.begin(), 1, std::make_pair(event.mouseButton.x, event.mouseButton.y));
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
			if (vec_line.size() % 2 == 0) {
				cyrusBeck(vec_points, vec_line, vec_line_cb);
			}
			auto it0 = vec_line_cb.begin();
			auto it1 = vec_line_cb.begin();
			++it1;
			for (int i = 0; it1 != vec_line_cb.end(); ++it1, ++it0, ++i) {
				if (i % 2 == 0) {
					drawLineGreen(it0->first, it0->second, it1->first, it1->second, window);
				}
			}
		}
		window.display();
	}
	return 0;
}
