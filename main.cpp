#include <iostream>
#include <chrono>
#include <thread>
#include "sorting.h"
#include <SFML/Graphics.hpp>
using namespace std;

// g++ *.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/ -o Simulator -L/opt/homebrew/Cellar/sfml/2.6.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system
// ./Simulator

// Default window sizes
#define WIDTH 700.0
#define HEIGHT 700.0

// Global variables
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting");
sf::Font font;
Screen currentScreen = Screen::Home;
bool cursorOn = true;
bool paused = false;

/* Initialize a vector to have elements [1, n], where n == nums.size() */
void initialize(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = i + 1;
    }
    shuffle(nums);
}

/* Show to the user that nums is sorted */
void finishedSorting(vector<int>& nums, string sortTitle = "") {
    updateWindow(window, currentScreen, nums, font, cursorOn, -1, false, sortTitle);

    // If the sorting stopped from user pausing
    if (paused) {
        paused = false;
        return;
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        if (checkPause(window, paused)) {
            updateWindow(window, currentScreen, nums, font, cursorOn, -1, false, sortTitle);
            return;
        }
        updateWindow(window, currentScreen, nums, font, cursorOn, i, true, sortTitle);
        this_thread::sleep_for(chrono::milliseconds(800 / nums.size()));
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main(int argc, char** argv) {
    // Create and initialize all of the different vector sizes that can be used
    vector<int> nums5(5, 0);
    initialize(nums5);
    vector<int> nums10(10, 0);
    initialize(nums10);
    vector<int> nums50(50, 0);
    initialize(nums50);
    vector<int> nums100(100, 0);
    initialize(nums100);
    vector<int> nums250(250, 0);
    initialize(nums250);
    vector<int> nums500(500, 0);
    initialize(nums500);
    vector<int> nums1000(1000, 0);
    initialize(nums1000);

    // Default nums to be a 250-element vector
    vector<int> nums;
    nums = nums250;

    // Boolean for if window is still open
    bool done = false;

    // Load font for instructions
    if (!font.loadFromFile("arial.ttf")) {
        cout << "ERROR WITH TEXT" << endl;
    }

    // Slowing the program down for ease CPU and GPU
    int waitMS = 30;

    // Main program loop
    while (window.isOpen()) {
        switch (currentScreen) {
            // Detect event
            sf::Event event;
            case Screen::Home:
                while (window.pollEvent(event)) {
                    this_thread::sleep_for(chrono::milliseconds(waitMS));
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        done = true;
                    } else if (event.type == sf::Event::KeyPressed) {
                        switch(event.key.scancode) {
                            // Close window
                            case sf::Keyboard::Scan::Escape:
                                window.close();
                                done = true;
                                break;
                            // Switch to Instructions
                            case sf::Keyboard::Scan::Right:
                                currentScreen = Screen::Instructions;
                                break;
                            // Switch to Sorting
                            case sf::Keyboard::Scan::Left:
                                currentScreen = Screen::Sorting;
                                break;
                            // Do nothing
                            default:
                                break;
                        }
                    }
                }
                break;
            case Screen::Instructions:
                while (window.pollEvent(event)) {
                    this_thread::sleep_for(chrono::milliseconds(waitMS));
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        done = true;
                    } else if (event.type == sf::Event::KeyPressed) {
                        switch(event.key.scancode) {
                            // Close window
                            case sf::Keyboard::Scan::Escape:
                                window.close();
                                done = true;
                                break;
                            // Switch to Sorting
                            case sf::Keyboard::Scan::Right:
                                currentScreen = Screen::Sorting;
                                break;
                            // Switch to Home
                            case sf::Keyboard::Scan::Left:
                                currentScreen = Screen::Home;
                                break;
                            // Do nothing
                            default:
                                break;
                        }
                    }
                }
                break;
            case Screen::Sorting:
                while (window.pollEvent(event)) {
                    this_thread::sleep_for(chrono::milliseconds(waitMS));
                    // Close window
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        done = true;
                    } else if (event.type == sf::Event::KeyPressed) {
                        // Detect which key is pressed
                        switch(event.key.scancode) {
                            // Close window
                            case sf::Keyboard::Scan::Escape:
                                window.close();
                                done = true;
                                break;
                            // Switch to Home
                            case sf::Keyboard::Scan::Right:
                                currentScreen = Screen::Home;
                                break;
                            // Switch to Instructions
                            case sf::Keyboard::Scan::Left:
                                currentScreen = Screen::Instructions;
                                break;
                            // Toggle Cursor
                            case sf::Keyboard::Scan::C:
                                cursorOn = !cursorOn;
                                break;
                            // Shuffle nums
                            case sf::Keyboard::Scan::S:
                                shuffle(nums);
                                break;
                            // Bubble Sort
                            case sf::Keyboard::Scan::B:
                                bubbleSort(nums, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "BubbleSort");
                                break;
                            // Selection Sort
                            case sf::Keyboard::Scan::E:
                                selectionSort(nums, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "SelectionSort");
                                break;
                            // Insertion Sort
                            case sf::Keyboard::Scan::I:
                                insertionSort(nums, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "InsertionSort");
                                break;
                            // Merge Sort
                            case sf::Keyboard::Scan::M:
                                mergeSort(nums, 0, nums.size() - 1, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "MergeSort");
                                break;
                            case sf::Keyboard::Scan::Q:
                                quickSort(nums, 0, nums.size() - 1, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "QuickSort");
                                break;
                            // Bogo Sort
                            case sf::Keyboard::Scan::X:
                                bogoSort(nums, window, currentScreen, cursorOn, font, paused);
                                finishedSorting(nums, "BogoSort");
                                break;
                            // Switch to 5-element vector
                            case sf::Keyboard::Scan::Num1:
                                nums = nums5;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 10-element vector
                            case sf::Keyboard::Scan::Num2:
                                nums = nums10;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 50-element vector
                            case sf::Keyboard::Scan::Num3:
                                nums = nums50;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 100-element vector
                            case sf::Keyboard::Scan::Num4:
                                nums = nums100;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 250-element vector
                            case sf::Keyboard::Scan::Num5:
                                nums = nums250;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 500-element vector
                            case sf::Keyboard::Scan::Num6:
                                nums = nums500;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Switch to 1000-element vector
                            case sf::Keyboard::Scan::Num7:
                                nums = nums1000;
                                shuffle(nums);
                                updateWindow(window, currentScreen, nums, font, cursorOn);
                                break;
                            // Do nothing
                            default:
                                break;
                        }
                    }
                }
                break;
        }
        
        // If window is still open, update it
        if (!done) {
            this_thread::sleep_for(chrono::milliseconds(waitMS));
            updateWindow(window, currentScreen, nums, font, cursorOn);
        }
    }
    return 0;
}