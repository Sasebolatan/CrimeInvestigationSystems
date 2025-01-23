#ifndef WINSOCKCLIENT_H
#define WINSOCKCLIENT_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <codecvt>
#include <stdexcept>
#pragma comment(lib, "ws2_32.lib") // Link Winsock library

using namespace std;

class WinsockClient {
private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    bool isConnected;

    // Helper function to convert std::string to std::wstring
    std::wstring toWideString(const std::string& str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str);
    }

public:
    // Constructor
    WinsockClient() : isConnected(false) {}

    // Initialize the Winsock client
    void initialize(const string& serverIP, int port) {
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw runtime_error("Failed to initialize Winsock.");
        }

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            WSACleanup();
            throw runtime_error("Failed to create socket.");
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        // Convert IP address to binary form
        wstring wideIP = toWideString(serverIP);
        if (InetPton(AF_INET, wideIP.c_str(), &serverAddr.sin_addr) <= 0) {
            closesocket(clientSocket);
            WSACleanup();
            throw runtime_error("Invalid IP address.");
        }
    }

    // Connect to the server
    void connectToServer() {
        cout << "Attempting to connect to server..." << endl;

        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            closesocket(clientSocket);
            WSACleanup();
            throw runtime_error("Failed to connect to server.");
        }

        isConnected = true;
        cout << "Connected to server successfully!" << endl;
    }

    // Send a query and receive a response
    string sendAndReceive(const string& query) {
        if (!isConnected) {
            throw runtime_error("Not connected to a server.");
        }

        cout << "Sending query to server: " << query << endl;

        // Send query
        if (send(clientSocket, query.c_str(), query.length(), 0) == SOCKET_ERROR) {
            throw runtime_error("Failed to send query.");
        }

        // Receive response
        char buffer[1024] = { 0 };
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesReceived == SOCKET_ERROR) {
            throw runtime_error("Failed to receive response.");
        }

        cout << "Response received from server." << endl;
        return string(buffer, bytesReceived);
    }

    // Gracefully close the connection
    void cleanup() {
        if (isConnected) {
            cout << "Closing connection to server..." << endl;
            closesocket(clientSocket);
            isConnected = false;
        }
        WSACleanup();
    }

    // Destructor
    ~WinsockClient() {
        cleanup();
    }
};

#endif // WINSOCKCLIENT_H
