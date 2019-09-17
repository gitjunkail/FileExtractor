#pragma warning(disable:4996)

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void incrementFilename(std::string& outputFilename)
{
	static int fileCounter = 1;
	outputFilename = std::to_string(++fileCounter) + ".pdf";
}

int main(int argc, char* argv[]) {
	std::ifstream input(argv[1], std::ifstream::binary);

	//continue if input is correct
	if (input) {
		std::string outputFilename = "1.pdf";
		std::ofstream output(outputFilename, std::ofstream::binary);

		//test case, paste the hex number of the known header
		std::vector<char> testCase{ 0x25, 0x50, 0x44, 0x46, 0x2D, 0x31, 0x2E, 0x37 };
		//initialize a vector for future compare with test case during runtime
		std::vector<char> memBytes;
		memBytes.reserve(testCase.size());

		bool foundFirstFile = false;

		//get the file size
		input.seekg(0, input.end);
		int length = input.tellg();
		input.seekg(0, input.beg);

		//store the file into a buffer
		char* buffer = new char[length];
		input.read(buffer, length);
		input.close();

		//store found files
		for (int i = 0; i < length; i++) {
			if (buffer[i] == testCase[0]) {
				for (int j = 0; j < testCase.size(); j++) {
					memBytes.emplace_back( buffer[i+j] );
				}
					
				if (testCase == memBytes) {
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

				//clear stored memBytes
				memBytes.clear();
			}
			else if (foundFirstFile == true) {
				output.write(&buffer[i], 1);
			}
		}

		//clear used memories
		delete[] buffer;
	}

	return 0;
}