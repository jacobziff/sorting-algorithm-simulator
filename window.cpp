#include "window.h"
#include <vector>
using namespace std;

// Default window sizes
#define WIDTH 700.0
#define HEIGHT 700.0

/* Update the window to display the instructions and the current array nums */
void updateWindow(sf::RenderWindow& window, Screen currentScreen, const vector<int>& nums, sf::Font& font, bool cursorOn, int cursor, bool doneSorting, string sortTitle, int comparisons, int swaps) {
    window.clear();

    sf::Text title;
    sf::Text instructions;
    sf::Text sortInfo;

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
            title.setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / 15));
            title.setCharacterSize(48);
            title.setFillColor(sf::Color::White);
            instructions.setFont(font);
            instructions.setString("Esc: Exit\nP: Pause Sorting\nS: Shuffle Array\nC: Enable/Disable Cursor\n\n1 - 7: Change Size of Array (Default is 5)\n\nB: BubbleSort (Recommended for medium arrays)\nE: SelectionSort (Recommended for medium arrays)\nI: InsertionSort (Recommended for medium arrays)\nM: MergeSort (Recommended for large arrays)\nQ: QuickSort (Recommended for large arrays)\nZ: SlowSort (Recommended for small arrays)\nX: BogoSort (Recommended for smallest arrays)\n\n1: Smallest\n2 - 3: Small\n4 - 5: Medium\n6 - 7: Large");
            instructions.setPosition(sf::Vector2f(WIDTH / 10, HEIGHT / 6));
            instructions.setCharacterSize(24);
            instructions.setFillColor(sf::Color::White);
            window.draw(title);
            window.draw(instructions);
            break;
        case Screen::Sorting:
            title.setFont(font);
            title.setString(sortTitle);
            title.setPosition(sf::Vector2f(WIDTH / 3, HEIGHT / 32));
            title.setCharacterSize(48);
            title.setFillColor(sf::Color::White);
            sortInfo.setFont(font);
            if (comparisons != -1 && swaps != -1) {
                sortInfo.setString("Comparisons: " + to_string(comparisons) + "\nSwaps: " + to_string(swaps));
            } else {
                sortInfo.setString("");
            }
            sortInfo.setPosition(sf::Vector2f(WIDTH / 32, HEIGHT / 32));
            sortInfo.setCharacterSize(20);
            sortInfo.setFillColor(sf::Color::White);
            // Create and draw sorting screen
            for (int i = 0; i < nums.size(); ++i) {
                sf::RectangleShape rectangle(sf::Vector2f(((WIDTH - 200) / nums.size()), (nums[i] * ((HEIGHT - 200) / nums.size()))));
                rectangle.setPosition(sf::Vector2f(100 + ((i + 1) * ((WIDTH - 200) / nums.size())), HEIGHT - 100));
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
            window.draw(title);
            window.draw(sortInfo);
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