#include <iostream>
#include <string>
#include <vector>

// entry structure for downloads
struct Entry{
  std::string _name; // The main filename,
  std::string _link; // the source link to download from
  std::string _filepath; // the directory the file is going to be downloaded to,
  int _priority;
  int _blocksize; // The number of lines needed to print the whole block. Usually 4 + num of subentries
  // For downloads with the same name with the exception of a number on the end ex. PART_1 PART_2
  std::vector<Entry> _subEntries; //TODO Implement proper handling of subentries

  Entry();
  Entry(std::string, std::string, std::string, int = 0);
  Entry(const Entry &);
  Entry(Entry &&);
  ~Entry();
  Entry& operator=(const Entry &);
  Entry& operator=(Entry &&);

  const char* to_string();
};
