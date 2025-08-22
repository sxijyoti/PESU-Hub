import socket

HOST = '127.0.0.1'
PORT = 5001

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp_client:
    message = "Hello from UDP client"
    udp_client.sendto(message.encode(), (HOST, PORT))

    data, server = udp_client.recvfrom(1024)
    print(f"Server response: {data.decode()}")
