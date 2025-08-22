import socket

HOST = '127.0.0.1'
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_client:
    tcp_client.connect((HOST, PORT))
    tcp_client.sendall(b"Hello from TCP client")

    data = tcp_client.recv(1024)
    print(f"Server response: {data.decode()}")
