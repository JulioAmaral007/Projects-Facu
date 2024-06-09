#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

#include <cmath>

template<typename T, std::size_t capac>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, capac>
{
    public:

        virtual std::size_t capacidade() const {
            return this->tabela.size();
        };

        virtual void inserir(T dado) {
            size_t posicao = funcaoEspalhamento(dado);

            if (!this->tabela[posicao].contem(dado))
            {
                this->tabela[posicao].inserirNoFim(dado);
            }  
        };

        virtual void remover(T dado) {
            size_t posicao = funcaoEspalhamento(dado);
            if (this->tabela[posicao].contem(dado))
            {
                this->tabela[posicao].remover(dado);
            }
            else
            {
                throw ExcecaoDadoInexistente();
            }
        };

        virtual bool contem(T dado) const {
            size_t posicao = funcaoEspalhamento(dado);
            return this->tabela[posicao].contem(dado);
        };

        virtual std::size_t quantidade() const {
            size_t quantidade = 0;
            
            for (int i = 0; i < this->tabela.size(); i++) {
                quantidade += this->tabela[i].tamanho();
            }
            
            return quantidade;
        };
    
    protected:

        virtual std::size_t funcaoEspalhamento(T dado) const {
            return codigoEspalhamento(dado) % capacidade();
        };
        
    private:
        /**
         * @brief Calcula a representação numérica de um tipo integral.
         * 
         * @tparam U O tipo integral.
         * @param integral Um valor integral.
         * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
         */
        template<typename U>
        std::size_t codigoEspalhamento(U integral) const
        {
            return static_cast<std::size_t>(integral);
        }
        
        std::size_t codigoEspalhamento(std::string const& string) const
        {
            size_t valor = 0;
            size_t length = string.length();
            
           for (std::size_t i = 0; i < length; i++) {
                valor += string[i] * std::pow(31, length - (i + 1));
            }

            return valor;
        }
        
    };

#endif
