#pragma once
class IO_REQUEST
{
private:
	int IO_R;
	int IO_D;
public:
	IO_REQUEST() {};
	IO_REQUEST(int IO_R, int IO_D){
		this->IO_R = IO_R;
		this->IO_D = IO_D;
	}
	 int getIO_R() {
		 return IO_R;
	}
	 int getIO_D() {
		 return IO_D;
	}

};

