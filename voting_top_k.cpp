#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cassert>
using namespace std;

const int NUM_VOTERS = 1000;
const int NUM_ALTERNATIVES = 5;
const int NUM_ALTERNATIVES_FACTORIAL = 120;
const int NUM_EXPERIMENT_DRAWS = 1000000;
const int NUM_DATA_POINTS = 18;
const int DATA_POINTS[NUM_DATA_POINTS] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900};

int preferences[NUM_ALTERNATIVES_FACTORIAL][NUM_ALTERNATIVES];

void init() {
	for (int i = 0; i < NUM_ALTERNATIVES; i++) {
		preferences[0][i] = i;
	}
	for (int i = 1; i < NUM_ALTERNATIVES_FACTORIAL; i++) {
		memcpy(preferences[i], preferences[i - 1], sizeof(preferences[i]));
		next_permutation(preferences[i], preferences[i] + NUM_ALTERNATIVES);
	}
}

class Result {
public:
	int result[NUM_ALTERNATIVES];
	Result() {
		for (int i = 0; i < NUM_ALTERNATIVES; i++) {
			result[i] = i;
		}
	}
};

class PredictabilityResult {
public:
	int num_experiment_draws;
	int predictable[NUM_ALTERNATIVES][NUM_DATA_POINTS];  // predictable[k][p]: if we can predict top k+1 using DATA_POINTS[p] samples
	void print(const char *name) const {
		printf("'%s': ", name);
		printf("[");
		for (int k = 0; k < NUM_ALTERNATIVES; k++) {
			printf("[");
			for (int p = 0; p < NUM_DATA_POINTS; p++) {
				printf("%.6f%s", (double)predictable[k][p] / num_experiment_draws, p == NUM_DATA_POINTS - 1 ? "]" : ", ");
			}
			printf("%s", k == NUM_ALTERNATIVES - 1 ? "]" : ",\n");
		}
		printf(",\n");
	}
};

class Sample {
public:
	vector<int> votes;
	static mt19937 gen;
	Sample(){}
	Sample(int n) {
		votes.reserve(n);
		uniform_int_distribution<int> dist(0, NUM_ALTERNATIVES_FACTORIAL);
		for (int i = 0; i < n; i++) {
			votes.emplace_back(dist(gen));
		}
	}
	template<typename T>
	void run_experiment(T voting_rule, PredictabilityResult &answer) {
		answer.num_experiment_draws++;
		Result r;  // voting result
		Result backup[NUM_DATA_POINTS];
		vector<int> scores(NUM_ALTERNATIVES * NUM_ALTERNATIVES, 0);
		int data_point_ptr = 0;
		for (vector<int>::iterator it = votes.begin(); it != votes.end(); it++) {
			bool update_result = false;
			if (data_point_ptr < NUM_DATA_POINTS && it - votes.begin() + 1 == DATA_POINTS[data_point_ptr]) {
				update_result = true;
				data_point_ptr++;
			}
			voting_rule(r, scores, votes.begin(), it, update_result || it == votes.end() - 1);
			if (update_result) {
				backup[data_point_ptr - 1] = r;
			}
		}
		for (int p = 0; p < NUM_DATA_POINTS; p++) {
			for (int k = 0; k < NUM_ALTERNATIVES; k++) {
				if (backup[p].result[k] != r.result[k]) {
					break;
				}
				// top-k predictable
				answer.predictable[k][p]++;
			}
		}
	}
};
mt19937 Sample::gen(0);

void plurality(Result &r, vector<int> &scores, vector<int>::iterator vote_begin, vector<int>::iterator new_vote, bool update_result) {
	scores[preferences[*new_vote][0]]++;
	if (update_result) {
		sort(r.result, r.result + NUM_ALTERNATIVES, [&](int a, int b) {
			return scores[a] == scores[b] ? a < b : scores[a] > scores[b];
		});
	}
}
void borda(Result &r, vector<int> &scores, vector<int>::iterator vote_begin, vector<int>::iterator new_vote, bool update_result) {
	for (int i = 0; i < NUM_ALTERNATIVES; i++) {
		scores[preferences[*new_vote][i]] += 4 - i;
	}
	if (update_result) {
		sort(r.result, r.result + NUM_ALTERNATIVES, [&](int a, int b) {
			return scores[a] == scores[b] ? a < b : scores[a] > scores[b];
		});
	}
}

PredictabilityResult answers[2];

int main() {
	init();
	for (int i = 0; i < NUM_EXPERIMENT_DRAWS; i++) {
		Sample s(NUM_VOTERS);
		s.run_experiment(plurality, answers[0]);
		s.run_experiment(borda, answers[1]);
	}
	answers[0].print("plurality");
	answers[1].print("borda");
	return 0;
}
