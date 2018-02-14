#include <iostream>
#include <fstream>
#include <algorithm>
#include "glglobal.h"
#include "mesh.h"
#include <cmath>

using namespace std;
//////////////////////////FACE///////////////////////
Face::Face(int a,vector<VertexID> n){
	nNumVerts=a;
	mVerts = n;
}
////////////////CONSTRUCTORS/////////////////////////
Mesh::Mesh() {
    numVerts = numFaces = numNorms = 0;
    // pt = NULL; norm  =  NULL; face = NULL;
    lastVertUsed = lastNormUsed = lastFaceUsed = -1;
    scale = 1.0;
    mode = MODE_WIRE;
}

Mesh::Mesh(string fname){ // read this file to build mesh
    numVerts = numFaces = numNorms = 0;
    scale = 1.0;
    mode = MODE_WIRE;
    readMesh(fname);
}

Mesh::Mesh(Face f){
	//push back points in face??
	face.push_back(f);
	norm.push_back(this->findNormal(f));
}

////////////////////////////Functions///////////////////////////////
void Mesh::setRenderMode(RenderMode m){
    mode = m;
}

void Mesh::setScale(double s){
    scale = s;
}

bool Mesh::readMesh(string fname){
    int i;
    GLdouble x,y,z;
    fstream inStream;
    inStream.open(fname.c_str(), ios ::in);
    if(inStream.fail() || inStream.eof()){
        cout << "can't open file " << fname << endl;
        return false;
    }
    inStream >> numVerts >> numNorms >> numFaces;

    // points
    for (i=0; i<numVerts; i++) {
        inStream >> x >> y >> z;
        pt.push_back(GLdoublePoint(x,y,z));
    }
    // normals
    for (i=0; i<numNorms; i++) {
        inStream >> x >> y >> z;
        norm.push_back(GLdoublePoint(x,y,z));
    }
    // face information
    for (i=0; i<numFaces; i++) {
        Face f;
        f.mVerts.clear();
        int m,n,j;
        inStream >> n;
        f.mNumVerts = n;
        // first read the vertex indices and allocate VertexIDs
        for (j=0; j<n; j++) {
            VertexID vtx;
            inStream >> vtx.vertIndex;
            f.mVerts.push_back(vtx);
        }
        // now go back and read the normal Indices
        for (j=0; j<n; j++) {
            inStream >> f.mVerts[j].normIndex;
        }
        face.push_back(f);
    }
    return true;
}

void Mesh::addFace(vector<VertexID> verts, int num){
	face.push_back(Face(num,verts));
}

void Mesh::findNormal(Face){
	
}

void Mesh::addNormal(GLDoublePoint n){
	norm.push_back(n);
}

void Mesh::drawOpenGL() {
}

void Mesh::drawEdges() {
    GLdouble x,y,z;
    if (numFaces == 0) return;

    for(int f = 0; f < numFaces; f++) {
        int n = face[f].mNumVerts;
        glBegin(GL_LINE_LOOP);
        for(int v = 0; v < n; v++) {
            int iv = face[f].mVerts[v].vertIndex;
            pt[iv].getXYZ(x,y,z);
            glVertex3d(x,y,z);
        }
        glEnd();
    }
    glFlush();
}

void Mesh::drawFaces() {
    GLdouble x,y,z;
    if (numFaces == 0) return;

    for(int f = 0; f < numFaces; f++) {
        int n = face[f].mNumVerts;
        glBegin(GL_POLYGON);
        for(int v = 0; v < n; v++) {
            // get the corresponding normal
            // without the normals, the lighting doesn't work correctly
            // you get dull reflections instead of variations in light bounce
            int ni = face[f].mVerts[v].normIndex;
            norm[ni].getXYZ(x,y,z);
            glNormal3f(x,y,z);

            // get the corresponding vertex
            int iv = face[f].mVerts[v].vertIndex;
            pt[iv].getXYZ(x,y,z);
            glVertex3d(x,y,z);
        }
        glEnd();
    }
    glFlush();
}
