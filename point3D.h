#ifndef POINTTHREED_H
#define POINTTHREED_H

class Point3D
{

public:
	Point3D();
	Point3D(float,float,float);
	virtual ~Point3D();
	float getXval();
	float getYval();
	float getZVal();
	void setXYZval(int,int,int);
	void setXval(int newVal);
	void setYval(int newVal);
	void setZval(int newVal);

protected:
	float xval, yval,zval;
};
#endif 