module Core;


void hentai::exec()
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode({800,600}), L"変態", sf::Style::Default, sf::State::Windowed, settings);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::RectangleShape rectBox{{50,50}};
	rectBox.setPosition({400,300});
	rectBox.setFillColor({83,148,255});
	rectBox.setOrigin({rectBox.getSize().x / 2.0f,rectBox.getSize().y / 2.0f});
	rectBox.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f});
	constexpr float moveSpeed = 1000.0f;
	constexpr float moveRotate = 15.0f;
	constexpr auto pi = std::numbers::pi_v<float>;
	float shapeSize_x = rectBox.getSize().x / 2.0f;
	float shapeSize_y = rectBox.getSize().y / 2.0f;

	sf::Clock cl;
	while (window.isOpen())
	{
		float dt = cl.restart().asSeconds();
	    while (const std::optional event = window.pollEvent())
	    {
	        if (event->is<sf::Event::Closed>())
	        {
	            window.close();
	        }
	        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
	        {
	            if (keyPressed->scancode == sf::Keyboard::Scancode::LAlt && 
	            	keyPressed->scancode == sf::Keyboard::Scancode::F4)
	                window.close();
	        }
	    }


	    auto [x_Pos,y_Pos] = rectBox.getPosition();

	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	    {
	    	rectBox.rotate(sf::degrees(moveRotate));
	    	rectBox.move({-moveSpeed * dt, 0.0f});
	    	if (x_Pos < -shapeSize_x)
	    	{
	    		rectBox.setPosition({(float)window.getSize().x + rectBox.getSize().x, y_Pos});
	    	}
	    }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	    {
	    	rectBox.rotate(sf::degrees(moveRotate));
	    	rectBox.move({moveSpeed * dt, 0.0f});
	    	if (x_Pos > window.getSize().x + shapeSize_x)
	    	{
	    		rectBox.setPosition({-rectBox.getSize().x, y_Pos});
	    	}
	    }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
	    {
	    	rectBox.rotate(sf::degrees(moveRotate));
	    	rectBox.move({0.0f, -moveSpeed * dt});
	    	if (y_Pos < -shapeSize_y)
	    	{
	    		rectBox.setPosition({x_Pos, (float)window.getSize().y + rectBox.getSize().y});
	    	}
	    }
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
	    {
	    	rectBox.rotate(sf::degrees(moveRotate));
	    	rectBox.move({0.0f, moveSpeed * dt});
	    	if (y_Pos > window.getSize().y + shapeSize_y)
	    	{
	    		rectBox.setPosition({x_Pos, (float)-rectBox.getSize().y});
	    	}
	    }

	    window.clear({49,51,49});
	    window.draw(rectBox);
	    window.display();
	}
}