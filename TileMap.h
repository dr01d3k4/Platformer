#pragma once

#include <SFML/Graphics.hpp>


class TileMap : public sf::Drawable, public sf::Transformable {
public:
	bool load(const std::string& tilset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray _vertices;
	sf::Texture _tileset;
};