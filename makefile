main:
	rm -rf ./pathtracer
	rm -rf ./out.ppm
	rm -rf ./out.png
	g++ -o pathtracer ./code/main.cpp
	./pathtracer
	convert out.ppm out.png
	code out.png