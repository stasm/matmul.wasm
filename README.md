# matmul

A matrix multiplication benchmark for WASM. Compile and run a local server:

    npm install webassembly serve
    npx wa compile mat4.c -o mat4.wasm -O
    npx serve

Go to http://localhost:5000 and open the console.

## `malloc` Implementations

Try compiling it with different `malloc` implementations.

  - The default allocator provided by the `webassembly` package, `dlmalloc`. See
    [source](https://github.com/dcodeIO/webassembly/blob/master/lib/musl-wasm32/src/malloc/malloc.c).

        npx wa compile mat4.c -o mat4.wasm -O


  - `tinyalloc` by @thi-ng, licensed under Apache 2.0. See
    [source](https://github.com/thi-ng/tinyalloc/blob/master/tinyalloc.c).

        npx wa compile mat4.c -i malloc_ta.c -o mat4.wasm -O


  - `wasm-malloc` by @maxkl, licensed under MIT. See
    [source](https://github.com/maxkl/wasm-malloc/blob/master/src/malloc.c).

        npx wa compile mat4.c -i malloc_wasm.c -o mat4.wasm -O


  - A simple stack-based allocator which requires that memory is freed in the
    reverse order to how it was allocated:

        npx wa compile mat4.c -i malloc_stack.c -o mat4.wasm -O

## Size Comparison

Here is the binary size comparison between different `malloc` implentations, in bytes.

    dlmalloc    (default)        10834
    tinyalloc   (malloc_ta.c)     8682
    wasm-alloc  (malloc_wasm.c)   1894
    stack-based (malloc_stack.c)  1121

## Compiling with Emscripten

You can also try compiling with `emcc` and then optimizing the binary with
`binaryen`. In my tests, `webassembly` produces smaller binaries, still.

    emcc mat4.c alloc.c -s SIDE_MODULE=1 -Oz -o mat4.wasm
    path/to/binaryen/bin/wasm-opt -Os mat4.wasm -o mat4.wasm
