#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::ifstream input("input.txt");

	int aim = 0;
	int horizontal_pos = 0;
	int depth = 0;

	std::string cmd;
	int tmp;

	while(input >> cmd && input >> tmp) {
		if(cmd == "forward") {
			horizontal_pos += tmp;
			depth += (aim * tmp);
		} else if(cmd == "down") {
			aim += tmp;
		} else if(cmd == "up") {
			aim -= tmp;
		}
	}

	std::cout << (horizontal_pos * depth) << '\n';

	return 0;
}