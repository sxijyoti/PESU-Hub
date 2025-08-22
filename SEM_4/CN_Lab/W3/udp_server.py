import socket

HOST = '127.0.0.1'
PORT = 5001

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_server:
    udp_server.bind((HOST, PORT))
    print(f"UDP Server listening on {HOST}:{PORT}")

    while True:
        data, addr = udp_server.recvfrom(1024)
        print(f"Received (UDP) from {addr}: {data.decode()}")
        udp_server.sendto(b"UDP Message Received", addr)
