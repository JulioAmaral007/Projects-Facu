import jwt

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
