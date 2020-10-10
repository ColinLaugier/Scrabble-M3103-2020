/**
 * @authors LAUGIER Colin, RADJA Samy, SOLLIER Alexandre, TRON Anthony
 * @date 10/10/2020
 * @brief main.cpp
 */

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "dico.h"

using namespace std;

typedef std::vector<std::string> VStr_t;
typedef map<char, unsigned short> MScrabble_t;

unsigned short computeScore (const string& word, const MScrabble_t& scrabble)
{
    unsigned short Score(0);
    for (unsigned i(0); i < word.size(); ++i)
    {
        Score = Score + scrabble.at(toupper(word[i]));
    }

    return Score;
} // computeScore

void generer(const std::string& word, size_t loop, const std::string& sb, std::list<std::string>& wordList)
{
    if (sb.size() >= loop)
    {
        // Mot fini, on le met dans la liste de mots
        wordList.push_back(sb);
        return;
    }

    // On genere la lettre suivante
    for (size_t i = 0; i < word.size(); ++i)
    {
        // On enlève la lettre en cours du mot, pour éviter de la voir se répéter
        std::string tempWord = word;
        tempWord.erase(i, 1);

        generer(tempWord, loop, sb + word[i], wordList);
    }
} // generer - adapté de https://www.developpez.net/forums/d877113/c-cpp/c/debuter/afficher-toutes-combinaisons-possibles-partir-d-chaine-reference/#post4991039

std::list<std::string> fctMagique(const std::string& word, const MScrabble_t& scrabble)
{
    std::list<std::string> ret;

    // On genere toutes les combinaisons pour les 1..n lettres du mot
    for (size_t i = 1; i <= word.size(); ++i)
        generer(word, i, "", ret);

    // On trie la liste
    ret.sort([&](const std::string& a, const std::string& b) {
        return computeScore(b, scrabble) < computeScore(a, scrabble);
    });

    return ret;
} // fctMagique

MScrabble_t ChoiceScrabble (void)
{
    MScrabble_t scrabble ;
    while (true)
    {
        cout << "Dans quel langue jouez vous ? (1 : Fr | 2 : En)" << endl
             << "> ";

        char choice;
        cin >> choice;

        if (choice == '1')
        {
            scrabble['A'] =  1;
            scrabble['B'] =  3;
            scrabble['C'] =  3;
            scrabble['D'] =  2;
            scrabble['E'] =  1;
            scrabble['F'] =  4;
            scrabble['G'] =  2;
            scrabble['H'] =  4;
            scrabble['I'] =  1;
            scrabble['J'] =  8;
            scrabble['K'] = 10;
            scrabble['L'] =  1;
            scrabble['M'] =  2;
            scrabble['N'] =  1;
            scrabble['O'] =  1;
            scrabble['P'] =  3;
            scrabble['Q'] =  8;
            scrabble['R'] =  1;
            scrabble['S'] =  1;
            scrabble['T'] =  1;
            scrabble['U'] =  1;
            scrabble['V'] =  4;
            scrabble['W'] = 10;
            scrabble['X'] = 10;
            scrabble['Y'] = 10;
            scrabble['Z'] = 10;

            cin.ignore();
            return scrabble;
        }
        else if (choice == '2')
        {
            scrabble['A'] =  1;
            scrabble['B'] =  3;
            scrabble['C'] =  3;
            scrabble['D'] =  2;
            scrabble['E'] =  1;
            scrabble['F'] =  4;
            scrabble['G'] =  2;
            scrabble['H'] =  4;
            scrabble['I'] =  1;
            scrabble['J'] =  8;
            scrabble['K'] =  5;
            scrabble['L'] =  1;
            scrabble['M'] =  3;
            scrabble['N'] =  1;
            scrabble['O'] =  1;
            scrabble['P'] =  3;
            scrabble['Q'] = 10;
            scrabble['R'] =  1;
            scrabble['S'] =  1;
            scrabble['T'] =  1;
            scrabble['U'] =  1;
            scrabble['V'] =  4;
            scrabble['W'] =  4;
            scrabble['X'] =  8;
            scrabble['Y'] =  4;
            scrabble['Z'] = 10;

            cin.ignore();
            return scrabble;
        }
        else
        {
            cout << "Mauvaise manip !" << endl << endl;
        }
    }
} // ChoiceScrabble

void askForDico(dico& dict)
{
    while (true)
    {
        std::cout << "Entrez le nom du fichier de dictionnaire a utiliser: " << std::endl
                  << "> ";

        std::string input;
        std::getline(std::cin, input);

        if (dict.parseFile(input))
            return;
        else
            std::cout << "Fichier inexistant..." << std::endl << std::endl;
    }
} // askForDico

int main() {
    MScrabble_t scrabble(ChoiceScrabble());

    dico dict;
    askForDico(dict);

    while (true)
    {
        std::cout << "Entrez vos lettres: " << std::endl
                  << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::list<std::string> combos = fctMagique(input, scrabble);
        auto iter = combos.begin();
        while (iter != combos.end())
        {
            if (dict.find(*iter)) break;
            ++iter;
        }

        if (iter == combos.end())
            std::cout << "Mot inconnu :(" << std::endl;
        else
            std::cout << "Essayez " << std::quoted(*iter) << " (ce mot vaut " << computeScore(*iter, scrabble) << " points)" << std::endl;

        std::cout << std::endl;
    }

    return 0;
} // main
