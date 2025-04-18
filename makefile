all:
	gcc -g3 -o XNAP_Server XNAP_Server.c -L. libXNAP_18_5.so libsicore.so -I./ -lpthread -lsctp -DSCTP_SUPPORT -Wl,-rpath .
	gcc -g3 -o XNAP_Client XNAP_Client.c XNAP_test.c -L. libXNAP_18_5.so libsicore.so -I./ -lpthread -lsctp -DSCTP_SUPPORT -Wl,-rpath .
