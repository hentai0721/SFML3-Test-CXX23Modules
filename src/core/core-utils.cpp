module core;

namespace hentai {

ShapeUtils::ShapeUtils(sf::RenderWindow &window) : window{window} {}

void ShapeUtils::create(sf::Vector2f shapeSize, sf::Vector2f shapePos,
                        sf::Color shapeColor, sf::Vector2f shapeMove) {
  rectBox.setSize(shapeSize);
  rectBox.setPosition(shapePos);
  rectBox.setFillColor(shapeColor);
  moveSpeed = shapeMove.x;
  moveRotate = shapeMove.y;
}

void ShapeUtils::draw() {
  rectBox.setOrigin({rectBox.getSize().x / 2.0f, rectBox.getSize().y / 2.0f});
  window.draw(rectBox);
}

void ShapeUtils::setSize(sf::Vector2f shapeSize) { rectBox.setSize(shapeSize); }

void ShapeUtils::moveShape() {
  float dt = clock.restart().asSeconds();
  float shapeSize_x = rectBox.getSize().x / 2.0f;
  float shapeSize_y = rectBox.getSize().y / 2.0f;
  auto [x_Pos, y_Pos] = rectBox.getPosition();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
    rectBox.rotate(sf::degrees(-moveRotate));
    rectBox.move({-moveSpeed * dt, 0.0f});
    if (x_Pos < -shapeSize_x) {
      rectBox.setPosition(
          {static_cast<float>(window.getSize().x) + rectBox.getSize().x,
           y_Pos});
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
    rectBox.rotate(sf::degrees(moveRotate));
    rectBox.move({moveSpeed * dt, 0.0f});
    if (x_Pos > window.getSize().x + shapeSize_x) {
      rectBox.setPosition({-rectBox.getSize().x, y_Pos});
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
    rectBox.rotate(sf::degrees(-moveRotate));
    rectBox.move({0.0f, -moveSpeed * dt});
    if (y_Pos < -shapeSize_y) {
      rectBox.setPosition({x_Pos, static_cast<float>(window.getSize().y) +
                                      rectBox.getSize().y});
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
    rectBox.rotate(sf::degrees(moveRotate));
    rectBox.move({0.0f, moveSpeed * dt});
    if (y_Pos > window.getSize().y + shapeSize_y) {
      rectBox.setPosition({x_Pos, -rectBox.getSize().y});
    }
  }
};

} // namespace hentai