for ((i=1; i<=3; i++)); do
	bash $0 &
    nc -w 2 127.0.0.1 8081 < test/testmsg.txt &
done