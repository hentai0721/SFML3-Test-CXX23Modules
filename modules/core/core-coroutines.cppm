export module core:coroutines;
import std;
import sfml;
import :concepts;

export namespace hentai {

template <hasChrono T> class await {
public:
  consteval explicit await(T _setTime) noexcept : setTime(_setTime) {}
  constexpr bool await_ready() noexcept { return false; }
  constexpr void await_suspend(std::coroutine_handle<> handle) noexcept {
    std::this_thread::sleep_for(setTime);
    if (handle && !handle.done())
      handle.resume();
  }
  constexpr void await_resume() noexcept {}

private:
  T setTime;
};

template <typename T> class Task {
public:
  class promise_type {
  public:
    constexpr static auto get_return_object_on_allocation_failure() {
      return Task{nullptr};
    }
    constexpr auto get_return_object() {
      return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    [[noreturn]] void unhandled_exception() { std::terminate(); }

    constexpr std::suspend_always yield_value(auto &&value) noexcept {
      if(current_value.has_value()) [[likely]] {
        current_value = std::forward<decltype(value)>(value);
      } else [[unlikely]] {
        current_value.emplace( std::forward<decltype(value)>(value) );
      }
      return {};
    }

    constexpr auto await_transform(hasAwait auto time) noexcept {
      return time;
    }

    constexpr void return_void() noexcept {}

  private:
    friend class Task<T>;
    std::optional<T> current_value;
  };

  Task(const Task &) = delete;
  Task &operator=(const Task &) = delete;

  Task(Task &&other) noexcept : handle(other.handle) { other.handle = nullptr; }

  Task &operator=(Task &&other) noexcept {
    if (this != &other) {
      if (handle)
        handle.destroy();
      handle = other.handle;
      other.handle = nullptr;
    }
    return *this;
  }

  constexpr explicit operator bool() const noexcept {
    if (handle && !handle.done()) [[likely]] {
      handle.resume();
      return !handle.done();
    } else [[unlikely]] {
      return false;
    }
  }

  T& operator*() const noexcept {
    return *handle.promise().current_value;
  }

  explicit Task(std::coroutine_handle<promise_type> _handle)
      : handle(_handle) {}
  ~Task() {
    if (handle)
      handle.destroy();
  }

  [[nodiscard("hentai!!!")]] auto has_value() -> bool {
    if (handle && !handle.done()) [[likely]] {
      handle.resume();
      return !handle.done();
    } else [[unlikely]] {
      return false;
    }
  }

  [[nodiscard("hentai!!!")]] auto current_value() -> std::optional<T> {
    if (handle && !handle.done()) [[likely]] {
      return handle.promise().current_value;
    } else [[unlikely]] {
      return std::nullopt;
    }
  }

  class iterator {
  public:
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

    explicit iterator(std::coroutine_handle<promise_type> _handle)
        : handle(_handle) {}
    reference operator*() const { return *handle.promise().current_value; }
    pointer operator->() const { return &*handle.promise().current_value; }

    iterator &operator++() {
      if (handle && !handle.done())
        handle.resume();
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const iterator &it, std::default_sentinel_t) {
      return !it.handle || it.handle.done();
    }

  private:
    std::coroutine_handle<promise_type> handle;
  };

  iterator begin() {
    if (handle && !handle.done()) {
      handle.resume();
      return iterator{handle};
    } else {
      return iterator{nullptr};
    }
  }

  std::default_sentinel_t end() { return {}; }

private:
  std::coroutine_handle<promise_type> handle;
};

} // namespace hentai
