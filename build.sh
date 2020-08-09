#gcc -Wall -I. -o test cargs.c test.c
#g++ -Wall -std=c++11 -I. -o test cargs.c test.c
#g++ -Wall -std=c++11 -DDEBUG -I. -o test cargs.c test.c
#https://github.com/DaveGamble/cJSON.git
g++ -Wall -std=c++11 -I. -o cjsontest pjson.c cJSON.c