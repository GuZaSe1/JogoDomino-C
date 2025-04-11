#ifndef JOGADOR_HPP
#define JOGADOR_HPP
#include <string>
#include "lista_encadeada.hpp"
#include "peca_domino.hpp"
using namespace std;

struct Jogador{         //Estrutura para representar um jogador;
    string nome;
    ListaEncadeada<PecaDomino> mao;
};
#endif