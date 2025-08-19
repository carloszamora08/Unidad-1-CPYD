#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>

class Summation {
    int number;
    int total;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;

public:
    Summation(int number) : number(number), total(0), gen(rd()), distrib(1, 1000) {}

    void doSum() {
        for (int i = 0; i < 100; i++) {
            total += distrib(gen);
        }
    }

    int Number() const {
        return number;
    }

    int Total() const {
        return total;
    }

    static bool greaterComparison(std::shared_ptr<Summation> summation1, std::shared_ptr<Summation> summation2) {
        return summation1->Total() > summation2->Total();
    }
};

int main() {
    const int TOTAL_THREADS = 10;

    std::vector<std::shared_ptr<std::thread>> threads(TOTAL_THREADS);
    std::vector<std::shared_ptr<Summation>> summations(TOTAL_THREADS);

    for (int i = 0; i < TOTAL_THREADS; i++) {
        summations[i] = std::make_shared<Summation>(i + 1);
        threads[i] = std::make_shared<std::thread>([&, i](){summations[i]->doSum();});
    }

    for (int i = 0; i < TOTAL_THREADS; i++) {
        threads[i]->join();
    }

    for (int i = 0; i < TOTAL_THREADS; i++) {
        std::cout << "El thread #" << i + 1 << " sumo: " << summations[i]->Total() << std::endl;
    }

    std::sort(summations.begin(), summations.end(), Summation::greaterComparison);

    std::cout << "El thread con mayor puntuacion fue el #" << summations[0]->Number() << " y sumo: " << summations[0]->Total() << std::endl;

    return 0;
}