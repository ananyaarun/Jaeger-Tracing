# jaeger client examples in C++
This repo has example projects as a proof of concept for tracing of modules written in C++ using jaeger. In 
order to instrument the program with jaeger and run it, we need the various jaeger dependencies made available.
We also need the jaeger backend setup and running to see the traces on the jaeger UI.

## The jaeger backend

We setup and run the all-in-one jaeger docker image (https://www.jaegertracing.io/docs/1.6/getting-started/)

```bash
  docker run -d --name jaeger \
  -e COLLECTOR_ZIPKIN_HTTP_PORT=9411 \
  -p 5775:5775/udp \
  -p 6831:6831/udp \
  -p 6832:6832/udp \
  -p 5778:5778 \
  -p 16686:16686 \
  -p 14268:14268 \
  -p 9411:9411 \
  jaegertracing/all-in-one:1.6
```
This makes available the jaeger backend on standard ports. In particular the jaeger UI is availbale at https://localhost:16686

## Quicksort
This program traces the quicksort algorithm and its helper functions like partitioning the array and swapping 

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make
```
After building, the [quicksort](./examples/App.cpp) program can be run
with:

```bash
    ./app ../examples/config.yml
```
The traces show 3 spans: quicksort, partition, and swap

## Socket programming
This program implements a client and server and interprocess communication using sockets. 
Since this is a distributed program, we need to implement distributed tracing. 
This is done using Inject and Extract operations which transmit the span context across process boundaries.

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make
```
The Server and Client need to be started on different terminals. The Server needs to be started before the Client.

After building, the [Server](./examples/Server.cpp) program can be run
with:

```bash
    ./server ../examples/config.yml
```

The [Client](./examples/Client.cpp) program can be run
with:

```bash
    ./client
```



