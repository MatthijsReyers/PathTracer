main:
	rm -rf ./pathtracer
	rm -rf ./out.ppm
	rm -rf ./out.png
	nvcc -o pathtracer ./code/main.cpp
	./pathtracer
	convert out.ppm out.png
	code out.png