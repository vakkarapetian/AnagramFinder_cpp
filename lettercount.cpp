#include <iostream>
#include <sstream>
#include <cstring>
#include <cctype>
using namespace std;

#include "lettercount.h"

LetterCount::LetterCount()
{
  count = new int[NUMLETTERS];
  memset(count, 0, NUMLETTERS * sizeof(int));
}

LetterCount::LetterCount(const char* str)
{
  count = new int[NUMLETTERS];
  memset(count, 0, NUMLETTERS * sizeof(int));

  istringstream iss(str);
  char c;
  while (iss >> c)
    if (isalpha(c))
      count[tolower(c) - 'a']++;
}

LetterCount::LetterCount(const LetterCount& copy)
{
  count = new int[NUMLETTERS];
  memcpy(count, copy.count, NUMLETTERS * sizeof(int));
}

LetterCount::LetterCount(LetterCount&& move)
{
  count = move.count;
  move.count = nullptr;
}

LetterCount::~LetterCount()
{
  delete[] count;
}

bool LetterCount::hasAsMany(const LetterCount& oth) const
{
  for (int i = 0; i < NUMLETTERS; i++)
    if (count[i] < oth.count[i])
      return false;
  return true;
}

bool LetterCount::equals(const LetterCount& oth) const
{
  for (int i = 0; i < NUMLETTERS; i++)
    if (count[i] != oth.count[i])
      return false;
  return true;
}

int LetterCount::totalCount() const
{
  int sum = 0;
  for (int i = 0; i < NUMLETTERS; i++)
    sum += count[i];
  return sum;
}

void LetterCount::print() const
{
  int i;

  for (i = 0; i < NUMLETTERS && count[i] == 0; i++);
  if (i == NUMLETTERS)
    cout << "none";
  else
  {
    cout << static_cast<char>(i + 'a') << ' ' << count[i];
    for (i++; i < NUMLETTERS; i++)
      if (count[i] > 0)
        cout << ' ' << static_cast<char>(i + 'a') << ' ' << count[i];
  }
}

void LetterCount::subtract(const LetterCount& oth)
{
  if (!hasAsMany(oth))
    return;

  for (int i = 0; i < NUMLETTERS; i++)
    count[i] -= oth.count[i];
}

void LetterCount::add(const LetterCount& oth)
{
  for (int i = 0; i < NUMLETTERS; i++)
    count[i] += oth.count[i];
}

/*
bool LetterCount::hasAsMany(const char* str) const
{
  return hasAsMany(LetterCount(str));
}

bool LetterCount::equals(const char* str) const
{
  return equals(LetterCount(str));
}

void LetterCount::subtract(const char* str)
{
  subtract(LetterCount(str));
}

void LetterCount::add(const char* str)
{
  add(LetterCount(str));
}
//*/