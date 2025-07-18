module;
#if defined(_WIN32)
#  if defined(__clang__) || defined(__GNUC__)
#    define HENTAI_API __attribute__((dllexport))
#    define HENTAI_ABI __cdecl
#  else
#     define HENTAI_API __declspec(dllexport)
#     define HENTAI_ABI __cdecl
#  endif
#else
#    define HENTAI_API __attribute__((visibility("default")))
#    define HENTAI_ABI
#endif

export module core;
export import std;
export import sfml;
export import :concepts;
export import :math;
export import :ui;
export import :utils;
export import :coroutines;

export namespace hentai {
  extern "C" {
    HENTAI_API void HENTAI_ABI exec();
  }
}