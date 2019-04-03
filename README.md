# Jaeger client examples in C++
This repo has example projects as a proof of concept for tracing of modules written in C++ using jaeger. In 
order to instrument the program with jaeger and run it, we need the various jaeger dependencies made available.
We also need the jaeger backend setup and running to see the traces on the jaeger UI.

A few examples I forked and built to visualize Traces can be found here:
- [distributed-tracing-example](./distributed-tracing-example.md)
- [Jaeger-client-cpp](./Jaeger-client-cpp.md)

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
This makes available the jaeger backend on standard ports. In particular the jaeger UI is available at https://localhost:16686

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

![quicksort1](https://user-images.githubusercontent.com/32260628/55090750-a8195780-50d5-11e9-9fd3-e6d297059252.png)

![quicksort2](https://user-images.githubusercontent.com/32260628/55090787-b8313700-50d5-11e9-9229-f24c5264a4e5.png)


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

Some screenshots of traces seen

![socket1](https://user-images.githubusercontent.com/32260628/55090825-cbdc9d80-50d5-11e9-8213-7603cfc9ab1b.png)

![socket2](https://user-images.githubusercontent.com/32260628/55090847-d5660580-50d5-11e9-9a61-3c1f2a51a0de.png)


NOTE : Building of the repository needs to be done just once after which Traces of both quicksort program and socket programming can be seen in Jaeger UI under sorting-service and socketservice respectively.
