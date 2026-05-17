#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// =====================
// Queen Solution Class
// =====================
class Queen {
public:
    vector<int> board;
    int fit;

    Queen(int n = 8) {
        board.resize(n);
        fit = 0;
    }
};

// =====================
// Genetic Algorithm
// =====================
class GA {

private:
    int n = 8;
    int popSize = 200;
    int maxGen = 5000;
    double mutRate = 0.2;

    vector<Queen> pop;

public:

    // Fitness Function
    int fitness(vector<int> b) {

        int score = 0;

        for (int i = 0; i < n; i++) {

            for (int j = i + 1; j < n; j++) {

                bool row = (b[i] == b[j]);

                bool diag =
                    abs(b[i] - b[j]) == abs(i - j);

                if (!row && !diag)
                    score++;
            }
        }

        return score;
    }
