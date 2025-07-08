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
	using ::sf::Music;
	using ::sf::Sound;
	using ::sf::SoundBuffer;
	using ::sf::SoundBufferRecorder;
	using ::sf::SoundFileFactory;
	using ::sf::SoundFileReader;
	using ::sf::SoundFileWriter;
	using ::sf::SoundRecorder;
	using ::sf::SoundSource;
	using ::sf::SoundStream;
	using ::sf::StencilMode;
	using ::sf::StencilValue;
	using ::sf::String;
	using ::sf::TcpListener;
	using ::sf::TcpSocket;
	using ::sf::Transform;
	using ::sf::Transformable;
	using ::sf::U8StringCharTraits;
	using ::sf::UdpSocket;
	using ::sf::Utf;
	using ::sf::Vector3f;
	using ::sf::Vertex;
	using ::sf::VertexArray;
	using ::sf::VertexBuffer;
	using ::sf::View;
	using ::sf::Window;
	using ::sf::WindowBase;
	using ::sf::Angle;
	using ::sf::AudioResource;
	using ::sf::BlendMode;
	using ::sf::CircleShape;
	using ::sf::Context;
	using ::sf::ConvexShape;
	using ::sf::Cursor;
	using ::sf::Drawable;
	using ::sf::Exception;
	using ::sf::FileInputStream;
	using ::sf::Ftp;
	using ::sf::GlResource;
	using ::sf::Glyph;
	using ::sf::Http;
	using ::sf::Image;
	using ::sf::InputSoundFile;
	using ::sf::InputStream;
	using ::sf::IpAddress;
	using ::sf::MemoryInputStream;
	using ::sf::OutputSoundFile;
	using ::sf::Packet;
	using ::sf::Rect;
	using ::sf::RenderStates;
	using ::sf::RenderTarget;
	using ::sf::Shader;
	using ::sf::Shape;
	using ::sf::Socket;
	using ::sf::SocketSelector;
	using ::sf::SoundChannel;
	using ::sf::CoordinateType;
	using ::sf::StencilComparison;
	using ::sf::StencilUpdateOperation;
	using ::sf::swap;
	using ::sf::radians;
	using ::sf::err;
	using ::sf::sleep;
}

export namespace sf::Keyboard {
	using ::sf::Keyboard::isKeyPressed;
	using ::sf::Keyboard::Scancode;
	using ::sf::Keyboard::Key;
	using ::sf::Keyboard::Scan;
	using ::sf::Keyboard::localize;
	using ::sf::Keyboard::delocalize;
	using ::sf::Keyboard::getDescription;
	using ::sf::Keyboard::setVirtualKeyboardVisible;
}

export namespace sf::Style {
	using ::sf::Style::Default;
	using ::sf::Style::None;
	using ::sf::Style::Titlebar;
	using ::sf::Style::Resize;
	using ::sf::Style::Close;
}

export namespace sf::Mouse {
	using ::sf::Mouse::isButtonPressed;
	using ::sf::Mouse::Button;
	using ::sf::Mouse::Wheel;
	using ::sf::Mouse::getPosition;
	using ::sf::Mouse::setPosition;
}

export namespace sf::Vulkan {
	using ::sf::Vulkan::isAvailable;
	using ::sf::Vulkan::getGraphicsRequiredInstanceExtensions;
	using ::sf::Vulkan::getFunction;
}

export namespace sf::Clipboard {
	using ::sf::Clipboard::getString;
	using ::sf::Clipboard::setString;
}

export namespace sf::Joystick {
	using ::sf::Joystick::Identification;
	using ::sf::Joystick::Axis;
	using ::sf::Joystick::isConnected;
	using ::sf::Joystick::getButtonCount;
	using ::sf::Joystick::hasAxis;
	using ::sf::Joystick::isButtonPressed;
	using ::sf::Joystick::getAxisPosition;
	using ::sf::Joystick::getIdentification;
	using ::sf::Joystick::update;
}

export namespace sf::Listener {
	using ::sf::Listener::setGlobalVolume;
	using ::sf::Listener::getGlobalVolume;
	using ::sf::Listener::setPosition;
	using ::sf::Listener::setDirection;
	using ::sf::Listener::getDirection;
	using ::sf::Listener::setVelocity;
	using ::sf::Listener::getVelocity;
	using ::sf::Listener::setCone;
	using ::sf::Listener::getCone;
	using ::sf::Listener::setUpVector;
	using ::sf::Listener::getUpVector;
	using ::sf::Listener::Cone;
}

export namespace sf::PlaybackDevice {
	using ::sf::PlaybackDevice::getAvailableDevices;
	using ::sf::PlaybackDevice::getDefaultDevice;
	using ::sf::PlaybackDevice::setDevice;
	using ::sf::PlaybackDevice::getDevice;
}

export namespace sf::Sensor {
	using ::sf::Sensor::Type;
	using ::sf::Sensor::isAvailable;
	using ::sf::Sensor::setEnabled;
	using ::sf::Sensor::getValue;
}

export namespace sf::Touch {
	using ::sf::Touch::isDown;
	using ::sf::Touch::getPosition;
}

export namespace sf::Glsl {
	using ::sf::Glsl::Vec2;
	using ::sf::Glsl::Ivec2;
	using ::sf::Glsl::Bvec2;
	using ::sf::Glsl::Vec3;
	using ::sf::Glsl::Ivec3;
	using ::sf::Glsl::Bvec3;
	using ::sf::Glsl::Vec4;
	using ::sf::Glsl::Ivec4;
	using ::sf::Glsl::Bvec4;
	using ::sf::Glsl::Mat3;
	using ::sf::Glsl::Mat4;
}