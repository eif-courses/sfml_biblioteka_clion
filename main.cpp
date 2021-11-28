#include <SFML/Graphics.hpp>

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
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
}
