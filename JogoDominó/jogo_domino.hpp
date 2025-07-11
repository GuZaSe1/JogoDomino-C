#ifndef JOGO_DOMINO_HPP
#define JOGO_DOMINO_HPP
#include <cstdlib>      //Para usar a função rand()
#include <ctime>        //Para usar a função time()
#include <vector>       //Para usar o vetor
#include <fstream>      //Para usar o arquivo de log
#include <iostream>     
#include "lista_estatica.hpp"
#include "lista_encadeada.hpp"
#include "jogador.hpp"
#include "peca_domino.hpp"
using namespace std;

ofstream arquivoLog("log.txt", ios::app);       // Arquivo de log para registrar as jogadas

struct JogoDomino{      //Estrutura para representar o jogo de dominó
    ListaEstatica<PecaDomino> monte;
    ListaEstatica<PecaDomino> mesa;
    vector<Jogador> jogadores;      // Usando vetor para armazenar os jogadores
    int jogadorAtual;
    int rodadaAtual;
    int maxRodadas;
};

void gerarPecas(ListaEstatica<PecaDomino>& lista){      //1.Gerar as peças de dominó
    lista.inicializar();                                // Cada peça é representada por dois números de 0 a 6, formando pares (ladoA, ladoB)
    for (int i = 0; i <= 6; i++){
        for (int j = i; j <= 6; j++){
            PecaDomino p = {i, j};
            lista.inserirFim(p);
        }
    }
}

void embaralhar(ListaEstatica<PecaDomino>& lista){      //2.Embaralhar as peças de dominó
    srand(time(0));
    for (int i = lista.tamanho - 1; i > 0; i--){
        int j = rand() % (i + 1);                   // Gera um índice aleatório entre 0 e 6
        swap(lista.dados[i], lista.dados[j]);       // Troca as peças de lugar
    }
}

void distribuirPecas(JogoDomino& jogo, int pecasPorJogador){        //3.Distribuir as peças de dominó para os jogadores
    for (auto& jogador : jogo.jogadores){
        jogador.mao.inicializar();
        for (int j = 0; j < pecasPorJogador; j++){
            PecaDomino p = *jogo.monte.obter(jogo.monte.tamanho - 1);       // Pega a última peça do monte
            jogo.monte.removerFim();
            jogador.mao.inserirFim(p);
        }
    }
}

void mostrarMaos(const JogoDomino& jogo){           //4.Mostrar as mãos dos jogadores
    cout << "\n==== MAOS INICIAIS ====" << endl;
    if (arquivoLog.is_open()){
        arquivoLog << "\n==== MãOS INICIAIS ====" << endl;
    }

    for (const auto& jogador : jogo.jogadores){
        cout << jogador.nome << ": ";
        if (arquivoLog.is_open()){              
            arquivoLog << jogador.nome << ": ";
        }

        Nodo<PecaDomino>* atual = jogador.mao.inicio;       // Percorre a lista de peças do jogador    
        while (atual) {
            atual->dado.imprimir();
            cout << " ";
            if (arquivoLog.is_open()){      
                arquivoLog << "[" << atual->dado.ladoA << "|" << atual->dado.ladoB << "] ";
            }
            atual = atual->prox;
        }
        cout << endl;
        if (arquivoLog.is_open()){
            arquivoLog << endl;
        }
    }

    cout << "======================\n" << endl;
    if (arquivoLog.is_open()){
        arquivoLog << "======================\n" << endl;
    }
}

int encontrarJogadorComMaiorDupla(JogoDomino& jogo, PecaDomino& duplaEncontrada){    //5.Encontrar o jogador com a maior dupla
    int jogadorComMaiorDupla = -1;
    int maiorValor = -1;

    for (size_t i = 0; i < jogo.jogadores.size(); i++){
        Nodo<PecaDomino>* atual = jogo.jogadores[i].mao.inicio;
        while (atual){
            if (atual->dado.ladoA == atual->dado.ladoB && atual->dado.ladoA > maiorValor){
                maiorValor = atual->dado.ladoA;
                duplaEncontrada = atual->dado;
                jogadorComMaiorDupla = i;       
            }
            atual = atual->prox;        
        }
    }

    return jogadorComMaiorDupla;
}

bool pecaEncaixa(const PecaDomino& p, const ListaEstatica<PecaDomino>& mesa){       //6.Verificar se a peça encaixa na mesa
    if (mesa.tamanho == 0) return true;

    const PecaDomino& esquerda = *mesa.obter(0);
    const PecaDomino& direita = *mesa.obter(mesa.tamanho - 1);      

    return p.ladoA == esquerda.ladoA || p.ladoB == esquerda.ladoA ||
           p.ladoA == direita.ladoB || p.ladoB == direita.ladoB;
}

bool jogarPecaNaMesa(ListaEstatica<PecaDomino>& mesa, PecaDomino peca){       //7.Jogar a peça na mesa
    if (mesa.tamanho == 0){
        mesa.inserirFim(peca);
        return true;
    }

    const PecaDomino& esquerda = *mesa.obter(0);
    const PecaDomino& direita = *mesa.obter(mesa.tamanho - 1);

    if (peca.ladoB == esquerda.ladoA){
        mesa.inserir(peca, 0);
        return true;
    } else if (peca.ladoA == esquerda.ladoA){
        swap(peca.ladoA, peca.ladoB);
        mesa.inserir(peca, 0);
        return true;
    } else if (peca.ladoA == direita.ladoB){
        mesa.inserirFim(peca);
        return true;
    } else if (peca.ladoB == direita.ladoB){
        swap(peca.ladoA, peca.ladoB);
        mesa.inserirFim(peca);
        return true;
    }

    return false;
}

void logJogada(const string& nome, const PecaDomino& peca, int rodada){        //8.Logar a jogada
    cout << "[Rodada " << rodada << "] " << nome << " jogou ";
    peca.imprimir();
    cout << endl;

    if (arquivoLog.is_open()){      //Salva a jogada no arquivo log.txt
        arquivoLog << "[Rodada " << rodada << "] " << nome << " jogou ["
                   << peca.ladoA << "|" << peca.ladoB << "]" << endl;
    }
}

bool jogarRodada(JogoDomino& jogo){       //9.Jogar uma rodada
    Jogador& jogador = jogo.jogadores[jogo.jogadorAtual];
    Nodo<PecaDomino>* atual = jogador.mao.inicio;
    int pos = 0;
    bool jogou = false;

    while (atual){
        if (pecaEncaixa(atual->dado, jogo.mesa)){
            PecaDomino jogada = atual->dado;
            jogarPecaNaMesa(jogo.mesa, jogada);
            jogador.mao.remover(pos);
            logJogada(jogador.nome, jogada, jogo.rodadaAtual);
            jogou = true;
            break;
        }
        atual = atual->prox;
        pos++;
    }

    if (!jogou){
        cout << "[Rodada " << jogo.rodadaAtual << "] " << jogador.nome << " passou." << endl;
        if (arquivoLog.is_open()) {
            arquivoLog << "[Rodada " << jogo.rodadaAtual << "] " << jogador.nome << " passou." << endl;
        }
    }

    jogo.jogadorAtual = (jogo.jogadorAtual + 1) % jogo.jogadores.size();
    jogo.rodadaAtual++;
    return jogou;
}

void iniciarJogo(JogoDomino& jogo){       //10.Iniciar o jogo
    int passesConsecutivos = 0;

    mostrarMaos(jogo);

    PecaDomino duplaInicial;
    int primeiro = encontrarJogadorComMaiorDupla(jogo, duplaInicial);       // Encontra o jogador com a maior dupla

    if (primeiro != -1){
        jogo.jogadorAtual = primeiro;
        jogo.mesa.inserirFim(duplaInicial);

        Nodo<PecaDomino>* atual = jogo.jogadores[primeiro].mao.inicio;
        int pos = 0;
        while (atual){
            if (atual->dado == duplaInicial){
                jogo.jogadores[primeiro].mao.remover(pos);
                break;
            }
            atual = atual->prox;
            pos++;
        }

        cout << jogo.jogadores[primeiro].nome << " comecou jogando ";       // O jogador que começou a jogar é o que tem a maior dupla
        duplaInicial.imprimir();
        cout << endl;

        if (arquivoLog.is_open()){
            arquivoLog << jogo.jogadores[primeiro].nome << " começou jogando ["
                       << duplaInicial.ladoA << "|" << duplaInicial.ladoB << "]" << endl;
        }

        jogo.jogadorAtual = (jogo.jogadorAtual + 1) % jogo.jogadores.size();
    }

    while (jogo.rodadaAtual <= jogo.maxRodadas){
        Jogador& jogador = jogo.jogadores[jogo.jogadorAtual];

        if (jogador.mao.inicio == nullptr){
            cout << jogador.nome << " venceu!" << endl;
            if (arquivoLog.is_open()){
                arquivoLog << jogador.nome << " venceu!" << endl;
            }
            break;
        }

        bool jogou = jogarRodada(jogo);

        if (!jogou) {
            passesConsecutivos++;
            if (passesConsecutivos >= static_cast<int>(jogo.jogadores.size())){     // Se todos os jogadores passaram consecutivamente
                cout << "Todos os jogadores passaram. Jogo empatado!" << endl;
                if (arquivoLog.is_open()){
                    arquivoLog << "Todos os jogadores passaram. Jogo empatado!" << endl;
                }
                break;
            }
        }else{
            passesConsecutivos = 0;
        }

        cout << "Mesa: ";
        jogo.mesa.imprimir();
        cout << endl;
    }

    cout << "Jogo encerrado apos " << jogo.rodadaAtual - 1 << " rodadas." << endl;
    if (arquivoLog.is_open()){
        arquivoLog << "Jogo encerrado após " << jogo.rodadaAtual - 1 << " rodadas." << endl;
        arquivoLog.close();
    }
}
#endif