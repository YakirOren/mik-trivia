import socket

SERVER_IP = '127.0.0.1'
PORT = 6969

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        try:
            client_socket.connect((SERVER_IP, PORT))
        except Exception as e:
            print("Error: ", e)
        data = client_socket.recv(1024)

        print(data.decode())   
        if data.decode() == "hello":
            client_socket.send('hello'.encode())
        
        while(True):
            pass


if __name__ == "__main__":
    main()
