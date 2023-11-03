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


template<typename T, std::size_t capac>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, capac>
{
    protected:
        std::size_t funcaoEspalhamento(std::string dado) const {
            std::size_t value = 0;
            std::size_t n = 31; // Fator de espalhamento


            // Itera pelos caracteres na string e calcula o valor de espalhamento.
            for (std::size_t i = 0; i < dado.length(); i++) {
                value += static_cast<std::size_t>(dado[i]) * std::pow(n, dado.length() - (i + 1));
            }


            // Calcula o índice final usando o módulo com a capacidade da tabela hash.
            std::size_t tDado = (value % capacidade());
            return tDado;
        }


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
            return this->tabela.size();
        };


        /**
         * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
         * é inserido novamente.
         *
         * @param dado O dado a ser inserido.
         */
        void inserir(T dado)
        {
            std::size_t tDado = funcaoEspalhamento(dado);
            if(!this->tabela.at(tDado).contem(dado))
                this->tabela.at(tDado).inserirNoFim(dado);
        };


        /**
         * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
         * exceção ExcecaoDadoInexistente é lançada.
         *
         * @param dado O dado a ser removido.
         */
        void remover(T dado)
        {
            std::size_t tDado = funcaoEspalhamento(dado);
            if(!this->tabela.at(tDado).contem(dado))
                throw ExcecaoDadoInexistente();
            this->tabela.at(tDado).remover(dado);
        };


        /**
         * @brief Verifica se \p dado está contido na tabela.
         *
         * @param dado O dado sendo buscado.
         * @return true se o dado está contido na tabela; false caso contrário.
         */
        bool contem(T dado) const
        {
            std::size_t tDado = funcaoEspalhamento(dado);
            if(this->tabela.at(tDado).contem(dado))
                return true;
            return false;
        };


        /**
         * @brief Obtém a quantidade de dados contidos na árvore.
         *
         * @return Um inteiro maior ou igual a 0.
         */
        std::size_t quantidade() const
        {
            std::size_t size = 0;
            for (size_t i = 0; i < capacidade(); i++)
                size += this->tabela.at(i).tamanho();
            return size;
        };


        std::size_t funcaoEspalhamento(int dado) const
        {
        // Converte o valor inteiro em um valor sem sinal de tamanho.
        std::size_t value = static_cast<std::size_t>(dado);


        // Calcula o índice usando a operação de módulo com o tamanho da tabela.
        std::size_t tDado = value % this->tabela.size();
        return tDado;
        };
};


#endif





