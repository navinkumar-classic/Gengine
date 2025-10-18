//
// Created by navin on 10/18/25.
//
#include "TileManager.h"

TileMap::TileMap(float tileWidth, float tileHeight)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight) {}

// Base class overrides
void TileMap::update(float dt) {
    // Static tiles for now
}

void TileMap::draw(sf::RenderWindow& window) {
    // Draw each tile individually with its own texture
    for (size_t row = 0; row < m_matrix.size(); ++row) {
        for (size_t col = 0; col < m_matrix[row].size(); ++col) {
            int id = m_matrix[row][col];
            auto it = m_textures.find(id);
            if (it == m_textures.end()) continue;

            sf::Sprite sprite;
            sprite.setTexture(*it->second);
            sprite.setPosition(m_position.x + col * m_tileWidth,
                               m_position.y + row * m_tileHeight);
            sprite.setScale(
                m_tileWidth / it->second->getSize().x,
                m_tileHeight / it->second->getSize().y
            );
            window.draw(sprite);
        }
    }
}

void TileMap::setPosition(const sf::Vector2f& pos) {
    m_position = pos;
}

sf::FloatRect TileMap::getBounds() const {
    if (m_matrix.empty() || m_matrix[0].empty()) return sf::FloatRect();
    return sf::FloatRect(m_position.x, m_position.y,
                         m_matrix[0].size() * m_tileWidth,
                         m_matrix.size() * m_tileHeight);
}

// TileMap-specific
void TileMap::setMatrix(const std::vector<std::vector<int>>& mat) {
    m_matrix = mat;
}

void TileMap::loadTexture(int id, const std::string& filename) {
    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    m_textures[id] = tex;
}

