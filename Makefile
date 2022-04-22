all: running

main.o: main.cpp
	g++ -c main.cpp

char_buffer.o: char_buffer.cpp
	g++ -c char_buffer.cpp

sender.o: sender.cpp
	g++ -c sender.cpp

reader.o: reader.cpp
	g++ -c reader.cpp

proxy_base.o: proxy_base.cpp
	g++ -c proxy_base.cpp	

limitation_map.o: limitation_map.cpp
	g++ -c limitation_map.cpp

conductor.o: conductor.cpp
	g++ -c conductor.cpp

regulator_speed.o: regulator_speed.cpp
	g++ -c regulator_speed.cpp

task_map.o: task_map.cpp
	g++ -c task_map.cpp

monitor.o: monitor.cpp
	g++ -c monitor.cpp

running: main.o sender.o reader.o proxy_base.o limitation_map.o conductor.o char_buffer.o regulator_speed.o task_map.o monitor.o
	g++ main.o sender.o reader.o proxy_base.o limitation_map.o conductor.o char_buffer.o regulator_speed.o task_map.o monitor.o -lpthread -o running

clean:
	rm -rf *.o running