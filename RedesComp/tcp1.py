import socket
import time

def tcp_server():
    # Cria um objeto socket TCP
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    host = 'localhost'
    port = 14000

    # Vincula o host e a porta ao socket
    s.bind((host, port))

    # Escuta por conexões
    s.listen(1)
    print('TCP Server is listening on port', port)

    with open('received_file_tcp_12.txt', 'w') as f:
        while True:
            # Aceita a conexão
            conn, addr = s.accept()
            # Recebe os dados da conexão
            data = conn.recv(1024)
            if not data:
                break
            # Decodifica os dados recebidos para uma string e converte para maiúsculas
            response = data.decode('utf-8').upper()

            # Cria uma string com a resposta desejada, incluindo um timestamp formatado
            data_s = 'ACK' + '.' + response + '.18912.' + time.strftime('%Y-%m-%d %H:%M:%S')

            # Monta a mensagem de log
            message = 'Received message: ' + data_s + ' from: ' + str(addr)
            print(message)

            # Escreve a mensagem de log no arquivo
            f.write(message + '\n')

            try:
                # Envia a resposta de volta para o cliente
                conn.sendall(data_s.encode('utf-8'))
            except BrokenPipeError:
                print('Client connection closed.')

    # Fecha a conexão
    conn.close()

tcp_server()
