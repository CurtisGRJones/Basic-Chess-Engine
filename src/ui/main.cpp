#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    try
    {
        sf::RenderWindow window(sf::VideoMode(200, 200), "Basic Chess Engine");

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.display();
        }
    }
    catch (...)
    {
        std::cout << "An unexpected error occured";
    }

    return 0;
}