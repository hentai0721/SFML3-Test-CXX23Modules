PCM := $(patsubst modules/sfml/%.cppm,release/%.pcm,$(foreach mod,$(wildcard modules/sfml/*.cppm),$(if $(findstring sfml,$(mod)),$(mod)))) .WAIT
PCM += $(patsubst modules/core/%.cppm,release/%.pcm,$(foreach mod,$(wildcard modules/core/*.cppm),$(if $(findstring core-concepts,$(mod)),$(mod)))) .WAIT
PCM += $(patsubst modules/core/%.cppm,release/%.pcm,$(foreach mod,$(wildcard modules/core/*.cppm),$(if $(findstring core-coroutines,$(mod)),$(mod)))) .WAIT

PCM += $(patsubst modules/core/%.cppm,release/%.pcm,$(foreach mod,$(wildcard modules/core/*.cppm),$(if $(findstring -,$(mod)),$(mod))))
PCX := $(patsubst modules/core/%.cppm,release/%.pcm,$(foreach mod,$(wildcard modules/core/*.cppm),$(if $(findstring -,$(mod)),,$(mod))))

OBJ := $(patsubst modules/sfml/%.cppm,release/%.pcm.o,$(wildcard modules/sfml/*.cppm)) $(patsubst modules/core/%.cppm,release/%.pcm.o,$(wildcard modules/core/*.cppm)) $(patsubst src/core/%.cpp,release/%.cpp.o,$(wildcard src/core/*.cpp)) $(patsubst src/%.cpp,release/%.cpp.o,$(wildcard src/*.cpp))

ifeq ($(shell xxd -l 2 -p $$(command -v make)),4d5a)
CXX = clang++
CXXFLAGS = -DSFML_STATIC -O3 -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -fprebuilt-module-path=$(RELEASE_PATH) --precompile
CXXFLAGS_P = -O3 -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -fprebuilt-module-path=$(RELEASE_PATH)
LDFLAGS = -static -Wl,-s,--no-insert-timestamp -mwindows
TARGET = release/hentai.exe
STDCPPM = /clang64/share/libc++/v1/std.cppm
#STDCPPM = $(shell llvm-config --prefix | awk "{print \$$1 \"/share/libc++/v1/std.cppm\"}")
LIBS = -lfreetype -lgdi32 -lopengl32 -lwinmm -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s
endif

ifeq ($(shell xxd -l 4 -p $$(command -v make)),7f454c46)
CXX = clang++
CXXFLAGS = -stdlib=libc++ -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -O3 -std=c++23 -fprebuilt-module-path=$(RELEASE_PATH) --precompile
CXXFLAGS_P = -O3 -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -fprebuilt-module-path=$(RELEASE_PATH)
LDFLAGS = -Wl,-s -stdlib=libc++ -fuse-ld=lld 
TARGET = release/hentai
STDCPPM = /usr/share/libc++/v1/std.cppm
#STDCPPM = $(shell llvm-config-21 --prefix | awk "{print \$$1 \"/share/libc++/v1/std.cppm\"}")
LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
endif

ifeq ($(shell xxd -l 4 -p $$(command -v gmake || printf /dev/null)),cffaedfe)
CXX = /opt/homebrew/opt/llvm/bin/clang++
CXXFLAGS = -I/opt/homebrew/include -O3 -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -fprebuilt-module-path=$(RELEASE_PATH) --precompile
CXXFLAGS_P = -O3 -std=c++23 -Wall -Wextra -Wpedantic -Wreturn-type -Wconversion -fprebuilt-module-path=$(RELEASE_PATH)
LDFLAGS = -Wl,-s -L/opt/homebrew/lib -fuse-ld=lld
TARGET = release/hentai
STDCPPM = /opt/homebrew/opt/llvm/share/libc++/v1/std.cppm
LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
endif

RELEASE_PATH = release/

release: $(RELEASE_PATH) .WAIT release/std.pcm .WAIT release/std.pcm.o $(TARGET)

release/std.pcm: $(STDCPPM)
	@$(CXX) -std=c++23 -O3 -stdlib=libc++ -Wno-reserved-module-identifier --precompile -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'
release/std.pcm.o: release/std.pcm
	@$(CXX) $(CXXFLAGS_P) -c -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'

$(TARGET): $(PCM) .WAIT $(PCX) .WAIT $(OBJ)
	@$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LIBS)
	@printf '\033[38;2;100;251;109mリンク中 $(OBJ) -> $@\033[0m\n'
release/%.pcm: modules/sfml/%.cppm
	@$(CXX) $(CXXFLAGS) -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'
release/%.pcm: modules/core/%.cppm
	@$(CXX) $(CXXFLAGS) -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'
release/%.pcm.o: release/%.pcm
	@$(CXX) $(CXXFLAGS_P) -c -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'
release/%.cpp.o: src/core/%.cpp
	@$(CXX) $(CXXFLAGS_P) -c -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'
release/%.cpp.o: src/%.cpp
	@$(CXX) $(CXXFLAGS_P) -c -o $@ $<
	@printf '\033[38;2;109;100;251mコンパイル中 $< -> $@\033[0m\n'

$(RELEASE_PATH):
	@mkdir -p release

run: release
	./$(TARGET)

clean:
	@rm -rf release/
	@printf '\033[38;2;255;83;83mクリア完了\033[0m\n'

.PHONY: clean release run