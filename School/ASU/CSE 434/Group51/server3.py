from socket import *
import sys

IMlist = []
IMstartname = ''
IMstartlist = ''
#dict for registered contact-name database
register = {}

#dict for contact-list-name database
conlistname = {}

print("Enter port number:")
serverPort = int(input())
print(serverPort)

#serverPort = 19999
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print('The server is ready to receive')

#This loop keeps running to recieve requests from clients
while True:
 message, clientAddress = serverSocket.recvfrom(2048)
 print('recieved',clientAddress)

 modifiedMessage = message.decode()

 #The condition check for all the queries
 cmd = modifiedMessage.split(" ")[0]
 if cmd == '':
     pass
 elif cmd == "register":
  contactname = modifiedMessage.split(" ")[1]
  ip = modifiedMessage.split(" ")[2]
  port = modifiedMessage.split(" ")[3]
  if contactname not in register:
   register[contactname] = [ip, port]
   serverSocket.sendto("Success".encode(), clientAddress)
  else:
   serverSocket.sendto("Failure".encode(), clientAddress)

 elif cmd == "create":
  contactlistname = modifiedMessage.split(" ")[1]
  if contactlistname not in conlistname:
   conlistname[contactlistname] = []  # create a empty list for the name(as dict key)
   serverSocket.sendto("Success".encode(), clientAddress)
  else:
   serverSocket.sendto("Failure".encode(), clientAddress)

 elif cmd == "query-lists":
  returnstr = str(len(conlistname)) + " " + str(conlistname.keys())
  serverSocket.sendto(returnstr.encode(), clientAddress)

 elif cmd == "join":          #IM priority
  contactlistname2 = modifiedMessage.split(" ")[1]
  contactname2 = modifiedMessage.split(" ")[2]

  if contactname2 in IMlist:
      serverSocket.sendto("Failure".encode(), clientAddress)
  else:
      if contactname2 in register:  # check to see if the contact name is registered
          if contactlistname2 in conlistname:  # check to see if the contact-name-list exists
              if contactname2 not in conlistname.get(
                      contactlistname2):  # check to see if the contact name is already in the contact-name-list
                  conlistname[contactlistname2].append(contactname2)
                  conlistname[contactlistname2].append(register.get(contactname2))
                  serverSocket.sendto("Success".encode(), clientAddress)
              else:
                  serverSocket.sendto("Failure".encode(), clientAddress)
          else:
              serverSocket.sendto("Failure".encode(), clientAddress)
      else:
          serverSocket.sendto("Failure".encode(), clientAddress)



 elif cmd == "leave":      #IM priority
  leavecontactlist = modifiedMessage.split(" ")[1]
  leavecontactname = modifiedMessage.split(" ")[2]
  leaveIPandport = register.get(leavecontactname)
  if leavecontactname in IMlist:
      serverSocket.sendto("Failure".encode(), clientAddress)
  else:
      for key in conlistname:
          if leavecontactname in conlistname[key]:
              conlistname[key].remove(leavecontactname)
              conlistname[key].remove(leaveIPandport)
              serverSocket.sendto("Success".encode(), clientAddress)
          else:
              serverSocket.sendto("Failure".encode(), clientAddress)




 elif cmd == "exit":       #IM priority
  exitcontactname = modifiedMessage.split(" ")[1]
  exitIPandport = register.get(exitcontactname)
  if exitcontactname in IMlist:
      serverSocket.sendto("Failure".encode(), clientAddress)
  else:
      del register[exitcontactname]
      for key in conlistname:
          if exitcontactname in conlistname[key]:
              conlistname[key].remove(exitcontactname)
              conlistname[key].remove(exitIPandport)
              serverSocket.sendto("Success".encode(), clientAddress)
          else:
              serverSocket.sendto("Failure".encode(), clientAddress)


 elif cmd == "save":
  try:
   file_name = modifiedMessage.split(" ")[1]
   # add info to the new file
   with open("%s.txt" % file_name, "w+") as txt:
    print(len(register), file=txt)
    print(register, file=txt)
    print(len(conlistname), file=txt)
    for name in conlistname:
     print(name, (len(conlistname[name]) / 2), file=txt)
    print((conlistname), file=txt)

    serverSocket.sendto("Success".encode(), clientAddress)
  except:
   serverSocket.sendto("Failure".encode(), clientAddress)


 elif cmd == "im-start":
    imstartcontactlist = modifiedMessage.split(" ")[1]
    imstartcontactname = modifiedMessage.split(" ")[2]
    IMstartname = imstartcontactname
    IMstartlist = imstartcontactlist
    #maybe it work
    #should print the number of people in contact list

    if imstartcontactlist not in conlistname:                       # if contact list name NOT in conlistname
      serverSocket.sendto("Number of Contact: 0".encode(), clientAddress)
    else:                                                           # if contact list name IS in conlistname
      try:
        if imstartcontactname in conlistname[imstartcontactlist]:   # if contact name exist in contact list
          result = ''
          result += ("Number of contact: " + str(len(conlistname[imstartcontactlist]) / 2)) + '\n'
          for name in conlistname[imstartcontactlist]:              # print the contact name "first"
            if name == imstartcontactname:
              ipandport = register.get(str(name))
              result += str(name) + " " + str(ipandport) + '\n'

          for name in conlistname[imstartcontactlist]:              # print the rest contacts after contact name
            if name != imstartcontactname and type(name) is str:
              ipandport = register.get(str(name))
              result += str(name) + " " + str(ipandport) + "\n"
          serverSocket.sendto(result.encode(), clientAddress)       # send contact list list
          modifiedMessage, clientAddress = serverSocket.recvfrom(2048)  # received message from client
          messagetosend = modifiedMessage.decode()
          print("Received Text: " + messagetosend)
          i = 0
          for name in conlistname[imstartcontactlist]:              # loop to send message to everyone in contact list
            messagetosend = modifiedMessage.decode()
            if type(name) is str:
                IMlist.append(name)  #add to IMlist to give priority
                i += 2
                if name != imstartcontactname:
                   # send to everyone other then the person itself(imstartcontactname)
                    ipandport = register.get(str(name))
                    contactip = ipandport[0]  # get ip    ['123.1.2.3', '12']
                    contactport = ipandport[1]  # get port
                    # print("Name: " + name + " IP: " + contactip + " Port: " + contactport)
                    if i >= len(conlistname[imstartcontactlist]) - 1:
                        nextname = imstartcontactname
                        nextipandport = register.get(str(nextname))
                        nextip = nextipandport[0]
                        nextport = nextipandport[1]
                        messagetosend = imstartcontactname + ' says: ' + messagetosend + '\n' + '[sent to ' + nextname + ' at IP ' + nextip + ' and port ' + nextport + ' ]'
                    else:
                        nextname = conlistname[imstartcontactlist][i]
                        nextipandport = register.get(str(nextname))
                        nextip = nextipandport[0]
                        nextport = nextipandport[1]
                        messagetosend = imstartcontactname + ' says: ' + messagetosend + '\n' + '[sent to ' + nextname + ' at IP ' + nextip + ' and port ' + nextport + ' ]'

                    serverSocket.sendto(messagetosend.encode(),(contactip, int(contactport)))  # this line has error contactport is string



          serverSocket.sendto("Success".encode(), clientAddress)
        else:
          serverSocket.sendto("Number of contact: 0".encode(), clientAddress)
      except KeyError:
        serverSocket.sendto("Numner of contact: 0".encode(), clientAddress)


        # for key in conlistname:
        #  if leavecontactname in conlistname[key]:
        #   conlistname[key].remove(leavecontactname)
        #   conlistname[key].remove(leaveIPandport)



 elif cmd == "im-complete":
    imcompcontactlist = modifiedMessage.split(" ")[1]
    imcompcontactname = modifiedMessage.split(" ")[2]
    if IMstartname == imcompcontactname and IMstartlist == imcompcontactlist:
        IMlist = []
        serverSocket.sendto("Success".encode(), clientAddress)
    else:
        serverSocket.sendto("Failure".encode(), clientAddress)








 #print(register)   #print all registered contact-names
 #serverSocket.sendto(modifiedMessage.encode(), clientAddress)

