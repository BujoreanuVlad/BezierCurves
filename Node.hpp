#if !defined NODE_HPP
#define NODE_HPP
#include <SFML/Graphics.hpp>

class Node {

	private:
		float x, y;
	
	public:
		Node(float X, float Y): x {X}, y {Y} {}
		float getX() const { return x; }
		float getY() const { return y; }
		void draw(sf::RenderWindow &window);
		Node scale(float scale_factor) { return Node { x * scale_factor, y * scale_factor }; }
		Node operator+(const Node &node) const { return Node {x + node.x, y + node.y}; }
};

#endif
