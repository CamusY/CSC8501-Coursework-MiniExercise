#include <iostream>
#include <stdio.h>
#include <random>
#include <iomanip>

using namespace std;

const int numDoors = 3;
bool doors[numDoors] = { false, false, false }; // false means closed, true means open
// so let's assume there are n doors, all closed initially
// and the host opens the doors, which left m doors closed
// so the host open n-m-1 doors
// and m equals 1 ususally

// in that case, the P_stay = 1/n, and P_switch = (n-1)/n
// and if the host opens n-m-1 doors, then P_switch_random_m = (n-1)/(mn)
// so if m = 1, then P_switch_random_1 = (n-1)/n


//BUT the puzzle need Monte Carlo simulation to verify the result
enum class Strategy { STAY, SWITCH_TO_SINGLE, SWITCH_RANDOM_M };

double theoreticalProbability(size_t numDoors, size_t numRemainingUnopened, Strategy strategy) {
	if (numDoors < 2) return 0.0;
	if (strategy == Strategy::STAY) return 1.0 / numDoors;
	if (strategy == Strategy::SWITCH_TO_SINGLE){
		if (numRemainingUnopened != 1) return (numDoors - 1.0) / numDoors; // invalid
		else return (numDoors - 1.0) / numDoors;
	}
	if (strategy == Strategy::SWITCH_RANDOM_M) {
		size_t m = numRemainingUnopened;
		if (m == 0) return 0.0; // invalid
		return (numDoors - 1.0) / (m * numDoors);
	}
	return 0.0; // should not reach here
}

struct SimulationResult {
	uint64_t wins;
	uint64_t trials;
};

// acturally I want to use rand() but it is not thread safe, so I use mt19937
SimulationResult Monte_Carlo(size_t numDoors, size_t numRemainingUnopened, Strategy strategy, uint64_t trails, mt19937_64 &rng) {
	uniform_int_distribution<size_t> doorDist(0, numDoors - 1);
	uint64_t wins = 0;

	for (uint64_t t = 0; t < trails; ++t) {
		std::size_t prizeDoor = doorDist(rng);
		std::size_t initialChoice = doorDist(rng);

		bool win = false;
		// host opens n-m-1 doors that are not the prize door and not the player choice
		if(strategy == Strategy::STAY) 
			win = (initialChoice == prizeDoor);
		else if (strategy == Strategy::SWITCH_TO_SINGLE)
			win = (initialChoice != prizeDoor);
		else if (strategy == Strategy::SWITCH_RANDOM_M) {
			size_t m = numRemainingUnopened;
			if (m == 0) win = false; // invalid
			else {
				// the player switches to one of the m remaining unopened doors
				// if the initial choice is the prize door, then the player loses
				// if the initial choice is not the prize door, then the player wins with probability 1/m
				if (initialChoice == prizeDoor) win = false;
				else {
					uniform_int_distribution<size_t> switchDist(0, m - 1);
					size_t switchChoice = switchDist(rng);
					win = (switchChoice == 0); // only one of the m doors has the prize
				}
			}
		}
		if (win) wins++;
	}
	return { wins, trails };
}

int main() {
	size_t numDoors = 3; // n
	size_t numRemainingUnopened = 1; // m
	uint64_t numTrials = 1000000; // number of Monte Carlo trials
	Strategy strategy = Strategy::SWITCH_RANDOM_M;
	
	random_device rd;
	mt19937_64 rng(rd());

	SimulationResult res = Monte_Carlo(numDoors, numRemainingUnopened, strategy, numTrials, rng);
	double p_hat = static_cast<double>(res.wins) / static_cast<double>(res.trials);
	double p_theoretical = theoreticalProbability(numDoors, numRemainingUnopened, strategy);

	double se = sqrt(p_hat * (1.0 - p_hat) / static_cast<double>(res.trials));
	double z = 1.96; // for 95% confidence interval
	double ci_lower = p_hat - z * se;
	double ci_upper = p_hat + z * se;

	cout << fixed << setprecision(6);


}