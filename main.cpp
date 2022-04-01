#include <SFML/Graphics.hpp>
#include "Node.hpp"
#include <vector>
#include <iostream>

const float width {1920};
const float height {1080};

sf::RenderWindow window(sf::VideoMode(width, height), "Bezier Demo");

Node BezierGet(std::vector<Node> nodes1, std::vector<Node> nodes2, float t) {

	if (nodes1.size() == 1)
		return (nodes1[0].scale(t) + nodes2[0].scale(1-t));

	return (BezierGet(std::vector<Node> (nodes1.begin(), nodes1.end()-1), std::vector<Node> (nodes1.begin()+1, nodes1.end()), t).scale(t) + 
			BezierGet(std::vector<Node> (nodes2.begin(), nodes2.end()-1), std::vector<Node> (nodes2.begin()+1, nodes2.end()), t).scale(1-t));
}

void BezierDraw(std::vector<Node> &nodes) {

	if (nodes.size() < 2)
		return;

	for (float t {}; t <= 1; t+=0.0005) {
		BezierGet(std::vector<Node> (nodes.begin(), nodes.end()-1), std::vector<Node> (nodes.begin()+1, nodes.end()), t).draw(window);
	}
}

void SupportLines(std::vector<Node> &nodes) {

	for (size_t i {1}; i < nodes.size(); i++) {
		std::vector<Node> vec {nodes[i-1], nodes[i]};
		BezierDraw(vec);
	}
}

void ControlPoints(std::vector<Node> &nodes) {

	for (auto node : nodes) {

		sf::CircleShape shape(5);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(node.getX(), node.getY());
		window.draw(shape);
	}
}

void drawAll(std::vector<Node> &nodes, bool withSupportLines, bool withControlPoints) {

	window.clear(sf::Color::White);
	if (withSupportLines)
		SupportLines(nodes);
	if (withControlPoints)
		ControlPoints(nodes);
	BezierDraw(nodes);
	window.display();
}

int main() {

	window.setFramerateLimit(60);

	std::vector<Node> nodes;
	bool withSupportLines {};
	bool withControlPoints {true};

	window.clear(sf::Color::White);
	window.display();

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::MouseButtonPressed) {
				
				if (event.mouseButton.button == sf::Mouse::Left) {
					auto position = sf::Mouse::getPosition();
					Node buff {static_cast<float>(position.x), static_cast<float>(position.y)};
					nodes.push_back(buff);
					drawAll(nodes, withSupportLines, withControlPoints);
				}
			}

			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::S:
						withSupportLines = !withSupportLines;
						break;
					case sf::Keyboard::C:
						withControlPoints = !withControlPoints;
						break;
					case sf::Keyboard::R:
						nodes.clear();
						break;
					case sf::Keyboard::Escape:
						window.close();
						break;
				}
				drawAll(nodes, withSupportLines, withControlPoints);
			}
		}

	}

	return 0;
}
