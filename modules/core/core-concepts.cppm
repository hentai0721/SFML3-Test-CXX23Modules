export module core:concepts;
import std;

export template <typename T>

concept hasMap = requires(T obj, typename T::key_type key) {
  typename T::key_type;
  typename T::mapped_type;
  { obj.begin() } -> std::same_as<typename T::iterator>;
  { obj.end() } -> std::same_as<typename T::iterator>;
  { obj.find(key) } -> std::same_as<typename T::iterator>;
};

export template <typename T>

concept hasChrono = requires(T t) {
  typename T::rep;
  typename T::period;
  { t.count() } -> std::same_as<typename T::rep>;
};

export template <typename T>

concept hasAwait = requires(T coro, std::coroutine_handle<> handle) {
  { coro.await_ready() } -> std::same_as<bool>;
  { coro.await_suspend(handle) };
  { coro.await_resume() };
};