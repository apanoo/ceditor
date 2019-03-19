package main

import (
	"fmt"
)

// Task in pipe
type Task struct {
	Name    string
	Index   string
	Desc    string
	Command string
	Tasks   []*Task
}

// Action task
func (t *Task) Action() {
	fmt.Printf("task action [%s]\n", t.Name)
}

// Cancel task
func (t *Task) Cancel() {
	fmt.Printf("task cancel [%s]\n", t.Name)
}
