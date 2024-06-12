#include "window.h"
#include <vector>
using namespace std;

// Default window sizes
#define WIDTH 700.0
#define HEIGHT 700.0

/* Update the window to display the instructions and the current array nums */
void updateWindow(sf::RenderWindow& window, Screen currentScreen, const vector<int>& nums, sf::Font& font, bool cursorOn, int cursor, bool doneSorting) {
    window.clear();

    sf::Text title;
    sf::Text instructions;

    switch (currentScreen) {
        case Screen::Home:
            // Create and draw home screen
            title.setFont(font);
            title.setString("Sorting Simulator");
            title.setPosition(sf::Vector2f(WIDTH / 4, HEIGHT / 4));
            title.setCharacterSize(48);
            title.setFillColor(sf::Color::White);
            instructions.setFont(font);
            instructions.setString("Use the left and right arrows\nto navigate between screens.");
            instructions.setPosition(sf::Vector2f(WIDTH / 4, HEIGHT / 2));
            instructions.setCharacterSize(24);
            instructions.setFillColor(sf::Color::White);
            window.draw(title);
            window.draw(instructions);
            break;
        case Screen::Instructions:
            // Create and draw instructions screen
            title.setFont(font);
            title.setString("Instructions");
            title.setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / 10));
            title.setCharacterSize(48);
            title.setFillColor(sf::Color::White);
            instructions.setFont(font);
            instructions.setString("Esc: Exit\nP: Pause Sorting\nS: Shuffle Array\nC: Enable/Disable Cursor\nB: Bubble Sort\nX: Bogo Sort\nE: Selection Sort\nI: Insertion Sort\nM: Merge Sort\nQ: Quick Sort\n1 - 7: Change Size of Array");
            instructions.setPosition(sf::Vector2f(WIDTH / 10, HEIGHT / 3));
            instructions.setCharacterSize(24);
            instructions.setFillColor(sf::Color::White);
            window.draw(title);
            window.draw(instructions);
            break;
        case Screen::Sorting:
            // Create and draw sorting screen
            for (int i = 0; i < nums.size(); ++i) {
                sf::RectangleShape rectangle(sf::Vector2f(((WIDTH - 200) / nums.size()), (nums[i] * ((HEIGHT - 200) / nums.size()))));
                rectangle.setPosition(sf::Vector2f(100 + (i * ((WIDTH - 200) / nums.size())), HEIGHT - 100));
                rectangle.setFillColor(sf::Color(150, 150, 150));
                if (cursorOn && i == cursor) {
                    rectangle.setFillColor(sf::Color(219, 31, 34));
                }
                if (doneSorting && i <= cursor) {
                    rectangle.setFillColor(sf::Color(38, 183, 255));
                }
                rectangle.rotate(180.f);
                window.draw(rectangle);
            }
            break;
    }

    // Display everything on the window
    window.display();
}

/* Detect P or Esc key being pressed (used for pausing in-progress sorting) */
bool checkPause(sf::RenderWindow& window, bool& paused) {
    sf::Event event;
    if (window.pollEvent(event) && event.type == sf::Event::KeyPressed && (event.key.scancode == sf::Keyboard::Scan::P || event.key.scancode == sf::Keyboard::Scan::Escape)) {
        paused = true;
        return true;
    }
    return false;
}