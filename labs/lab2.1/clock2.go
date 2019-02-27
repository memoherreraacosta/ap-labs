// Clock2 is a concurrent TCP server that periodically writes the time.
package main

import (
	"io"
	"log"
	"net"
	"os"
	"time"
)

func handleConn(c net.Conn) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {

	if len(os.Args) != 3 {
		log.Printf("Error in number of arguments\n ")
		return
	}
	if os.Args[1] != "-port" {
		log.Printf("Error in arguments\n")
		return
	}

	lh := "localhost:" + os.Args[2]

	listener, err := net.Listen("tcp", lh)
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err) // e.g., connection aborted
			continue
		}
		go handleConn(conn) // handle connections concurrently
	}
}
