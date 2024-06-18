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
    int comparisons = 0;
    int swaps = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < nums.size() - i - 1; ++j) {
            if (checkPause(window, paused)) {
                return;
            }
            ++comparisons;
            if (nums[j] > nums[j + 1]) {
                ++swaps;
                swap(nums[j], nums[j + 1]);
                this_thread::sleep_for(chrono::microseconds(1000));
                if (rand() % 4 == 0) {
                    updateWindow(window, currentScreen, nums, font, cursorOn, j, false, "BubbleSort", comparisons, swaps);
                }
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
    int comparisons = 0;
    int swaps = 0;
    for (int i = 0; i < nums.size(); ++i) {
        int minIndex = i;
        for (int j = i; j < nums.size(); ++j) {
            if (checkPause(window, paused)) {
                return;
            }
            ++comparisons;
            this_thread::sleep_for(chrono::microseconds(1000));
            if (rand() % 4 == 0) {
                updateWindow(window, currentScreen, nums, font, cursorOn, j, false, "SelectionSort", comparisons, swaps);
            }
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        ++swaps;
        swap(nums[i], nums[minIndex]);
    }
}

/* Insertion Sort Algorithm */
void insertionSort(vector<int>& nums, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    int comparisons = 0;
    int swaps = 0;
    for (int i = 1; i < nums.size(); ++i) {
        int j = i;
        while (j > 0 && nums[j] < nums[j - 1]) {
            this_thread::sleep_for(chrono::microseconds(1000));
            ++comparisons;
            if (checkPause(window, paused)) {
                return;
            }
            ++swaps;
            swap(nums[j], nums[j - 1]);
            if (rand() % 4 == 0) {
                updateWindow(window, currentScreen, nums, font, cursorOn, j, false, "InsertionSort", comparisons, swaps);
            }
            --j;
        }
        ++comparisons;
    }
}

/* Merge two subsequent parts of nums */
/* If return false, it means to stop the whole algorithm */
int mergeComps = 0;
int mergeSwaps = 0;
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
        ++mergeSwaps;
        if (a <= mid - start && b <= end - start) {
            ++mergeComps;
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
        if (rand() % 4 == 0) {
            updateWindow(window, currentScreen, nums, font, cursorOn, i, false, "MergeSort", mergeComps, mergeSwaps);
        }
        ++i;
    }
    updateWindow(window, currentScreen, nums, font, cursorOn, i, false, "MergeSort", mergeComps, mergeSwaps);
    return true;
}

/* Merge Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool mergeSort(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    if (start == 0 && end == nums.size() - 1) {
        mergeComps = 0;
        mergeSwaps = 0;
    }
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
int quickComps = 0;
int quickSwaps = 0;
int partition(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    int pivot = nums[end];
    int i = start - 1;
    for (int j = start; j <= end; ++j) {
        if (checkPause(window, paused)) {
            return -1;
        }
        this_thread::sleep_for(chrono::microseconds(800));
        ++quickComps;
        if (nums[j] < pivot) {
            ++quickSwaps;
            ++i;
            swap(nums[i], nums[j]);
            if (rand() % 4 == 0) {
                updateWindow(window, currentScreen, nums, font, cursorOn, j, false, "QuickSort", quickComps, quickSwaps);
            }
        }
    }
    ++quickSwaps;
    swap(nums[i + 1], nums[end]);
    updateWindow(window, currentScreen, nums, font, cursorOn, i, false, "QuickSort", quickComps, quickSwaps);
    return i + 1;
}

/* Quick Sort Algorithm */
/* If return false, it means to stop the whole algorithm */
bool quickSort(vector<int>& nums, int start, int end, sf::RenderWindow& window, Screen currentScreen, bool cursorOn, sf::Font& font, bool& paused) {
    if (start == 0 && end == nums.size() - 1) {
        quickComps = 0;
        quickSwaps = 0;
    }
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
    int comparisons = 0;
    int swaps = 0;
    while (true) {
        if (checkPause(window, paused)) {
            return;
        }
        shuffle(nums);
        bool good = true;
        for (int i = 0; i < nums.size() - 1; ++i) {
            updateWindow(window, currentScreen, nums, font, cursorOn, i, false, "BogoSort", comparisons, swaps);
            ++comparisons;
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