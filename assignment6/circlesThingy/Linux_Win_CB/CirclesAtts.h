#ifndef CIRCLESATTS_H_INCLUDED
#define CIRCLESATTS_H_INCLUDED

class CirclesAtts{
private:
    float Center[3];
    float r;
    float Color[4];
    float rotateAng;
    float rotateVec[3];

public:
    CirclesAtts(float cenx = 0, float ceny = 0, float cenz = 0, float radius = 1);
    ~CirclesAtts();

    void setCenter(float cenx, float ceny, float cenz);
    void setRadius(float radius);
    void setColor(float r, float g, float b, float a);
    void setRotateAngle(float ang);
    void setRotateVec(float x, float y, float z);

    void getCenter(float* cen);
    float getRadius();
    void getColor(float* col);
    float getRotateAngle();
    void getRotateVec(float* rot);
};

#endif // CIRCLESATTS_H_INCLUDED
