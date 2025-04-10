#include "jogo_domino.hpp"

int main() {
    JogoDomino jogo;
    jogo.jogadorAtual = 0;
    jogo.rodadaAtual = 1;
    jogo.maxRodadas = 100;

    gerarPecas(jogo.monte);
    embaralhar(jogo.monte);

    int numJogadores = 3;       // Número de jogadores
    int pecasPorJogador = 7;    // Número de peças por jogador
    for (int i = 0; i < numJogadores; i++){
        Jogador j;
        j.nome = "Jogador " + to_string(i + 1);
        jogo.jogadores.push_back(j);
    }

    distribuirPecas(jogo, pecasPorJogador);     
    jogo.mesa.inicializar();        

    iniciarJogo(jogo);

    return 0;
}   //fazer com que o jogdor com a peça mais alta comece jogando
    //salvar em pastas
    //testar possibilidades