#include "Vector3.h"
#include "EngineMath.h"

Vector3 Vector3::Zero;
Vector3 Vector3::One(1.f, 1.f, 1.f);
Vector3 Vector3::Axis[AXIS_END] =
{
    Vector3(1.f, 0.f, 0.f),
    Vector3(0.f, 1.f, 0.f),
    Vector3(0.f, 0.f, 1.f)
};

Vector3::Vector3() :
    x(0.f),
    y(0.f),
    z(0.f)
{
}

Vector3::Vector3(float _x, float _y, float _z) :
    x(_x),
    y(_y),
    z(_z)
{
}

Vector3::Vector3(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

Vector3::Vector3(const XMVECTOR& v)
{
    XMStoreFloat3((XMFLOAT3*)this, v);
}

Vector3& Vector3::operator=(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

Vector3& Vector3::operator=(const XMVECTOR& v)
{
    XMStoreFloat3((XMFLOAT3*)this, v);

    return *this;
}

Vector3& Vector3::operator=(float f)
{
    x = f;
    y = f;
    z = f;

    return *this;
}

bool Vector3::operator==(const Vector3& v) const
{
    return (x == v.x && y == v.y && z == v.z);
}

bool Vector3::operator==(const XMVECTOR& v) const
{
    Vector3 v1(v);

    return (x == v1.x && y == v1.y && z == v1.z);
}

bool Vector3::operator!=(const Vector3& v) const
{
    return (x != v.x || y != v.y || z != v.z);
}

bool Vector3::operator!=(const XMVECTOR& v) const
{
    Vector3 v1(v);

    return (x != v1.x || y != v1.y || z != v1.z);
}

float Vector3::operator[](int Index) const
{
    switch (Index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }

    assert(false);
    return -1.f;
}

float& Vector3::operator[](int Index)
{
    switch (Index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }

    assert(false);
    return x;
}


// + ============================================
Vector3 Vector3::operator+(const Vector3& v) const
{
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator+(const XMVECTOR& v) const
{
    XMVECTOR    v1 = Convert();

    return Vector3(v + v1);
}

Vector3 Vector3::operator+(float f) const
{
    return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

Vector3 Vector3::operator+=(const XMVECTOR& v)
{
    XMVECTOR    v1 = Convert();

    Convert(v + v1);

    return *this;
}

Vector3 Vector3::operator+=(float f)
{
    x += f;
    y += f;
    z += f;

    return *this;
}

// - ===================================================

Vector3 Vector3::operator-(const Vector3& v) const
{
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-(const XMVECTOR& v) const
{
    XMVECTOR    v1 = Convert();

    return Vector3(v1 - v);
}

Vector3 Vector3::operator-(float f) const
{
    return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator-(int) const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

Vector3 Vector3::operator-=(const XMVECTOR& v)
{
    XMVECTOR    v1 = Convert();

    Convert(v1 - v);

    return *this;
}

Vector3 Vector3::operator-=(float f)
{
    x -= f;
    y -= f;
    z -= f;

    return *this;
}


// * ===================================================

Vector3 Vector3::operator*(const Vector3& v) const
{
    return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*(const XMVECTOR& v) const
{
    XMVECTOR    v1 = Convert();

    return Vector3(v * v1);
}

Vector3 Vector3::operator*(float f) const
{
    return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;

    return *this;
}

Vector3 Vector3::operator*=(const XMVECTOR& v)
{
    XMVECTOR    v1 = Convert();

    Convert(v * v1);

    return *this;
}

Vector3 Vector3::operator*=(float f)
{
    x *= f;
    y *= f;
    z *= f;

    return *this;
}

// / ===================================================

Vector3 Vector3::operator/(const Vector3& v) const
{
    return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator/(const XMVECTOR& v) const
{
    XMVECTOR    v1 = Convert();

    return Vector3(v1 / v);
}

Vector3 Vector3::operator/(float f) const
{
    return Vector3(x / f, y / f, z / f);
}

Vector3 Vector3::operator/=(const Vector3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;

    return *this;
}

Vector3 Vector3::operator/=(const XMVECTOR& v)
{
    XMVECTOR    v1 = Convert();

    Convert(v1 / v);

    return *this;
}

Vector3 Vector3::operator/=(float f)
{
    x /= f;
    y /= f;
    z /= f;

    return *this;
}

float Vector3::Length() const
{
    return XMVectorGetX(XMVector3Length(Convert()));
}

float Vector3::Distance(const Vector3& v) const
{
    Vector3 result = v - *this;
    return result.Length();
}

void Vector3::Normalize()
{
    Convert(XMVector3Normalize(Convert()));
}

float Vector3::Dot(const Vector3& v) const
{
    return XMVectorGetX(XMVector3Dot(Convert(), v.Convert()));
}

float Vector3::Angle(const Vector3& v) const
{
    Vector3 v1 = *this;
    Vector3 v2 = v;

    v1.Normalize();
    v2.Normalize();

    float   Angle = v1.Dot(v2);

    Angle = RadianToDegree(acosf(Angle));

    return Angle;
}

Vector3 Vector3::Cross(const Vector3& v) const
{
    return Vector3(XMVector3Cross(Convert(), v.Convert()));
}

Vector3 Vector3::TransformNormal(const Matrix& m) const
{
    return Vector3(XMVector3TransformNormal(Convert(), m.m));
}

Vector3 Vector3::TransformCoord(const Matrix& m) const
{
    return Vector3(XMVector3TransformCoord(Convert(), m.m));
    
}

Vector3 Vector3::CatmullRom(const Vector3& Pos0, const Vector3& Pos1, const Vector3& Pos2, const Vector3& Pos3, float t) const
{
	return Vector3(XMVectorCatmullRom(Pos0.Convert(), Pos1.Convert(), Pos2.Convert(), Pos3.Convert(), t));
}

Vector4 Vector3::ToQuaternion()
{
	return XMQuaternionRotationRollPitchYawFromVector(Convert());
}

XMVECTOR Vector3::Convert() const
{
    return XMLoadFloat3((XMFLOAT3*)this);
}

void Vector3::Convert(const XMVECTOR& v)
{
    XMStoreFloat3((XMFLOAT3*)this, v);
}

FMOD_VECTOR Vector3::FMODConvert() const
{
    FMOD_VECTOR Vec;
    Vec.x = this->x;
    Vec.y = this->y;
    Vec.z = this->z;
    return Vec;
}

float Vector3::Length(const Vector3& v)
{
    return XMVectorGetX(XMVector3Length(v.Convert()));
}

float Vector3::Distance(const Vector3& v, const Vector3& v1)
{
    Vector3 result = v - v1;
    return result.Length();
}

Vector3 Vector3::Normalize(const Vector3& v)
{
    Vector3 v1 = v;
    v1.Normalize();
    return v1;
}

Vector3 Vector3::Lerp3DMax(Vector3 _Start, Vector3 _End, float _Ratio)
{

	if (0 >= _Ratio)
	{
		_Ratio = 0.0f;
	}

	if (1.f <= _Ratio)
	{
		_Ratio = 1.f;
	}

	return Lerp3D(_Start, _End, _Ratio);
}


Vector3 Vector3::Lerp3D(Vector3 _Start, Vector3 _End, float percentage)
{
	Vector3 ReturnValue;
    if (percentage >= 1.f)
        percentage = 1.f;

    ReturnValue = _End - _Start;

    return _Start + ReturnValue * percentage;
}

Vector3 Vector3::GetRandomDir()
{
	return Vector3(GetRandomFloat(-1.f, 1.f), GetRandomFloat(-1.f, 1.f), GetRandomFloat(-1.f, 1.f));
}