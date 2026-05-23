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

    // Mutation
    void mutate(Queen &q) {

        double p = (double)rand() / RAND_MAX;

        if (p < mutRate) {

            int col = rand() % n;
            int row = rand() % n;

            q.board[col] = row;

            q.fit = fitness(q.board);
        }
    }

    // Solve
    Queen solve(bool useRoulette, ofstream &file) {

        startPop();

        Queen best(n);

        for (int g = 1; g <= maxGen; g++) {

            for (int i = 0; i < pop.size(); i++) {

                if (pop[i].fit > best.fit)
                    best = pop[i];
            }

            // Save Fitness Values
           file << g << " "
     << pop[0].fit
     << endl;

            // Max Fitness = 28
            if (best.fit == 28) {

                cout << "Generation: "
                     << g << endl;

                return best;
            }

            vector<Queen> newPop;

            while (newPop.size() < popSize) {

                Queen p1(n), p2(n);

                if (useRoulette) {

                    p1 = roulette();
                    p2 = roulette();
                }
                else {

                    p1 = tournament();
                    p2 = tournament();
                }

                Queen child = cross(p1, p2);

                mutate(child);

                newPop.push_back(child);
            }

            pop = newPop;
        }

        return best;
    }
};



// =====================
// Main
// =====================
int main() {

    srand(time(0));

    ofstream file("result.txt");

    GA ga;

    for (int t = 1; t <= 5; t++) {

        cout << "Test " << t << endl;

        bool rouletteMethod = (t % 2 == 1);

        Queen ans =
            ga.solve(rouletteMethod, file);
        
        cout << "Fitness: "
             << ans.fit << endl;

        cout << "Board: ";

        file << "Test " << t << endl;

        for (int i = 0;
             i < ans.board.size();
             i++) {

            cout << ans.board[i] << " ";

            file << ans.board[i] << " ";
        }

        cout << endl << endl;

        file << endl;

        file << "Fitness: "
             << ans.fit
             << endl << endl;
    }

    file.close();

    return 0;
    }
