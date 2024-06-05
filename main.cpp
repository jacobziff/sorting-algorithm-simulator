#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
using namespace std;

// g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/ -o viz -L/opt/homebrew/Cellar/sfml/2.6.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system 
// ./viz

// Default window sizes
#define WIDTH 700.0
#define HEIGHT 700.0

enum Screen {
    Home,
    Instructions,
    Sorting
};

// Global variables
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Sorting");
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine e(seed);
sf::Font font;
Screen currentScreen = Screen::Home;
bool cursorOn = true;
bool paused = false;

/* Update the window to display the instructions and the current array nums */
void updateWindow(const vector<int>& nums, int cursor = -1, bool doneSorting = false) {
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

/* Shuffle a vector to prepare for sorting */
void shuffle(vector<int>& nums) {
    shuffle(nums.begin(), nums.end(), e);
}

/* Initialize a vector to have elements [1, n], where n == nums.size() */
void initialize(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = i + 1;
    }
    shuffle(nums);
}

/* Detect P or Esc key being pressed (used for pausing in-progress sorting) */
bool checkPause() {
    sf::Event event;
    if (window.pollEvent(event) && event.type == sf::Event::KeyPressed && (event.key.scancode == sf::Keyboard::Scan::P || event.key.scancode == sf::Keyboard::Scan::Escape)) {
        paused = true;
        return true;
    }
    return false;
}

/* Show to the user that nums is sorted */
void finishedSorting(vector<int>& nums) {
    updateWindow(nums);

    // If the sorting stopped from user pausing
    if (paused) {
        paused = false;
        return;
    }
    
    for (int i = 0; i < nums.size(); ++i) {
        if (checkPause()) {
            updateWindow(nums);
            return;
        }
        updateWindow(nums, i, true);
        this_thread::sleep_for(chrono::milliseconds(800 / nums.size()));
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

/* Bubble Sort Algorithm */
void bubbleSort(vector<int>& nums) {
    for (int i = 0; i < nums.size() - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < nums.size() - i - 1; ++j) {
            if (checkPause()) {
                return;
            }
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                updateWindow(nums, j);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

/* Selection Sort Algorithm */
void selectionSort(vector<int>& nums) {
    for (int i = 0; i < nums.size(); ++i) {
        int minIndex = i;
        for (int j = i; j < nums.size(); ++j) {
            if (checkPause()) {
                return;
            }
            updateWindow(nums, j);
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        swap(nums[i], nums[minIndex]);
    }
}

/* Insertion Sort Algorithm */
void insertionSort(vector<int>& nums) {
    for (int i = 1; i < nums.size(); ++i) {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1]) {
            if (checkPause()) {
                return;
            }
            swap(nums[j], nums[j - 1]);
            updateWindow(nums, j);
            --j;
        }
    }
}

/* Merge two subsequent parts of nums */
/* If return false, it means to stop the whole algorithm */
bool merge(vector<int>& nums, int start, int mid, int end) {
    vector<int> temp;
    for (int i = start; i <= end; ++i) {
        temp.push_back(nums[i]);
    }
    int a = 0;
    int b = mid - start + 1;
    int i = start;
    while (a <= mid - start || b <= end - start) {
        if (checkPause()) {
            return false;
        }
        if (a <= mid - start && b <= end - start) {
            if (temp[a] < temp[b]) {
                nums[i] = temp[a];
                ++a;
            } else {
                nums[i] = temp[b];
                ++b;
            }
        } else if (a <= mid - start) {
            nums[i] = temp[a];
            ++a;
        } else {
            nums[i] = temp[b];
            ++b;
        }
        this_thread::sleep_for(chrono::microseconds(1000));
        updateWindow(nums, i);
        ++i;
    }
    return true;
}

/* Merge Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool mergeSort(vector<int>& nums, int start, int end) {
    if (start >= end) {
        return true;
    } else {
        if (checkPause()) {
            return false;
        }
        int mid = start + ((end - start) / 2);
        if (!mergeSort(nums, start, mid)) {
            return false;
        }
        if (!mergeSort(nums, mid + 1, end)) {
            return false;
        }
        if (!merge(nums, start, mid, end)) {
            return false;
        }
        return true;
    }
}

/* Partition nums for Quick Sort algorithm */
/* Return -1 if user pauses, otherwise return partition index */
int partition(vector<int>& nums, int start, int end) {
    int pivot = nums[end];
    int i = start - 1;
    for (int j = start; j <= end; ++j) {
        if (checkPause()) {
            return -1;
        }
        this_thread::sleep_for(chrono::microseconds(250));
        if (nums[j] < pivot) {
            ++i;
            swap(nums[i], nums[j]);
            updateWindow(nums, j);
        }
    }
    swap(nums[i + 1], nums[end]);
    updateWindow(nums, i);
    return i + 1;
}

/* Quick Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool quickSort(vector<int>& nums, int start, int end) {
    if (start < end) {
        int partitionIndex = partition(nums, start, end);
        if (partitionIndex == -1) {
            return false;
        }
        if (!quickSort(nums, start, partitionIndex - 1)) {
            return false;
        }
        if (!quickSort(nums, partitionIndex + 1, end)) {
            return false;
        }
    }
    return true;
}

/* Bogo Sort Algorithm */
void bogoSort(vector<int>& nums) {
    while (true) {
        if (checkPause()) {
            return;
        }
        shuffle(nums);
        bool good = true;
        for (int i = 0; i < nums.size() - 1; ++i) {
            updateWindow(nums, i);
            if (nums[i] > nums[i + 1]) {
                good = false;
                break;
            }
        }
        if (good) {
            return;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
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
        cout << "ERROR" << endl;
    }

    // Main program loop
    while (window.isOpen()) {
        switch (currentScreen) {
            // Detect event
            sf::Event event;
            case Screen::Home:
                while (window.pollEvent(event)) {
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
                                bubbleSort(nums);
                                finishedSorting(nums);
                                break;
                            // Selection Sort
                            case sf::Keyboard::Scan::E:
                                selectionSort(nums);
                                finishedSorting(nums);
                                break;
                            // Insertion Sort
                            case sf::Keyboard::Scan::I:
                                insertionSort(nums);
                                finishedSorting(nums);
                                break;
                            // Merge Sort
                            case sf::Keyboard::Scan::M:
                                mergeSort(nums, 0, nums.size() - 1);
                                finishedSorting(nums);
                                break;
                            case sf::Keyboard::Scan::Q:
                                quickSort(nums, 0, nums.size() - 1);
                                finishedSorting(nums);
                                break;
                            // Bogo Sort
                            case sf::Keyboard::Scan::X:
                                bogoSort(nums);
                                finishedSorting(nums);
                                break;
                            // Switch to 5-element vector
                            case sf::Keyboard::Scan::Num1:
                                nums = nums5;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 10-element vector
                            case sf::Keyboard::Scan::Num2:
                                nums = nums10;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 50-element vector
                            case sf::Keyboard::Scan::Num3:
                                nums = nums50;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 100-element vector
                            case sf::Keyboard::Scan::Num4:
                                nums = nums100;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 250-element vector
                            case sf::Keyboard::Scan::Num5:
                                nums = nums250;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 500-element vector
                            case sf::Keyboard::Scan::Num6:
                                nums = nums500;
                                shuffle(nums);
                                updateWindow(nums);
                                break;
                            // Switch to 1000-element vector
                            case sf::Keyboard::Scan::Num7:
                                nums = nums1000;
                                shuffle(nums);
                                updateWindow(nums);
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
            updateWindow(nums);
        }
    }
    return 0;
}