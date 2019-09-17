#pragma warning(disable:4996)

#include <fstream>
#include <iostream>
#include <string>

void incrementFilename(std::string& outputFilename)
{
	static int fileCounter = 1;
	outputFilename = std::to_string(++fileCounter) + ".pdf";
}

int main(int argc, char* argv[]) {
	std::ifstream input(argv[1], std::ifstream::binary);

	if (input) {
		std::string outputFilename = "1.pdf";
		std::ofstream output(outputFilename, std::ofstream::binary);

		//test case, paste the hex number of the known header
		unsigned char testCase[8] = { 0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x37 };

		bool foundFirstFile = false;

		input.seekg(0, input.end);
		int length = input.tellg();
		input.seekg(0, input.beg);

		char* buffer = new char[length];

		input.read(buffer, length);
		input.close();

		for (int i = 0; i < length; i++) {
			if (buffer[i] == testCase[0]) {
				char memBytes[sizeof(testCase) / sizeof(testCase[0])] = { buffer[i], buffer[i + 1], buffer[i + 2], buffer[i + 3], buffer[i + 4], buffer[i + 5], buffer[i + 6], buffer[i + 7] };
				if (memcmp(memBytes, testCase, sizeof(testCase) / sizeof(testCase[0])) == 0) {
					if (foundFirstFile) {
						output.close();
						incrementFilename(outputFilename);
						output.open(outputFilename, std::ofstream::binary);
					}
					output.write(&buffer[i], 1);
					foundFirstFile = true;
				}
				else if (foundFirstFile == true) {
					output.write(&buffer[i], 1);
				}
			}
			else if (foundFirstFile == true) {
				output.write(&buffer[i], 1);
			}
		}

		delete[] buffer;
	}

	return 0;
}