#ifndef __AccumulateNode_hh__
#define __AccumulateNode_hh__

#include "Node.hh"

class AccumulateNode : public Node {
public:
    size_t maxLevel     = 0;
    size_t currentLevel = 0;
    sf::Text subTitle;
    sf::Texture mTexture;
    sf::Sprite mSprite;

    AccumulateNode(sf::Vector2f &position, const sf::Font &font, size_t max_level);

    void leftMouseButtonPressed (sf::Vector2f mouseCoords) override;
    void rightMouseButtonPressed(sf::Vector2f mouseCoords) override; 
    bool collisionTest(sf::Vector2f mouseCoords) const override;
    void draw(sf::RenderWindow &window) const override;
    
    virtual sf::String getIconPath() = 0;

    void loadTexture() ;
    sf::Color getCurrentColor() const ;

    inline static const size_t kCharacterSize = 16;
    inline static const size_t width = 50;
    inline static const size_t height = 50;
    inline static const size_t radius = 24;
    inline static const size_t subtitle_offset = 4;

};

class SwordRectSkillNode : public AccumulateNode {
public:
    inline static const size_t mxlvl = 6;

    SwordRectSkillNode(sf::Vector2f position, const sf::Font &font) : AccumulateNode{position, font, mxlvl} { loadTexture(); }

    sf::String getIconPath() override {
        return sf::String{"../sources/icons/icon_rect_sword.png"};
    }
};

std::shared_ptr<Node> anotherTree(const sf::Font &font);

#endif