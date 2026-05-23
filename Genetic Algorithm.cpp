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

    // Random Solution
    Queen randomQueen() {

        Queen q(n);

        for (int i = 0; i < n; i++) {
            q.board[i] = rand() % n;
        }

        q.fit = fitness(q.board);

        return q;
    }

    // Create Population
    void startPop() {

        pop.clear();

        for (int i = 0; i < popSize; i++) {
            pop.push_back(randomQueen());
        }
    }

    // Roulette Selection
    Queen roulette() {

        int total = 0;

        for (int i = 0; i < pop.size(); i++) {
            total += pop[i].fit;
        }

        int r = rand() % total;

        int sum = 0;

        for (int i = 0; i < pop.size(); i++) {

            sum += pop[i].fit;

            if (sum > r)
                return pop[i];
        }

        return pop[0];
    }

    // Tournament Selection
    Queen tournament() {

        Queen best = pop[rand() % pop.size()];

        for (int i = 0; i < 5; i++) {

            Queen q = pop[rand() % pop.size()];

            if (q.fit > best.fit)
                best = q;
        }

        return best;
    }
 // Cross Over
    Queen cross(Queen a, Queen b) {

        Queen child(n);

        int cut = rand() % n;

        for (int i = 0; i < cut; i++) {
            child.board[i] = a.board[i];
        }

        for (int i = cut; i < n; i++) {
            child.board[i] = b.board[i];
        }

        child.fit = fitness(child.board);

        return child;
    }

