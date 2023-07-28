#pragma once
#include <immintrin.h>
#include "Includes.h"
#include "Offsets.h"
#include "Helper.h"
#include "Vector.h"
#include "drvkm.h"
#include "defs.h"

INT32 find_process(LPCTSTR process_name) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hsnap, &pt)) {
		do {
			if (!lstrcmpi(pt.szExeFile, process_name)) {
				CloseHandle(hsnap);
				process_id = pt.th32ProcessID;
				return pt.th32ProcessID;
			}
		} while (Process32Next(hsnap, &pt));
	}
	CloseHandle(hsnap);


	return { NULL };
}

struct Camera
{
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
}; Camera vCamera;

struct FMinimalViewInfo
{
	Vector3 Location;
	Vector3 Rotation;
	float FOV;
	float DesiredFOV;
};



char __fastcall sub_1480C05B0(char* a1, _BYTE* Buffer, uintptr_t Orig)
{
    int v2; // esi
    _BYTE* v3; // rbx
    char* v5; // rdi
    __int64 v6; // rcx
    __int64 v7; // rdi
    int v8; // edx
    char v9; // al
    char result; // al
    char v11; // al
    int v12; // edx
    __int64 v13; // r8
    char v14; // al

    v2 = 0;
    v3 = Buffer;
    _BYTE byte_14EA7AD00 = driver.readptr<_BYTE>(virtualaddy + 0xEA7AD00);
    if (byte_14EA7AD00)
    {
        v5 = a1 + 6;
        v6 = 52i64;
        v7 = v5 - (char*)Orig;
        v8 = -544805623;
        do
        {
            v9 = v8;
            v8 += 11;
            result = v3[v7] ^ v9;
            *v3++ = result;
            --v6;
        } while (v6);
    }
    else
    {
        v12 = 2957419;
        v13 = (__int64)(__int64)(a1 + 1) + 52i64 - (_QWORD)v3;
        do
        {
            v14 = v12;
            v12 ^= v2 ^ 0xFEDCBA98;
            result = (v3[v13] ^ v14) - v2++;
            *v3++ = result;
        } while (v2 < 52);
    }
    return result;
}


struct OtherViewInf
{
    int trash;
    Vector3 Location;
    Vector3 Rotation;
    float FOV;
};

struct ViewTarget
{
    uintptr_t Target;
    OtherViewInf POV;
};



void update_camera()
{
	if (auto LocalPlayerCachedLODDistanceFactor = driver.readptr<unsigned long long>(pointer::LocalPlayer + 0xd0))
	{
		if (LocalPlayerCachedLODDistanceFactor = driver.readptr<unsigned long long>(LocalPlayerCachedLODDistanceFactor + 0x8))
		{
			uint64_t FGC_Pointerloc = driver.readptr<uint64_t>(pointer::Uworld + 0x110);
			camera::location = driver.readptr<Vector3>(FGC_Pointerloc);
			auto YawSine = driver.readptr<double>(LocalPlayerCachedLODDistanceFactor + 0x8f0);
			auto YawCosine = driver.readptr<double>(LocalPlayerCachedLODDistanceFactor + 0x910);

			camera::rotation.x = asin(driver.readptr<double>(LocalPlayerCachedLODDistanceFactor + 0x9c0)) * (180.0 / 3.14159265358979323846);
			camera::rotation.y = atan2(YawSine, YawCosine) * (180.0 / 3.14159265358979323846) * -1;
			camera::rotation.z = 0;
			camera::fov = driver.readptr<float>(pointer::PlayerController + 0x38C) * 90.f;
		}
	}
}

struct CamewaDescwipsion
{
	Vector3 Location;
	Vector3 Rotation;
	float FieldOfView;
	char Useless[0x18];
};
CamewaDescwipsion GetViewPoint()
{
	char v1; // r8
	CamewaDescwipsion ViewPoint = driver.readptr<CamewaDescwipsion>(virtualaddy + 0xF0E8BD0);
	BYTE* v2 = (BYTE*)&ViewPoint;
	int i; // edx
	__int64 result; // rax

	v1 = 0x40;
	for (i = 0; i < 0x40; ++i)
	{
		*v2 ^= v1;
		result = (unsigned int)(i + 0x17);
		v1 += i + 0x17;
		v2++;
	}

	return ViewPoint;
}



bool worldtoscreentwo = false;
bool EnableWidescreenCompat = true;
Vector3 W2S(Vector3 WorldLocation)
{
		CamewaDescwipsion ud = GetViewPoint();
		camera::location = ud.Location;
		camera::rotation.x = ud.Rotation.x;
		camera::rotation.y = ud.Rotation.y;
		camera::rotation.z = 0;
		camera::fov = ud.FieldOfView;
	
	D3DMATRIX tempMatrix = Matrix(camera::rotation);

	Vector3 vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	Vector3 vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	Vector3 vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - camera::location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;
	if (EnableWidescreenCompat)
	{
		Vector3 Screenlocation = Vector3(0, 0, 0);
		float ratio = (float)width / height;

		if (ratio < 4.0f / 3.0f)
			ratio = 4.0f / 3.0f;

		float fov = ratio / (16.0f / 9.0f) * (float)tanf(camera::fov * M_PI / 360.0f);

		Screenlocation.x = (width / 2.0f) + vTransformed.x * (((width / 2.0f) / fov)) / vTransformed.z;
		Screenlocation.y = (height / 2.0f) - vTransformed.y * (((width / 2.0f) / fov)) / vTransformed.z;

		return Screenlocation;
	}
	else {
		Vector3 location = Vector3((width / 2.0f) + vTransformed.x * (((width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z, (height / 2.0f) - vTransformed.y * (((width / 2.0f) / tanf(camera::fov * (float)M_PI / 360.f))) / vTransformed.z, 0);

		if (isvectorvalid(location))
		{
			if (IsInScreen(location))
			{
				return location;
			}
		}
	}

}


FN_VECTOR get_bone(const FN_POINTER mesh, const int id)
{
	int isCached = driver.readptr<int>(mesh + 0x648);
	pointer::BoneArray = driver.readptr<uintptr_t>(mesh + 0x600 + (isCached * 0x10));

	FTransform Bone = driver.readptr<FTransform>(pointer::BoneArray + (id * 0x60));
	FTransform ComponentToWorld = driver.readptr<FTransform>(mesh + 0x240);

	const D3DMATRIX Matrix = MatrixMultiplication(Bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return FN_VECTOR(Matrix._41, Matrix._42, Matrix._43);
}

bool fisVisible(FN_POINTER mesh)
{
	if (!mesh)
		return false;
	float fLastSubmitTime = driver.readptr<float>(mesh + 0x360);
	float fLastRenderTimeOnScreen = driver.readptr<float>(mesh + 0x368);

	const float fVisionTick = 0.06f;
	bool bVisible = fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
	return bVisible;
}



bool fisOverlappingBuilds(FN_POINTER actor)
{
	if (!actor)
		return false;
//	float fLastSubmitTime = driver.readptr<float>(actor + 0x1b10);
	float softaim = driver.readptr<float>(actor + 0x1b10); //AFortPawn	OverlappingBuildings
	bool bVisible = softaim;
	if (!bVisible)
		return false;
	return bVisible;
}


//OverlappingBuildings 