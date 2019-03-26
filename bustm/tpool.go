package main

import (
	"fmt"
)

var (
	taskQueue      chan Task
	taskDispatcher Dispatcher
	debug          = true // debug log
)

// Dispatcher will disptach task
type Dispatcher struct {
	taskPool   chan chan Task
	maxWorkers int
}

// NewDispatcher return a new dispatcher
func NewDispatcher(queueSize, maxWorkers int) *Dispatcher {
	taskQueue = make(chan Task, queueSize)

	return &Dispatcher{
		taskPool:   make(chan chan Task, maxWorkers),
		maxWorkers: maxWorkers,
	}
}

// Run dispatcher
func (d *Dispatcher) Run() {
	for i := 0; i < d.maxWorkers; i++ {
		worker := NewWorker(d.taskPool)
		worker.start()
	}

	go d.dispatch()
}

func (d *Dispatcher) dispatch() {
	if debug {
		fmt.Println("waiting for task submit")
	}

	for {
		select {
		case task := <-taskQueue:
			if debug {
				fmt.Printf("get task [%s] from task queue\n", task.Name)
			}
			taskChan := <-d.taskPool
			go func(t Task) {
				if debug {
					fmt.Printf("put task [%s] to a worker's task channel\n", task.Name)
				}
				taskChan <- t
			}(task)
		}
	}
}

func (d *Dispatcher) submit(task Task) {
	if debug {
		fmt.Printf("begain submit a task [%s], len: %d\n", task.Name, len(taskQueue))
	}
	taskQueue <- task
	if debug {
		fmt.Printf("finish submit a task [%s], len: %d\n", task.Name, len(taskQueue))
	}
}
