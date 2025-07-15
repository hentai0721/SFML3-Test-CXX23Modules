module;
#if defined(_WIN32)
#  if defined(__clang__) || defined(__GNUC__)
#    define EXPORT_API __attribute__((dllexport))
#  else
#     define EXPORT_API __declspec(dllexport)
#  endif
#else
#    define EXPORT_API __attribute__((visibility("default")))
#endif
export module core;
export import std;
export import sfml;
export import :concepts;
export import :math;
export import :ui;
export import :utils;
export import :coroutines;

export extern "C++" {
  namespace hentai {
     EXPORT_API void exec();
  }
}





