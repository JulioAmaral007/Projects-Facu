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
    //override == sobrepor(sobrepõe os metodos usados na classe herdada)

    //destrutor
    ~MinhaListaEncadeada() override 
    {
        for(Elemento<T>  * aux = this->_primeiro;
            aux != nullptr;)
        {
            Elemento<T> * destruir = aux;
            aux = aux->proximo;
            delete destruir;
        }
    };
    
    //tamanho da lista encadeada
    size_t tamanho() const override
    {
        return this->_tamanho;
    };
    
    //verificação de lista vazia
    bool vazia() const override
    {
        if(tamanho() == 0 or this->_primeiro == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    
    //posição de um dado
    size_t posicao(T dado) const override
    {
    if(vazia())
    {
        throw ExcecaoListaEncadeadaVazia{};
    }
    size_t pos = 0;
    for(Elemento<T> * elemento = this->_primeiro;
        elemento != nullptr; 
        elemento = elemento->proximo, pos++)
        {
        if(dado == elemento->dado)
            {
                return pos;
            }
        }
    throw ExcecaoDadoInexistente{};
    };
    
    //verificação, caso pussua um certo dado
    bool contem(T dado) const override
    {
        for(Elemento<T> * elemento = this->_primeiro;
            elemento != nullptr;
            elemento = elemento->proximo)
        {
        if(elemento->dado == dado)
            {
                return true;
            }
        }
        return false;
    };
    
    //inserir um elemento no inicio da lista encadeada
    void inserirNoInicio(T dado) override
    {
        Elemento<T> * novoElemento = new Elemento<T>(dado, this->_primeiro);
        this->_primeiro = novoElemento;
        this->_tamanho ++;
    };
    
    //inserir um elemento em determinada posição da lista encadeada
    void inserir(size_t posicao, T dado) override
    {
        if(posicao < 0 or posicao > tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        if(posicao == 0)
        {
            this->inserirNoInicio(dado);
            return;
        }
        if(posicao == tamanho())
        {
            this->inserirNoFim(dado);
            return;
        }
        Elemento<T>  * Eauxiliar = this->_primeiro;
        for(size_t i = 1; i < posicao;
        Eauxiliar = Eauxiliar->proximo, i++){}
        Elemento<T> * novoElemento = new Elemento<T>{dado, Eauxiliar->proximo};
        Eauxiliar->proximo = novoElemento;
        this->_tamanho ++;
    };
    
    //inserir um elemento no final da minha lista encadeada
    void inserirNoFim(T dado) override
    {
        if(vazia())
        {   
            inserirNoInicio(dado);
            return;
        }
        Elemento<T>  * ultimo = this->_primeiro;
        while(ultimo->proximo != nullptr)
        {
            ultimo = ultimo->proximo;
        }
        Elemento<T>  * novoElemento = new Elemento<T>{dado, nullptr};
        ultimo->proximo = novoElemento;
        this->_tamanho ++;
    };
    
    //remover um elemento no inicio da minha lista encadeada
    T removerDoInicio() override
    {
        if(vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        Elemento<T>  * elemento = this->_primeiro;
        T dado = elemento->dado;
        this->_primeiro = elemento->proximo;
        delete elemento;
        this->_tamanho --;
        return dado;
    };
    
    //remover um elemento em determinada posição da lista encadeada
    T removerDe(size_t posicao) override
    {
        if(posicao < 0 or posicao >= tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        if(posicao == 0)
        {
            return this->removerDoInicio();
        }
        if(posicao == tamanho() - 1)
        {
            return this->removerDoFim();
        }
        Elemento<T>  * aux = this->_primeiro;
        for(size_t i = 1; i < posicao;
        aux = aux->proximo, i++) {}
        Elemento<T>  * deletar = aux->proximo;
        aux->proximo = deletar->proximo;
        T dado = deletar->dado;
        delete deletar;
        this->_tamanho --;
        return dado;
    };
    
    // remover o ultimo elemento da minha lista encadeada
    T removerDoFim() override
    {
        if(vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if(tamanho() == 1)
        {
            return this->removerDoInicio();
        }
        Elemento<T>  * pultimo = this->_primeiro;
        for(size_t i = 0; i < tamanho() - 2;
        pultimo = pultimo->proximo, i++) {}
        Elemento<T>  * ultimo = pultimo->proximo;
        T dado = ultimo->dado;
        pultimo->proximo = nullptr;
        delete ultimo;
        this->_tamanho --;
        return dado;
    };
    
    //remover algum dado
    void remover(T dado) override
    {
        removerDe(this->posicao(dado));
    };
};

#endif