
// jaeger client adapted from https://github.com/jaegertracing/jaeger-client-cpp
// socket code adapted from https://www.geeksforgeeks.org/socket-programming-cc/

#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <yaml-cpp/yaml.h>
#include <jaegertracing/Tracer.h>
#include <jaegertracing/propagation/Propagator.h>

  namespace {

    void extractTracer() {

      /* 
      TO DO
      Assumes use of HTTP_HEADERS carrier format

      Step 1: Initialise http server on agreed IP (localhost in this example) and port

      Step 2: Get incoming request

      Step 3: Set carrier using HTTP_HEADERS format with the incoming request

      Step 4: Create a tracer

      Step 5: Extract the span context from the carrier specifying the format as HTTP_HEADERS and initialise tracer

      Step 6: start a child span on the tracer with the extracted span context
      */
    }

  } // anonymous namespace




int main(int argc, char
  const * argv[]) {

  extractTracer();

  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char * hello = "Hello from client";
  char buffer[1024] = {
    0
  };
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  memset( & serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form 
  if (inet_pton(AF_INET, "127.0.0.1", & serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if (connect(sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }
  send(sock, hello, strlen(hello), 0);
  printf("Hello message sent\n");
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);

  return 0;
}
