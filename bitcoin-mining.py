'''
Código que mostra o algoritmo de mineração do bitcoin, é importante 
dizer que atualmente o nível de dificuldade (números de zeros) é de 20 hoje.

A chave é descobrir o nonce.

BoaSorte!

By Marcos Bah
'''

from hashlib import sha256
MAX_NONCE = 100000000000000

def SHA256(text):
    return sha256(text.encode("ascii")).hexdigest()

def mine(block_number, transactions, previous_hash, prefix_zeros):
    prefix_str = '0' * prefix_zeros
    for nonce in range(MAX_NONCE):
        text = str(block_number) + transactions + previous_hash + str(nonce);
        new_hash = SHA256(text)
        if(new_hash.startswith(prefix_str)):
            print(f"WOWWWWW! Successfully mined bitcoins with nonce value:{nonce}")
            return new_hash

    raise BaseException(f"Couldn find correct has after trying {MAX_NONCE} times")

if __name__ == '__main__':
    transactions='''
    Dhaval->Bhavin->20,
    Mando->Cara->45
    '''

    #today is 20 on Bitcoin Chain
    difficulty=6
    new_hash = mine(5, transactions, 'b5d4045c3f466fa91fe2cc6abe79232a1a57cdf104f7a26e716e0a1e2789df78',difficulty)
    print(new_hash)
    