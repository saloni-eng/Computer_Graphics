#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <numeric>
#include <span>
#include <tuple>
#include <vector>

// ==================================
// ========    Exercise 1    ========
// ==================================
std::pair<float, float> statistics(std::span<const float> values){
    // Your solution goes here
    if(values.size() == 0){
        return std::pair<float, float>{0.0f, 0.0f}; 
    }

    const float n = static_cast<float>(values.size());
    float sum = 0.0f;
    float standard = 0.0f;

    for(float v : values){
        sum += v;
    }

    const float mean = (sum / n);

    for(float v : values){
        standard += (v-mean)*(v-mean);
    }

    const float stddev = std::sqrt(standard/n);

    return { mean, stddev };
}

// ==================================
// ========    Exercise 2    ========
// ==================================
struct Tree {
    float value;
    std::vector<Tree> children;
};
// Your implementation goes here. Feel free to define helper functions/structs/classes in this
// file if you need to. Make sure to put them above this function to prevent linker warnings.

float countTreeHelper(const Tree& tree, int level, bool even){
    float sum = 0.0f;

    if(!even || (level%2 == 0)){
        sum += tree.value;
    }

    for(const Tree& child : tree.children){
        sum += countTreeHelper(child, level+1, even);
    }

    return sum;
}

float countTree(const Tree& tree, bool countOnlyEvenLevels)
{
    // Your solution goes here
    return countTreeHelper(tree, 0, countOnlyEvenLevels);

}
