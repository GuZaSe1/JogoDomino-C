#ifndef LISTA_ESTATICA_HPP
#define LISTA_ESTATICA_HPP
#include <iostream>
using namespace std;

const int MAX = 50;

template <typename T>
struct ListaEstatica{
    T dados[MAX];
    int tamanho;

    void inicializar(){        //1.Inicializar
        tamanho = 0;
    }

    bool inserirInicio(T item){        //2.1.Inserir no início
        return inserir(item, 0);
    }

    bool inserir(T item, int posicao){      //2.2.Inserir em uma posição específica
        if (tamanho >= MAX || posicao < 0 || posicao > tamanho)
        return false;
        
        for (int i = tamanho; i > posicao; i--){
            dados[i] = dados[i - 1];
        }
        dados[posicao] = item;
        tamanho++;
        return true;
    }

    bool inserirFim(T item){       //2.3.Inserir no fim
        return inserir(item, tamanho);
    }

    bool removerInicio(){       //3.1.Remover do início      
        return remover(0);
    }

    bool remover(int posicao){          //3..Remover de uma posição específica
        if (posicao < 0 || posicao >= tamanho)
        return false;
        
        for (int i = posicao; i < tamanho - 1; i++) {
            dados[i] = dados[i + 1];
        }
        tamanho--;
        return true;
    }
    
    bool removerFim(){         //3.2.Remover do fim
        return remover(tamanho - 1);
    }

    const T* obter(int posicao) const{        //4.Obter item da lista
        if (posicao < 0 || posicao >= tamanho)
            return nullptr;
        return &dados[posicao];
    }

    bool contem(T item){        //5.Contém item
        return descobrirIndice(item) != -1;
    }

    int descobrirIndice(T item){        //6.Descobrir índice
        for (int i = 0; i < tamanho; i++) {
            if (dados[i] == item)
                return i;
        }
        return -1;
    }

    void imprimir(){        //7.Imprimir lista
        cout << "[ ";
        for (int i = 0; i < tamanho; i++){     
            dados[i].imprimir();  // Pressupõe que T tenha método imprimir()
            cout << " ";
        }
        cout << "]\n";          
    }
};
#endif