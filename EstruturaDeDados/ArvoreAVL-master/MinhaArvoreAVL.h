#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    protected:

    // Rotação 

    int getRotacao(Nodo<T> *chave) const 
    {
        int aux = 0, esquerda = 0, direita = 0;

        if (chave != nullptr)
         {
              if (chave->filhoEsquerda != nullptr)
                 {
                    esquerda = chave->filhoEsquerda->altura;
                esquerda = this->alturaSubArvore(chave->filhoEsquerda) + 1;
                 }
              if (chave->filhoDireita != nullptr)
                 {
                direita = this->alturaSubArvore(chave->filhoDireita) + 1;
                 }

            aux = esquerda - direita;

            return aux;
        }
        return 0;
    }

    void balanceiaArvore(Nodo<T> *pai)
    {
        if (pai != nullptr)
        {
            int aux = this->getRotacao(pai);

            // Rotação Simples a Esquerda
            if (aux < -1)
            {
                aux = this->getRotacao(pai->filhoDireita);
                if (aux <= 0)
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->raiz);

                    if (avo == nullptr)
                    {
                        this->raiz = this->RotacaoEsquerdaEsquerda(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->RotacaoEsquerdaEsquerda(pai);
                    }
                    return;

                }
                else    // Rotação Direita Esquerda
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->raiz);

                    if (avo == nullptr)
                    {
                        this->raiz = this->RotacaoDireitaEsquerda(pai);
                    }
                    else
                    {
                        avo->filhoDireita = this->RotacaoDireitaEsquerda(pai);
                    }

                    return;
                }
            }

            // Rotação Simples a Direita
            if (aux > 1)
            {
                aux = this->getRotacao(pai->filhoEsquerda);
                if (aux >= 0)
                {
                    Nodo<T> *avo = this->getPai(pai->chave, this->raiz);

                    if (avo == nullptr)
                    {
                        this->raiz = this->RotacaoDireitaDireita(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->RotacaoDireitaDireita(pai);
                    }
                    return;
                }
                else    // Rotação Esquerda Direita
                {   
                    Nodo<T> *avo = this->getPai(pai->chave, this->raiz);

                    if (avo == nullptr)
                    {
                        this->raiz = this->RotacaoEsquerdaDireita(pai);
                    }
                    else
                    {
                        avo->filhoEsquerda = this->RotacaoEsquerdaDireita(pai);
                    }
                    return;
                }
            }

            if (pai->chave == this->raiz->chave)
            {
                return;
            }
            
            return balanceiaArvore(this->getPai(pai->chave, this->raiz));
        }
        return;
    }

    Nodo<T> *RotacaoDireitaDireita(Nodo<T> *pai) 
    {
        Nodo<T> *filho      = pai->filhoEsquerda;
        pai->filhoEsquerda  = filho->filhoDireita;
        filho->filhoDireita = pai;

        return filho;
    }

    Nodo<T> *RotacaoEsquerdaEsquerda(Nodo<T> *pai) 
    {
        Nodo<T> *filho       = pai->filhoDireita;
        pai->filhoDireita    = filho->filhoEsquerda;
        filho->filhoEsquerda = pai;

        return filho;
    }

    Nodo<T> *RotacaoDireitaEsquerda(Nodo<T> *pai) 
    {
        pai->filhoDireita = this->RotacaoDireitaDireita(pai->filhoDireita);
        return this->RotacaoEsquerdaEsquerda(pai);
    }

     Nodo<T> *RotacaoEsquerdaDireita(Nodo<T> *pai) 
    {
        pai->filhoEsquerda = this->RotacaoEsquerdaEsquerda(pai->filhoEsquerda);
        return this->RotacaoDireitaDireita(pai);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////

    int getQuantidade(Nodo<T> *chave) const
    {
        if (chave != nullptr)
        {
            return (1 + this->getQuantidade(chave->filhoEsquerda) + this->getQuantidade(chave->filhoDireita));
        }
        return 0;
    }


    void emOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaEmOrdem) const
    {
        if (chave != nullptr)
        {
            this->emOrdemAux(chave->filhoEsquerda, listaEmOrdem);
            listaEmOrdem->inserirNoFim(chave->chave);
            this->emOrdemAux(chave->filhoDireita, listaEmOrdem);
        }
        return;
    }

    void preOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPreOrdem) const
    {
        if (chave != nullptr)
        {
            listaPreOrdem->inserirNoFim(chave->chave);
            this->preOrdemAux(chave->filhoEsquerda, listaPreOrdem);
            this->preOrdemAux(chave->filhoDireita, listaPreOrdem);
        }
        return;
    }

    void posOrdemAux(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *listaPosOrdem) const
    {
        if (chave != nullptr)
        {
            this->posOrdemAux(chave->filhoEsquerda, listaPosOrdem);
            this->posOrdemAux(chave->filhoDireita, listaPosOrdem);
            listaPosOrdem->inserirNoFim(chave->chave);
        }
        return;
    }

    
    void insereNaArvore(Nodo<T> *chaveAtual, T novoValor)
    {
        if (this->vazia())
        {
            Nodo<T> *novaChave = new Nodo<T>{novoValor, 0};

            delete this->raiz;

            this->raiz = novaChave;

            return;
        }

        if (novoValor < chaveAtual->chave)
        {
            if (chaveAtual->filhoEsquerda == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>
                {
                    novoValor, chaveAtual->altura+1
                };

                chaveAtual->filhoEsquerda = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoEsquerda, novoValor);
            }
        }
        else
        {
            if (chaveAtual->filhoDireita == nullptr)
            {
                Nodo<T> *novaChave = new Nodo<T>{novoValor, chaveAtual->altura+1};

                chaveAtual->filhoDireita = novaChave;
            }
            else
            {
                this->insereNaArvore(chaveAtual->filhoDireita, novoValor);
            }
        }
        return;
    }

    Nodo<T> *getContem(T chave, Nodo<T> *raiz) const
    {
        while (raiz != nullptr && raiz->chave != chave)
        {
            if (raiz->chave < chave)
            {
                raiz = raiz->filhoDireita;
            }
            else
            {
                raiz = raiz->filhoEsquerda;
            }
        }
        return raiz; 
    }

    Nodo<T> *getPai(T chave, Nodo<T> *pai) const
    {
        if (pai == nullptr)
        {
            return nullptr;
        }

        if (pai->chave == chave)
        {
            return nullptr;
        }

        if (pai != nullptr && pai->chave != chave)
        {
            if (pai->chave < chave)
            {
                if (pai->filhoDireita->chave != chave)
                {
                    return this->getPai(chave, pai->filhoDireita);
                }
            }

            if (pai->chave > chave)
            {
                if (pai->filhoEsquerda->chave != chave)
                {
                    return this->getPai(chave, pai->filhoEsquerda);
                }
            }
        }
        return pai;
    }

    
    int alturaSubArvore(Nodo<T> *chave) const
    {
        int alturaEsquerda = 0, alturaDireita = 0, altura = 0;

        if (chave->filhoEsquerda != nullptr)
        {
            alturaEsquerda = 1 + alturaSubArvore(chave->filhoEsquerda);
        }

        if (chave->filhoDireita != nullptr)
        {
            alturaDireita = 1 + alturaSubArvore(chave->filhoDireita);
        }

        return checaAltura(alturaEsquerda, alturaDireita, altura);
    }

    int checaAltura(int Esquerda, int Direita, int altura) const
    {
        if (Esquerda >= Direita)
        {
            altura = Esquerda;
            return altura;
        }
        else
        {
            altura = Direita;
            return altura;
        }
    }

    
    T removeDaArvore(T chaveParaRemover, Nodo<T> *chavePai)
    {
        Nodo<T> *chave;

        if (chavePai->chave == chaveParaRemover)
        {
            if (verificaFolha(chavePai))
            {
                T chaveRemovida = chavePai->chave;

                chavePai = nullptr;
                delete chavePai;

                return chaveRemovida;
            }
            chave = chavePai;
        }
        else if (chavePai->filhoEsquerda != nullptr && chavePai->filhoEsquerda->chave == chaveParaRemover)
        {
            chave = chavePai->filhoEsquerda;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoEsquerda = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        else if (chavePai->filhoDireita != nullptr && chavePai->filhoDireita->chave == chaveParaRemover)
        {
            chave = chavePai->filhoDireita;

            if (verificaFolha(chave))
            {
                T chaveRemovida = chave->chave;

                chavePai->filhoDireita = nullptr;
                delete chave;

                return chaveRemovida;
            }
        }
        
        if(chave != nullptr && chave->filhoDireita != nullptr)
        {
            Nodo<T> *chaveAux = chave->filhoDireita;
            Nodo<T> *chavePaiAux = chave;

            while (chaveAux->filhoEsquerda != nullptr)
            {
                chavePaiAux = chaveAux;
                chaveAux = chaveAux->filhoEsquerda;
            }

            chave->chave = chaveAux->chave;
            chaveAux->chave = chaveParaRemover;
            return this->removeDaArvore(chaveParaRemover, chavePaiAux);
        }
        return chaveParaRemover;
    }

    bool verificaFolha(Nodo<T> *chave)
    {
        if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
        {
            return true;
        }
        return false;
    }


    void destruirArvore(Nodo<T> *chave)
    {
        if (chave != nullptr)
        {
            this->destruirArvore(chave->filhoEsquerda);
            this->destruirArvore(chave->filhoDireita);
            delete chave;
        }
    }
    
    public:

    MinhaArvoreAVL(){
        this->raiz = nullptr;
    };

    virtual ~MinhaArvoreAVL(){
        if (this->raiz != nullptr)
        {
            this->destruirArvore(this->raiz);
        }
        return;
    };

    bool vazia() const 
    {
        if (this->quantidade() == 0 || this->raiz == nullptr)
        {
            return true;
        }
        return false;
    };
    
 
    int quantidade() const 
    {
        int quantidade = 0;

        quantidade = this->getQuantidade(this->raiz);

        return quantidade;
    };
    
 
    bool contem(T chave) const 
    {    
        if (!this->vazia())
        {
            Nodo<T> *raiz = this->getContem(chave, this->raiz);

            if (raiz == nullptr)
            {
                return false;
            }

            if (raiz->chave == chave)
            {
                return true;
            }

        }
        return false;
    };
    
    
    std::optional<int> altura(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *raiz = this->getContem(chave, this->raiz);
            return this->alturaSubArvore(raiz);
        }
        return std::nullopt;
    };
       
    void inserir(T chave) 
    {
        this->insereNaArvore(this->raiz, chave);
        Nodo<T> *pai = this->getPai(chave, this->raiz);
        this->balanceiaArvore(pai);
    };

      
    void remover(T chave)
    {
        Nodo<T> *raiz = this->raiz;

        if(raiz->chave == chave && this->verificaFolha(raiz))
        {
            this->raiz = nullptr;

            delete raiz;

            return;
        }

        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getPai(chave, raiz);
            if (chavePai == nullptr)
            {
                this->removeDaArvore(chave, raiz);
                return;
            }
            this->removeDaArvore(chave, chavePai);
            this->balanceiaArvore(chavePai);
        }
    };


    std::optional<T> filhoEsquerdaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getContem(chave, this->raiz);

            if (chavePai->filhoEsquerda != nullptr)
            {
                return chavePai->filhoEsquerda->chave;
            }
        }
        return std::nullopt;
    };
       
    std::optional<T> filhoDireitaDe(T chave) const 
    {
        if (this->contem(chave))
        {
            Nodo<T> *chavePai = this->getContem(chave, this->raiz);

            if (chavePai->filhoDireita != nullptr)
            {
                return chavePai->filhoDireita->chave;
            }
        }
        return std::nullopt;
    };

    ListaEncadeadaAbstrata<T>* emOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaEmOrdem = new MinhaListaEncadeada<T>();

        this->emOrdemAux(this->raiz, listaEmOrdem);

       return listaEmOrdem;
    
    };

    ListaEncadeadaAbstrata<T>* preOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPreOrdem = new MinhaListaEncadeada<T>();

        this->preOrdemAux(this->raiz, listaPreOrdem);

        return listaPreOrdem;
     
    };
    
    ListaEncadeadaAbstrata<T>* posOrdem() const 
    {
        ListaEncadeadaAbstrata<T> *listaPosOrdem = new MinhaListaEncadeada<T>();

        this->posOrdemAux(this->raiz, listaPosOrdem);

       return listaPosOrdem;
      
    };
};

#endif