### setup
[libc7](https://github.com/codr7/libc7) requires a C99 compiler and CMake to build.

```
$ git clone https://github.com/codr7/libc7.git
$ cd libc7
$ mkdir build
$ cd build
$ cmake ..
$ sudo make install
$ valgrind ./tests
```

### list ([h](https://github.com/codr7/libc7/blob/master/source/c7/list.h)/[c](https://github.com/codr7/libc7/blob/master/source/c7/list.c))
An embedded, double linked list. Since one set of links is needed for each list, the maxiumum number of lists an item is placed in simultaneously needs to be static.

### deque ([h](https://github.com/codr7/libc7/blob/master/source/c7/deque.h)/[c](https://github.com/codr7/libc7/blob/master/source/c7/deque.c))
A deque with value semantics and pool allocated items.

### rbtree ([h](https://github.com/codr7/libc7/blob/master/source/c7/rbtree.h)/[c](https://github.com/codr7/libc7/blob/master/source/c7/rbtree.c))
A left leaning red/black tree with value semantics and pool allocated items.

### usage
The only example that exists at the moment is the commented [test suite](https://github.com/codr7/libc7/blob/master/source/tests.c).

### license
[MIT](https://github.com/codr7/libc7/blob/master/LICENSE.txt)

### support
Please consider a donation if you would like to support the project, every contribution helps.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>