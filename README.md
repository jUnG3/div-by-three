# is-div-by-3

Takes an input from the `stdin`, checks if the given input is dividable by `3`.
Reads buffer until it hits `\n` or `\0`.

## Build

Execute the following commands to build a release version.

```shell
$ cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build-release -S .
$ cmake --build cmake-build-release
```

## Run

The program is stored in the `${CMAKE_CURRENT_BINARY_DIR}/bin`. In our case
it's `./cmake-build-release/bin`.

```shell
$ print "1234123412343" | ./cmake-build-release/bin/is-div-by-3
The given input is accepted.
```
