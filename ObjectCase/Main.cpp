///////////////////////////////////////////////////////////////////////////////
//
// Main.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DPrint.h"
#include "NewtonPhysics.h"

#include "PrimitiveObject.h"
#include "PrimitiveAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

void main(int argc,char* argv[])
{
	_FLOAT3 v;
	v[0] = 1.0f;
	v[1] = 2.0f;
	v[2] = 3.0f;

	_FLOAT3 q;
	q[0] = 1.0f;
	q[1] = 2.0f;
	q[2] = 3.0f;

	C4DVector3 vector(v);
	C4DQuaternion quaternion;
	//Set eular.
	quaternion.eular(C4DVector3(q));

	//Matrix.
	C4DMatrix4 matrix;
	//Identity.
	matrix.identity();
	//Rotate.
	matrix.rotate(quaternion);

	C4DMatrix4 matrix2;
	//Translate
	matrix2.translate(v[0],v[1],v[2]);

	//Multiply.
	matrix *= matrix2;
	//Print.
	for(int i = 0;i < 4;i ++) for(int j = 0;j < 4;j ++)
	{
		C4DPrint::printLine(stdout,L"matrix[%d][%d] = %f",i,j,matrix(i,j));
	}

	dVector newtonVector;
	newtonVector[0] = v[0];
	newtonVector[1] = v[1];
	newtonVector[2] = v[2];
	dQuaternion newtonQuaternion;
	newtonQuaternion.m_q0 = quaternion.w();
	newtonQuaternion.m_q1 = quaternion.x();
	newtonQuaternion.m_q2 = quaternion.y();
	newtonQuaternion.m_q3 = quaternion.z();
	dMatrix newtonMatrix(newtonQuaternion,newtonVector);
	//Print.
	for(int i = 0;i < 4;i ++) for(int j = 0;j < 4;j ++)
	{
		C4DPrint::printLine(stdout,L"newtonMatrix[%d][%d] = %f",i,j,newtonMatrix[i][j]);
	}
}