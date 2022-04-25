#include "HitNode.hh"

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(1000, 800), "Skill Tree",
                          sf::Style::Close, settings);
  window.setFramerateLimit(60);

  std::shared_ptr<Node> root = createSkillTree();
  root->unblock();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseCoords =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        root->onMousePressed(mouseCoords);
      }
    }

    window.clear(sf::Color::Black);
    root->draw(window);
    window.display();
  }

  return 0;
}