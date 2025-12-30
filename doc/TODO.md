- Remove wildcard in Makefile
- In irc bot usage of inet_pton which is not explicitely permitted.

- Sending private message in some cases generates a "heap use after free", but 
	not crashing ?
	Therefore messages are not shown in the client but seem the be sent ...

sdemey:
	- Channel key pass
	- User Prefix

mmichele :
	- Investigate read_buffer and stash variables in Client class, 
		one of them may be not necessary.
		- Make a generic request reader, so the bot can use it as well
		-> get_next_request() ? or class GNR