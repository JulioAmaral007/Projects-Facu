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

    int atuAltura(Nodo<T> *chave) const {
        if (chave == nullptr) {
            return 0;
        }

        int alturaEsquerda = (chave->filhoEsquerda != nullptr) ? recAltura(chave->filhoEsquerda) + 1 : 0;
        int alturaDireita = (chave->filhoDireita != nullptr) ? recAltura(chave->filhoDireita) + 1 : 0;

        int equilibrio = alturaEsquerda - alturaDireita;

        return equilibrio;
    }

    void balanceiaArvore(Nodo<T> *pai)
    {
        if (pai != nullptr) {
            int aux = this->atuAltura(pai);

            // Rotação Simples a Esquerda
            if (aux < -1){
                RotacaoSimplesEsquerda(pai);
            }

            // Rotação Simples a Direita
            if (aux > 1){
                RotacaoSimplesDireita(pai);
            }

            if (pai->chave == this->raiz->chave)
            {
                return;
            }
            
            return balanceiaArvore(this->buscarPai(pai->chave, this->raiz));
        }
        return;
    }

    Nodo<T> *buscarPai(T chave, Nodo<T> *pai) const
    {
        if (pai == nullptr || pai->chave == chave){
            return nullptr;
        }

            if (pai->chave < chave){
                if (pai->filhoDireita->chave != chave) {
                    return this->buscarPai(chave, pai->filhoDireita);
                }
            }

            if (pai->chave > chave){
                if (pai->filhoEsquerda->chave != chave) {
                    return this->buscarPai(chave, pai->filhoEsquerda);
                }
            }
        
        return pai;
    }

    void RotacaoSimplesEsquerda (Nodo<T> *pai){
        if (pai == nullptr || pai->filhoDireita == nullptr)
            return;

        Nodo<T> *nodo = buscarPai(pai->chave, this->raiz);
        Nodo<T> *nova_raiz = nullptr;

        if (atuAltura(pai->filhoDireita) <= 0) {
            nova_raiz = RotacaoEsquerdaEsquerda(pai);
        } else {
            nova_raiz = RotacaoDireitaEsquerda(pai);
        }

        if (nodo == nullptr) {
            this->raiz = nova_raiz;
        } else if (nodo->filhoEsquerda == pai) {
            nodo->filhoEsquerda = nova_raiz;
        } else {
            nodo->filhoDireita = nova_raiz;
        }
    }

    void RotacaoSimplesDireita (Nodo<T> *pai){
        if (pai == nullptr || pai->filhoEsquerda == nullptr)
            return;

        Nodo<T> *nodo = buscarPai(pai->chave, this->raiz);
        Nodo<T> *nova_raiz = nullptr;

        if (atuAltura(pai->filhoEsquerda) >= 0) {
            nova_raiz = RotacaoDireitaDireita(pai);
        } else {
            nova_raiz = RotacaoEsquerdaDireita(pai);
        }

        if (nodo == nullptr) {
            this->raiz = nova_raiz;
        } else if (nodo->filhoEsquerda == pai) {
            nodo->filhoEsquerda = nova_raiz;
        } else {
            nodo->filhoDireita = nova_raiz;
        }
    }

    Nodo<T> *RotacaoDireitaDireita(Nodo<T> *pai) {
        Nodo<T> *filhoEsquerda = pai->filhoEsquerda;
        Nodo<T> *subarvoreDireita = filhoEsquerda->filhoDireita;

        // Realiza a rotação
        filhoEsquerda->filhoDireita = pai;
        pai->filhoEsquerda = subarvoreDireita;

        return filhoEsquerda; // Retorna o novo nó pai
    }

    Nodo<T> *RotacaoEsquerdaEsquerda(Nodo<T> *pai) {
        Nodo<T> *filhoDireita = pai->filhoDireita;
        Nodo<T> *subarvoreEsquerda = filhoDireita->filhoEsquerda;

        // Realiza a rotação
        filhoDireita->filhoEsquerda = pai;
        pai->filhoDireita = subarvoreEsquerda;

        return filhoDireita; // Retorna o novo nó pai
    }

    Nodo<T> *RotacaoDireitaEsquerda(Nodo<T> *pai) {
        // Realiza a rotação à direita seguida de uma rotação à esquerda
        pai->filhoDireita = RotacaoDireitaDireita(pai->filhoDireita);
        return RotacaoEsquerdaEsquerda(pai);
    }

    Nodo<T> *RotacaoEsquerdaDireita(Nodo<T> *pai) {
        // Realiza a rotação à esquerda seguida de uma rotação à direita
        pai->filhoEsquerda = RotacaoEsquerdaEsquerda(pai->filhoEsquerda);
        return RotacaoDireitaDireita(pai);
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////

    void recDestrutor(Nodo<T> *chave) {
        // Verifica se o nó atual não é nulo.
        if (chave != nullptr) {
            // Chama recursivamente o destrutor para a subárvore esquerda.
            this->recDestrutor(chave->filhoEsquerda);
            
            // Chama recursivamente o destrutor para a subárvore direita.
            this->recDestrutor(chave->filhoDireita);
            
            // Libera a memória alocada para o nó atual.
            delete chave;
        }
    }

    int recQuantidade(Nodo<T> *nodo) const {
        if (nodo != nullptr) {
            return (1 + this->recQuantidade(nodo->filhoEsquerda) + this->recQuantidade(nodo->filhoDireita));
        }
        return 0;
    }

    Nodo<T> *recContem(T chave, Nodo<T> *nodo) const {
        if (nodo->chave == chave) {
            return nodo;
        }
        while (nodo && nodo->chave != chave) {
            if (nodo->chave < chave) {
                nodo = nodo->filhoDireita;
            } else {
                nodo = nodo->filhoEsquerda;
            }
        }
        
        return nodo;
    }

    int recAltura(Nodo<T> *chave) const {
        int altura = 0, Esquerda = 0, Direita = 0;

        if (chave->filhoEsquerda != nullptr) {
            Esquerda = 1 + recAltura(chave->filhoEsquerda);
        }
        if (chave->filhoDireita != nullptr) {
            Direita = 1 + recAltura(chave->filhoDireita);
        }

        altura = std::max(Esquerda, Direita);
        return altura;
    }

    void recInserir(Nodo<T> *chaveAtual, T chave) {
        Nodo<T> *pai = nullptr;
        Nodo<T> *atual = chaveAtual;

        // Encontra o local de inserção correto e o nó pai.
        while (atual != nullptr) {
            pai = atual;
            if (chave == atual->chave) {
                // Valor já existe na árvore.
                return;
            } else if (chave < atual->chave) {
                atual = atual->filhoEsquerda;
            } else {
                atual = atual->filhoDireita;
            }
        }

        // Cria o novo nó com o novo valor.
        Nodo<T> *novoNodo = new Nodo<T>{chave, 0}; // Suponha que a altura seja inicializada como 0.

        if (pai == nullptr) {
            // Se o pai for nulo, a árvore estava vazia, então o novo nó se torna a raiz.
            chaveAtual = novoNodo;
        } else if (chave < pai->chave) {
            pai->filhoEsquerda = novoNodo;
        } else {
            pai->filhoDireita = novoNodo;
        }

        this->balanceiaArvore(pai);
    }
    
    void removeDaArvore(T chaveParaRemover, Nodo<T> *chavePai) {
        Nodo<T> *chave;

        if (chavePai->chave == chaveParaRemover) {
            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr) {
                chavePai = nullptr;
                delete chavePai;

                return;
            }
            chave = chavePai;
        }
        else if (chavePai->filhoEsquerda != nullptr && chavePai->filhoEsquerda->chave == chaveParaRemover){
            chave = chavePai->filhoEsquerda;

            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr) {
                chavePai->filhoEsquerda = nullptr;
                delete chave;

                return;
            }
        }
        else if (chavePai->filhoDireita != nullptr && chavePai->filhoDireita->chave == chaveParaRemover) {
            chave = chavePai->filhoDireita;

            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr) {
                chavePai->filhoDireita = nullptr;
                delete chave;

                return;
            }
        }
        
        if(chave != nullptr && chave->filhoDireita != nullptr) {
            Nodo<T> *chaveAux = chave->filhoDireita;
            Nodo<T> *chavePaiAux = chave;

            while (chaveAux->filhoEsquerda != nullptr) {
                chavePaiAux = chaveAux;
                chaveAux = chaveAux->filhoEsquerda;
            }

            chave->chave = chaveAux->chave;
            chaveAux->chave = chaveParaRemover;
            return this->removeDaArvore(chaveParaRemover, chavePaiAux);
        }

        return;
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

    MinhaArvoreAVL(){
        this->raiz = nullptr;
    };

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
    virtual bool vazia() const
    {
        if (this->raiz == nullptr)
            return true;
        return false;
    };
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    int quantidade() const
    {
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
        
        Nodo<T> * nodo = this->recContem(chave, this->raiz);
    
        if(nodo && nodo->chave == chave){
            return true;
        }   
        return false;
    };
    
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. 
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const {
        if (!contem(chave))
            return std::nullopt;

        Nodo<T> *raiz = this->recContem(chave, this->raiz);
        return this->recAltura(raiz);
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */     

    virtual void inserir(T chave) {
        if (this->vazia()) {
            Nodo<T> *novoNodo = new Nodo<T>();
            novoNodo->chave = chave;
            novoNodo->altura = 0;
            delete this->raiz;
            this->raiz = novoNodo;
            return;
        }

        this->recInserir(this->raiz, chave);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */        
    virtual void remover(T chave) {
        if (this->vazia()) {
            return;
        }

        Nodo<T> *raiz = this->raiz;

        if(raiz->chave == chave && raiz->filhoEsquerda == nullptr && raiz->filhoDireita == nullptr) {
            this->raiz = nullptr;
            delete raiz;
            return;
        }

        if (this->contem(chave)) {
            Nodo<T> *chavePai = this->buscarPai(chave, raiz);
            if (chavePai == nullptr) {
                this->removeDaArvore(chave, raiz);
                return;
            }
            this->removeDaArvore(chave, chavePai);  
            this->balanceiaArvore(chavePai);
        }
    };

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const {
        if (!contem(chave))
            return std::nullopt;

        Nodo<T> *chavePai = this->recContem(chave, this->raiz);

        if (chavePai->filhoEsquerda != nullptr)
        {
            return chavePai->filhoEsquerda->chave;
        }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */        
    virtual std::optional<T> filhoDireitaDe(T chave) const {
        if (!contem(chave))
            return std::nullopt;

        Nodo<T> *chavePai = this->recContem(chave, this->raiz);

        if (chavePai->filhoDireita != nullptr)
        {
            return chavePai->filhoDireita->chave;
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