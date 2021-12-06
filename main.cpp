#include <SFML/Graphics.hpp>
#include <iostream>

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
  text.setPosition(125,0);
  //text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  sf::RectangleShape currentColor(sf::Vector2f(120.f, 50.f));
  currentColor.setFillColor(sf::Color::Green);
  currentColor.setPosition(0,0);

  sf::RectangleShape saveToFile(sf::Vector2f(120.f, 50.f));
  saveToFile.setFillColor(sf::Color::Red);
  currentColor.setPosition(125,0);


  // Piesimo zonos kurimas
  sf::RenderTexture canvas;
  canvas.create(width, height);
  canvas.clear(sf::Color::White);

  sf::Sprite sprite;
  sprite.setTexture(canvas.getTexture(), true);
  sprite.setPosition(0.0f, 50.0f);

  const std::vector<sf::Color> colors = {
      sf::Color::Blue,
      sf::Color(255, 0, 0, 100),
      sf::Color(0, 255, 0, 100),
      sf::Color(0, 255, 255, 100),
  };
  currentColor.setFillColor(colors[3]);
  const float brushSize = 25.0f;
  sf::CircleShape brush(brushSize, 24);
  brush.setOrigin(brushSize, brushSize);

  sf::Vector2f lastPos;
  bool isDrawing = false;
  unsigned int color = 0;
  brush.setFillColor(colors[color]);






  // Game Loop
  while (window.isOpen()) {

    // Track keyboard and mouse & Joystick
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
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
