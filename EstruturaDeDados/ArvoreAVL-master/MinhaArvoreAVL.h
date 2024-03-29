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
    // Balanceamemto da árvore   
    Nodo<T>* BalancArvore(Nodo<T>* nodoPai) {
        if (!nodoPai)
            return nullptr;

        int equilibrio = fatorEquilibrio(nodoPai);

        if (equilibrio < -1) {
            return (fatorEquilibrio(nodoPai->filhoDireita) <= 0) ? RotacaoSimplesEsquerda(nodoPai) : RotacaoDireitaEsquerda(nodoPai);
        } else if (equilibrio > 1) {
            return (fatorEquilibrio(nodoPai->filhoEsquerda) >= 0) ? RotacaoSimplesDireita(nodoPai) : RotacaoEsquerdaDireita(nodoPai);
        } else if (nodoPai->chave == this->raiz->chave) {
            return nodoPai;
        }

        return nodoPai;
    }


    Nodo<T> * RotacaoSimplesEsquerda(Nodo<T> * nodo) {
        if (!nodo || !nodo->filhoDireita) {
            return nodo;
        }

        Nodo<T>* filhoD = nodo->filhoDireita;
        nodo->filhoDireita = filhoD->filhoEsquerda;
        filhoD->filhoEsquerda = nodo;

        return filhoD;
    };

    Nodo<T> * RotacaoSimplesDireita(Nodo<T> * nodo) {
        if (!nodo || !nodo->filhoEsquerda) {
            return nodo;
        }

        Nodo<T>* filhoE = nodo->filhoEsquerda;
        nodo->filhoEsquerda = filhoE->filhoDireita;
        filhoE->filhoDireita = nodo;

        return filhoE;
    };

    Nodo<T> *RotacaoEsquerdaDireita(Nodo<T> *nodo) {
        if (!nodo || !nodo->filhoEsquerda || !nodo->filhoEsquerda->filhoDireita)
            return nullptr;

        Nodo<T> *B = nodo->filhoEsquerda;
        Nodo<T> *C = B->filhoDireita;
        Nodo<T> *D = C->filhoEsquerda;

        // Realiza a rotação simples à esquerda em B
        B->filhoDireita = D;
        C->filhoEsquerda = B;

        // Atualiza as alturas de B e C
        atualizarAltura(B);
        atualizarAltura(C);

        // Realiza a rotação simples à direita em nodo
        nodo->filhoEsquerda = C;
        atualizarAltura(nodo);

        Nodo<T> * filhoE = nodo->filhoEsquerda;
        Nodo<T> * filhoD = filhoE->filhoDireita;
        filhoE->filhoDireita = nodo;
        nodo->filhoEsquerda = filhoD;
        return filhoE;
    }

    Nodo<T> *RotacaoDireitaEsquerda(Nodo<T> *nodo) {
        if (!nodo || !nodo->filhoDireita || !nodo->filhoDireita->filhoEsquerda)
            return nullptr;

        Nodo<T> *B = nodo->filhoDireita;
        Nodo<T> *C = B->filhoEsquerda;
        Nodo<T> *D = C->filhoDireita;

        // Realiza a rotação simples à direita em B
        B->filhoEsquerda = D;
        C->filhoDireita = B;

        // Atualiza as alturas de B e C
        atualizarAltura(B);
        atualizarAltura(C);

        // Realiza a rotação simples à esquerda em nodo
        nodo->filhoDireita = C;
        atualizarAltura(nodo);

        Nodo<T> * filhoD = nodo->filhoDireita;
        Nodo<T> * filhoE = filhoD->filhoEsquerda;
        filhoD->filhoEsquerda = nodo;
        nodo->filhoDireita = filhoE;
        return filhoD;
    }

    ///////////////////////////////////////////////////////////////////////
    int fatorEquilibrio(Nodo<T> * nodo) const {
        return (nodo) ? (atualizarAltura(nodo->filhoEsquerda) - atualizarAltura(nodo->filhoDireita)) : 0;
    };

    int atualizarAltura(Nodo<T> * nodo) const {
        return (nodo) ? recAltura(nodo) : -1;
    };

    Nodo<T>* buscaPai(Nodo<T>* nodo, T chave) const {
        for (; nodo && nodo->chave != chave; ) {
            if (nodo->chave < chave) {
                if (nodo->filhoDireita) {
                    if (nodo->filhoDireita->chave == chave) {
                        return nodo;
                    }
                    nodo = nodo->filhoDireita;
                } else {
                    break;
                }
            } else {
                if (nodo->filhoEsquerda) {
                    if (nodo->filhoEsquerda->chave == chave) {
                        return nodo;
                    }
                    nodo = nodo->filhoEsquerda;
                } else {
                    break;
                }
            }
        }
        return nodo;
    }

    void recDestrutor(Nodo<T> *chave) {
        if (chave != nullptr) {
            this->recDestrutor(chave->filhoEsquerda);
            this->recDestrutor(chave->filhoDireita);
        
            delete chave;
        }
    }

    int recQuantidade(Nodo<T> *nodo) const {
        if (nodo != nullptr) {
            return (1 + this->recQuantidade(nodo->filhoEsquerda) + this->recQuantidade(nodo->filhoDireita));
        }
        return 0;
    }

    int recAltura(Nodo<T> *chave) const {
        if (!chave)
            return 0;

        int alturaEsquerda = atualizarAltura(chave->filhoEsquerda);
        int alturaDireita = atualizarAltura(chave->filhoDireita);

        return std::max(alturaEsquerda, alturaDireita) + 1;
    }

    void recInserir(Nodo<T> *nodo, T chave) {
         if(chave < nodo->chave) {
            if(!nodo->filhoEsquerda){
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                novoNodo->altura = nodo->altura + 1;
                nodo->filhoEsquerda = novoNodo;
            }  else {
                recInserir(nodo->filhoEsquerda, chave);
                if(nodo->filhoEsquerda)
                    nodo->filhoEsquerda = BalancArvore(nodo->filhoEsquerda);
                    
                if(nodo->filhoDireita)
                    nodo->filhoDireita = BalancArvore(nodo->filhoDireita);
                nodo = nodo;
            }
        } else {
            if(!nodo->filhoDireita){
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                novoNodo->altura = nodo->altura + 1;
                nodo->filhoDireita = novoNodo;
            } else {
                recInserir(nodo->filhoDireita, chave);
                if(nodo->filhoEsquerda)
                    nodo->filhoEsquerda = BalancArvore(nodo->filhoEsquerda);
                    
                if(nodo->filhoDireita)
                    nodo->filhoDireita = BalancArvore(nodo->filhoDireita);
                nodo = nodo;
            }
        }
    }
    
    void recRemover(Nodo<T> * nodoPai, T chave) {
        Nodo<T>* nodo = nullptr;

        if (nodoPai && nodoPai->chave == chave) {
            nodo = nodoPai;
        } else if (nodoPai && nodoPai->filhoEsquerda && nodoPai->filhoEsquerda->chave == chave) {
            nodo = nodoPai->filhoEsquerda;
        } else if (nodoPai && nodoPai->filhoDireita && nodoPai->filhoDireita->chave == chave) {
            nodo = nodoPai->filhoDireita;
        }

        if (nodo && nodoPai == nodo && !nodo->filhoEsquerda && !nodo->filhoDireita) {
            delete nodo;
            nodoPai = nullptr;
            return;
        } else if (nodo && nodoPai->filhoEsquerda == nodo && !nodo->filhoEsquerda && !nodo->filhoDireita) {
            delete nodo;
            nodoPai->filhoEsquerda = nullptr;
            return;
        } else if (nodo && nodoPai->filhoDireita == nodo && !nodo->filhoEsquerda && !nodo->filhoDireita) {
            delete nodo;
            nodoPai->filhoDireita = nullptr;
            return;
        }

        if(nodo->filhoDireita) {
            Nodo<T> * aux = nodo->filhoDireita;
            Nodo<T> * auxPai = nodo;
            while(aux->filhoEsquerda) {
                auxPai = aux;
                aux = aux->filhoEsquerda;
            }
            std::swap(nodo->chave, aux->chave);
            recRemover(auxPai, chave);

            if(nodo->filhoEsquerda)
                nodo->filhoEsquerda = BalancArvore(nodo->filhoEsquerda);
                    
            if(nodo->filhoDireita)
                nodo->filhoDireita = BalancArvore(nodo->filhoDireita);
            nodoPai = nodo;
        }
    }

    void recEmOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const {
        if (chave != nullptr){
            this->recEmOrdem(chave->filhoEsquerda, lista);
            lista->inserirNoFim(chave->chave);
            this->recEmOrdem(chave->filhoDireita, lista);
        }
        return;
    }

    void recPreOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const{
        if (chave != nullptr) {
            lista->inserirNoFim(chave->chave);
            this->recPreOrdem(chave->filhoEsquerda, lista);
            this->recPreOrdem(chave->filhoDireita, lista);
        }
        return;
    }

    void recPosOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const{
        if (chave != nullptr) {
            this->recPosOrdem(chave->filhoEsquerda, lista);
            this->recPosOrdem(chave->filhoDireita, lista);
            lista->inserirNoFim(chave->chave);
        }
        return;
    }

    public:

    virtual ~MinhaArvoreAVL(){
        if (this->raiz == nullptr) {
            return;
        }

        this->recDestrutor(this->raiz);
    };  

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    virtual bool vazia() const {
        if (this->raiz == nullptr)
            return true;
        return false;
    };
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidade() const {
        return this->recQuantidade(this->raiz);
    };
    
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */    
    virtual bool contem(T chave) const {
        if(vazia()){
            return false;
        }

        Nodo<T>* nodoAtual = this->raiz;
        
        while (nodoAtual != nullptr) {
            if (nodoAtual->chave == chave) {
                return true;
            }

        
            if (nodoAtual->chave < chave) {
                nodoAtual = nodoAtual->filhoDireita;
            } else {
                nodoAtual = nodoAtual->filhoEsquerda;
            }
        }

        return false;
    };
    
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. 
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const {
        Nodo<T>* nodo = this->raiz;

            while (nodo) {
                if (nodo->chave == chave) {
                    return recAltura(nodo);
                }
                if (nodo->chave < chave) {
                    nodo = nodo->filhoDireita;
                } else {
                    nodo = nodo->filhoEsquerda;
                }
            }

        return std::nullopt;
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */     

    virtual void inserir(T chave) {
        if(this->vazia()) {
            Nodo<T> * novoNodo = new Nodo<T>();
            novoNodo->chave = chave;
            novoNodo->altura = 0;
            this->raiz = novoNodo;
            return;
        }
        recInserir(this->raiz, chave);
        this->raiz = BalancArvore(this->raiz);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */        
    virtual void remover(T chave) {
        if (this->contem(chave)) {
            if (this->raiz->chave == chave && !this->raiz->filhoEsquerda && !this->raiz->filhoDireita) {
                delete this->raiz;
                this->raiz = nullptr;
                return;
            }

            Nodo<T>* chavePai = buscaPai(this->raiz, chave);
            if (chavePai) {
                recRemover(chavePai, chave);
                this->raiz = BalancArvore(this->raiz);
            }
        }
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const {
        Nodo<T>* nodo = this->raiz;

            while (nodo) {
                if (nodo->chave == chave) {
                    if (nodo->filhoEsquerda != nullptr) {
                        return nodo->filhoEsquerda->chave;
                    } else {
                        return std::nullopt;
                    }
                }

                if (nodo->chave < chave) {
                    nodo = nodo->filhoDireita;
                } else {
                    nodo = nodo->filhoEsquerda;
                }
            }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    virtual std::optional<T> filhoDireitaDe(T chave) const {
        Nodo<T>* nodo = this->raiz;

            while (nodo) {
                if (nodo->chave == chave) {
                    if (nodo->filhoDireita != nullptr) {
                        return nodo->filhoDireita->chave;
                    } else {
                        return std::nullopt;
                    }
                }

                if (nodo->chave < chave) {
                    nodo = nodo->filhoDireita;
                } else {
                    nodo = nodo->filhoEsquerda;
                }
            }

        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* emOrdem() const {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>();

        this->recEmOrdem(this->raiz, lista);

       return lista;
    };

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* preOrdem() const {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>();

        this->recPreOrdem(this->raiz, lista);

        return lista;
    };

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem. 
     */
    virtual ListaEncadeadaAbstrata<T>* posOrdem() const {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>();

        this->recPosOrdem(this->raiz, lista);

       return lista;
    };
};

#endif