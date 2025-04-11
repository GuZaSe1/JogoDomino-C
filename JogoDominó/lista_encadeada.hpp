#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP
#include <iostream>
using namespace std;

template <typename T>
struct Nodo{
    T dado;
    Nodo *prox;
};

template <typename T>
struct ListaEncadeada{
    Nodo<T>* inicio;

    void inicializar(){     //1.Inicializar
        inicio = nullptr;
    }

    bool inserirInicio(T item){     //2.1.Inserir no início
        return inserir(item, 0);
    }

    bool inserir(T item, int posicao){      //2.2.Inserir em uma posição específica
        Nodo<T>* novo = new Nodo<T>{item, nullptr};

        if (posicao == 0){
            novo->prox = inicio;
            inicio = novo;
            return true;
        }

        Nodo<T>* aux = inicio;          // Ponteiro auxiliar para percorrer a lista
        for (int i = 0; i < posicao - 1 && aux; i++)
            aux = aux->prox;

        if (!aux){
            delete novo;
            return false;
        }

        novo->prox = aux->prox;
        aux->prox = novo;
        return true;
    }
    
    bool inserirFim(T item){        //2.3.Inserir no fim
        int pos = 0;
        Nodo<T> *aux = inicio;      // Ponteiro auxiliar para percorrer a lista
        while (aux) {
            aux = aux->prox;
            pos++;
        }
        return inserir(item, pos);
    }

    bool removerInicio(){       //3.1.Remover do início
        return remover(0);
    }

    bool remover(int posicao){        //3.2.Remover de uma posição específica
        if (!inicio) return false;

        Nodo<T>* aux = inicio;      // Ponteiro auxiliar para percorrer a lista
        if (posicao == 0) {
            inicio = inicio->prox;
            delete aux;
            return true;
        }

        Nodo<T>* anterior = nullptr;        // Ponteiro para o nó anterior
        for (int i = 0; i < posicao && aux; i++) {
            anterior = aux;
            aux = aux->prox;
        }

        if (!aux) return false;

        anterior->prox = aux->prox;     // Desvincula o nó a ser removido
        delete aux;
        return true;
    }

    bool removerFim(){      //3.3.Remover do fim
        if (!inicio) return false;

        int pos = 0;
        Nodo<T>* aux = inicio;
        while (aux->prox) {
            aux = aux->prox;
            pos++;
        }
        return remover(pos);
    }

    Nodo<T>* obter(int posicao){      //4.Obter item da lista
        Nodo<T>* aux = inicio;
        for (int i = 0; i < posicao && aux; i++)
            aux = aux->prox;
        return aux;
    }

    bool contem(T item){        //5.Contém item
        return descobrirIndice(item) != -1;
    }

    int descobrirIndice(T item){        //6.Descobrir índice
        Nodo<T>* aux = inicio;
        int pos = 0;
        while (aux){
            if (aux->dado == item)
                return pos;
            aux = aux->prox;
            pos++;
        }
        return -1;
    }

    void imprimir(){    //7.Imprimir lista
        cout<<"[ ";
        Nodo<T>* aux = inicio;
        while (aux){
            aux->dado.imprimir();
            cout<<" ";
            aux = aux->prox;
        }
        cout<<"]\n";
    }
};
#endif