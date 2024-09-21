#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "graph.hpp"
#include "./button/Button.hpp"
#include "myFont.h"
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
  mainWindow.setMouseCursorVisible(true);

  Graph graph(mainWindow,A,omega,phi);
  sf::VertexArray mouseVerticalLine(sf::Lines, 2);
  sf::VertexArray mouseHorizontalLine(sf::Lines, 2);
  mouseVerticalLine[0].color = sf::Color::Blue;
  mouseVerticalLine[1].color = sf::Color::Blue;
  mouseHorizontalLine[0].color = sf::Color::Blue;
  mouseHorizontalLine[1].color = sf::Color::Blue;

  sf::Font LucidaGrande;
  if (!LucidaGrande.loadFromMemory(LucidaGrande_ttc, LucidaGrande_ttc_len)){
    return -1;
  };
  graph.setFont(LucidaGrande);
  sf::Text mousePositionIndicator;
  sf::Text cordinateIndicator;
  sf::Text velocityIndicator;
  sf::Text accelerationIndicator;
  sf::Text phaseIndicator;
  sf::Text timeIndicator;
  mousePositionIndicator.setFont(LucidaGrande);
  mousePositionIndicator.setFillColor(sf::Color::Black);
  mousePositionIndicator.setStyle(sf::Text::Regular);
  mousePositionIndicator.setCharacterSize(10);
  mousePositionIndicator.setPosition(10,10);

  cordinateIndicator.setFont(LucidaGrande);
  cordinateIndicator.setFillColor(sf::Color::Black);
  cordinateIndicator.setStyle(sf::Text::Regular);
  cordinateIndicator.setCharacterSize(10);
  cordinateIndicator.setPosition(10,25);

  velocityIndicator.setFont(LucidaGrande);
  velocityIndicator.setFillColor(sf::Color::Black);
  velocityIndicator.setStyle(sf::Text::Regular);
  velocityIndicator.setCharacterSize(10);
  velocityIndicator.setPosition(10,40);

  accelerationIndicator.setFont(LucidaGrande);
  accelerationIndicator.setFillColor(sf::Color::Black);
  accelerationIndicator.setStyle(sf::Text::Regular);
  accelerationIndicator.setCharacterSize(10);
  accelerationIndicator.setPosition(10,55);

  phaseIndicator.setFont(LucidaGrande);
  phaseIndicator.setFillColor(sf::Color::Black);
  phaseIndicator.setStyle(sf::Text::Regular);
  phaseIndicator.setCharacterSize(10);
  phaseIndicator.setPosition(10,70);

  timeIndicator.setFont(LucidaGrande);
  timeIndicator.setFillColor(sf::Color::Black);
  timeIndicator.setStyle(sf::Text::Regular);
  timeIndicator.setCharacterSize(10);
  timeIndicator.setPosition(10,85);

  Button startStopButton(sf::Vector2f(100,30),"start",LucidaGrande,sf::Color(200, 200, 200),mainWindow);
  startStopButton.setPosition(60,115);
  startStopButton.setCharacterSize(16);



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

    cordinateIndicator.setString(std::string("x = ") + graph.getCordinate());
    velocityIndicator.setString(std::string("v = ") + graph.getVelocity());
    accelerationIndicator.setString(std::string("a = ") + graph.getAcceleration());
    phaseIndicator.setString(std::string("Phase: ") + graph.getPhase());
    if (graph.runClock)
    {
      startStopButton.setText("Stop");
    }
    else {
      startStopButton.setText("Resume");
    }
    if (startStopButton.buttonRelease())
      graph.runClock = !graph.runClock;

    timeIndicator.setString(std::string("Time: ") + graph.getTime());
    // even loop
    while (mainWindow.pollEvent(event)) {
      if(event.type == sf::Event::Closed) 
        mainWindow.close();
    }

    mainWindow.clear(sf::Color::White);

    graph.render();
    mainWindow.draw(mouseVerticalLine);
    mainWindow.draw(mouseHorizontalLine);
    startStopButton.render();
    mainWindow.draw(mousePositionIndicator) ;
    mainWindow.draw(cordinateIndicator);
    mainWindow.draw(velocityIndicator);
    mainWindow.draw(accelerationIndicator);
    mainWindow.draw(phaseIndicator);
    mainWindow.draw(timeIndicator);
    mainWindow.display();

  }

  return 0;
}
