#include "sphere.h"
void calcTexcoord(double x,double z,double r,double st[2]){
	double t = acos(z/r)/M_PI;
	double s = acos(x/(r*sin(t*M_PI)))/(2*M_PI);
	st[0] = s;
	st[1] = t;
}
int makeSphere2(std::vector<vec4>& vertices,std::vector<vec4>& normals){

	std::vector<vec4> temp_vertices;
	std::vector<vec4> temp_normals;
	int k = 0;
	int strip_index = 0;
	double scale_factor = 0.7;
	double interval = 6.0;
	for(double phi = -(180-interval);phi<=(180-interval);phi+=interval){
		double phir = phi*DegreesToRadians;
		double phir_int = (phi + interval)*DegreesToRadians;

		for(double theta = -180.0; theta <= 180.0; theta += interval){
			double thetar = theta * DegreesToRadians;
			temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos(phir),scale_factor*cos(thetar)*cos(phir),scale_factor*sin(phir)));			
			vec4 normal1 = vec4(sin(thetar)*cos(phir),cos(thetar)*cos(phir),sin(phir),0.0);
			temp_normals.push_back(normal1);
			temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos(phir_int),scale_factor*cos(thetar)*cos(phir_int),scale_factor*sin(phir_int)));
			vec4 normal2 = vec4(sin(thetar)*cos(phir_int),cos(thetar)*cos(phir_int),sin(phir_int),0);
			
			temp_normals.push_back(normal2);
		}
	}
	strip_index = temp_vertices.size();
		

	temp_vertices.push_back(vec3(0.0,0.0,scale_factor*1.0));
	temp_normals.push_back(vec4(0.0,0.0,scale_factor*1.0,0.0));

	double sin_pol = sin((180-interval)/2*DegreesToRadians);
	double cos_pol = cos((180-interval)/2*DegreesToRadians);

	for(double theta = -180.0; theta <= 180.0 ; theta += interval){
		double thetar = theta*DegreesToRadians;
		temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos_pol,scale_factor*cos(thetar)*cos_pol,scale_factor*sin_pol));
		vec4 normal3 = vec4(sin(thetar)*cos_pol,cos(thetar)*cos_pol,sin_pol,0);
		temp_normals.push_back(normal3);
	}

	int minpol_idx = temp_vertices.size();
	temp_vertices.push_back(vec3(0.0,0.0,scale_factor*(-1.0)));
	temp_normals.push_back(vec4(0.0,0.0,scale_factor*(-1.0),0.0));

	for(double theta = -180.0; theta <=180.0; theta += interval){
		double thetar = theta;
		temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos_pol,scale_factor*cos(thetar)*cos_pol,scale_factor*sin_pol));		
		vec4 normal4 = vec4(sin(thetar)*cos_pol,cos(thetar)*cos_pol,sin_pol,0);
		temp_normals.push_back(normal4);
	}
	for(int i=2;i<strip_index;i++){
		if(i%2 == 0){
			vertices.push_back(temp_vertices[i-2]);
			normals.push_back(temp_normals[i-2]);
			vertices.push_back(temp_vertices[i-1]);
			normals.push_back(temp_normals[i-1]);
			vertices.push_back(temp_vertices[i]);
			normals.push_back(temp_normals[i]);
		}else{
			vertices.push_back(temp_vertices[i-2]);
			normals.push_back(temp_normals[i-2]);			
			vertices.push_back(temp_vertices[i]);
			normals.push_back(temp_normals[i]);
			vertices.push_back(temp_vertices[i-1]);
			normals.push_back(temp_normals[i-1]);
		}
	}

	for(int i=strip_index + 2;i<minpol_idx;i++){
		vertices.push_back(temp_vertices[strip_index]);
		normals.push_back(temp_normals[strip_index]);
		vertices.push_back(temp_vertices[i-1]);
		normals.push_back(temp_normals[i-1]);
		vertices.push_back(temp_vertices[i]);
		normals.push_back(temp_normals[i]);
	}

	for(int i= minpol_idx +2;i<temp_vertices.size();i++){
		vertices.push_back(temp_vertices[minpol_idx]);
		normals.push_back(temp_normals[minpol_idx]);
		vertices.push_back(temp_vertices[i-1]);
		normals.push_back(temp_normals[i-1]);
		vertices.push_back(temp_vertices[i]);
		normals.push_back(temp_normals[i]);
	}

	return strip_index;
}
int makeSphere(std::vector<vec4>& vertices,std::vector<vec4>& normals,std::vector<vec2>& texCoord){

	std::vector<vec4> temp_vertices;
	std::vector<vec4> temp_normals;
	std::vector<vec2> temp_coord;
	int k = 0;
	int strip_index = 0;
	double scale_factor = 0.7;
	double interval = 6.0;
	double tst[2];
	for(double phi = -(180-interval);phi<=(180+interval);phi+=interval){
		double phir = phi*DegreesToRadians;
		double phir_int = (phi + interval)*DegreesToRadians;

		for(double theta = -180.0; theta <= 180.0; theta += interval){
			double thetar = theta * DegreesToRadians;
			temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos(phir),scale_factor*cos(thetar)*cos(phir),scale_factor*sin(phir)));			
			calcTexcoord(scale_factor*sin(thetar)*cos(phir),scale_factor*sin(phir),scale_factor,tst);
			temp_coord.push_back(vec2(tst[0],tst[1]));
			vec4 normal1 = vec4(sin(thetar)*cos(phir),cos(thetar)*cos(phir),sin(phir),0.0);
			temp_normals.push_back(normal1);
			temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos(phir_int),scale_factor*cos(thetar)*cos(phir_int),scale_factor*sin(phir_int)));
			calcTexcoord(scale_factor*sin(thetar)*cos(phir_int),scale_factor*sin(phir_int),scale_factor,tst);
			temp_coord.push_back(vec2(tst[0],tst[1]));
			vec4 normal2 = vec4(sin(thetar)*cos(phir_int),cos(thetar)*cos(phir_int),sin(phir_int),0);
			
			temp_normals.push_back(normal2);
		}
	}
	strip_index = temp_vertices.size();
		

	/*temp_vertices.push_back(vec3(0.0,0.0,scale_factor*1.0));
	calcTexcoord(0.0,scale_factor,scale_factor,tst);
	temp_coord.push_back(vec2(tst[0],tst[1]));
	temp_normals.push_back(vec4(0.0,0.0,scale_factor*1.0,0.0));

	double sin_pol = sin((180-interval)/2*DegreesToRadians);
	double cos_pol = cos((180-interval)/2*DegreesToRadians);

	for(double theta = -180.0; theta <= 180.0 ; theta += interval){
		double thetar = theta*DegreesToRadians;
		temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos_pol,scale_factor*cos(thetar)*cos_pol,scale_factor*sin_pol));
		calcTexcoord(scale_factor*sin(thetar)*cos_pol,scale_factor*sin_pol,scale_factor,tst);
		temp_coord.push_back(vec2(tst[0],tst[1]));
		vec4 normal3 = vec4(sin(thetar)*cos_pol,cos(thetar)*cos_pol,sin_pol,0);
		temp_normals.push_back(normal3);
	}

	int minpol_idx = temp_vertices.size();
	temp_vertices.push_back(vec3(0.0,0.0,scale_factor*(-1.0)));
	calcTexcoord(0.0,-scale_factor,scale_factor,tst);
	temp_coord.push_back(vec2(tst[0],tst[1]));
	temp_normals.push_back(vec4(0.0,0.0,scale_factor*(-1.0),0.0));

	for(double theta = -180.0; theta <=180.0; theta += interval){
		double thetar = theta;
		temp_vertices.push_back(vec3(scale_factor*sin(thetar)*cos_pol,scale_factor*cos(thetar)*cos_pol,scale_factor*sin_pol));		
		calcTexcoord(scale_factor*sin(thetar)*cos_pol,scale_factor*sin_pol,scale_factor,tst);
		temp_coord.push_back(vec2(tst[0],tst[1]));
		vec4 normal4 = vec4(sin(thetar)*cos_pol,cos(thetar)*cos_pol,sin_pol,0);
		temp_normals.push_back(normal4);
	}*/
	for(int i=2;i<strip_index;i++){
		if(i%2 == 0){
			vertices.push_back(temp_vertices[i-2]);
			normals.push_back(temp_normals[i-2]);
			texCoord.push_back(temp_coord[i-2]);
			vertices.push_back(temp_vertices[i-1]);
			normals.push_back(temp_normals[i-1]);
			texCoord.push_back(temp_coord[i-1]);
			vertices.push_back(temp_vertices[i]);
			normals.push_back(temp_normals[i]);
			texCoord.push_back(temp_coord[i]);
		}else{
			vertices.push_back(temp_vertices[i-2]);
			normals.push_back(temp_normals[i-2]);			
			texCoord.push_back(temp_coord[i-2]);
			vertices.push_back(temp_vertices[i]);
			normals.push_back(temp_normals[i]);
			texCoord.push_back(temp_coord[i]);
			vertices.push_back(temp_vertices[i-1]);
			normals.push_back(temp_normals[i-1]);
			texCoord.push_back(temp_coord[i-1]);
		}
	}

	/*for(int i=strip_index + 2;i<minpol_idx;i++){
		vertices.push_back(temp_vertices[strip_index]);
		normals.push_back(temp_normals[strip_index]);
		texCoord.push_back(temp_coord[strip_index]);
		vertices.push_back(temp_vertices[i-1]);
		normals.push_back(temp_normals[i-1]);
		texCoord.push_back(temp_coord[i-1]);
		vertices.push_back(temp_vertices[i]);
		normals.push_back(temp_normals[i]);
		texCoord.push_back(temp_coord[i]);
	}*/

	/*for(int i= minpol_idx +2;i<temp_vertices.size();i++){
		vertices.push_back(temp_vertices[minpol_idx]);
		normals.push_back(temp_normals[minpol_idx]);
		texCoord.push_back(temp_coord[minpol_idx]);
		vertices.push_back(temp_vertices[i-1]);
		normals.push_back(temp_normals[i-1]);
		texCoord.push_back(temp_coord[i-1]);
		vertices.push_back(temp_vertices[i]);
		normals.push_back(temp_normals[i]);
		texCoord.push_back(temp_coord[i]);
	}*/

	return strip_index;
}
bool gluInvertMatrix(double m[16], double invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}
mat4 InvMat(mat4 m){
	double m_ele[16];
	m_ele[0] = m[0][0]; m_ele[1] = m[0][1]; m_ele[2] = m[0][2]; m_ele[3] = m[0][3];
	m_ele[4] = m[1][0]; m_ele[5] = m[1][1]; m_ele[6] = m[1][2]; m_ele[7] = m[1][3];
	m_ele[8] = m[2][0]; m_ele[9] = m[2][1]; m_ele[10] = m[2][2]; m_ele[11] = m[2][3];
	m_ele[12] = m[3][0]; m_ele[13] = m[3][1]; m_ele[14] = m[3][2]; m_ele[15] = m[3][3];
	double inv_m[16];
	gluInvertMatrix(m_ele,inv_m);
	return mat4(inv_m[0],inv_m[4],inv_m[8],inv_m[12],inv_m[1],inv_m[5],inv_m[9],inv_m[13],inv_m[2],inv_m[6],inv_m[10],inv_m[14],inv_m[3],inv_m[7],inv_m[11],inv_m[15]);

}