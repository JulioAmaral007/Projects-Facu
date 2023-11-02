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

    // Rotação e Balanceamemto da árvore

    int rotacao(Nodo<T> *chave) const {
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
        if (pai != nullptr)
        {
            int aux = this->rotacao(pai);

            // Rotação Simples a Esquerda
            if (aux < -1)
            {
                aux = this->rotacao(pai->filhoDireita);
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
                aux = this->rotacao(pai->filhoEsquerda);
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
        // Verifica se o nó atual não é nulo.
        if (nodo != nullptr) {
            // Se o nó não for nulo, retorna 1 (para contar o próprio nó) mais a quantidade de nós
            // na subárvore esquerda e a quantidade de nós na subárvore direita.
            return (1 + this->recQuantidade(nodo->filhoEsquerda) + this->recQuantidade(nodo->filhoDireita));
        }
        // Se o nó for nulo, retorna 0, indicando que não há nós nesta subárvore.
        return 0;
    }

    Nodo<T> *recContem(T chave, Nodo<T> *nodo) const {
        // Verifica se a chave do nó atual é igual à chave que estamos procurando.
        if (nodo->chave == chave) {
            // Se for igual, encontramos o nó com a chave desejada e retornamos esse nó.
            return nodo;
        }
        // Entra em um loop enquanto o nó atual não for nulo e a chave não for encontrada.
        while (nodo && nodo->chave != chave) {
            // Verifica se a chave que estamos procurando é maior ou menor que a chave do nó atual.
            if (nodo->chave < chave) {
                // Se for maior, a chave que estamos procurando deve estar na subárvore direita.
                // Portanto, movemos para o nó filho direito.
                nodo = nodo->filhoDireita;
            } else {
                // Se for menor ou igual, a chave que estamos procurando deve estar na subárvore esquerda.
                // Portanto, movemos para o nó filho esquerdo.
                nodo = nodo->filhoEsquerda;
            }
        }
        
        // Retornamos o nó encontrado (que pode ser o nó com a chave desejada ou nulo se a chave não for encontrada).
        return nodo;
    }

    int recAltura(Nodo<T> *chave) const {
        // Inicializa as variáveis para a altura total, altura da subárvore esquerda e altura da subárvore direita.
        int altura = 0, Esquerda = 0, Direita = 0;

        // Verifica se o nó tem um filho esquerdo.
        if (chave->filhoEsquerda != nullptr) {
            // Se tiver um filho esquerdo, calcula a altura da subárvore esquerda de forma recursiva.
            // Incrementa 1 para contar o próprio nó atual.
            Esquerda = 1 + recAltura(chave->filhoEsquerda);
        }

        // Verifica se o nó tem um filho direito.
        if (chave->filhoDireita != nullptr) {
            // Se tiver um filho direito, calcula a altura da subárvore direita de forma recursiva.
            // Incrementa 1 para contar o próprio nó atual.
            Direita = 1 + recAltura(chave->filhoDireita);
        }

        // Calcula a altura total da subárvore como o máximo entre a altura da subárvore esquerda e a altura da subárvore direita.
        altura = std::max(Esquerda, Direita);

        // Retorna a altura total da subárvore enraizada no nó 'chave'.
        return altura;
    }

    Nodo<T> *recInserir(Nodo<T> *chaveAtual, T chave) {
        Nodo<T> *pai = nullptr;
        Nodo<T> *atual = chaveAtual;

        // Encontra o local de inserção correto e o nó pai.
        while (atual != nullptr) {
            pai = atual;
            if (chave == atual->chave) {
                // Valor já existe na árvore.
                return pai;
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

        return pai;
    }
    
    T removeDaArvore(T chaveParaRemover, Nodo<T> *chavePai)
    {
        Nodo<T> *chave;

        if (chavePai->chave == chaveParaRemover)
        {
            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
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

            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
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

            if (chave->filhoEsquerda == nullptr && chave->filhoDireita == nullptr)
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

    void recEmOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (chave != nullptr)
        {
            this->recEmOrdem(chave->filhoEsquerda, lista);
            lista->inserirNoFim(chave->chave);
            this->recEmOrdem(chave->filhoDireita, lista);
        }
        return;
    }

    void recPreOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (chave != nullptr)
        {
            lista->inserirNoFim(chave->chave);
            this->recPreOrdem(chave->filhoEsquerda, lista);
            this->recPreOrdem(chave->filhoDireita, lista);
        }
        return;
    }

    void recPosOrdem(Nodo<T> *chave, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (chave != nullptr)
        {
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

        Nodo<T> *pai = this->recInserir(this->raiz, chave);
        
        this->balanceiaArvore(pai);
    };

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */        
    virtual void remover(T chave) {
        if (this->vazia()) {
            return; // Árvore vazia, nada a fazer.
        }

        Nodo<T> *raiz = this->raiz;

        if(raiz->chave == chave && raiz->filhoEsquerda == nullptr && raiz->filhoDireita == nullptr)
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