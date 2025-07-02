module;
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
export module sfml;

export namespace sf {
	using ::sf::RenderWindow;
	using ::sf::VideoMode;
	using ::sf::Event;
	using ::sf::Color;
	using ::sf::RectangleShape;
	using ::sf::RenderTexture;
	using ::sf::Texture;
	using ::sf::Sprite;
	using ::sf::Clock;
	using ::sf::Time;
	using ::sf::degrees;
	using ::sf::ContextSettings;
	using ::sf::State;
	using ::sf::Vector2f;
	using ::sf::Font;
	using ::sf::Text;
}

export namespace sf::Keyboard {
	using ::sf::Keyboard::isKeyPressed;
	using ::sf::Keyboard::Scancode;
	using ::sf::Keyboard::Key;
}

export namespace sf::Style {
	using ::sf::Style::Default;
	using ::sf::Style::None;
	using ::sf::Style::Titlebar;
	using ::sf::Style::Resize;
	using ::sf::Style::Close;
}