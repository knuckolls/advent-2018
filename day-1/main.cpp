#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <unordered_map>

struct OperatorIntPair {
    std::string op;
    int number;
};

std::istream& operator>>(std::istream& is, OperatorIntPair& pair) {
    // read the entire line into a string
    std::string line;
    std::getline(is, line);

    // parse with a string stream
    std::istringstream ss(line);
    pair.op = ss.get();
    ss >> pair.number;
}


void program1() {
    std::ifstream file("/mnt/c/Users/kevin/Documents/Code/src/github.com/knuckolls/advent-2018/day-1/input.txt");
    std::vector<OperatorIntPair> pairs;

    if (file) {
        std::copy(
                std::istream_iterator<OperatorIntPair>(file),
                std::istream_iterator<OperatorIntPair>(),
                std::back_inserter(pairs)
        );
    } else {
        std::cerr << "Couldn't open file.";
    }

    int accumulate = 0;

    accumulate = std::accumulate(pairs.begin(), pairs.end(), accumulate, [](int &acc, OperatorIntPair &pair) {
        if (pair.op == "+") {
            acc = acc + pair.number;
        } else {
            acc = acc - pair.number;
        }

        return acc;
    });
    std::cout << "answer: " << accumulate << std::endl;
}

void program2() {
    std::ifstream file("/mnt/c/Users/kevin/Documents/Code/src/github.com/knuckolls/advent-2018/day-1/input.txt");
    std::vector<OperatorIntPair> pairs;

    if (file) {
        std::copy(
                std::istream_iterator<OperatorIntPair>(file),
                std::istream_iterator<OperatorIntPair>(),
                std::back_inserter(pairs)
        );
    } else {
        std::cerr << "Couldn't open file.";
    }

    int accumulate = 0;
    std::unordered_map<int,int> seen = {};
    bool found     = false;
    int  found_val;

    while (!found) {
        accumulate = std::accumulate(pairs.begin(), pairs.end(), accumulate, [&found,&seen,&found_val](int &acc, OperatorIntPair &pair) {
            if (pair.op == "+") {
                acc = acc + pair.number;
            } else {
                acc = acc - pair.number;
            }

            // keep a set of seen accumulations, and set an answer val when the current one is a previously seen item.
            if (!found) {
                auto query = seen.find(acc);
                if (query != seen.end()) {
                    found = true;
                    found_val = acc;
                }

                seen.insert(std::make_pair(acc,0));
            }

            return acc;
        });
    }
    std::cout << "answer: " << accumulate << std::endl;
    std::cout << "found_val: "  << found_val << std::endl;
}

int main() {
    typedef std::chrono::high_resolution_clock Clock;

    std::cout << "Phase 1:" << std::endl;
    auto t1 = Clock::now();
    program1();
    auto t2 = Clock::now();

    int p1_nanoseconds  = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
    float p1_microseconds = static_cast< float >(p1_nanoseconds)/1000;
    float p1_milliseconds = static_cast< float >(p1_nanoseconds)/1000000;
    float p1_seconds      = static_cast< float >(p1_nanoseconds)/1000000000;

    std::cout << "nanoseconds: "  << p1_nanoseconds  << std::endl;
    std::cout << "microseconds: " << p1_microseconds << std::endl;
    std::cout << "milliseconds: " << p1_milliseconds << std::endl;
    std::cout << "seconds: "      << p1_seconds      << std::endl;

    std::cout << std::endl;
    
    std::cout << "Phase 2:" << std::endl;
    auto t3 = Clock::now();
    program2();
    auto t4 = Clock::now();

    int p2_nanoseconds  = std::chrono::duration_cast<std::chrono::nanoseconds>(t4 - t3).count();
    float p2_microseconds = static_cast< float >(p2_nanoseconds)/1000;
    float p2_milliseconds = static_cast< float >(p2_nanoseconds)/1000000;
    float p2_seconds      = static_cast< float >(p2_nanoseconds)/1000000000;

    std::cout << "nanoseconds: "  << p2_nanoseconds  << std::endl;
    std::cout << "microseconds: " << p2_microseconds << std::endl;
    std::cout << "milliseconds: " << p2_milliseconds << std::endl;
    std::cout << "seconds: "      << p2_seconds      << std::endl;

    return 0;
}