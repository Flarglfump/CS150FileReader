#pragma once
#include <string>

namespace CS150 {

/**
 * @brief A dynamic array class for storing strings.
 *
 * This class manages a dynamically allocated array of strings, allowing
 * for operations such as insertion, appending, resizing, and more.
 */
class DynamicArray {
public:
  /**
   * @brief Default constructor.
   *
   * Constructs an empty DynamicArray with no allocated capacity.
   */
  DynamicArray();

  /**
   * @brief Constructs a DynamicArray with a specified initial capacity.
   * @param capacity The initial capacity of the array.
   */
  DynamicArray(unsigned int capacity);

  /**
   * @brief Destructor.
   *
   * Frees any allocated memory.
   */
  ~DynamicArray();

  /**
   * @brief Reserves space for at least new_capacity elements.
   *
   * If new_capacity is greater than the current capacity, the internal buffer
   * is reallocated.
   *
   * @param new_capacity The new capacity to reserve.
   * @return The updated capacity.
   */
  unsigned int reserve(unsigned int new_capacity);

  /**
   * @brief Truncates the array to a new length.
   *
   * If new_length is less than the current length, the array is truncated.
   *
   * @param new_length The new length of the array.
   * @return The updated length.
   */
  unsigned int truncate(unsigned int new_length);

  /**
   * @brief Inserts copies of a string into the array at a given position.
   *
   * If the position is -1, the insertion happens at the end.
   * Negative positions are interpreted as offsets from the end.
   *
   * @param val The string value to insert.
   * @param position The position at which to insert (-1 for append).
   * @param copies The number of copies to insert.
   * @return The new length of the array.
   */
  int insert(std::string val, int position=-1, unsigned int copies=1);

  /**
   * @brief Inserts copies of another DynamicArray into this array at a given position.
   *
   * The elements of the provided array are inserted sequentially.
   *
   * @param arr The DynamicArray whose elements to insert.
   * @param position The position at which to insert (-1 for append).
   * @param copies The number of times to insert the entire array.
   * @return The new length of the array.
   */
  int insert(DynamicArray& arr, int position=-1, unsigned int copies=1);

  /**
   * @brief Appends copies of a string to the end of the array.
   *
   * @param val The string value to append.
   * @param copies The number of copies to append.
   * @return The new length of the array.
   */
  int append(std::string val, unsigned int copies=1);

  /**
   * @brief Appends copies of another DynamicArray to the end of this array.
   *
   * @param arr The DynamicArray to append.
   * @param copies The number of times to append the array.
   * @return The new length of the array.
   */
  int append(DynamicArray& arr, unsigned int copies=1);

  /**
   * @brief Returns the capacity of the array.
   * @return The capacity.
   */
  unsigned int getCapacity() const;

  /**
   * @brief Returns the current length of the array.
   * @return The number of elements in the array.
   */
  unsigned int getLength() const;

  /**
   * @brief Returns the current length of the array.
   * @return The number of elements in the array.
   */
  unsigned int length() const;

  /**
   * @brief Returns the current length of the array.
   * @return The number of elements in the array.
   */
  unsigned int size() const;

  /**
   * @brief Checks whether the array is empty.
   * @return True if the array is empty, false otherwise.
   */
  bool empty() const;

  /**
   * @brief Clears the array without deallocating memory.
   */
  void clear();

  /**
   * @brief Frees the internal buffer and resets the array.
   */
  void free();

  /**
   * @brief Converts the array to a string.
   *
   * Elements are separated by the provided separator.
   *
   * @param sep The separator to use between elements.
   * @return A string representation of the array.
   */
  std::string toString(std::string sep=", ");

  /**
   * @brief Prints the array to the standard output.
   *
   * Optionally prints element numbering and uses the provided separator.
   *
   * @param doNumbering If true, prints element numbers.
   * @param sep The separator to use between elements.
   */
  void print(bool doNumbering=true, std::string sep="\n");

  /**
   * @brief Returns a reference to the element at the given index.
   *
   * @param index The index of the element.
   * @return A reference to the string at the given index.
   * @throws std::out_of_range if the index is out of range.
   */
  std::string& at(unsigned int index);

  /**
   * @brief Returns a const reference to the element at the given index.
   *
   * @param index The index of the element.
   * @return A const reference to the string at the given index.
   * @throws std::out_of_range if the index is out of range.
   */
  const std::string& at(unsigned int index) const;

  /**
   * @brief Subscript operator to access elements.
   *
   * @param index The index of the element.
   * @return A reference to the string at the given index.
   * @throws std::out_of_range if the index is out of range.
   */
  std::string& operator[](unsigned int index);

  /**
   * @brief Subscript operator to access elements (const version).
   *
   * @param index The index of the element.
   * @return A const reference to the string at the given index.
   * @throws std::out_of_range if the index is out of range.
   */
  const std::string& operator[](unsigned int index) const;

private:
  std::string* buffer;       ///< Pointer to the dynamic array of strings.
  unsigned int capacity;     ///< The allocated capacity of the array.
  unsigned int len;          ///< The current number of elements in the array.

  /**
   * @brief Grows the internal buffer to fit at least requiredSize elements.
   *
   * @param requiredSize The minimum required size.
   * @return The new capacity.
   */
  unsigned int grow_to_fit(unsigned int requiredSize);
};

} // namespace CS150
