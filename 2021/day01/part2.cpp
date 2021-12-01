#include <cstddef>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

int main() {
	std::ifstream input("input.txt");

	std::vector<int> depths;
	for(int depth; input >> depth; ) {
		depths.push_back(depth);
	}

	input.close();


	long int prev_sum = std::numeric_limits<long int>::max();
	long int cur_sum;
	std::size_t count = 0;

	for(std::size_t i = 0; i < (depths.size() - 2); ++i) {
		cur_sum = (long int)(depths[i + 0]) +
		          (long int)(depths[i + 1]) +
		          (long int)(depths[i + 2]);
		count += (cur_sum > prev_sum);
		prev_sum = cur_sum;
	}

	std::cout << count << '\n';

	return 0;
}
