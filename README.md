# Neo-Coding Bat

## Jason Tung, Larry Wong, Victor Lin   Period 5

#### This project is a more simplified emulation of codingbat. It will feature a server to client connection in which the user receives problems from the server. The user then codes the solution in a text editor; this solution is sent back to the server for evaluation. The server then tells the user whether he/she succeeded.

## Libraries needed:
##### <stdio.h>
##### <stdlib.h>
##### <unistd.h>
##### <sys/types.h>
##### <sys/socket.h>
##### <sys/wait.h>
##### <netinet/in.h>
##### <arpa/inet.h>
##### <netdb.h>
##### <string.h>
##### <errno.h>
##### <fcntl.h>
##### <ifaddrs.h>
##### <netinet/in.h>
##### <arpa/inet.h>


## Usage
#### 1) type $make into bash<br />2) type $./server into bash<br />3) type $./user "server ip" into bash on a different session<br />4) user session automatically opens a text editor with a prompt<br />5) when user is finished coding, he/she can save and exit the text editor, and the program will resume.<br />6) if user's solution is correct, the next prompt appears. Else, the user must redo the problem.


 
