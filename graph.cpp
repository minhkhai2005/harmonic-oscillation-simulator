#include "graph.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


Graph::Graph(sf::RenderWindow & target, float A, float sp, float initPh)
{
  amplitude = A;
  speed = sp;
  initPhase = initPh;
  renderTarget = & target; 
  sf::Vector2f targetSize = (sf::Vector2f)renderTarget->getSize();
  root = sf::Vector2f(targetSize.x/2, targetSize.y/2);
  x_axis = sf::VertexArray(sf::Lines, 2);
  y_axis = sf::VertexArray(sf::Lines, 2);
  x_axisNumbers = new sf::Text[32];
  y_axisNumbers = new sf::Text[19];

  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;
  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;

  x_axis[0].position = sf::Vector2f(0, targetSize.y / 2);
  x_axis[1].position = sf::Vector2f(targetSize.x, targetSize.y / 2);
  y_axis[0].position = sf::Vector2f(targetSize.x / 2, 0);
  y_axis[1].position = sf::Vector2f(targetSize.x / 2, targetSize.y);

  float windowWidth = 0;
  float windowHeight = 0;

  while (windowWidth <= targetSize.x)
  {
    sf::VertexArray verticalLine(sf::Lines, 2);
    verticalLine[0].position = sf::Vector2f(windowWidth, 0);
    verticalLine[1].position = sf::Vector2f(windowWidth, targetSize.y);
    verticalLine[0].color = sf::Color(194, 194, 194);
    verticalLine[1].color = sf::Color(194, 194, 194);

    verticalLines.push_back(verticalLine);

    x_axisNumbers[(int)windowWidth / 40].setFont(font);
    x_axisNumbers[(int)windowWidth / 40].setPosition(sf::Vector2f(windowWidth, targetSize.y / 2 + 5));
    x_axisNumbers[(int)windowWidth / 40].setCharacterSize(10);
    x_axisNumbers[(int)windowWidth / 40].setFillColor(sf::Color::Black);
    x_axisNumbers[(int)windowWidth / 40].setStyle(sf::Text::Regular);
    x_axisNumbers[(int)windowWidth / 40].setString(std::to_string((int)windowWidth / 40 - 640 / 40));
    windowWidth += targetSize.x * twoVerticalLineWidthRatio;
  }

  while (windowHeight <= targetSize.y)
  {
    sf::VertexArray HorizontalLine(sf::Lines, 2);
    HorizontalLine[0].position = sf::Vector2f(0, windowHeight);
    HorizontalLine[1].position = sf::Vector2f(targetSize.x, windowHeight);
    HorizontalLine[0].color = sf::Color(194, 194, 194);
    HorizontalLine[1].color = sf::Color(194, 194, 194);

    HorizontalLines.push_back(HorizontalLine);

    y_axisNumbers[(int)windowHeight / 40].setFont(font);
    y_axisNumbers[(int)windowHeight / 40].setPosition(sf::Vector2f(targetSize.x / 2 + 5,windowHeight));
    y_axisNumbers[(int)windowHeight / 40].setCharacterSize(10);
    y_axisNumbers[(int)windowHeight / 40].setFillColor(sf::Color::Black);
    y_axisNumbers[(int)windowHeight / 40].setStyle(sf::Text::Regular);
    y_axisNumbers[(int)windowHeight / 40].setString(std::to_string(-((int)windowHeight / 40 - 360 / 40)));
    windowHeight += targetSize.y * twoHorizontalLineHeightRatio;
  }

  x.setRadius(5);
  x.setFillColor(sf::Color::Red);
  x.setPosition(root);
  x.setOrigin(x.getLocalBounds().width/2, x.getLocalBounds().height/2);

  clock = sf::Clock();
  phaseCircle.setRadius(A * 40);
  phaseCircle.setOutlineThickness(2);
  phaseCircle.setOutlineColor(sf::Color::Blue);
  phaseCircle.setOrigin(phaseCircle.getLocalBounds().width/2, phaseCircle.getLocalBounds().height/2);
  phaseCircle.setPosition(root);

  phaseLine.setSize(sf::Vector2f(amplitude * 40,2));
  phaseLine.setFillColor(sf::Color::Red);
  phaseLine.setPosition(root);
  phaseLine.setRotation(initPhase * -180);

  xPositionLine.setFillColor(sf::Color::Red);
  xPositionLine.setRotation(90);

  runClock = true;
}

void Graph::render()
{
  //calculating ----------------------------------------------------------------
  if (runClock)
    t += clock.restart();
  else
    clock.restart();
  x.setPosition(root + sf::Vector2f(amplitude* cos(speed * t.asSeconds() + initPhase) * 40,0));
  phaseLine.setRotation(speed * -57.2958 * t.asSeconds() + initPhase * -57.2958);
  xPositionLine.setPosition(x.getPosition());
  xPositionLine.setSize(sf::Vector2f(velocity * 40,2));
  cordinate = amplitude * cos(speed * t.asSeconds() + initPhase);
  velocity = - amplitude * sin(speed * t.asSeconds() + initPhase);
  acceleration = - pow(speed,2) * cordinate;
  phase = speed * t.asSeconds() + initPhase ;
  // rendering -----------------------------------------------------------------

  renderTarget -> draw(phaseCircle);
  for (unsigned i = 0;i < verticalLines.size();++i)
  {
    renderTarget->draw(verticalLines[i]);
  }

  for (unsigned i = 0;i < HorizontalLines.size(); ++i)
  {
    renderTarget->draw(HorizontalLines[i]);
  }
  for (int i = 0;i < 32;++i)
  {
    renderTarget -> draw(x_axisNumbers[i]);
  }
  for (int i = 0; i < 19;++i)
  {
    renderTarget -> draw(y_axisNumbers[i]);
  }
  renderTarget -> draw(x_axis);
  renderTarget -> draw(y_axis);
  renderTarget->draw(x);
  renderTarget ->draw(phaseLine);
  renderTarget -> draw(xPositionLine);
}

std::string Graph::getCordinate()
{
  return std::to_string(cordinate);
}

std::string Graph::getAmplitude()
{
  return std::to_string(amplitude);
}

std::string Graph::getSpeed()
{
  return std::to_string(speed);
}

std::string Graph::getInitPhase()
{
  return std::to_string(initPhase);
}

std::string Graph::getAcceleration()
{
  return std::to_string(acceleration);
}

std::string Graph::getVelocity()
{
  return std::to_string(velocity);
}

std::string Graph::getPhase()
{
  return std::to_string(phase);
}

std::string Graph::getTime()
{
  return std::to_string(t.asSeconds());
}

void Graph::setFont(sf::Font &font)
{
  this->font = font;
}
float Graph::twoVerticalLineWidthRatio = 0.03125;
float Graph::twoHorizontalLineHeightRatio = 1.0/18;





