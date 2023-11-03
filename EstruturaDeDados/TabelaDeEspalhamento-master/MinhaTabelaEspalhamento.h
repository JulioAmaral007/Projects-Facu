#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

#include <typeinfo>
#include <cmath>

#include <array>
// std::array

template <typename T, std::size_t _capacidade>
class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, _capacidade>
{
public:
    ~MinhaTabelaEspalhamento()
    {
    }

    /**
     * @brief Obtém a capacidade da tabela.
     * 
     * @return Um inteiro maior do que 0.
     */
    std::size_t capacidade() const
    {
        return this->_tabela.size();
    };

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     * 
     * @param dado O dado a ser inserido.
     */
    void inserir(T dado)
    {
        std::size_t chaveDivisao = funcaoEspalhamento(dado);
        this->_tabela.at(chaveDivisao).adicionaNoFim(dado);
    };

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     * 
     * @param dado O dado a ser removido.
     */
    void remover(T dado)
    {
        try
        {
            std::size_t chaveDivisao = funcaoEspalhamento(dado);
            this->_tabela.at(chaveDivisao).retiraEspecifico(dado);
        }
        catch (const char *msg)
        {
            throw ExcecaoDadoInexistente();
        }
    };

    /**
     * @brief Verifica se \p dado está contido na tabela.
     * 
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    bool contem(T dado) const
    {
        std::size_t chaveDivisao = funcaoEspalhamento(dado);
        return this->_tabela.at(chaveDivisao).contem(dado);
    };

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    std::size_t quantidade() const
    {
        std::size_t size = 0;
        for (size_t i = 0; i < this->_tabela.size(); i++)
            size += this->_tabela.at(i).getTamanho();

        return size;
    };

protected:
    std::size_t funcaoEspalhamento(std::string dado) const
    {
        std::size_t value = 0;
        for (std::size_t i = 0; i < dado.length(); i++)
        {
            std::size_t n = 31;
            std::size_t teste = dado[i] * pow(n, dado.length() - (i + 1));
            value += teste;
        }
        std::cout << value << std::endl;

        std::size_t chaveDivisao = (value % this->_tabela.size());
        return chaveDivisao;
    };

    std::size_t funcaoEspalhamento(int dado) const
    {

        std::size_t value = (std::size_t)dado;

        std::size_t chaveDivisao = (value % this->_tabela.size());
        return chaveDivisao;
    };
};

#endif