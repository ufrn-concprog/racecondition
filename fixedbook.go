package main

import (
	"fmt"
	"sync"
	"time"
)

var seatsAvailable = 1

var mu sync.Mutex

func bookSeat(customer string) {
	mu.Lock()
	defer mu.Unlock()
	if seatsAvailable > 0 {
		fmt.Println(customer, "is trying to book a seat")
		time.Sleep(50 * time.Millisecond) // Simulate some processing time
		seatsAvailable--
		fmt.Println(customer, "booked a seat")
	} else {
		fmt.Println("No seats available for", customer)
	}
}

func main() {
	fmt.Println("Number of available seats:", seatsAvailable)

	go bookSeat("Customer A")
	go bookSeat("Customer B")

	time.Sleep(1 * time.Second) // Wait for goroutines to finish
	fmt.Printf("Seats remaining: %d\n\n", seatsAvailable)
}
