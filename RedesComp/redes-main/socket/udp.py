import signal
import sys
import socket
import time

# Define a função de manipulação de sinal
def signal_handler(signal, frame):
    print('\nVocê pressionou Ctrl+C! Encerrando o servidor...')
    # Aqui você pode adicionar qualquer limpeza ou funções de desligamento
    sys.exit(0)

# Configura o manipulador de sinal para capturar SIGINT
signal.signal(signal.SIGINT, signal_handler)

def udp_server():
    # cria um objeto socket UDP
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # define o host e a porta
    host = 'localhost'
    port = 16000

    # vincula o host e a porta
    s.bind((host, port))

    print('UDP Server is listening on port', port)

    with open('received_file_udp_16.txt', 'w') as f:
        # loop infinito
        while True:
            # recebe dados
            data, addr = s.recvfrom(1024)
            response = data.decode('utf-8').upper()
            data_s = 'ACK'+'.'+response+'.18912.'+time.strftime('%Y-%m-%d %H:%M:%S')

            message = 'Received message: ' + data_s + ' from: ' + str(addr)
            print(message)

            # grava os dados no arquivo de log
            f.write(message + '\n')

            # envia a mensagem de volta para o cliente
            s.sendto(bytes(data_s.encode('utf-8')), addr)

udp_server()
