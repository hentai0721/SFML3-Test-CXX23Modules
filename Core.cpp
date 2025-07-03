module Core;

template <std::unsigned_integral auto TIME>

hentai::Task<std::string> zoned_time_sequence(std::size_t size) {
  for (std::size_t i = 0; i <= size; ++i) {
#if !defined(_MSC_VER)
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    char time[32];
    std::strftime(time, sizeof(time), "%Y/%m/%d %H:%M:%S", std::localtime(&t));
    co_yield std::format("{}  [{}]", std::string{time}, i);
#else
    auto local_zone = std::chrono::current_zone();
    std::chrono::zoned_time time{local_zone, std::chrono::system_clock::now()};
    co_yield std::format("{:%Y/%m/%d %X}  [{}]", time, i);
#endif
    co_await hentai::await{std::chrono::milliseconds(TIME)};
    if (i == size) {
      i = 0;
    }
  }
}

void hentai::exec() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  sf::RenderWindow window{sf::VideoMode({800, 600}), L"変態",
                          sf::Style::Default, sf::State::Windowed, settings};
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  sf::Font font;
  if (!font.openFromFile("assets/font/arial.ttf")) {
    window.close();
    return;
  }

  font.setSmooth(true);
  sf::Text text(font);
  text.setCharacterSize(20);
  text.setPosition({240, 50});
  text.setFillColor(sf::Color::White);
  text.setOutlineThickness(1.f);
  text.setLetterSpacing(2.f);
  text.setOutlineColor({255, 41, 35});
  text.setStyle(sf::Text::Style::Underlined);

  sf::Text text1(font);
  text1.setCharacterSize(20);
  text1.setPosition({10, 10});
  text1.setFillColor({56, 84, 160});
  text1.setOutlineThickness(5.f);

  auto test0 = std::make_unique<ShapeUtils>(window);
  auto test1 = std::make_unique<ShapeUtils>(window);

  test0->create({50, 50},
                {window.getSize().x / 2.0f, window.getSize().y / 2.0f},
                {83, 148, 255}, {1000.0f, 15.0f});
  test1->create({50, 200}, {40, 50}, {156, 57, 241});

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_real_distribution<float> dist{3.0f, 150.0f};
  std::bernoulli_distribution rand{0.01f};
  
  std::atomic<bool> running{true};
  auto coro = zoned_time_sequence<30U>(2996);
  std::jthread owo{[&coro, &text, &running] {
    while (running.load(std::memory_order_acquire) && coro.has_value()) {
      text.setString(coro.current_value().value());
    }
  }};
  if (coro.current_value().has_value()) {
    text.setString(coro.current_value().value());
  }
  text1.setString(std::format("size => {}", sizeof(ShapeUtils)));
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::F4 && keyPressed->alt)
              window.close();
      }
    }

    if (rand(rng))
      test0->setSize({dist(rng), dist(rng)});

    window.clear({49, 51, 49});
    // test1->draw();
    test0->draw();
    window.draw(text1);
    window.draw(text);
    test0->moveShape();
    window.display();
  }
  running.store(false, std::memory_order_release);
}

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
    rectBox.rotate(sf::degrees(moveRotate));
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
    rectBox.rotate(sf::degrees(moveRotate));
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
}

} // namespace hentai
