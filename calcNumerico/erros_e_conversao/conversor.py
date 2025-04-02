def binario_para_decimal(binario):
    try:
        if not all(c in '01.' for c in binario):
            raise ValueError("Número binário inválido. Use apenas 0 e 1 (com ponto opcional para frações).")
        
        if '.' in binario:
            parte_inteira, parte_fracionaria = binario.split('.')
            decimal_inteiro = int(parte_inteira, 2)
            decimal_fracionario = sum(int(bit) * 2**(-i) for i, bit in enumerate(parte_fracionaria, 1))
            return decimal_inteiro + decimal_fracionario
        else:
            return int(binario, 2)
    except ValueError:
        raise ValueError("Número binário inválido.")

def decimal_para_binario(decimal):
    try:
        decimal = float(decimal)
        parte_inteira = int(decimal)
        parte_fracionaria = decimal - parte_inteira
        binario_inteiro = bin(parte_inteira)[2:]
        binario_fracionario = ''
        
        while parte_fracionaria and len(binario_fracionario) < 10:  # Limite de precisão
            parte_fracionaria *= 2
            bit = int(parte_fracionaria)
            binario_fracionario += str(bit)
            parte_fracionaria -= bit
        
        return binario_inteiro + ('.' + binario_fracionario if binario_fracionario else '')
    except ValueError:
        raise ValueError("Número decimal inválido.")

def main():
    print("Conversor de Binário <-> Decimal")
    while True:
        escolha = input("\nEscolha a conversão:\n1 - Binário para Decimal\n2 - Decimal para Binário\n3 - Sair\nOpção: ")
        
        if escolha == '1':
            binario = input("Digite um número binário (com ponto opcional para frações): ")
            try:
                decimal = binario_para_decimal(binario)
                print(f"O valor decimal de {binario} é {decimal}")
            except ValueError as e:
                print(e)
        
        elif escolha == '2':
            try:
                decimal = input("Digite um número decimal: ")
                binario = decimal_para_binario(decimal)
                print(f"O valor binário de {decimal} é {binario}")
            except ValueError as e:
                print(e)
        
        elif escolha == '3':
            print("Encerrando o programa...")
            break
        
        else:
            print("Opção inválida! Escolha novamente.")

if __name__ == "__main__":
    main()
