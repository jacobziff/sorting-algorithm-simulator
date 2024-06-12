#include <vector>
#include "screen.h"
#include <SFML/Graphics.hpp>

/* Update the window to display the instructions and the current array nums */
void updateWindow(sf::RenderWindow& window, Screen currentScreen, const std::vector<int>& nums, sf::Font& font, bool cursorOn = true, int cursor = -1, bool doneSorting = false, std::string sortTitle = "", int comparisons = -1, int swaps = -1);

/* Detect P or Esc key being pressed (used for pausing in-progress sorting) */
bool checkPause(sf::RenderWindow& window, bool& paused);