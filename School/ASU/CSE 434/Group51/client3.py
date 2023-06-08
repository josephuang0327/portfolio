from socket import *

print("Enter server IP address:")
serverName = input()
print(serverName)

print("Enter server port number:")
serverPort = int(input())
print(serverPort)

print("Enter client own port number:")
clientPort = int(input())
print(clientPort)


# serverName = '127.0.0.1'
# serverPort = 19999
clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.bind(('', clientPort))

while True:
    message = input('Input the info:')

    clientSocket.sendto(message.encode(), (serverName, serverPort))
    modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
    print(modifiedMessage.decode())

    if "exit" == message.split(" ")[0]:
        if modifiedMessage.decode() == "Success":
            clientSocket.close()
            break
    if "im-start" == message.split(" ")[0]:

        immessage = input('Text Message: ')
        print("Your message: " + immessage)
        clientSocket.sendto(immessage.encode(), (serverName, serverPort))
        modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
        if modifiedMessage.decode() == "Success":
            print("server received")


clientSocket.close()





