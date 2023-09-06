# Grupo: Soquetinho
#Alunos: Júlio, Gregory, Capistrano

import socket
import time
import requests
import jwt

def public_ip():
    ip = requests.get('https://api.ipify.org').text
    return ip

def encoder (sn):



def decoder(encoded_jwt):

    public_key = """
    -----BEGIN PUBLIC KEY-----
    MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDIcOn9vpMVbHMunQ4SxiPV1A+b
    LxZDtZLM8jph7H1tVSeUDg+LOef6vWICllI3eQ/qSeKY6cCBZUqQbahfGxh7lQoL
    vKciCeoX3M71HF4uuEFSfJtT7J0vRvLoONzq+wCAtrybKrS4LMpq0FdfONKAfWoR
    YyDIrkSMxuCqVVKHyQIDAQAB
    -----END PUBLIC KEY-----
    """
    try:
        decoded_payload = jwt.decode(encoded_jwt, public_key.encode('utf-8'), algorithms=["HS256"])
        print("JWT Received Decoded:", "/n", decoded_payload, "/n")
    except jwt.InvalidTokenError:
        decoded_payload = ("JWT Received Invalid or Expired")
        print("JWT Received Invalid or Expired", "/n")

    return(decoded_payload)

def scan_udp_port(ip, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #sock.settimeout(5)

    with open('Resultados.txt', 'a') as f:
        print(encoder(1))
        try:
            #for i in range(4):
            
            sock.sendto(bytes(encoder(1)), (ip, port))              
            data, server = sock.recvfrom(1024)
            data_payload = data.split('.')[1]

            message = time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || UDP - OPEN' + '\n' + data_payload + '\n' + data
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


    #scan_tcp_port(tcp, 80)
    #scan_tcp_port(tcp, 2000)
    #scan_tcp_port(tcp, 4000)

    #scan_udp_port(udp, 2000)
    #scan_udp_port(udp, 23456)
    scan_udp_port(udp, 34567)

#scanner()
encoder(1)