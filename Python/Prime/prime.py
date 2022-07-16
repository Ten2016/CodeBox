


def prime_idx(target_idx):

    idx = 0
    prime = 2

    while True :

        is_prime = True

        j = 2
        while j * j <= prime :
            if prime % j == 0 :
                is_prime = False
                break
            j += 1
        
        if is_prime :
            idx += 1
            if idx == target_idx:
                break
        
        prime += 1

    return prime



if __name__ == "__main__":
    while True:
        idx = input("prime idx: ")
        if idx == "q" or idx == "quit" or idx == "Q" or idx == "QUIT":
            print("quit")
            break
        
        idx = int(idx)

        if idx <= 0:
            continue

        prime = prime_idx(idx)
        print("prime:", prime)


