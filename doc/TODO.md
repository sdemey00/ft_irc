- Remove wildcard in Makefile

- Test script for nc

sdemey:
	- User Prefix (optional)
	- DoubleCheck every replies to avoid weird irssi behavior

mmichele :
	- Investigate read_buffer and stash variables in Client class, 
		one of them may be not necessary.
		- Make a generic request reader, so the bot can use it as well
		-> get_next_request() ? or class GNR