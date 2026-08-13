# Race Condition Demo — Flight Ticket Booking

A minimal Go example demonstrating a race condition and its fix, using a simplified flight seat booking scenario.

## Scenario

There is **one seat available** on a flight. Two customers (*A* and *B*) try to book it nearly simultaneously, each running as a concurrent goroutine.

## Files

| File | Description |
| ---- | ------------ |
| [`racebook.go`](racecondition.go) | Unsynchronized version. Both customers can pass the availability check before either one books, resulting in the seat being sold twice. |
| [`fixedbook.go`](fixedbook.go) | Corrected version. The entire check-and-book sequence is protected by a mutex, so only one customer can book the seat. |

## Running

```bash
go run racebook.go
```

```bash
go run fixedbook.go
```

Use the [`run.sh`](run.sh) script to run the program a few times in a row to observe the behavior:

```bash
sh run.sh PROG
```

where `PROG` is either `racebook` or `fixedbook`. The value for `PROG` must exactly match the names of the Go files.

## What to observe

**`racebook.go`**: both customers may report success, and the final seat count can go negative:

```bash
Number of available seats: 1
Customer A is trying to book a seat
Customer B is trying to book a seat
Customer A booked a seat
Customer B booked a seat
Seats remaining: -1
```

This happens because both goroutines check seat availability before either updates it, but the check and the update are not treated as a single, indivisible (atomic) step.

**`fixedbook.go`**: only one customer books the seat, consistently, on every run:

```bash
Number of available seats: 1
Customer B is trying to book a seat
Customer B booked a seat
No seats available for Customer A
Seats remaining: 0
```

The mutex wraps the **entire** check-and-book sequence, not just the final decrement. Locking only the write (a common first mistake) is not enough, since the incorrect decision to book has already been made by the time the write happens.

## Key takeaways

- A *race condition* occurs when the outcome depends on the relative timing of concurrent operations.
- A *critical section* must cover every step that handles the shared resource, including the check, not just the final write.
- *Mutual exclusion* (here, via the mutex) ensures only one goroutine executes the critical section at a time.
