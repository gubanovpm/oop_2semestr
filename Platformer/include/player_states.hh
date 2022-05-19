#ifndef __player_states_hh__
#define __player_states_hh__

#include "animation.hh"
#include "player.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Player;

class PlayerState {
public:
  PlayerState();
  void setSprite(sf::Sprite &sprite, bool isFacedRight);

  virtual void handleEvents(Player *player, const sf::Event &event) = 0;
  virtual void update(Player *player, float dt);

  virtual void hook(Player *player) = 0;
  virtual void attacked(Player *player) = 0;
  virtual void startFalling(Player *player) = 0;
  virtual void hitGround(Player *player) = 0;
  virtual ~PlayerState();

  void jump(Player *player, float jumpingVelocity);

protected:
  Animation mAnimation;
  static constexpr float kJumpingVelocity = 1500;
  static constexpr float kSubJumpingVelocity = 1000;
};

class Idle : public PlayerState {
public:
  Idle(Player *player);

  void update(Player *player, float dt);
  void handleEvents(Player *player, const sf::Event &event);
  void hook(Player *player);
  void attacked(Player *player);
  void startFalling(Player *player);
  void hitGround(Player *player);

private:
};

class Running : public PlayerState {
public:
  Running(Player *player);
  void update(Player *player, float dt);
  void handleEvents(Player *player, const sf::Event &event);
  void hook(Player *player);
  void attacked(Player *player);
  void startFalling(Player *player);
  void hitGround(Player *player);

private:
  float mRunningSpeed;
};

class Sliding : public PlayerState {

public:
  Sliding(Player *player);
  void update(Player *player, float dt);
  void handleEvents(Player *player, const sf::Event &event);
  void hook(Player *player);
  void attacked(Player *player);
  void startFalling(Player *player);
  void hitGround(Player *player);

private:
  float mCurrentTime;
  static constexpr float kSlidingTime = 0.50;
  static constexpr float kVelocityMultiplier = 2.5;
  static constexpr float kVelocityDecay = 0.99;
};

class Falling : public PlayerState {
public:
  Falling(Player *player);
  void update(Player *player, float dt);
  void handleEvents(Player *player, const sf::Event &event);
  void hook(Player *player);
  void attacked(Player *player);
  void startFalling(Player *player);
  void hitGround(Player *player);

private:
  unsigned jumpCount = 0;
  static constexpr float kHorizontalVelocity = 800;
};

class Hooked : public PlayerState {
public:
  static constexpr float kMaxHookOffset = 15;

  Hooked(Player *player);
  void update(Player *player, float dt);
  void handleEvents(Player *player, const sf::Event &event);
  void hook(Player *player);
  void attacked(Player *player);
  void startFalling(Player *player);
  void hitGround(Player *player);
};

#endif