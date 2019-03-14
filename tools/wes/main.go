package main

import (
	"net/http"
	"fmt"
)

func main() {
	http.Handle("/", http.FileServer(http.Dir("./bin")))
	fmt.Println("Listening localhost:8080")
    http.ListenAndServe(":8080", nil)
}