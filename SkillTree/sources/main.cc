#include "HitNode.hh"
#include "AccumulateNode.hh"

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(1000, 800), "Skill Tree",
                          sf::Style::Close, settings);
  window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("../sources/consolas.ttf")) {
      std::cout << "Can't load font" << std::endl;
  }

  std::shared_ptr<Node> root = anotherTree(font);
  root->unblock();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouseCoords =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (event.mouseButton.button == sf::Mouse::Left)
          root->onMousePressed(mouseCoords, Node::MouseState::LeftButton);
        if (event.mouseButton.button == sf::Mouse::Right)
          root->onMousePressed(mouseCoords, Node::MouseState::RightButton);
      }
    }

    window.clear(sf::Color::Black);
    root->draw(window);
    window.display();
  }

  return 0;
}