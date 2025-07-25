module core;


template <std::unsigned_integral auto TIME>

hentai::Task<std::string> hentai::zoned_time_sequence(std::size_t size) {
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
    co_await hentai::await{std::chrono::milliseconds{TIME}};
    if (i == size) {
      i = 0;
    }
  }
}



extern "C" void hentai::exec() {
  sf::ContextSettings settings;
  settings.antiAliasingLevel = 8;
  sf::RenderWindow window{sf::VideoMode({800, 600}), L"変態",
                          sf::Style::Default, sf::State::Windowed, settings};
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  sf::Font font;
  if (!font.openFromFile("assets/font/arial.ttf"))
    return;

  font.setSmooth(true);
  sf::Text text(font);
  text.setCharacterSize(20);
  text.setPosition({240, 50});
  text.setFillColor(sf::Color::White);
  text.setOutlineThickness(1.f);
  text.setLetterSpacing(2.f);
  text.setOutlineColor({255, 41, 35});
  text.setStyle(sf::Text::Style::Underlined);

  sf::Text text0(font);
  text0.setCharacterSize(20);
  text0.setPosition({240, 100});
  text0.setFillColor(sf::Color::White);
  text0.setOutlineThickness(1.f);
  text0.setLetterSpacing(2.f);
  text0.setOutlineColor({255, 41, 35});
  text0.setStyle(sf::Text::Style::Underlined);

  sf::Text text1(font);
  text1.setCharacterSize(20);
  text1.setPosition({10, 10});
  text1.setFillColor({56, 84, 160});
  text1.setOutlineThickness(5.f);

  sf::Text text2(font);
  text2.setCharacterSize(20);
  text2.setPosition({240, 500});
  text2.setFillColor(sf::Color::White);
  text2.setOutlineThickness(1.f);
  text2.setLetterSpacing(2.f);
  text2.setOutlineColor({255, 41, 35});
  text2.setStyle(sf::Text::Style::Underlined);

  auto test0 = std::make_unique<ShapeUtils>(window);
  auto test1 = std::make_unique<ShapeUtils>(window);

  test0->create({50, 50},
                {static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f},
                {83, 148, 255}, {1000.0f, 15.0f});
  test1->create({50, 200}, {40, 50}, {156, 57, 241});

  std::random_device rd;
  std::mt19937 rng{rd()};
  std::uniform_real_distribution<float> dist{3.0f, 150.0f};
  std::bernoulli_distribution rand{0.01f};

  alignas(CACHE_LINE_SIZE) std::atomic<bool> running{true};
  auto coro = hentai::zoned_time_sequence<30U>(2996);
  std::jthread owo{[&coro, &text, &running] {
    while (running.load(std::memory_order_acquire) && coro.has_value()) {
      text.setString(*coro.current_value());
    }
  }};

  auto coro0 = hentai::zoned_time_sequence<10U>(2996);
  std::jthread uwu{[&coro0, &text0](std::stop_token running) {
    while (!running.stop_requested() && coro0.has_value()) {
      text0.setString(*coro0.current_value());
    }
  }};

  auto coro1 = hentai::zoned_time_sequence<10U>(2996);
  std::jthread ovo{[&coro1, &text2](std::stop_token running) {
    while (!running.stop_requested() && coro1.has_value()) {
      text2.setString(*coro1.current_value());
    }
  }};

  hentai::FontAnimation fontAnim{255.0f, 20.0f, 80.0f};
  sf::Clock clock;
  text1.setString(std::format("size => {}", sizeof(ShapeUtils)));
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->scancode == sf::Keyboard::Scancode::F4 &&
            keyPressed->alt)
          window.close();
      }
    }

    if (rand(rng))
      test0->setSize({dist(rng), dist(rng)});
    float dt = clock.restart().asSeconds();
    sf::Vector2f pos = text2.getPosition();
    if (fontAnim.alpha > 0) {
      fontAnim.alpha -= (255.0f - fontAnim.speedAlpha * dt) / 30.0f;
      if (fontAnim.alpha < 0) {
        fontAnim.alpha = 0;
      }
      text2.setFillColor(
          {255, 255, 255, static_cast<std::uint8_t>(fontAnim.alpha)});
      text2.setOutlineColor(
          {255, 41, 35, static_cast<std::uint8_t>(fontAnim.alpha)});
      text2.setPosition({pos.x, pos.y - fontAnim.speedPos * dt});
    } else {
      fontAnim.alpha = 255.0f;
      text2.setPosition({pos.x, 500});
    }

    window.clear({49, 51, 49});
    // test1->draw();
    test0->draw();
    window.draw(text2);
    window.draw(text1);
    window.draw(text0);
    window.draw(text);
    test0->moveShape();
    window.display();
  }
  running.store(false, std::memory_order_release);
}


