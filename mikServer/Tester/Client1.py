import socket
import json
import bson

SERVER_IP = '127.0.0.1'
PORT = 6969


def main():
    client_data = {"username": "user1",
        "password": "1234", "mail": "user1@gmail.com"}
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            client_socket.connect((SERVER_IP, PORT))
            pass
        except Exception as e:
            print("Error: ", e)

        choise = input("1: Signup " + "\n" + "2: Login " +
                       "\n" + "3: Exit" + "\n")

        if choise == '1':
            client_socket.send(Serialize(200, client_data))
            data = client_socket.recv(1024)
            print(deSerialize(data))


def Serialize(code: int, data_string: json):
    d = code.to_bytes(1, byteorder='big') + (len(str(data_string))).to_bytes(4, byteorder='big') + json.dumps(data_string).encode()
    return d


def deSerialize(bin_string:str) -> (int, json):
    print(bin_string)
    return (int(bin_string[0]), json.loads(bin_string[5:]))

    


if __name__ == "__main__":
    main()
