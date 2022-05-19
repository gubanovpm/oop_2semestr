#include "player_states.hpp"
#include "animation.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

using std::cout, std::endl;

PlayerState::PlayerState() {}

void PlayerState::update(Player *player, float dt) { mAnimation.update(dt); }

void PlayerState::setSprite(sf::Sprite &sprite, bool isFacedRight) {
  mAnimation.updateSprite(sprite);

  if (!isFacedRight) {
    sprite.setScale({-4, 4});
  } else {
    sprite.setScale({4, 4});
  }
}

void PlayerState::jump(Player *player) {
  player->mPosition.y -= 1;
  player->mVelocity.y = -kJumpingVelocity;
  startFalling(player);
}

PlayerState::~PlayerState() {}

Idle::Idle(Player *player) {
  player->mVelocity = {0, 0};
  mAnimation = Animation();
  mAnimation.setAnimationSpeed(6);
  mAnimation.addTextureRect({14, 6, 21, 30});
  mAnimation.addTextureRect({64, 6, 21, 30});
  mAnimation.addTextureRect({114, 6, 21, 30});
  mAnimation.addTextureRect({164, 6, 21, 30});

  player->mCollisionRect = sf::FloatRect(-40, -60, 80, 120);

  cout << "Creating Idle state" << endl;
}

void Idle::attacked(Player *player) {}

void Idle::hook(Player *player) {}

void Idle::update(Player *player, float dt) {
  mAnimation.update(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player->setState(new Running(player));
  }
}

void Idle::handleEvents(Player *player, const sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Left ||
        event.key.code == sf::Keyboard::Right) {
      player->setState(new Running(player));
    }

    else if (event.key.code == sf::Keyboard::Space) {
      jump(player);
    }
  }
}

void Idle::startFalling(Player *player) {
  player->setState(new Falling(player));
}

void Idle::hitGround(Player *player) {}

Running::Running(Player *player) : PlayerState() {
  mRunningSpeed = 900;
  mAnimation = Animation();
  mAnimation.setAnimationSpeed(12);
  mAnimation.addTextureRect({67, 45, 20, 27});
  mAnimation.addTextureRect({116, 46, 20, 27});
  mAnimation.addTextureRect({166, 48, 20, 27});
  mAnimation.addTextureRect({217, 45, 20, 27});
  mAnimation.addTextureRect({266, 46, 20, 27});
  mAnimation.addTextureRect({316, 48, 20, 27});

  player->mCollisionRect = sf::FloatRect(-40, -60, 80, 120);

  cout << "Creating Running state" << endl;
}

void Running::hook(Player *player) {}

void Running::attacked(Player *player) {}

void Running::update(Player *player, float dt) {
  mAnimation.update(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player->mVelocity.x = -mRunningSpeed;
    player->mIsFacedRight = false;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player->mVelocity.x = mRunningSpeed;
    player->mIsFacedRight = true;
  }
}

void Running::handleEvents(Player *player, const sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Space) {
      jump(player);
      return;
    }

    if (event.key.code == sf::Keyboard::LShift) {
      player->setState(new Sliding(player));
    }
  }
  if (event.type == sf::Event::KeyReleased) {
    if (event.key.code == sf::Keyboard::Left &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player->setState(new Idle(player));
      player->mVelocity.x = 0;
    }

    if (event.key.code == sf::Keyboard::Right &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player->setState(new Idle(player));
      player->mVelocity.x = 0;
    }
  }
}

void Running::startFalling(Player *player) {
  player->setState(new Falling(player));
}

void Running::hitGround(Player *player) {}

Sliding::Sliding(Player *player) : PlayerState() {
  player->mVelocity.x *= kVelocityMultiplier;

  mAnimation = Animation(Animation::AnimationType::OneIteration);
  mAnimation.setAnimationSpeed(10);
  mAnimation.addTextureRect({155, 119, 34, 28});
  mAnimation.addTextureRect({205, 119, 34, 28});
  mAnimation.addTextureRect({255, 119, 34, 28});
  mAnimation.addTextureRect({307, 119, 34, 28});
  mAnimation.addTextureRect({9, 156, 34, 28});

  player->mCollisionRect = sf::FloatRect(-80, -20, 160, 80);
  mCurrentTime = kSlidingTime;

  cout << "Creating Sliding state" << endl;
}

void Sliding::hook(Player *player) {}

void Sliding::attacked(Player *player) {}

void Sliding::update(Player *player, float dt) {
  mAnimation.update(dt);
  player->mVelocity.x *= kVelocityDecay;
  mCurrentTime -= dt;
  if (mCurrentTime < 0 && player->mIsColliding) {
    player->setState(new Idle(player));
    return;
  }
}
void Sliding::handleEvents(Player *player, const sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Left ||
        event.key.code == sf::Keyboard::Right)
      player->setState(new Running(player));

    if (event.key.code == sf::Keyboard::Space && player->mIsColliding) {
      jump(player);
      player->setState(new Falling(player));
    }
  }
}

void Sliding::startFalling(Player *player) {}

void Sliding::hitGround(Player *player) {}

Falling::Falling(Player *player) : PlayerState() {
  mAnimation = Animation();
  mAnimation.setAnimationSpeed(12);
  mAnimation.addTextureRect({321, 155, 15, 26});

  player->mCollisionRect = sf::FloatRect(-40, -60, 80, 120);

  cout << "Creating Falling state" << endl;
}

void Falling::hook(Player *player) { player->setState(new Hooked(player)); }

void Falling::attacked(Player *player) {}

void Falling::update(Player *player, float dt) {
  mAnimation.update(dt);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    player->mVelocity.x = -kHorizontalVelocity;
    player->mIsFacedRight = false;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    player->mVelocity.x = kHorizontalVelocity;
    player->mIsFacedRight = true;
  }
}

void Falling::handleEvents(Player *player, const sf::Event &event) {}

void Falling::startFalling(Player *player) {}

void Falling::hitGround(Player *player) { player->setState(new Idle(player)); }

Hooked::Hooked(Player *player) : PlayerState() {
  mAnimation = Animation(Animation::AnimationType::OneIteration);
  mAnimation.setAnimationSpeed(12);
  mAnimation.addTextureRect({70, 151, 16, 34});
  mAnimation.addTextureRect({119, 151, 16, 34});
  mAnimation.addTextureRect({169, 151, 16, 34});
  mAnimation.addTextureRect({219, 151, 16, 34});

  player->mCollisionRect = sf::FloatRect(-40, -60, 80, 120);

  cout << "Creating Hooked state" << endl;
}

void Hooked::hook(Player *player) {}

void Hooked::attacked(Player *player) {}

void Hooked::update(Player *player, float dt) {
  player->mVelocity = {0, 0};
  mAnimation.update(dt);
}

void Hooked::handleEvents(Player *player, const sf::Event &event) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Space)
      jump(player);

    else if (event.key.code == sf::Keyboard::Down) {
      player->mVelocity.x = player->mIsFacedRight ? -100 : 100;
      player->setState(new Falling(player));
    }
  }
}

void Hooked::startFalling(Player *player) {
  player->setState(new Falling(player));
}

void Hooked::hitGround(Player *player) { player->setState(new Idle(player)); }
