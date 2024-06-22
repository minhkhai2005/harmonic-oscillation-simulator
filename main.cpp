#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include "graph.hpp"

int main(int argc, char *argv[])
{
 
  double x, A, omega, phi = 0;
  
  std::cout << "A = ";
  std::cin >> A;

  std::cout << "ω = ";
  std::cin >> omega;

  std::cout << "φ = ";
  std::cin >> phi;


  sf::RenderWindow mainWindow(sf::VideoMode(1280,720), "Harmonic Oscillator Simulator", sf::Style::Titlebar | sf::Style::Close);
  mainWindow.setFramerateLimit(100);
  mainWindow.setVerticalSyncEnabled(true);

  Graph graph(mainWindow,A,omega,phi);
  sf::VertexArray mouseVerticalLine(sf::Lines, 2);
  mouseVerticalLine[0].color = sf::Color::Black;
  mouseVerticalLine[1].color = sf::Color::Black;

  while (mainWindow.isOpen()) {
    sf::Event event;

    mouseVerticalLine[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow).x, 0);
    mouseVerticalLine[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow).x, 720);

    while (mainWindow.pollEvent(event)) {
      if(event.type == sf::Event::Closed) 
        mainWindow.close();
    }

    mainWindow.clear(sf::Color::White);

    graph.render();
    mainWindow.draw(mouseVerticalLine);
    
    mainWindow.display();

  }

  return 0;
}
