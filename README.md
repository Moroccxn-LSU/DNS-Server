Simple DNS Server
=========================================

### How to compile
```bash
$ gcc -o DNS DNS_Server.c
```

### How to execute
```bash
./DNS
```

### Parameters
- Used socket programming libraries to create a program that opens up a port on your machine where a max of 10 "clients" can make a DNS request.

- The program then gets the DNS query, resolves the Domain name, and responds accordingly to the "client"

- Program runs and accepts DNS queries until this program is terminated

**!!NOTE: Make sure port 53 on your machine is available!!**

### Dependencies
- <stdio.h>
- <stdlib.h>
- <string.h>
- <sys/socket.h>
- <netinet/in.h>
- <arpa/inet.h>
- <unistd.h>
- <netdb.h>
