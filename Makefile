part-b: part-b.cpp
	g++ -g -Wall part-b.cpp -o simulation -pthread

part-d: part-d.cpp
	g++ -g -Wall part-d.cpp -o simulation -pthread

clean:
	rm -f simulation 