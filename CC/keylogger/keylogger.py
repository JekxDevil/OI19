def init():
    dict = {}
    letters = [
        "clank",
        "bong",
        'click',
        "tap",
        "poing",
        "clonk",
        "clack",
        "ping",
        "tip",
        "cloing",
        "tic",
        "cling",
        "bing",
        "pong",
        "clang",
        "pang",
        "clong",
        "tac",
        "boing",
        "boink",
        "cloink",
        "rattle",
        "clock",
        "toc",
        "clink",
        "tuc",
    ]
    for i,v in enumerate(letters):
        dict[v] = chr(ord('a')+i)

    dict["whack"] = " "
    
    return dict

def main():
    output = []
    shifted = False
    caps = False
    N = int(input())
    letters = init()
    for i in range(N):
        sound = input()
        if sound in letters:
            if shifted or caps: output.append(letters[sound].upper())
            else: output.append(letters[sound])
        else:
            if sound == "pop":
                output = output[:-1]
            elif sound == "bump":
                caps = not caps
            elif sound == "dink":
                shifted = True
            else:
                shifted = False
    print(''.join(output))
    

if __name__ == "__main__":
    main()