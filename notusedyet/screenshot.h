class bitmapinfoclass {
public:

	long height;
	long width;
	long size;
	unsigned char* pointer;

	~bitmapinfoclass() {
		delete[] pointer;
	}
};