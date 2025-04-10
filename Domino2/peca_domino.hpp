#ifndef PECA_DOMINO_HPP
#define PECA_DOMINO_HPP
#include <iostream>
using namespace std;

struct PecaDomino{      //Estrutura para representar uma peça de dominó
    int ladoA;          //Cada peça tem dois lados, ladoA e ladoB, que podem ter valores de 0 a 6
    int ladoB;          //A peça [2|5] é equivalente a [5|2], então o operador == deve considerar isso

    void imprimir() const{
        cout << "[" << ladoA << "|" << ladoB << "]";
    }

    bool operator==(const PecaDomino& outra) const{
        return (ladoA == outra.ladoA && ladoB == outra.ladoB) ||
               (ladoA == outra.ladoB && ladoB == outra.ladoA);
    }
};
#endif