#include "sorting.h"
#include <random>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

// Default window sizes
#define WIDTH 700.0
#define HEIGHT 700.0

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine e(seed);

/* Shuffle a vector to prepare for sorting */
void shuffle(vector<int>& nums) {
    shuffle(nums.begin(), nums.end(), e);
}

/* Bubble Sort Algorithm */
void bubbleSort(vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    for (int i = 0; i < nums.size() - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < nums.size() - i - 1; ++j) {
            if (checkPause(window, paused)) {
                return;
            }
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
                updateWindow(window, currentScreen, nums, font, cursorOn, j);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

/* Selection Sort Algorithm */
void selectionSort(vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    for (int i = 0; i < nums.size(); ++i) {
        int minIndex = i;
        for (int j = i; j < nums.size(); ++j) {
            if (checkPause(window, paused)) {
                return;
            }
            updateWindow(window, currentScreen, nums, font, cursorOn, j);
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        swap(nums[i], nums[minIndex]);
    }
}

/* Insertion Sort Algorithm */
void insertionSort(vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    for (int i = 1; i < nums.size(); ++i) {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1]) {
            if (checkPause(window, paused)) {
                return;
            }
            swap(nums[j], nums[j - 1]);
            updateWindow(window, currentScreen, nums, font, cursorOn, j);
            --j;
        }
    }
}

/* Merge two subsequent parts of nums */
/* If return false, it means to stop the whole algorithm */
bool merge(vector<int>& nums, int start, int mid, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    vector<int> temp;
    for (int i = start; i <= end; ++i) {
        temp.push_back(nums[i]);
    }
    int a = 0;
    int b = mid - start + 1;
    int i = start;
    while (a <= mid - start || b <= end - start) {
        if (checkPause(window, paused)) {
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
        updateWindow(window, currentScreen, nums, font, cursorOn, i);
        ++i;
    }
    return true;
}

/* Merge Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool mergeSort(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    if (start >= end) {
        return true;
    } else {
        if (checkPause(window, paused)) {
            return false;
        }
        int mid = start + ((end - start) / 2);
        if (!mergeSort(nums, start, mid, window, currentScreen, cursorOn, font, paused)) {
            return false;
        }
        if (!mergeSort(nums, mid + 1, end, window, currentScreen, cursorOn, font, paused)) {
            return false;
        }
        if (!merge(nums, start, mid, end, window, currentScreen, cursorOn, font, paused)) {
            return false;
        }
        return true;
    }
}

/* Partition nums for Quick Sort algorithm */
/* Return -1 if user pauses, otherwise return partition index */
int partition(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    int pivot = nums[end];
    int i = start - 1;
    for (int j = start; j <= end; ++j) {
        if (checkPause(window, paused)) {
            return -1;
        }
        this_thread::sleep_for(chrono::microseconds(250));
        if (nums[j] < pivot) {
            ++i;
            swap(nums[i], nums[j]);
            updateWindow(window, currentScreen, nums, font, cursorOn, j);
        }
    }
    swap(nums[i + 1], nums[end]);
    updateWindow(window, currentScreen, nums, font, cursorOn, i);
    return i + 1;
}

/* Quick Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool quickSort(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    if (start < end) {
        int partitionIndex = partition(nums, start, end, window, currentScreen, cursorOn, font, paused);
        if (partitionIndex == -1) {
            return false;
        }
        if (!quickSort(nums, start, partitionIndex - 1, window, currentScreen, cursorOn, font, paused)) {
            return false;
        }
        if (!quickSort(nums, partitionIndex + 1, end, window, currentScreen, cursorOn, font, paused)) {
            return false;
        }
    }
    return true;
}

/* Bogo Sort Algorithm */
void bogoSort(vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    while (true) {
        if (checkPause(window, paused)) {
            return;
        }
        shuffle(nums);
        bool good = true;
        for (int i = 0; i < nums.size() - 1; ++i) {
            updateWindow(window, currentScreen, nums, font, cursorOn, i);
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