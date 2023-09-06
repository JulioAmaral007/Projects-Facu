# Grupo: Soquetinho
#Alunos: Júlio, Gregory, Capistrano 

import socket
import time
import requests
import jwt

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
            sock.sendto(bytes(encoder()), (ip, port)) 
            data, server = sock.recvfrom(1024)  
            data_split = decoder(data)
            print(data_split)
            
            for s in data_split:
                if s == 'SOQUETINHO':
                    message =  time.strftime('%Y-%m-%d %H:%M:%S') + ' || ' + public_ip() + ' -> ' + ip + '/'+ str(port) + ' || UDP - OPEN || Resposta ' + data_split.decode('utf-8')
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

def encoder ():
    private_key =  """
    -----BEGIN RSA PRIVATE KEY-----
    MIICXQIBAAKBgQDIcOn9vpMVbHMunQ4SxiPV1A+bLxZDtZLM8jph7H1tVSeUDg+L
    Oef6vWICllI3eQ/qSeKY6cCBZUqQbahfGxh7lQoLvKciCeoX3M71HF4uuEFSfJtT
    7J0vRvLoONzq+wCAtrybKrS4LMpq0FdfONKAfWoRYyDIrkSMxuCqVVKHyQIDAQAB
    AoGAIQXCnyc/GeKjT/+DBTfMnpq7NCYRT81se+8VDEix2gnopTKd1U0QeYBVqIx1
    y3raqDmiUe6s5FnjliDi15cMtMDiUtgr/6GBYy75BNXB36lyfLVQxj8AnWOuYnbE
    DyvZgRZwyymINRyfvr1ZgUPNQzZfO4omhaTnzWg5HW1LnksCQQDofU/29iTuRUAs
    0yMVdBCIaGrPEdEBjv63FmehuBNHfJ844GB0pvjSCuxrEm0LCucoAM5MgvbWOh/b
    gmIfvKSjAkEA3LXulSw3wiJzA7PbgiVW3aMyxZpnO/cDCSywlWiZYL5c4yXes3Xm
    2e92Tum4KEY9wTu9uQkw5hIDXLqW0lq8owJAG8mGejT3OwdJ4VGm+tRxeWxJf9BY
    U8Bcj1N9NWYD3+J0QV8ICElAqhImKbH9GHnIIQ7fmWN5zycJUbomsjZg0wJBAIx7
    OHq2hF8K8k4fAs7Z2WqFX+Gqn57pYINMcLEIvOd5A0KJbjCoEOISqykbVl48Jz6B
    Ogc2tGsceAtjsG//1SUCQQCyGCtnS0XtZZvkr43hzXiCpvo5UHy89FKR7+vD5GZG
    TdFel874nxCYmtqMhFxSmPjO3Zpeh4KU4KsfA5tX5QFU
    -----END RSA PRIVATE KEY-----
    """

    payload = {
        "group": "Soquetinho",
        "seq_number": 1,
        "seq_max": 3,
        "matricula": 18204884,
    }

    encoded = jwt.encode(payload, private_key.encode('utf-8'), algorithm="RS256")
    print(encoded)
    return(encoded)


def decoder():
    public_key = """
    -----BEGIN PUBLIC KEY-----
    MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDIcOn9vpMVbHMunQ4SxiPV1A+b
    LxZDtZLM8jph7H1tVSeUDg+LOef6vWICllI3eQ/qSeKY6cCBZUqQbahfGxh7lQoL
    vKciCeoX3M71HF4uuEFSfJtT7J0vRvLoONzq+wCAtrybKrS4LMpq0FdfONKAfWoR
    YyDIrkSMxuCqVVKHyQIDAQAB
    -----END PUBLIC KEY-----
    """

    encoded_jwt = input("Digite o token JWT a ser verificado: ")

    try:
        decoded_payload = jwt.decode(encoded_jwt, public_key.encode('utf-8'), algorithms=["RS256"])
        print("Token válido.","Payload:", decoded_payload)
    except jwt.InvalidTokenError:
        print("Token inválido ou expirado.")
    
    return(decoded_payload)

