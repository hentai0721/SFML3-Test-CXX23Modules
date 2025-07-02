export module Core;
export import sfml;
export import std;
export import :concepts;

export namespace hentai {
void exec();

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
template <typename T> class Task {
public:
  class promise_type {
  public:
    Task get_return_object() {
      return std::coroutine_handle<promise_type>::from_promise(*this);
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void unhandled_exception() { std::terminate(); }
    std::suspend_always yield_value(T &&value) noexcept {
      current_value = std::forward<T>(value);
      return {};
    }
    void return_void() {}


  private:
    friend class Task<T>;
    std::optional<T> current_value;
  };

  Task(std::coroutine_handle<promise_type> _handle) : handle(_handle) {}
  ~Task() {
    if (handle)
      handle.destroy();
  }

  auto has_value() -> bool {
    handle.resume();
    return !handle.done();
  }
  [[nodiscard("hentai!")]] auto current_value() -> std::optional<T> {
    if (!handle.done()) {
      return handle.promise().current_value;
    } else {
      return std::nullopt;
    }
  }

private:
  std::coroutine_handle<promise_type> handle;
};

template <hasChrono T>

class await {
public:
  consteval explicit await(T _setTime) noexcept : setTime(_setTime) {}
  bool await_ready() noexcept { return false; }
  void await_suspend(std::coroutine_handle<> handle) noexcept {
    std::this_thread::sleep_for(setTime);
    if (!handle.done())
      handle.resume();
  }
  void await_resume() noexcept {}

private:
  T setTime;
};

}

module : private;

template <std::unsigned_integral auto TIME>
hentai::Task<std::string> zoned_time_sequence(std::size_t size);