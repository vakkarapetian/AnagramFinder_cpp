#ifndef __LETTERCOUNT_H
#define __LETTERCOUNT_H

const int NUMLETTERS = 26;

class LetterCount
{
private:
    int* count;
    
public:
    LetterCount();
    LetterCount(const char*);
    LetterCount(const LetterCount& copy);
    LetterCount(LetterCount&& move);
    ~LetterCount();
    int totalCount() const;
    bool hasAsMany(const LetterCount& oth) const;
    //bool hasAsMany(const char* str) const;
    bool equals(const LetterCount& oth) const;
    //bool equals(const char* str) const;
    void print() const;
    void subtract(const LetterCount& other);//void subtract(const char* str);
    void add(const LetterCount& other);//void add(const char* str);
};

#endif
