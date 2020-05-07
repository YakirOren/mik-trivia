import socket
import json
import bson

SERVER_IP = '127.0.0.1'
PORT = 6969


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket: #
        try:
            client_socket.connect((SERVER_IP, PORT))
            pass
        except Exception as e:
            print("Error: ", e)
        data = client_socket.recv(1024)

        #print(deSerialize(data.decode()))

        choise = input("1: Signup " + "\n" + "2: Login " + "\n" + "3: Exit" + "\n")
        # while choise != 3:
        if choise == '1':
            client_data = {"username": "user1", "password": "1234", "mail": "user1@gmail.com"}
            
            #print(Serialize(20, json.dumps(client_data)))
            client_socket.send(Serialize(20, json.dumps(client_data)).encode())
                 
            data = client_socket.recv(1024)
            print(deSerialize(data.decode()))
            # break


def Serialize(code:int ,data_string:str) -> str:
    bin_data = ' '.join(format(ord(x), 'b') for x in str(data_string)) #convert to bin in ascii/utf8
    
    return bin(code)[2:]+' ' + bin(len(data_string))[2:] + ' ' + bin_data


def deSerialize(bin_string:str) -> (int, json):
    bin_list = bin_string.split(' ')[:-1]
    x = ''.join(list(map(lambda x: chr(int(x,2)), bin_list)))
    return (tuple(x.split(' ')))

    


if __name__ == "__main__":
    main()
