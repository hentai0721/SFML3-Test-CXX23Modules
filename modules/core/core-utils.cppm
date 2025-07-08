export module core:utils;
import std;
import sfml;
import :coroutines;

export inline constexpr auto CACHE_LINE_SIZE = std::hardware_destructive_interference_size;

export namespace hentai {

struct FontAnimation {
  float alpha;
  float speedAlpha;
  float speedPos;
};

class ShapeUtils {
public:
  explicit ShapeUtils(sf::RenderWindow &window);
  void create(sf::Vector2f shapeSize, sf::Vector2f shapePos,
              sf::Color shapeColor, sf::Vector2f shapeMove = {});
  void draw();
  void moveShape();
  void setSize(sf::Vector2f shapeSize);
  ~ShapeUtils() = default;

private:
  sf::RenderWindow &window;
  sf::RectangleShape rectBox;
  float moveSpeed;
  float moveRotate;
  sf::Clock clock;
};

template <std::unsigned_integral auto TIME>
Task<std::string> zoned_time_sequence(std::size_t size);

}

