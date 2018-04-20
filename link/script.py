#!/bin/env python3
import sys
import PIL.Image as Image
import numpy as np
import websockets
import base64
import os

png = 0

def transform(string):
    if len(string) > 7 and string[:7] == "\x1b[1;32m":
        return (0, 255, 0)
    elif len(string) > 7 and string[:7] == "\x1b[1;33m":
        return (255, 255, 0)
    elif len(string) > 7 and string[:7] == "\x1b[1;34m":
        return (0, 0, 255)
    elif len(string) > 7 and string[:7] == "\x1b[1;35m":
        return (255, 0, 0)
    elif string == "0x00 ":
        return (127, 127, 127)
    return ((127, 127, 127))

def process_dump(string):
    global png
    with websockets.connect('ws://localhost:3000/image') as websocket
        data = string.split("\x1b[0m")
        data = list(filter(lambda str: str if len(str) and not (len(str) == 12 and str.find(":") != -1) else 0, data))
        data = list(map(lambda str: str[11:] if str[0] == "\n" else str, data))
        data[0] = data[0][11:]
        data = list(map(transform, data))[:-1]
        arr = np.reshape(np.array(data, dtype=np.uint8), (64, 96, 3))
        image = Image.fromarray(arr, "RGB")
        image.save("file.png")
        with open("file.png", "rb") as f:
            websocket.send(base64.b64encode(f.read()))
        os.system("rm file.png")


string = ""
new_str = "a"
while len(new_str):
    new_str = sys.stdin.readline()
    if new_str != "====\n":
        string += new_str
    else:
        process_dump(string)
        string = ""
