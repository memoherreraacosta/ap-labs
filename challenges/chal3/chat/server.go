// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"bytes"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

var (
	entering                     = make(chan client)
	leaving                      = make(chan client)
	messages                     = make(chan string)       // all incoming client messages
	usuarios                     = make(map[string]string) // Variable to store clients
	userConn map[string]net.Conn = map[string]net.Conn{}
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}

		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn, who string) {

	// Remove \n from who variable
	who = strings.TrimSuffix(who, "\n")

	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	ipWho := conn.RemoteAddr().String()
	usuarios[who] = ipWho
	userConn[ipWho] = conn
	// Checar error de nombre replicado

	ch <- "irc-server > Welcome to the Simple IRC Server\nirc-server > Your user: " + who
	fmt.Printf("irc-server > New connected user %s\n", who)
	messages <- "\n" + who + " has arrived"
	entering <- ch

	input := bufio.NewScanner(conn)

	for input.Scan() {

		//Switch case input.Text() to check sub commands

		switch input.Text() {

		case "/time":
			ch <- getFecha()

		case "/users":

			// Recibir lista de usuarios
			// Print users by global variable
			b := new(bytes.Buffer)
			for key, value := range usuarios {
				fmt.Fprintf(b, "%s=\"%s\"\n", key, value)
			}

			ch <- b.String()

		default:

			inputText := strings.Split(input.Text(), " ") // String [] implicit variable

			if len(inputText) == 2 &&
				strings.Compare(inputText[0], "/user") == 0 &&
				strings.Compare(inputText[1], "") != 0 {

				// Case /user <user>
				usrU := inputText[1]
				if strings.Compare(usuarios[usrU], "") == 0 {
					ch <- "Usuario : " + usrU + " no encontrado\n"
				} else {
					ch <- "Usuario : " + usrU + "  IP: " + usuarios[usrU]
				}
			} else if len(inputText) >= 3 &&
				strings.Compare(inputText[0], "/msg") == 0 &&
				strings.Compare(inputText[1], " ") != 0 &&
				strings.Compare(inputText[2], "") != 0 {

				// Case /msg <user> <msg>
				usrM := inputText[1]       // Usuario llamado
				mensajito := inputText[2:] // Mensaje recibido en args

				mensajeEnviar := "" // Mensaje concatenado
				for _, element := range mensajito {
					mensajeEnviar += element + " "
				}
				mensajeEnviar += "\n"

				conex := userConn[usuarios[usrM]] // Conexion del usuario llamado

				fmt.Fprintln(conex, mensajeEnviar) // Mensaje enviado al usuario

			} else {
				messages <- who + ": " + input.Text()
			}
		}

	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- who + " has left"
	fmt.Println("irc-server > " + who + " has left")
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

func getFecha() string {
	return "irc-server > Local time : " + time.Now().Format("2006-01-02 3:4:5 pm")
}

//!+main
func main() {

	// Check args
	if (len(os.Args) != 5) ||
		(strings.Compare(os.Args[1], "-host") != 0) ||
		strings.Compare(os.Args[3], "-port") != 0 {
		log.Printf("Error in arguments\n ")
		return
	}

	// tcp port
	dir := os.Args[2] + ":" + os.Args[4]

	listener, err := net.Listen("tcp", dir)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println("irc-server > Simple IRC Server started at " + dir)

	go broadcaster()

	fmt.Println("irc-server > Ready for receiving new clients")

	for {
		conn, err := listener.Accept()
		nombrecito, _ := bufio.NewReader(conn).ReadString('\n')
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn, string(nombrecito))
	}
}

//!-main
