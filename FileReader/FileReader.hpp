#pragma once

#include <fstream>
#include <string>
#include "DynamicArray.hpp"

namespace CS150 {

/**
 * @brief A wrapper class for std::ifstream that provides convenient file reading methods.
 */
class FileReader {
private:
  std::ifstream fileStream; ///< Internal file stream object.
  std::string fileName;     ///< Stores the name of the currently open file.

public:
  /**
   * @brief Default constructor.
   */
  FileReader() = default;

  /**
   * @brief Constructs a FileReader and opens the specified file.
   * @param filePath The path to the file to open.
   */
  explicit FileReader(const std::string& filePath);

  /**
   * @brief Opens the file with the given filename.
   *
   * If another file is already open, it is first closed.
   *
   * @param filename The name (or path) of the file to open.
   * @return True if the file was successfully opened; false otherwise.
   */
  bool OpenFile(const std::string& filename);

  /**
   * @brief Checks if the file stream is open.
   * @return True if a file is currently open; false otherwise.
   */
  bool isOpen() const;

  /**
   * @brief Reads the next whitespace-delimited word from the file.
   * @return The next word read from the file.
   */
  std::string readWord();

  /**
   * @brief Reads the next line from the file.
   * @return The next line read from the file.
   */
  std::string readLine();

  /**
   * @brief Reads from the file until the specified delimiter is encountered.
   * @param delim The delimiter character.
   * @return The string read up to (but not including) the delimiter.
   */
  std::string readDelim(const char delim);
  
  /**
   * @brief Reads all lines from the file into a DynamicArray.
   *
   * Each element of the DynamicArray will contain one line from the file.
   *
   * @return A DynamicArray containing all the lines read from the file.
   */
  DynamicArray readLines();

  /**
   * @brief Closes the currently open file.
   */
  void closeFile();

  /**
   * @brief Gets the name of the currently open file.
   * @return The file name.
   */
  std::string getFileName() const;
};

} // namespace CS150
