#include <vector>
#include "window.h"

/* Shuffle a vector to prepare for sorting */
void shuffle(std::vector<int>& nums);

/* Bubble Sort Algorithm */
void bubbleSort(std::vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Selection Sort Algorithm */
void selectionSort(std::vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Insertion Sort Algorithm */
void insertionSort(std::vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Merge two subsequent parts of nums */
/* If return false, it means to stop the whole algorithm */
bool merge(std::vector<int>& nums, int start, int mid, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Merge Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool mergeSort(std::vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Partition nums for Quick Sort algorithm */
/* Return -1 if user pauses, otherwise return partition index */
int partition(std::vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Quick Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool quickSort(std::vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);

/* Bogo Sort Algorithm */
void bogoSort(std::vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused);