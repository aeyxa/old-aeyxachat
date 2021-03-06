#include "../common/common.h"

void StageConnection(int sock)
{
  char buffer[256];

  memset(buffer,0,sizeof(buffer));

  std::cout << "Your name: ";
  std::cin.getline(buffer,sizeof(buffer));
  write(sock,buffer,sizeof(buffer));

  memset(buffer,0,sizeof(buffer));

  std::cout << "Their name: ";
  std::cin.getline(buffer,sizeof(buffer));
  write(sock,buffer,sizeof(buffer));
}

std::string ReadConnection(int sock)
{
  char buffer[256]; std::string validation;

  memset(buffer,0,sizeof(buffer));

  read(sock,buffer,sizeof(buffer));

  validation = buffer;

  return validation;
}

void CheckConnection(int sock)
{
  std::string validation;

  validation = ReadConnection(sock);

  if(validation == "Connected!")
  {
    write(sock,"Online",6);
  }

  validation = ReadConnection(sock);

  if(validation == "Confirmed!")
  {
    return;
  }
  else std::cout << "Connection closed by other user." << std::endl; exit(1);
}

int CreateConnection()
{
  int sock, port = 9999; struct sockaddr_in address;
  struct hostent *host = gethostbyname("71.6.134.109");

  memset(&address,0,sizeof(address));

  address.sin_family = AF_INET; address.sin_port = htons(port);
  memcpy((char *)&address.sin_addr.s_addr, (char*)host->h_addr, host->h_length);

  sock = socket(AF_INET,SOCK_STREAM,0);

  if(sock)
  {
    connect(sock,(struct sockaddr*)&address,sizeof(address));

    return sock;
  }
  else std::cout << "Connection failed." << std::endl; exit(1);
}
