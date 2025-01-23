import socket

# Suspect database
suspects = {
    "John Doe": "Caught with fingerprints on the safe. Status: Guilty.",
    "Jane Smith": "Witness identified her at the scene. Status: Innocent.",
    "Robert Brown": "Surveillance footage showed him entering the building. Status: Guilty.",
}

# Server configuration
SERVER_IP = "127.0.0.1"  # Localhost
SERVER_PORT = 8080       # Port to listen on
BUFFER_SIZE = 1024       # Buffer size for incoming data

# Create and bind the server socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((SERVER_IP, SERVER_PORT))
server_socket.listen(5)  # Allow up to 5 simultaneous connections
print(f"Server is running on {SERVER_IP}:{SERVER_PORT}...")

# Accept and handle client connections
while True:
    client_socket, client_address = server_socket.accept()
    print(f"Connection from {client_address}")

    # Receive data from the client
    query = client_socket.recv(BUFFER_SIZE).decode()
    print(f"Received query: {query}")

    # Respond to the client's query
    response = suspects.get(query, "Suspect not found!")
    client_socket.send(response.encode())

    # Close the client connection
    client_socket.close()
