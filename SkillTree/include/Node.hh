#ifndef __NODE_HH__
#define __NODE_HH__

#include "sfLine.hh"

class Node {
public:
  enum class State { Blocked, Unblocked, Activated };

  Node(sf::Vector2f &position);
  sf::Vector2f getPosition();
  
  void onMousePressed(sf::Vector2f mouseCoords);
  void addChild(const std::shared_ptr<Node> &child);
  
  void block();
  void unblock();

  virtual bool collisionTest(sf::Vector2f mouseCoords) = 0;
  virtual void draw(sf::RenderWindow &window) const = 0;

protected:
  sf::Vector2f mPosition{0, 0};
  State mState = State::Blocked;

  std::vector<std::shared_ptr<Node>> mChildren{};

  inline static sf::Color sBlockedColor{40, 40, 40};
  inline static sf::Color sUnlockedColor{80, 80, 40};
  inline static sf::Color sActivatedColor{160, 160, 40};
};

#endif