
// jaeger client adapted from https://github.com/jaegertracing/jaeger-client-cpp
// socket code adapted from https://www.geeksforgeeks.org/socket-programming-cc/

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

#include <iostream>
#include <yaml-cpp/yaml.h>
#include <jaegertracing/Tracer.h>
#include <jaegertracing/propagation/Propagator.h>
#include <jaegertracing/propagation/Injector.h>

  namespace {

    void injectTracer(const char * configFilePath) {

      // Initialise a tracer
      auto configYAML = YAML::LoadFile(configFilePath);
      auto config = jaegertracing::Config::parse(configYAML);
      auto tracer = jaegertracing::Tracer::make(
        "socketService", config, jaegertracing::logging::consoleLogger());
      opentracing::Tracer::InitGlobal(
        std::static_pointer_cast < opentracing::Tracer > (tracer));

      // Create a span
      auto span = opentracing::Tracer::Global() -> StartSpan("socketServer");

      /* 
      TO DO
      Assumes use of HTTP_HEADERS carrier format
      We have already initialised a tracer and created a span. 
      We now need to propagate this span context to the other process by some sort of inter process communication. We will use http

      Step 1. Call Inject on the tracer with the span context, the carrier, and specifying the format as HTTP_HEADERS

      Step 2: Encode the span context as a collection of key value pairs in the carrier. Since we are using http the key value pairs should be safe to be used for http

      Step 3: Send the http request on agreed IP (localhost in this example) and port
      */

      }

    } // anonymous namespace



int main(int argc, char
  const * argv[]) {

  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <config-yaml-path>\n";
    return 1;
  }

  // helper function to create a tracer and span and tramsmit span context over the wire
  injectTracer(argv[1]);

  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[1024] = {
    0
  };
  char * hello = "Hello from server";

  // Creating socket file descriptor 
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Forcefully attaching socket to the port 8080 
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &
      opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Forcefully attaching socket to the port 8080 
  if (bind(server_fd, (struct sockaddr * ) & address,
      sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  if ((new_socket = accept(server_fd, (struct sockaddr * ) & address,
      (socklen_t * ) & addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }
  valread = read(new_socket, buffer, 1024);
  printf("%s\n", buffer);
  send(new_socket, hello, strlen(hello), 0);
  printf("Hello message sent\n");

  // Not stricly necessary to close tracer, but might flush any buffered
  // spans. See more details in opentracing::Tracer::Close() documentation.
  opentracing::Tracer::Global()->Close();

  return 0;
}

