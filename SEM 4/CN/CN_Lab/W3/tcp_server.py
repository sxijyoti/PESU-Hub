import socket

HOST = '127.0.0.1'
PORT = 5000

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcp_server:
    tcp_server.bind((HOST, PORT))
    tcp_server.listen()
    print(f"TCP Server listening on {HOST}:{PORT}")

    conn, addr = tcp_server.accept()
    with conn:
        print(f"Connected by {addr}")
        data = conn.recv(1024)
        if data:
            print(f"Received (TCP): {data.decode()}")
            conn.sendall(b"TCP Message Received")
