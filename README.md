### setup
[libcodr7](https://github.com/codr7/libcodr7) requires a C11 compiler and CMake to build.

```
$ git clone https://github.com/codr7/libcodr7.git
$ cd libcodr7
$ mkdir build
$ cd build
$ cmake ..
$ sudo make install
$ valgrind ./tests
```

### list ([h](https://github.com/codr7/libcodr7/blob/master/source/codr7/list.h)/[c](https://github.com/codr7/libcodr7/blob/master/source/codr7/list.c))
An intrusive, double linked list. Since one set of links is needed for each list, the maxiumum number of lists an item is placed in simultaneously needs to be static.

### deque ([h](https://github.com/codr7/libcodr7/blob/master/source/codr7/deque.h)/[c](https://github.com/codr7/libcodr7/blob/master/source/codr7/deque.c))
A deque with value semantics and pool allocated items.

### rbtree ([h](https://github.com/codr7/libcodr7/blob/master/source/codr7/rbtree.h)/[c](https://github.com/codr7/libcodr7/blob/master/source/codr7/rbtree.c))
A [left leaning red/black tree](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&cad=rja&uact=8&ved=2ahUKEwj8zeD6593mAhUxNOwKHcKlAW0QFjABegQIBBAC&url=https%3A%2F%2Fwww.cs.princeton.edu%2F~rs%2Ftalks%2FLLRB%2FLLRB.pdf&usg=AOvVaw0aj5xOszrudCcAFIuVqngg) with value semantics and pool allocated items.

### examples
Besides the commented [test suite](https://github.com/codr7/libcodr7/blob/master/source/tests.c), you may find a real world example [here](https://github.com/codr7/cfoo/tree/master/source/cfoo).

### license
[MIT](https://github.com/codr7/libcodr7/blob/master/LICENSE.txt)

### support
Please consider a donation if you would like to support the project, every contribution helps.

<a href="https://liberapay.com/codr7/donate"><img alt="Donate using Liberapay" src="https://liberapay.com/assets/widgets/donate.svg"></a>