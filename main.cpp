#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
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
#include <string>
#include <thread>
#include "graph.hpp"
#include "./button/Button.hpp"

int main(int argc, char *argv[])
{
  const std::string CURRENT_FILEPATH = std::string(argv[0]).substr(0,std::string(argv[0]).find_last_of("/") + 1);
 
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
  mainWindow.setMouseCursorVisible(false);

  Graph graph(mainWindow,A,omega,phi);
  sf::VertexArray mouseVerticalLine(sf::Lines, 2);
  sf::VertexArray mouseHorizontalLine(sf::Lines, 2);
  mouseVerticalLine[0].color = sf::Color::Blue;
  mouseVerticalLine[1].color = sf::Color::Blue;
  mouseHorizontalLine[0].color = sf::Color::Blue;
  mouseHorizontalLine[1].color = sf::Color::Blue;

  sf::Font LucidaGrande;
  LucidaGrande.loadFromFile(std::string(CURRENT_FILEPATH + "LucidaGrande.ttc"));
  sf::Text mousePositionIndicator;
  mousePositionIndicator.setFont(LucidaGrande);
  mousePositionIndicator.setFillColor(sf::Color::Black);
  mousePositionIndicator.setStyle(sf::Text::Regular);
  mousePositionIndicator.setCharacterSize(10);
  mousePositionIndicator.setPosition(10,10);

  Button startStopButton(sf::Vector2f(70,30),"start",LucidaGrande,sf::Color(49, 116, 224),mainWindow);
  startStopButton.setPosition(40,40);
  startStopButton.setCharacterSize(20);
  // main loop
  while (mainWindow.isOpen()) {
    sf::Event event;

    mouseVerticalLine[0].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow).x, 0);
    mouseVerticalLine[1].position = sf::Vector2f(sf::Mouse::getPosition(mainWindow).x, 720);
    mouseHorizontalLine[0].position = sf::Vector2f(0, sf::Mouse::getPosition(mainWindow).y);
    mouseHorizontalLine[1].position = sf::Vector2f(1280, sf::Mouse::getPosition(mainWindow).y);

    mousePositionIndicator.setString(std::to_string(  
          (mouseVerticalLine[0].position.x - 640) / 40.f  ) + " " +
          std::to_string(( -(mouseHorizontalLine[0].position.y - 360) / 40.f) )
        );

    if (graph.runClock)
    {
      startStopButton.setText("Stop");
    }
    else {
      startStopButton.setText("Resume");
    }
    if (startStopButton.buttonRelease())
      graph.runClock = !graph.runClock;
    while (mainWindow.pollEvent(event)) {
      if(event.type == sf::Event::Closed) 
        mainWindow.close();
    }

    mainWindow.clear(sf::Color::White);

    graph.render();
    startStopButton.render();
    mainWindow.draw(mouseVerticalLine);
    mainWindow.draw(mouseHorizontalLine);
    mainWindow.draw(mousePositionIndicator) ;
    mainWindow.display();

  }

  return 0;
}
