#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente
#include <cmath>

template<typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, _capacidade>
{
    ///////////////////////////////////////////////////////////////////////
    protected:
    std::size_t Valor(std::string str) const //ok
    {
        int id = 0;
        int tam = str.size();
        for(int i=0; i <= tam; i++)
        {
            id += str[i] * pow(31, tam -(i+1));
        }
        return id;
    };

    std::size_t Valor(std::size_t num) const //ok
    {
        return num; 
    };


    ///////////////////////////////////////////////////////////////////////
    public:
    ~MinhaTabelaEspalhamento() {};

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Obt?m a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    std::size_t capacidade() const
    {
        return this->_tabela.size();
    };

    ///////////////////////////////////////////////////////////////////////
    public:
    /**
     * @brief Insere um dado na tabela. Se a tabela j? contiver o dado, ele n?o
     * ? inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    void inserir(T dado) 
    {
        size_t FunH = funcaoEspalhamento(dado);
        if(!this->_tabela[FunH].contem(dado))
            this->_tabela[FunH].adicionaNoFim(dado);
    };

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Remove um dado da tabela. Se a tabela n?o contiver o dado, uma
     * exce??o ExcecaoDadoInexistente ? lan?ada.
     * 
     * @param dado O dado a ser removido.
     */
    void remover(T dado) 
    {
        size_t FunH = funcaoEspalhamento(dado);
        if(!this->_tabela[FunH].contem(dado))
            throw ExcecaoDadoInexistente();
        this->_tabela[FunH].retiraEspecifico(dado);
    };

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Verifica se \p dado est? contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado est? contido na tabela; false caso contr?rio.
     */
    bool contem(T dado) const //ok
    {
        return this->_tabela[funcaoEspalhamento(dado)].contem(dado);
    };

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Obt?m a quantidade de dados contidos na ?rvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t quantidade() const
    {
        std::size_t qnt = 0;
        for(int i=0; i < capacidade(); i++)
            qnt += this->_tabela[i].getTamanho();
        return qnt;
    };

    ///////////////////////////////////////////////////////////////////////

    /**
     * @brief Obt?m a posi??o correspondente na tabela para o dado.
     * 
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */

    //M?dulo
    std::size_t funcaoEspalhamento(T dado) const // ok
    {
        return Valor(dado) % capacidade();
    };

    ///////////////////////////////////////////////////////////////////////
};

#endif
