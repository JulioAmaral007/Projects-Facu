#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    public:

    //destrutor
    virtual ~MinhaListaEncadeada() 
    {
        // Inicializa um ponteiro auxiliar para percorrer a lista, começando pelo primeiro elemento.
        Elemento<T> *aux = this->_primeiro;
    
        // Percorre a lista em um loop.
        while (aux != nullptr) {
            // Armazena o ponteiro para o elemento atual que será destruído.
            Elemento<T> *destruir = aux;
    
            // Avança para o próximo elemento na lista.
            aux = aux->proximo;
    
            // Libera a memória do elemento atual.
            delete destruir;
        }
    };

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    
    virtual std::size_t tamanho() const {
        return this->_tamanho;
    }
    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const {
        if(this->_primeiro == NULL)
            return true;
        return false;
    }

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const {
        Elemento<T>* elemento = this->_primeiro;

        if(vazia())
            throw ExcecaoListaEncadeadaVazia();

       size_t pos = 0;
    
        // Percorre a lista em um loop enquanto não atingir o final (elemento == nullptr).
        while (elemento != nullptr) {
            // Compara o dado do elemento atual com o dado fornecido.
            if (dado == elemento->dado) {
                // Se encontrarmos o dado, retornamos a posição atual.
                return pos;
            }         
            // Avança para o próximo elemento na lista e incrementa a posição.
            elemento = elemento->proximo;
            pos++;
            }
    
        // Se chegarmos ao final da lista sem encontrar o dado, lançamos a exceção ExcecaoDadoInexistente.
        throw ExcecaoDadoInexistente();
    }
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const {
        // Verifica se a lista está vazia.
        if (vazia()) {
            return false;
        }
    
        // Inicializa um ponteiro para percorrer a lista.
        Elemento<T> *Elemento_Atual = this->_primeiro;
    
        // Percorre a lista enquanto não atingir o final (Elemento_Atual == nullptr).
        while (Elemento_Atual != nullptr) {
            // Compara o dado do Elemento_Atual atual com o dado fornecido.
            if (Elemento_Atual->dado == dado) {
                // Se encontrarmos o dado, retornamos true.
                return true;
            }
            // Avança para o próximo Elemento_Atual na lista.
            Elemento_Atual = Elemento_Atual->proximo;
        }
    
        // Se chegarmos ao final da lista sem encontrar o dado, retornamos false.
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) {
    // Cria um novo elemento com o dado fornecido e aponta para o elemento atualmente no início.
    Elemento<T> *novoElemento = new Elemento<T>(dado, this->_primeiro);

    // Atualiza o ponteiro do início para apontar para o novo elemento.
    this->_primeiro = novoElemento;

    // Incrementa o tamanho da lista.
    this->_tamanho++;
    }
    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado) {
        if(posicao > tamanho() || posicao < 0)
            throw ExcecaoPosicaoInvalida();

        if(posicao == 0)
           return inserirNoInicio(dado);
           
        if(posicao == tamanho())
           return inserirNoFim(dado);
           
       // Encontra o elemento anterior à posição de inserção.
        Elemento<T> *elementoAUX = this->_primeiro;
        for (size_t i = 1; i < posicao; ++i) {
            elementoAUX = elementoAUX->proximo;
        }
    
        // Cria um novo elemento com o dado fornecido e o insere na posição desejada.
        Elemento<T> *novoElemento = new Elemento<T>{dado, elementoAUX->proximo};
        elementoAUX->proximo = novoElemento;
    
        // Incrementa o tamanho da lista.
        this->_tamanho++;
    }
    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado) {
        // Verifica se a lista está vazia.
        if (vazia()) {
            // Se a lista estiver vazia, insere o elemento no início da lista.
            inserirNoInicio(dado);
            return;
        }
    
        // Inicializa um ponteiro para percorrer a lista e encontrar o último elemento.
        Elemento<T> *ultimo = this->_primeiro;
    
        // Percorre a lista até encontrar o último elemento (aquele cujo próximo é nullptr).
        while (ultimo->proximo != nullptr) {
            ultimo = ultimo->proximo;
        }
    
        // Cria um novo elemento com o dado fornecido e o torna o próximo do último elemento.
        Elemento<T> *novoElemento = new Elemento<T>{dado, nullptr};
        ultimo->proximo = novoElemento;
    
        // Incrementa o tamanho da lista.
        this->_tamanho++;
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio() {
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
            
        Elemento<T> *elementoRemovido = this->_primeiro;
        T dado = elementoRemovido->dado;
    
        // Atualiza o primeiro elemento para apontar para o próximo elemento.
        this->_primeiro = this->_primeiro->proximo;
    
        // Libera a memória do elemento removido.
        delete elementoRemovido;
    
        // Decrementa o tamanho da lista e retorna o dado removido.
        this->_tamanho--;
        return dado;
    }
    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao) {
         // Verifica se a posição é válida (dentro da faixa [0, tamanho)) e se a lista não está vazia.
        if(this->_primeiro != nullptr && posicao == 0)
            return removerDoInicio();

        if(posicao >= tamanho() || posicao < 0 || vazia())
            throw ExcecaoPosicaoInvalida();
        
        // Se a posição for igual ao tamanho menos 1 (último elemento), chama removerDoFim() para remover o último elemento.
        if(posicao == (tamanho()-1))
            return removerDoFim();
        
        // Se a posição estiver no meio da lista, encontra o elemento anterior à posição desejada.
        Elemento<T> *anterior = this->_primeiro;
        for (size_t i = 1; i < posicao; ++i) {
            anterior = anterior->proximo;
        }
    
        // Remove o elemento da posição, atualizando os ponteiros 'proximo' para manter a lista encadeada intacta.
        Elemento<T> *deletar = anterior->proximo;
        anterior->proximo = deletar->proximo;
        T dado = deletar->dado;
        
        // Libera a memória do elemento removido.
        delete deletar;
    
        // Decrementa o tamanho da lista e retorna o dado removido.
        this->_tamanho--;
        return dado;
    }
    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     *  
     */
    virtual T removerDoFim() {
        // Verifica se a lista está vazia.
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
        
        // Se a lista tiver apenas um elemento, chama removerDoInicio() para removê-lo.
        if(tamanho() == 1)
            return removerDoInicio();
            
        Elemento<T> *elemento = this->_primeiro;
        Elemento<T> *anterior = nullptr; // Guarda o elemento anterior.
        T dado;
    
        // Percorre a lista até encontrar o último elemento.
        while (elemento->proximo != nullptr) {
            anterior = elemento;
            elemento = elemento->proximo;
        }
    
        dado = elemento->dado; // Obtém o dado do último elemento.
    
        if (anterior != nullptr) {
            // Remove a conexão com o último elemento se ele não for o primeiro.
            anterior->proximo = nullptr;
        } else {
            // Se o elemento anterior for nulo, significa que estamos removendo o primeiro elemento.
            // Atualize o primeiro para apontar para o próximo elemento.
            this->_primeiro = elemento->proximo;
        }
    
        delete elemento; // Libera a memória do último elemento.
    
        this->_tamanho--;
        return dado; // Retorna o dado do último elemento removido.
    };
    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado) {
        if(vazia())
            throw ExcecaoListaEncadeadaVazia();
        
        if(contem(dado) == false)
            throw ExcecaoDadoInexistente();
            
        removerDe(this->posicao(dado));
    }
};

#endif