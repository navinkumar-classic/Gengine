//
// Created by navin on 10/18/25.
//
#include "TileManager.h"

TileMap::TileMap(float tileWidth,
    float tileHeight,
    const std::unordered_map<int, std::string>& ref_texture)
    : m_tileWidth(tileWidth), m_tileHeight(tileHeight), ref_texture(ref_texture) {}

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
            if (it == m_textures.end()) {
                auto ref_it = ref_texture.find(id);
                if (ref_it != ref_texture.end()) {
                    loadTexture(id, ref_it->second);
                    it = m_textures.find(id);
                }
                else
                    continue;
            }

            sf::Sprite sprite;
            sprite.setTexture(*it->second);
            sprite.setPosition(m_position.x + col * m_tileWidth,
                               m_position.y + row * m_tileHeight);
            sprite.setScale(
                m_tileWidth / it->second->getSize().x,
                m_tileHeight / it->second->getSize().y
            );
            float x = col * m_tileWidth  - m_origin.x + m_position.x;
            float y = row * m_tileHeight - m_origin.y + m_position.y;
            sprite.setPosition(x, y);

            window.draw(sprite);
        }
    }
}

void TileMap::setPosition(const sf::Vector2f& pos) {
    m_position = pos;
}

sf::FloatRect TileMap::getBounds() const {
    if (m_matrix.empty() || m_matrix[0].empty()) return sf::FloatRect();
    float width  = m_matrix[0].size() * m_tileWidth;
    float height = m_matrix.size() * m_tileHeight;

    float left = m_position.x - m_origin.x;
    float top  = m_position.y - m_origin.y;

    return sf::FloatRect(left, top, width, height);

}

// TileMap-specific
void TileMap::setMatrix(const std::vector<std::vector<int>>& mat) {
    m_matrix = mat;

    float width  = m_matrix[0].size() * m_tileWidth;
    float height = m_matrix.size() * m_tileHeight;

    setOrigin(width / 2.f, height / 2.f);
}

void TileMap::loadTexture(int id, const std::string& filename) {
    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    m_textures[id] = tex;
}

void TileMap::setOrigin(float a, float b) {
    m_origin = sf::Vector2f(a,b);
}