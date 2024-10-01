#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

int main() {
  std::ofstream outputFile("test7.in"); // create a new output file or overwrite an existing one

  if (outputFile.is_open()) { // check if the file was opened successfully

    int v = 100;
    int s = 100;

    srand(time(0));
    outputFile << v << " " << s << '\n';
    for(int i= 0; i < v; i++){
        for(int j = 0; j < s; j++){
            outputFile << rand()%100000 << " ";
        }
        outputFile << '\n';
    }
    outputFile.close(); // close the file when done
    std::cout << "Data was written to output.txt\n";
  }
  else {
    std::cerr << "Error opening file\n";
  }

  return 0;
}
