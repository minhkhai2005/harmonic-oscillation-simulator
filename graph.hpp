
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
class Graph 
{
protected:
  sf::VertexArray x_axis;
  sf::VertexArray y_axis;
  sf::RenderWindow * renderTarget;
  static float twoVerticalLineWidthRatio;
  static float twoHorizontalLineHeightRatio;
  std::vector<sf::VertexArray> verticalLines;
  std::vector<sf::VertexArray> HorizontalLines;
  sf::Vector2f root;
  sf::CircleShape x; 
  sf::CircleShape phaseCircle;
  sf::RectangleShape phaseLine;
  sf::RectangleShape xPositionLine;
  sf::Clock clock;
  sf::Time t;
  float amplitude;
  float speed;
  float initPhase;
  float acceleration;
  float velocity;
public:
  bool runClock;
  Graph(sf::RenderWindow & target, float A = 0, float sp = 0, float initPh = 0);
  void render();
};







#endif // GRAPH_HPP
