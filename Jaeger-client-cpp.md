Forked repository: https://github.com/ananyaarun/jaeger-client-cpp
Jaeger client cpp was built and traces were visualised

# jaeger-client-cpp
C++ OpenTracing binding for [Jaeger](https://www.jaegertracing.io/)

## Building

jaeger-client-cpp is built using CMake. It will automatically download
needed dependencies using [Hunter](https://docs.hunter.sh/en/latest/).

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make
```

After building, the [example](./examples/App.cpp) program can be run
with:

```bash
    ./app ../examples/config.yml
```

To run tests:

```bash
    make test
```

To install the library:

```bash
    make install
```

### Generated files

This project uses Apache Thrift for wire-format protocol support code
generation. It currently requires Thrift 0.11.0.

The code can be re-generated with

```bash
    $ git submodule update --init
    $ find idl/thrift/ -type f -name \*.thrift -exec thrift -gen cpp -out src/jaegertracing/thrift-gen {} \;
    $ git apply scripts/thrift-gen.patch
```

## Traces
These were the traces obtained on Jaeger UI

![jaeger1](https://user-images.githubusercontent.com/32260628/55513833-4f712e00-5684-11e9-9e45-5a09599da116.png)

On changing the trace function to take a parameter and generating spans recursively, we can visualise traces with more depth

![jaeger2](https://user-images.githubusercontent.com/32260628/55513927-80e9f980-5684-11e9-8a97-a868f2ae1a8a.jpeg)
