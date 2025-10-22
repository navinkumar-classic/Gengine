//
// Created by navin on 10/18/25.
//

#pragma once
#include "../SpriteBase.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <memory>

class TileMap : public SpriteBase {
public:
    TileMap(float tileWidth, float tileHeight, const std::unordered_map<int, std::string>& ref_texture);

    // SpriteBase overrides
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void setPosition(const sf::Vector2f& pos) override;
    sf::FloatRect getBounds() const override;

    // TileMap-specific
    void setMatrix(const std::vector<std::vector<int>>& mat);
    void loadTexture(int id, const std::string& filename);
    void setOrigin(float x, float y);

private:
    float m_tileWidth;
    float m_tileHeight;
    sf::VertexArray m_vertices;
    sf::Vector2f m_position {0.f, 0.f};
    sf::Vector2f m_origin;

    std::vector<std::vector<int>> m_matrix;

    // Each tile ID maps to its own texture
    std::unordered_map<int, std::shared_ptr<sf::Texture>> m_textures;

    const std::unordered_map<int, std::string>& ref_texture;

    void buildVertexArray();
};
