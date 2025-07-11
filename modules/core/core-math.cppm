export module core:math;
import std;

export namespace MATH {

inline constexpr auto E32 = std::numbers::e_v<float>;
inline constexpr auto E64 = std::numbers::e_v<double>;
inline constexpr auto PI32 = std::numbers::pi_v<float>;
inline constexpr auto PI64 = std::numbers::pi_v<double>;
inline constexpr auto INV_PI32 = std::numbers::inv_pi_v<float>;
inline constexpr auto INV_PI64 = std::numbers::inv_pi_v<double>;
inline constexpr auto INV_SQRTPI32 = std::numbers::inv_sqrtpi_v<float>;
inline constexpr auto INV_SQRTPI64 = std::numbers::inv_sqrtpi_v<double>;
inline constexpr auto LN2_32 = std::numbers::ln2_v<float>;
inline constexpr auto LN2_64 = std::numbers::ln2_v<double>;
inline constexpr auto LN10_32 = std::numbers::ln10_v<float>;
inline constexpr auto LN10_64 = std::numbers::ln10_v<double>;
inline constexpr auto SQRT2_32 = std::numbers::sqrt2_v<float>;
inline constexpr auto SQRT2_64 = std::numbers::sqrt2_v<double>;
inline constexpr auto SQRT3_32 = std::numbers::sqrt3_v<float>;
inline constexpr auto SQRT3_64 = std::numbers::sqrt3_v<double>;
inline constexpr auto INV_SQRT3_32 = std::numbers::inv_sqrt3_v<float>;
inline constexpr auto INV_SQRT3_64 = std::numbers::inv_sqrt3_v<double>;
inline constexpr auto LOG2E32 = std::numbers::log2e_v<float>;
inline constexpr auto LOG2E64 = std::numbers::log2e_v<double>;
inline constexpr auto LOG10E32 = std::numbers::log10e_v<float>;
inline constexpr auto LOG10E64 = std::numbers::log10e_v<double>;
inline constexpr auto EGAMMA32 = std::numbers::egamma_v<float>;
inline constexpr auto EGAMMA64 = std::numbers::egamma_v<double>;
inline constexpr auto PHI32 = std::numbers::phi_v<float>;
inline constexpr auto PHI64 = std::numbers::phi_v<double>;

} // namespace MATH

export namespace consteval_context {
constexpr auto fib(std::integral auto n) {
  if consteval {
    if (n <= 1)
      return n;
    return fib(n - 1) + fib(n - 2);
  } else {
    std::vector<int> fib{0, 1};
    while (fib.size() <= n) {
      fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }
    return fib[n];
  }
}

} // namespace consteval_context

export namespace math {

consteval float to_radians(float degrees) {
  return degrees * MATH::PI32 / 180.0f;
}
consteval float to_degrees(float radians) {
  return radians * 180.0f / MATH::PI32;
}

} // namespace math