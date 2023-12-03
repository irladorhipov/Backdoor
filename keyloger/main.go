package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/MarinX/keylogger"
)

func main() {
	dev := "/dev/input/eventX"
	kl, err := keylogger.New(dev)
	if err != nil {
		log.Fatal(err)
	}
	defer kl.Close()

	done := make(chan os.Signal, 1)
	signal.Notify(done, os.Interrupt, syscall.SIGTERM)

	fmt.Println("Начало записи...")

	for {
		event := kl.Read()
		if event != nil {
			fmt.Println("Нажата клавиша: %s\n", event)
		}

		select {
		case <-done:
			fmt.Println("nЗавершение...")
			time.Sleep(1 * time.Second)
			return
		default:
		}
	}
}
