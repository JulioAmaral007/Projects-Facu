# Grupo: Soquetinho
#Alunos: Júlio, Gregory, Capistrano 

import socket
import time
import requests

def public_ip():
    ip = requests.get('https://api.ipify.org').text
    return ip

def scan_tcp_port(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5)
    with open('Resultados.txt', 'a') as f:
        try:
            sock.connect((ip, port)) 
            sock.sendall(bytes('soquetinho'.encode('utf-8'))) 
            data = sock.recv(1024)  
            
            if data:  
                message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || TCP - OPEN'
                print(message)
                f.write(message + '\n')
            else:
                message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || TCP - CLOSE'
                print(message)
                f.write(message + '\n')
                sock.close() 

        except socket.error:
            message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || TCP - CLOSE'
            print(message)
            f.write(message + '\n')
            sock.close()  
            pass

def scan_udp_port(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(5) 

    with open('Resultados.txt', 'a') as f:
        try:
            sock.sendto(bytes('soquetinho'.encode('utf-8')), (ip, port)) 
            data, server = sock.recvfrom(1024)  
            data_split = data.decode('utf-8').split('.') 
            
            for s in data_split:
                if s == 'SOQUETINHO':
                    message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || UDP - OPEN || Resposta ' + data.decode('utf-8')
                    print(message)
                    f.write(message + '\n')   

        except:
            message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || UDP - CLOSE FILTERED'
            print(message)
            f.write(message + '\n')
            pass

def scanner():
    tcp = 'noctilucentis.com.br'
    udp = 'gersoncamillo.seg.br'
    public_ip()
    

    scan_tcp_port(tcp, 80)
    scan_tcp_port(tcp, 2000)
    scan_tcp_port(tcp, 4000)

    scan_udp_port(udp, 2000)
    scan_udp_port(udp, 23456)
    scan_udp_port(udp, 34567)

scanner()
