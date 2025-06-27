**minitalk is part of the second milestone of the 42 Common Core**

The PDF of the original subject is attached.

The goal is to build a simple client-server model where messages are sent from the client to the server using only Unix signals (SIGUSR1, SIGUSR2).

We have to implement 2 programs:

- server: constantly waiting for signals from client, using them to construct the messages sent.

- client: sends signals to the pid of the server, representing the bits extracted from the characters we want to send.


We are restricted to only these functions:

◦ libft/

◦ ft_printf

◦ signal

◦ sigemptyset

◦ sigaddset

◦ sigaction

◦ kill

◦ getpid

◦ malloc

◦ free

◦ pause

◦ sleep

◦ usleep

◦ exit

The bonus part requires us to be able to support Unicode characters and that the server acknowledges every message received by sending back a signal to the client.


To send a message, the client needs the server's PID (Process ID). This is because the kill() function needs it to know where it's sending a signal to.

Once it has the server PID, it will send the message bit by bit, with a succession of 8 bits representing one byte of data.

Example: if the client wants to send the message "hi" to the server with PID = 25898

It will send the bit representation 01101000 of 'h' (ASCII: 104) first.

Then it will send the bit representation 01101001 of 'i' (ASCII: 105).


To perform this, it will use SIGUSR1 to represent a 1, and SIGUSR2 to represent a 0.

Using the example above, sending "hi" would mean sending SIGUSR2 SIGUSR1 SIGUSR1 SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR2 SIGUSR2 and SIGUSR2 SIGUSR1 SIGUSR1 SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR2 SIGUSR1.


I have decided to make my client send:

- its own PID first (very slowly: 0.001 seconds per bit) and waits for the server to send a signal back;
  
- the size of the message it wants to send second (ended by a '\0' character), this is to be able to allocate the exact size on the server side;

- the message.

(To avoid any data being lost due to the rapid succession of signals being sent, I made each bit sent after the PID rely on a "handshake" mechanism: the client sends a signal, and waits for the server to send a signal back to confirm it has received it. We also add a small usleep() between the receiving of bits on the server side to ensure this is reliable.)

and my server is constantly waiting for signals:

- if the PID has not yet been received, it reconstructs the PID of the client bit by bit, then sends an acknowledgement signal;

- if the size has not yet been received, it reconstructs the size bit by bit, usleeping 200 microseconds in between each bit received and acknowledgement signal sent, and sends another acknowledgement once the size is received;

- if the info ]has ]
=een received constructs the message bit by bit, again usleeping 200 microseconds in between each bit received and acknowledgement signal sent, and sends a final acknowledgement once the full message is received.

