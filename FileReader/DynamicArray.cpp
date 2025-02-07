#include "DynamicArray.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

CS150::DynamicArray::DynamicArray() {
  // Initially, buffer completely empty and not allocated
  buffer = nullptr;
  len = 0;
  capacity = 0;
}
CS150::DynamicArray::DynamicArray(unsigned int capacity) {
  // Nothing stored in buffer, but buffer is allocated
  buffer = new std::string[capacity];
  this->capacity = capacity;
  len = 0;
}

CS150::DynamicArray::~DynamicArray() {
  // Free dynamically allocated buffer on destruction of object
  if (buffer != nullptr) {
    delete[] buffer;
  }
  capacity = 0;
  len = 0;
}

unsigned int CS150::DynamicArray::reserve(unsigned int new_capacity) {
  if (new_capacity <= capacity) {
    // Have already reserved enough space
    return capacity;
  }

  // Create new buffer and copy over elements from old buffer
  std::string* newBuf = new std::string[new_capacity];
  for (unsigned int i = 0; i < len; i++) {
    newBuf[i] = buffer[i];
  }

  // Free old buffer and point to new buffer, update capacity
  if (buffer != nullptr) {
    delete[] buffer;
  }
  buffer = newBuf;
  capacity = new_capacity;

  return capacity;
}
unsigned int CS150::DynamicArray::truncate(unsigned int new_length) {
  if (new_length < len) {
    len = new_length;
  }
  return len;
}

int CS150::DynamicArray::insert(std::string val, int position, unsigned int copies) {
  unsigned int newLen = len + copies; // Elements in buffer after insertion
  int insertPos = len == 0 ? 0 : // If empty, insert at position 0
                  position == -1 ? len : // If -1, insert at end 
                  (static_cast<int>(len) + (position % static_cast<int>(len))) % static_cast<int>(len); // Otherwise, handle position with wraparound logic
  int insertEndPos = insertPos + copies;
  grow_to_fit(newLen); // Resize buffer to fit enough elements if needed
  if (len != 0) {
    // Shift existing elements down to make room for new inserted elements
    for (int i = static_cast<int>(len) - 1; i >= insertPos; i--) {
      buffer[i+copies] = buffer[i];
    }
  }
  // Insert new elements
  for (unsigned int i = insertPos; i < insertPos + copies; i++) {
    buffer[i] = val;
  }

  // Update length
  len = newLen; 
  return len;
}

int CS150::DynamicArray::insert(DynamicArray& arr, int position, unsigned int copies) {
  unsigned int copiedArrLen = arr.getLength();
  unsigned int insertSize = copies * copiedArrLen;
  unsigned int newLen = len + insertSize;
  int insertPos = len == 0 ? 0 :
                  position == -1 ? len :
                  (static_cast<int>(len) + (position % static_cast<int>(len))) % static_cast<int>(len);
  int insertEndPos = insertPos + insertSize;

  grow_to_fit(newLen);

  if (len != 0) {
    for (int i = static_cast<int>(len) - 1; i >= insertPos; i--) {
      buffer[i+insertSize] = buffer[i];  
    }
  }
  
  unsigned int curInsertPos = insertPos;
  for (unsigned int curCopy = 0; curCopy < copies && curInsertPos < insertEndPos; curCopy++) {
    for (unsigned int i = 0; i < copiedArrLen && curInsertPos < insertEndPos; i++) {
      buffer[curInsertPos++] = arr[i];
    }
  }
  
  len = newLen;
  return len;
}

int CS150::DynamicArray::append(std::string val, unsigned int copies) {
  return insert(val, -1, copies); // Insert at end of list
}
int CS150::DynamicArray::append(DynamicArray& arr, unsigned int copies) {
  return insert(arr, -1, copies); // Insert at end of list
}

unsigned int CS150::DynamicArray::getCapacity() const {
  return capacity;
}
unsigned int CS150::DynamicArray::getLength() const {
  return len;
}
unsigned int CS150::DynamicArray::length() const {
  return len;
}
unsigned int CS150::DynamicArray::size() const {
  return len;
}

bool CS150::DynamicArray::empty() const {
  return (len == 0);
}

void CS150::DynamicArray::clear() {
  len = 0; // Setting length to 0 effectively removes elements from list
}
void CS150::DynamicArray::free() {
  if (buffer != nullptr) {
    // Deallocate buffer if already allocated
    delete[] buffer;
    buffer = nullptr;
  }
  len = 0;
  capacity = 0;
}

std::string CS150::DynamicArray::toString(std::string sep) {
  std::stringstream ss;
  if (len == 0) {
    return ""; // Empty buffer means empty string
  }

  // Separator placed only between elements
  ss << buffer[0];
  for (unsigned int i = 0; i < len; i++) {
    ss << sep << buffer[i];
  }

  return ss.str();
}
void CS150::DynamicArray::print(bool doNumbering, std::string sep) {
  if (len == 0) {return;}
  unsigned int maxNumLen = std::to_string(len).length(); // Calculated to ensure equal spacing with different digit counts
  std::cout << std::left;
  for (int i = 0; i < len; i++) {
    if (doNumbering) {
      std::cout << std::setw(maxNumLen + 4) << "[" + std::to_string(i) + "]:";
    }
    std::cout << buffer[i] << sep;
  }
  std::cout << std::endl;
}

std::string& CS150::DynamicArray::at(unsigned int index) {
  if (index >= len) {
    throw std::out_of_range("Index out of range");
  }
  return buffer[index];
}
const std::string& CS150::DynamicArray::at(unsigned int index) const {
  if (index >= len) {
    throw std::out_of_range("Index out of range");
  }
  return buffer[index];
}

std::string& CS150::DynamicArray::operator[](unsigned int index) {
  if (index >= len) {
    throw std::out_of_range("Index out of range");
  }
  return buffer[index];
}
const std::string& CS150::DynamicArray::operator[](unsigned int index) const {
  if (index >= len) {
    throw std::out_of_range("Index out of range");
  }
  return buffer[index];
}

unsigned int CS150::DynamicArray::grow_to_fit(unsigned int requiredSize) {
  if (requiredSize <= capacity) {
    // Already have enough capacity
    return capacity;
  }

  unsigned int newCapacity = capacity;
  while (newCapacity < requiredSize) {
    // Double until required size is reached or surpassed
    // 1 added before doubling to handle when capacity is at 0
    newCapacity = (newCapacity + 1) * 2; 
  }

  // Allocate new buffer
  std::string* newBuf = new std::string[newCapacity];
  if (buffer != nullptr) {
    // Copy previous elements and free old buffer
    for (unsigned int i = 0; i < len; i++) {
      newBuf[i] = buffer[i];
    }
    delete[] buffer;
  }
  // Point to new buffer and update capacity
  buffer = newBuf;
  capacity = newCapacity;

  return capacity;
}