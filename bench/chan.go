package main

import (
       "fmt"
       "sync"
       "time"
)

func main() {
     const QUEUE_MAX = 100
     c := make(chan uint64, QUEUE_MAX)
     var w sync.WaitGroup
     w.Add(2);

     t := time.Now()

     go func() {
     	for i := uint64(0); i < 10000000; i++ {
	    c<- i
	}

	w.Done()
     }()

     go func() {
     	for i := uint64(0); i < 10000000; i++ {
	    <-c
	}

	w.Done()
     }()

     w.Wait()
     fmt.Printf("%vns\n", time.Since(t).Microseconds());
}