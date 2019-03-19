package main

import (
	"fmt"
)

// Pipe global pipe data
type Pipe struct {
	Name string
	Desc string
	Head *Task
}

// Start pipe
func (p *Pipe) Start() {
	fmt.Printf("pipe start [%s]\n", p.Name)
}

// Cancel pipe
func (p *Pipe) Cancel() {
	fmt.Printf("pipe cancel [%s]\n", p.Name)
}
