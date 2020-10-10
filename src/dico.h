/**
  * @authors LAUGIER Colin, RADJA Samy, SOLLIER Alexandre, TRON Anthony
  * @date 10/10/2020
  * @brief The dico class
  */

#ifndef DICO_H
#define DICO_H

#include <string>
#include <map>
#include <unordered_set>

typedef unsigned char word_size_t;

class dico
{

private:
    std::map<word_size_t, std::unordered_set<std::string>> m_dico;

public:
    void add(const std::string& word);
    void show() const;
    bool find(const std::string& word) const;

    bool parseFile(const std::string& file);
};

#endif // DICO_H
