#include "AccumulateNode.hh"

AccumulateNode::AccumulateNode(sf::Vector2f &position, const sf::Font &font, size_t max_level) : 
    Node(position) {
        std::string subtitle = std::to_string(0) + "/" + std::to_string(max_level);

        subTitle.setFont(font);
        subTitle.setCharacterSize(kCharacterSize);
        subTitle.setFillColor(sBlockedColor);
        subTitle.setString(subtitle);
        subTitle.setOrigin({kCharacterSize/2, (float)subtitle.length()/2});
        subTitle.setPosition({position.x, position.y + subtitle_offset});

        currentLevel = 0;
        maxLevel = max_level;
    }

void AccumulateNode::leftMouseButtonPressed(sf::Vector2f mouseCoords) {
  if (mState == State::Blocked)
    return;

  if (collisionTest(mouseCoords)) {
    if (mState == State::Unblocked) {
      mState = State::Activated;
      currentLevel = 1;
      subTitle.setString(std::to_string(currentLevel) + "/" + std::to_string(maxLevel));
      for (const auto &child : mChildren)
        child->unblock();
    }
    else if (mState == State::Activated) {
      currentLevel = (currentLevel == maxLevel) ? maxLevel : currentLevel + 1;
      subTitle.setString(std::to_string(currentLevel) + "/" + std::to_string(maxLevel));
    }
  }
}

void AccumulateNode::rightMouseButtonPressed(sf::Vector2f mouseCoords) {
  if (mState == State::Blocked)
    return;

  if (collisionTest(mouseCoords)) {
    if (mState == State::Activated) {
      if (currentLevel == 1) {
          mState = State::Unblocked;
          for (const auto &child : mChildren)
            child->block();
      } else --currentLevel;

      subTitle.setString(std::to_string(currentLevel) + "/" + std::to_string(maxLevel));
    }
  }
  if (mState == State::Unblocked)
    subTitle.setString(std::to_string(0) + "/" + std::to_string(maxLevel));
}

void AccumulateNode::loadTexture() {
  sf::String texturePath = getIconPath();
  if (!mTexture.loadFromFile(texturePath)) {
    std::cout << "Error! Can't load file " << texturePath.toAnsiString() << std::endl;
    std::exit(1);
  }
  mSprite.setTexture(mTexture);
  mSprite.setOrigin({width, height});
  mSprite.setPosition(mPosition);
}

bool AccumulateNode::collisionTest(sf::Vector2f mouseCoords) const {
  sf::Vector2f d = mPosition - mouseCoords;
  return (std::abs(d.x) < width ) && (std::abs(d.y) < height );
}

sf::Color AccumulateNode::getCurrentColor() const {
  if (mState == State::Unblocked)
    return sUnlockedColor;
  else if (mState == State::Activated)
    return sActivatedColor;
  return sBlockedColor;
}

void AccumulateNode::draw(sf::RenderWindow &window) const {
  for (const auto &el : mChildren) {
    sfLine connectionLine{mPosition, el->getPosition(), getCurrentColor(), 2};
    connectionLine.draw(window);
    el->draw(window);
  }

  static sf::CircleShape shape(std::max(width, height), 4);
  shape.setOrigin({width, height});
  shape.setFillColor(getCurrentColor());
  shape.setPosition(mPosition);
  shape.setRotation(45);
  window.draw(shape);

  window.draw(mSprite);
  window.draw(subTitle);
}

std::shared_ptr<Node> anotherTree(const sf::Font &font) {
    std::shared_ptr<Node> root{new SwordRectSkillNode({400, 500}, font)};
    root->addChild(std::shared_ptr<Node>{new SwordRectSkillNode({100, 200}, font)});
    return root;
}