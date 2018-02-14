#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include "glglobal.h"

class GLdoublePoint {
    public:
    GLdoublePoint() {};
    GLdoublePoint(GLdouble ix,GLdouble iy,GLdouble iz=0.0):x(ix),y(iy),z(iz){};
    GLdouble getX() {return x;};
    GLdouble getY() {return y;};
    GLdouble getXYZ(GLdouble& xx, GLdouble& yy, GLdouble& zz) {xx=x;yy=y;zz=z;};
private:
    GLdouble x,y,z;
};

// for meshes
enum RenderMode { MODE_WIRE, MODE_SOLID, MODE_WIRE_SOLID };

// used by Mesh Class
typedef struct {
    int vertIndex;
    int normIndex;
} VertexID;

class Face {
public:
    friend class Mesh;
    Face()  { mNumVerts = 0;}
		//Face(int,std::vector<VertexID>);
private:
    int mNumVerts;
    std::vector<VertexID> mVerts;
};

class Mesh {
				public:
						Mesh();
						Mesh(std::string fname);
						Mesh(Face);
						void drawEdges();
						void drawFaces();
						bool readMesh(std::string fname);
						void setRenderMode(RenderMode m);
						void setScale(double s);
						void addFace(??????);
						void findNormal(Face);
						void addNormal(GLdoublePoint);
				private:
						std::string meshFileName;
						int numVerts;
						int numNorms;
						int numFaces;
						std::vector <GLdoublePoint> pt;     // points
						std::vector <GLdoublePoint> norm;   // normals
						std::vector <Face> face;            // faces
						int lastVertUsed;
						int lastNormUsed;
						int lastFaceUsed;
						double scale;
						RenderMode mode;
};

#endif
