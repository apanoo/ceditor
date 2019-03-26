package main

// Worker for task exec
type Worker struct {
	taskPool    chan chan Task
	taskChannel chan Task
	quit        chan struct{}
}

// NewWorker return a new worker
func NewWorker(pool chan chan Task) Worker {
	return Worker{
		taskPool:    pool,
		taskChannel: make(chan Task),
		quit:        make(chan struct{}),
	}
}

// start a worker waitting for task
func (w *Worker) start() {

}

// stop worker
func (w *Worker) stop() {
	go func() {
		w.quit <- struct{}{}
	}()
}
