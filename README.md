# tndev::geolib
![CI](https://github.com/tndev/geolib/workflows/CI/badge.svg)

## Design goals

There are several libraries that support working with geo coradiante. The design goals of this library are:

- **Modern syntax** Many of the existing libraries are ports from or were inspired by other languages, and their syntax therefore does not fit well in a modern C++ environment. This library is based on the way duration is implemented in the std library.

- **Type safety** When working with geo-coordinates it is always necessary to know if you are working with degrees or radians or in which projection the point you are working with has. And it quickly happens that if there is no type safety, you make mistakes because of it. The focus is the library is there for on clearity about the types, and automatic conversion between them.