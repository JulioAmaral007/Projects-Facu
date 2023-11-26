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
#include <numeric> 


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
            for (const char& c : dado) {
                value = (value * n) + static_cast<std::size_t>(c);
            }

            // Calcula o índice final usando o módulo com a capacidade da tabela hash.
            return value % capacidade();
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
        std::size_t capacidade() const  {
            return this->tabela.size();
        };


        /**
         * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
         * é inserido novamente.
         *
         * @param dado O dado a ser inserido.
         */
        void inserir(T dado) {
            std::size_t tDado = funcaoEspalhamento(dado);
            auto& lista = this->tabela.at(tDado);
            if (!lista.contem(dado)) {
                lista.inserirNoFim(dado);
            }
        };


        /**
         * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
         * exceção ExcecaoDadoInexistente é lançada.
         *
         * @param dado O dado a ser removido.
         */
        void remover(T dado) {
            std::size_t tDado = funcaoEspalhamento(dado);
            if (!this->tabela[tDado].contem(dado))
                throw ExcecaoDadoInexistente();
            this->tabela[tDado].remover(dado);
        };


        /**
         * @brief Verifica se \p dado está contido na tabela.
         *
         * @param dado O dado sendo buscado.
         * @return true se o dado está contido na tabela; false caso contrário.
         */
        bool contem(T dado) const {
            std::size_t tDado = funcaoEspalhamento(dado);
            return this->tabela[tDado].contem(dado);
        };


        /**
         * @brief Obtém a quantidade de dados contidos na árvore.
         *
         * @return Um inteiro maior ou igual a 0.
         */
        virtual std::size_t quantidade() const  {
            return std::accumulate(this->tabela.begin(), this->tabela.end(), 0,
                           [](std::size_t total, const auto& lista) {
                               return total + lista.tamanho();
                           });
        };


        std::size_t funcaoEspalhamento(int dado) const {
            return static_cast<std::size_t>(dado) % this->tabela.size();
        }
};


#endif





