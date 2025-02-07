#include <iostream>
#include <fstream>
#include <string>
#include "FileReader.hpp"
#include "DynamicArray.hpp"

using namespace CS150;

/**
 * @brief Creates a temporary test file with sample content.
 *
 * @param filename The name of the file to create.
 */
void createTestFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Could not create test file." << std::endl;
        return;
    }
    // Write sample content.
    outFile << "Hello world\n";
    outFile << "This is a test file.\n";
    outFile << "Line three: testing, one, two, three!\n";
    outFile << "Final line with delimited content;another part;and one more part\n";
    outFile.close();
}

/**
 * @brief Unit tests for the FileReader and DynamicArray classes.
 */
int main() {
    const std::string testFileName = "test.txt";
    createTestFile(testFileName);

    FileReader fileReader;
    
    // Test: OpenFile and isOpen.
    std::cout << "Testing OpenFile() and isOpen():" << std::endl;
    if (fileReader.OpenFile(testFileName)) {
        std::cout << "File '" << fileReader.getFileName() << "' opened successfully." << std::endl;
    } else {
        std::cerr << "Failed to open file '" << testFileName << "'." << std::endl;
        return 1;
    }
    
    // Test: readWord
    std::cout << "\nTesting readWord():" << std::endl;
    // The first word in our file should be "Hello"
    std::string word = fileReader.readWord();
    std::cout << "First word: " << word << std::endl;
    
    // Test: readLine
    std::cout << "\nTesting readLine():" << std::endl;
    // The next call to readLine() should read the rest of the first line (if any) or the next line.
    // In our test file, after reading "Hello" from "Hello world", we should get "world"
    std::string line = fileReader.readLine();
    std::cout << "Next line: " << line << std::endl;
    
    // For a more controlled test, we close and re-open the file to test readLine() from the beginning.
    fileReader.closeFile();
    fileReader.OpenFile(testFileName);
    std::cout << "\nReading all lines using readLine():" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::string l = fileReader.readLine();
        std::cout << "Line " << i+1 << ": " << l << std::endl;
    }
    
    // Test: readDelim
    std::cout << "\nTesting readDelim():" << std::endl;
    // The fourth line contains semicolon-delimited parts.
    std::string delimPart = fileReader.readDelim(';');
    std::cout << "First part (up to ';'): " << delimPart << std::endl;
    delimPart = fileReader.readDelim(';');
    std::cout << "Second part (up to ';'): " << delimPart << std::endl;
    delimPart = fileReader.readDelim(';');
    std::cout << "Third part (rest of the line): " << delimPart << std::endl;
    
    // Test: readLines
    std::cout << "\nTesting readLines():" << std::endl;
    // Close and reopen the file to read from the beginning.
    fileReader.closeFile();
    fileReader.OpenFile(testFileName);
    DynamicArray lines = fileReader.readLines();
    std::cout << "Read " << lines.getLength() << " lines:" << std::endl;
    lines.print(); // Using DynamicArray's print() function
    
    // Test: closeFile
    std::cout << "\nTesting closeFile():" << std::endl;
    fileReader.closeFile();
    if (!fileReader.isOpen()) {
        std::cout << "File closed successfully." << std::endl;
    } else {
        std::cerr << "File did not close as expected." << std::endl;
    }
    
    // Clean up the temporary test file (optional)
    if (std::remove(testFileName.c_str()) == 0) {
        std::cout << "\nTemporary test file removed." << std::endl;
    } else {
        std::cerr << "\nWarning: Could not remove temporary test file." << std::endl;
    }

    return 0;
}
