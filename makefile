main:
	rm -rf ./pathtracer
	rm -rf ./out.ppm
	rm -rf ./out.png
	nvcc -o pathtracer ./src/main.cu
	./pathtracer
	convert out.ppm out.png
	code out.png