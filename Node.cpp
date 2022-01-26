#include "Node.hpp"

void Node::draw(sf::RenderWindow &window) {

	sf::Vertex point(sf::Vector2f(x, y), sf::Color::Black);
	window.draw(&point, 1, sf::Points);
}
