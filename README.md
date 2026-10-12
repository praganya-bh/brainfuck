# Brainfuck Compiler & Interpreter written in C++

## Building

```sh
g++ brainfuck_INT.cpp -o bf
g++ brainfuck_COMP.cpp -o bfc
```

## Usage

**Interpreter:**
```sh
./bf program.bf
```

**Compiler:**
```sh
./bfc program.bf      # generates out.c
gcc out.c -o out
./out
```
