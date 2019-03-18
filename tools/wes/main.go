package main

import (
	"net/http"
	"fmt"
)

func main() {
	http.Handle("/", http.FileServer(http.Dir("./bin")))
	fmt.Println("Listening localhost:8081")
    if err := http.ListenAndServe(":8081", nil); err != nil {
		panic(err)
	}
}