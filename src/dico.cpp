/**
 * @authors LAUGIER Colin, RADJA Samy, SOLLIER Alexandre, TRON Anthony
 * @date 10/10/2020
 * @brief The dico.cpp class
 */
#include <fstream>
#include <iostream>

#include "dico.h"


void dico::add(const std::string &word)
{
    m_dico[word.size()].insert(word);
} // add

void dico::show() const
{
    for (auto it = m_dico.begin(); it != m_dico.end(); ++it)
    {
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
            std::cout << '\t' << *iter << std::endl;
    }
} // show

bool dico::find(const std::string &word) const
{
    try {
        return m_dico.at(word.length()).find(word) != m_dico.at(word.length()).end();
    } catch (const std::out_of_range& exception) {
        return false;
    }
} // find

bool dico::parseFile(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (ifs.fail()) return false;

    for (std::string aLine; getline(ifs, aLine); ){
        size_t pos(aLine.find_first_of("-/"));
        std::string word ((pos == std::string::npos) ? aLine : aLine.substr(0, pos));

        for (char& car : word)
            car = tolower (car);

        add(word);
    }

    return true;
} // parseFile
