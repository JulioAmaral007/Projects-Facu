import jwt

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

# payload = {
#     "group": "Soquetinho",
#     "seq_number": 1,
#     "seq_max": 3,
#     "matricula": 18204884,
# }

encoded = jwt.encode(payload, private_key.encode('utf-8'), algorithm="RS256")
print(encoded)