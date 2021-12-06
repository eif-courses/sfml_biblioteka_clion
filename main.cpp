#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

/*
 SFML 2.5.1 versija:
 1. Windows OS Kompiliatorius: MinGW Builds 7.3.0 (64-bit) rasite archyve: x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z
 2. Biblioteka SFML 2.5.1 rasite archyve: SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip
 3. Išskleisti du archyvus, bet kur patogioje vietoje geriau ne projekto kataloge taip greičiau veiks CLION.
 4. CmakeLists.txt faile atitinkamai pakeisti katalogų kelius priklausomai kur išskleidėte

 Kitoms Operacinėms sistemoms reikia skaityti dokumentaciją ir naudoti kito tipo kompiliatorius/programavimo aplinkas.
 Plačiau rasite oficialioje svetainėje: https://www.sfml-dev.org/

*/

int main() {

  int width = 1024;
  int height = 768;

  // Pagrindinis langas
  sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

  window.setFramerateLimit(100);
  window.setVerticalSyncEnabled(false);


  sf::Font font;
  if (!font.loadFromFile("Amatic-Bold.ttf")) {
    // error...
    std::cout << "NEPAVYKO";
  }
  sf::Text text;
  text.setFont(font);
  text.setString("SAVE");
  text.setCharacterSize(54); // in pixels, not points!
  text.setFillColor(sf::Color::Yellow);
  text.setPosition(150, -10);
  //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  sf::RectangleShape currentColor(sf::Vector2f(120.f, 50.f));
  currentColor.setFillColor(sf::Color::Green);
  currentColor.setPosition(0, 0);

  sf::RectangleShape saveToFile(sf::Vector2f(120.f, 50.f));
  saveToFile.setFillColor(sf::Color::Red);
  saveToFile.setPosition(125, 0);


  // Piesimo zonos kurimas
  sf::RenderTexture canvas;
  canvas.create(width, height);
  canvas.clear(sf::Color::Black);

  sf::Sprite sprite;
  sprite.setTexture(canvas.getTexture(), true);
  sprite.setPosition(0.0f, 50.0f);

  const std::vector<sf::Color> colors = {
      sf::Color(255, 0, 255, 10),
      sf::Color(255, 0, 0, 10),
      sf::Color(0, 255, 0, 10),
      sf::Color(0, 255, 255, 10),
  };
  currentColor.setFillColor(colors[1]);

  // Piesimo irankiai

  const float brushSize = 25.0f;
  sf::CircleShape brush(brushSize, 24);
  brush.setOrigin(brushSize, brushSize);

  sf::Vector2f lastPos;
  bool isDrawing = false;
  unsigned int color = 1;
  brush.setFillColor(colors[color]);

  sf::VertexArray lines(sf::Lines, 2);


  // Laikmatis

  sf::Clock clock;
  sf::Time time;



  // Game Loop
  while (window.isOpen()) {

    // einamaji laika nuo startavimo arba paskutinio restarto
    time = clock.getElapsedTime();

    if(time.asSeconds() > 2){
      text.setString("SAVE");
    }

    // Track keyboard and mouse & Joystick
    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::C:
              canvas.clear(sf::Color::Black);
              canvas.display();
              break;
            case sf::Keyboard::Right:
              color = (color + 1) % colors.size();
              brush.setFillColor(colors[color]);

              currentColor.setFillColor(sf::Color(colors[color].r,
                                                  colors[color].g,
                                                  colors[color].b));
              break;
            case sf::Keyboard::Left:
              color = (color - 1) % colors.size();
              brush.setFillColor(colors[color]);
              currentColor.setFillColor(sf::Color(colors[color].r,
                                                  colors[color].g,
                                                  colors[color].b));
              break;
          }


        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            cout << "pos windows: " << localPosition.x << ", " << localPosition.y << endl;
            isDrawing = true;
            lastPos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y - 50});
            brush.setPosition(lastPos);
            canvas.draw(brush);
            canvas.display();

            if(saveToFile.getGlobalBounds().contains((float)localPosition.x, (float)localPosition.y)){
              canvas.getTexture().copyToImage().saveToFile("manopav.png");
              text.setString("SAVED!");
              clock.restart();
            }
          }
          break;
        case sf::Event::MouseButtonReleased:
          if (event.mouseButton.button == sf::Mouse::Left) {
            isDrawing = false;
          }
          break;
        case sf::Event::MouseMoved:
          if (isDrawing) {
            const sf::Vector2f newPos(window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y - 50}));
            brush.setPosition(newPos);

            // Tieses piesimas
            lines[0].position = newPos;
            lines[1].position = lastPos;
            lastPos = newPos;
            canvas.draw(lines);

            // teptuko arba apskritimo piesimas
            canvas.draw(brush);
            canvas.display();
          }

          break;

      }


    }

    window.clear(); // Kas bus atvaizduojama kai isvalome langa

    window.draw(currentColor);
    window.draw(saveToFile);
    window.draw(sprite);
    // Kokius objektus norite atvaizduoti realiu laiku
    window.draw(text);

    window.display();
  }
}
