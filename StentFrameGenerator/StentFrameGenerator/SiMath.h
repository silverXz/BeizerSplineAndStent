#ifndef _SILVERX_MATH_H_
#define _SILVERX_MATH_H_

#include <math.h>
#include <iostream>
#include <assert.h>

namespace iv
{
	const double ivPI = 3.141592653589793;
	const double ivTWOPI = 2.0 * ivPI;
	const double ivHALFPI = ivPI / 2.0;
	const double Eps = 0.000000001;

	template<typename Type>
	bool IsZero(Type v)
	{
		return ( v < Eps && v > -Eps );
	}


	template<class Type> class Vector2;
	template<class Type> class Vector3;
	template<class Type> class Vector4;
	template<class Type> class Matrix3;
	template<class Type> class Matrix4;
	template<class Type> class Quaternion;


	// Vector which has 2 components

	template<class Type>
	class Vector2
	{
	public:
		Vector2()
		{
			v[0] = v[1] = (Type)0;
		}

		Vector2(const Vector2& refV2)
		{
			for (int i = 0; i < 2; i++)
				v[i] = refV2.v[i];
		}

		Vector2(const Type& x, const Type& y)
		{
			v[0] = x;
			v[1] = y;
		}

		~Vector2() {}

		Vector2& operator = (const Vector2& refV2)
		{
			v[0] = refV2.v[0];
			v[1] = refV2.v[1];
			return *this;
		}

		Vector2& operator += (const Vector2& refV2)
		{
			for (int i = 0; i < 2; i++)
				v[i] += refV2.v[i];
			return *this;
		}

		Vector2& operator -= (const Vector2& refV2)
		{
			for (int i = 0; i < 2; i++)
				v[i] -= refV2.v[i];
			return *this;
		}

		Vector2& operator *= (const Type& val)
		{
			for (int i = 0; i < 2; i++)
				v[i] *= val;
			return *this;
		}

		Vector2& operator /= (const Type& val)
		{
			for (int i = 0; i < 2; i++)
				v[i] /= val;
			return *this;
		}

		template<class Type> friend Vector2<Type> operator + (const Vector2<Type>& r1, const Vector2<Type>& r2);
		template<class Type> friend Vector2<Type> operator - (const Vector2<Type>& r1, const Vector2<Type>& r2);
		template<class Type> friend Vector2<Type> operator * (const Vector2<Type>& r1, const Type& v);
		template<class Type> friend Vector2<Type> operator / (const Vector2<Type>& r1, const Type& v);

			

	public:
		union
		{
			struct {
				Type v[2];
			};
			struct {
				Type x,y;
			};
		};
	};

	template<class Type>
	Vector2<Type> operator + (const Vector2<Type>& r1, const Vector2<Type>& r2)
	{
		return Vector2<Type>(r1.v[0] + r2.v[0], r1.v[1] + r2.v[1]);
	}
	template<class Type>
	Vector2<Type> operator - (const Vector2<Type>& r1, const Vector2<Type>& r2)
	{
		return Vector2<Type>(r1.v[0] - r2.v[0], r1.v[1] - r2.v[1])
	}
	template<class Type>
	Vector2<Type> operator * (const Vector2<Type>& r1, const Type& val)
	{
		return Vector2<Type>(r1.v[0] * val, r1.v[1] * val);
	}
	template<class Type>
	Vector2<Type> operator / (const Vector2<Type>& r1, const Type& val)
	{
		return Vector2<Type>(r1.v[0]/val,r1.v[1]/val)
	}

	// Vector which has 3 components

	template<class Type>
	class Vector3
	{
	public:
		Vector3()
		{
			for(int i = 0; i < 3; i++)
				v[i] = (Type)0;
		}

		Vector3(Type val)
		{
			for( int i = 0 ; i < 3 ; ++i )
				v[i] = val;
		}


		Vector3(Type _x, Type _y, Type _z)
		{
			v[0] = _x;
			v[1] = _y;
			v[2] = _z;
		}

		explicit Vector3(Type* pv)
		{
			assert( pv );
			for( int i = 0 ; i < 3 ; ++i )
				v[i] = *(pv + i);
		}

		explicit Vector3(const Vector4<Type>& rv4)
		{
			for( int i = 0 ; i < 3 ; ++i )
				v[i] = rv4.v[i];
		}

		Vector3(const Vector3& refV3)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] = refV3.v[i];
		}
		~Vector3() {}

		Vector3& operator = (const Vector3& refV3)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] = refV3.v[i];
			return *this;
		}

		bool operator < (const Vector3& refV3) const
		{
			return ( v[0] < refV3.v[0] ) || 
				((v[0] == refV3.v[0])&&(v[1] < refV3.v[1])) ||
				((v[0] == refV3.v[0])&&(v[1] == refV3.v[1])&&(v[2] < refV3.v[2]));
		}

		template<typename CastType>
		operator Vector3<CastType>() const
		{
			return Vector3<CastType>(static_cast<CastType>(x),static_cast<CastType>(y),static_cast<CastType>(z));
		}

		Vector3& operator += (const Vector3& refV3)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] += refV3.v[i];
			return *this;
		}
		Vector3& operator -= (const Vector3& refV3)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] -= refV3.v[i];
			return *this;
		}
		Vector3& operator *= (const Type& v)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] *= refV3.v[i];
			return *this;
		}
		Vector3& operator /= (const Type& val)
		{
			for(int i = 0 ; i < 3 ; i++ )
				v[i] /= val;
			return *this;
		}

		bool operator == (const Vector3 &refV3)
		{
			return (x == refV3.x) && (y == refV3.y) && (z == refV3.z);
		}
		
		void SetZero()
		{
			for(int i = 0; i < 3 ; i++)
				v[i] = (Type)0;
		}


		template<class Type> friend Vector3<Type> operator + (const Vector3<Type>& r1, const Vector3<Type>& r2);

		template<class Type> friend Vector3<Type> operator - (const Vector3<Type>& r1, const Vector3<Type>& r2);

		template<class Type> friend Vector3<Type> operator * (const Vector3<Type>& r1, const Vector3<Type>& r2);

		template<class Type> friend Vector3<Type> operator * (const Vector3<Type>& r1, const Type& v);

		template<class Type> friend Vector3<Type> operator / (const Vector3<Type>& r1, const Type& v);

		template<class Type> friend Type length(const Vector3<Type>& refV);

		template<class Type> friend Type square(const Vector3<Type>& refV);

		template<class Type> friend Vector3<Type> normalize(const Vector3<Type>& refV);

		template<class Type> friend Vector3<Type> cross(const Vector3<Type>& r1, const Vector3<Type>& r2);

		template<class Type> friend Type dot(const Vector3<Type>& r1, const Vector3<Type>& r2);

		template<class Type> friend Type AngleRadian(const Vector3<Type>& ref1, const Vector3<Type>& ref2);

		template<class Type> friend std::ostream& operator<<(std::ostream& os, const Vector3<Type>& refV3);

	public:
		union {
			struct {
				Type v[3];
			};
			struct {
				Type x,y,z;
			};
		};
	};


	template<class Type>
	Vector3<Type> operator + (const Vector3<Type>& r1, const Vector3<Type>& r2)
	{
		return Vector3<Type>(r1.v[0] + r2.v[0], r1.v[1] + r2.v[1], r1.v[2] + r2.v[2]);
	}

	template<class Type>
	Vector3<Type> operator - (const Vector3<Type>& r1, const Vector3<Type>& r2)
	{
		return Vector3<Type>(r1.v[0] - r2.v[0], r1.v[1] - r2.v[1], r1.v[2] - r2.v[2]);
	}

	template<class Type>
	Vector3<Type> operator * ( const Vector3<Type>& r1,const Vector3<Type>& r2)
	{
		return Vector3<Type>(r1.v[0]*r2.v[0],r1.v[1]*r2.v[1],r1.v[2]*r2.v[2]);
	}

	template<class Type>
	Vector3<Type> operator * (const Vector3<Type>& r1, const Type& v)
	{
		return Vector3<Type>(r1.v[0] * v, r1.v[1] * v, r1.v[2] * v);
	}

	template<class Type>
	Vector3<Type> operator / (const Vector3<Type>& r1, const Type& val)
	{
		return Vector3<Type>(r1.v[0] / val, r1.v[1] / val, r1.v[2] / val);
	}

	template<class Type>
	std::ostream& operator<<(std::ostream& os, const Vector3<Type>& refV3)
	{
		os << "(" << refV3.x() << "," << refV3.y() << "," << refV3.z() << ")" << std::endl;
		return os;
	}

	template<class Type>
	inline Type length(const Vector3<Type>& refV)
	{
		Type square = refV.v[0] * refV.v[0] + refV.v[1] * refV.v[1] + refV.v[2] * refV.v[2];
		return (Type)sqrt(square);
	}

	template<class Type>
	inline Type square(const Vector3<Type>& refV)
	{
		return refV.v[0] * refV.v[0] + refV.v[1] * refV.v[1] + refV.v[2] * refV.v[2];
	}

	template<class Type>
	inline Vector3<Type> normalize(const Vector3<Type>& refV)
	{
		Type rlen = Type(1.0)/length(refV);
		return Vector3<Type>(refV.v[0] * rlen, refV.v[1] *rlen, refV.v[2] * rlen);
	}

	template<class Type>
	inline Vector3<Type> cross(const Vector3<Type>& r1, const Vector3<Type>& r2)
	{
		return Vector3<Type>(r1.v[1] * r2.v[2] - r2.v[1] * r1.v[2],
			r2.v[0] * r1.v[2] - r1.v[0] * r2.v[2],
			r1.v[0] * r2.v[1] - r2.v[0] * r1.v[1]);
	}

	template<class Type>
	inline Type dot(const Vector3<Type>& r1, const Vector3<Type>& r2)
	{
		return r1.v[0] * r2.v[0] + r1.v[1] * r2.v[1] + r1.v[2] * r2.v[2];
	}

	// Vector which has 4 components
	template<class Type>
	class Vector4
	{
	public:
		explicit Vector4()
		{
			for (int i = 0; i < 3; i++)
				v[i] = (Type)0.0f;
			v[3] = (Type)1;
		}

		explicit Vector4(Type n)
		{
			for(int i = 0 ; i < 3 ; i++)
				v[i] = n;
			v[3] = (Type)1;
		}

		explicit Vector4(const Type& x, const Type& y, const Type& z, const Type& w)
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}

		explicit Vector4(const Vector3<Type>& v3, const Type& w)
		{
			v[0] = v3.x;
			v[1] = v3.y;
			v[2] = v3.z;
			v[3] = w;
		}

		explicit Vector4(Type* pv)
		{
			for (int i = 0; i < 4; i++)
				v[i] = *(pv + i);
		}


		~Vector4(){}

		template<class Type> friend Vector4<Type> operator + (const Vector4<Type>& lhs, const Vector4<Type> rhs);
		template<class Type> friend Vector4<Type> operator - (const Vector4<Type>& lhs, const Vector4<Type> rhs);
		template<class Type> friend Vector4<Type> operator * (const Vector4<Type>& lhs, const Type& val);
		template<class Type> friend Vector4<Type> operator / (const Vector4<Type>& lhs, const Type& val);
		template<class Type> friend std::ostream& operator<< (std::ostream& os, const Vector4<Type>& refV4);
		template<class Type> friend Vector4<Type> operator * (const Matrix4<Type>& lhs, const Vector4<Type>& rhs);

		Vector4& operator = (const Vector4& refV4)
		{
			for (int i = 0; i < 4; i++)
				v[i] = refV4.v[i];
			return *this;
		}

		Vector4& operator += (const Vector4& refV4)
		{
			for (int i = 0; i < 4; i++)
				v[i] += refV4.v[i];
			return *this;
		}

		Vector4& operator -= (const Vector4& refV4)
		{
			for (int i = 0; i < 4; i++)
				v[i] -= refV4.v[i];
			return *this;
		}

		Vector4* operator *= (const Type& val)
		{
			for (int i = 0; i < 4; i++)
				v[i] *= val;
		}

		Vector4* operator /= (const Type& val)
		{
			for (int i = 0; i < 4; i++)
				v[i] /= val;
		}

		Vector3<Type> xyz() const
		{
			return Vector3<Type>(v[0],v[1],v[2]);
		}

		Type x() const
		{
			return v[0];
		}

		Type y() const
		{
			return v[1];
		}

		Type z() const
		{
			return v[2];
		}

		Type w() const
		{
			return v[3];
		}

		void perspectiveDiv(void)
		{
			if (v[3] == (Type)0)
				return;
			for (int i = 0; i < 4; i++)
				v[i] /= v[3];
		}

	public:
		Type v[4];
	};

	template<class Type> 
	Vector4<Type> operator + (const Vector4<Type>& lhs, const Vector4<Type> rhs)
	{
		return Vector4<Type>(lhs.v[0] + rhs.v[0],lhs.v[1] + rhs.v[1],lhs.v[2] + rhs.v[2],lhs.v[3] + rhs.v[3]);
	}
	template<class Type>
	Vector4<Type> operator - (const Vector4<Type>& lhs, const Vector4<Type> rhs)
	{
		return Vector4<Type>(lhs.v[0] - rhs.v[0], lhs.v[1] - rhs.v[1], lhs.v[2] - rhs.v[2], lhs.v[3] - rhs.v[3]);
	}
	template<class Type>
	inline Vector4<Type> operator * (const Vector4<Type>& lhs, const Type& val)
	{
		return Vector4<Type>(lhs.v[0] * val, lhs.v[1] * val, lhs.v[2] * val, lhs.v[3]);
	}
	template<class Type>
	inline Vector4<Type> operator / (const Vector4<Type>& lhs, const Type& val)
	{
		return Vector4<Type>(lhs.v[0] / val, lhs.v[1] / val, lhs.v[2] / val, lhs.v[3] / val);
	}

	template<class Type>
	std::ostream& operator<< (std::ostream& os, const Vector4<Type>& refV4)
	{
		os << "(" << refV4.v[0] << "," << refV4.v[1] << "," << refV4.v[2] << "," << refV4.v[3] << ")" << std::endl;
		return os;
	}


	// Column-Major Matrix for OpenGL
	//	v[0]	v[3]	v[6]	
	//	v[1]	v[4]	v[7]	
	//	v[2]	v[5]	v[8]	
	template<class Type>
	class Matrix3
	{
	public:
		Matrix3()
		{
			memset(v,0,sizeof(Type)*9);
			v[0] = v[4] = v[8] = (Type)1.0f;
		}

		explicit Matrix3(Type val)
		{
			memset(v,0,sizeof(Type)*9);
			v[0] = v[4] = v[8] = val;
		}

		Matrix3(const Vector3<Type>& v1,const Vector3<Type>& v2, const Vector3<Type>& v3)
		{
			v[0] = v1.x();	v[3] = v2.x();	v[6] = v3.x();
			v[1] = v1.y();	v[4] = v2.y();	v[7] = v3.y();
			v[2] = v1.z();	v[5] = v2.z();	v[8] = v3.z();
		}

		explicit Matrix3( const Matrix4<Type>& mat4x4)
		{
			v[0] = mat4x4.v[0];	v[1] = mat4x4.v[1]; v[2] = mat4x4.v[2];
			v[3] = mat4x4.v[4];	v[4] = mat4x4.v[5]; v[5] = mat4x4.v[6];
			v[6] = mat4x4.v[8]; v[7] = mat4x4.v[9]; v[8] = mat4x4.v[10];
		}

		explicit Matrix3(Type m00,Type m10,Type m20,Type m01,Type m11,Type m21,Type m02,Type m12,Type m22)
		{
			v[0] = m00;		v[3] = m01;		v[6] = m02;
			v[1] = m10;		v[4] = m11;		v[7] = m12;
			v[2] = m20;		v[5] = m12;		v[8] = m22;
		}

		explicit Matrix3(Type* pv)
		{
			assert(pv);
			for( int i = 0 ; i < 9 ; ++i )
				v[i] = *(pv + i);
		}

		~Matrix3() {}


		bool operator == (const Matrix3& refMat )
		{
			return v[0] == refMat.v[0] &&
				v[1] == refMat.v[1] &&
				v[2] == refMat.v[2] &&
				v[3] == refMat.v[3] &&
				v[4] == refMat.v[4] &&
				v[5] == refMat.v[5] &&
				v[6] == refMat.v[6] &&
				v[7] == refMat.v[7] &&
				v[8] == refMat.v[8];
		}

		Matrix3& operator = (const Matrix3& refMat)
		{
			for (int i = 0; i < 9; ++i )
				v[i] = refMat.v[i];
			return *this;
		}

		Matrix3& operator += (const Matrix3& refMat)
		{
			for (int i = 0; i < 9; ++i )
				v[i] += refMat.v[i];
			return *this;
		}

		Matrix3& operator -= (const Matrix3& refMat)
		{
			for (int i = 0; i < 9; ++i)
				v[i] -= refMat.v[i];
			return *this;
		}

		Matrix3& operator *= (const Type& val)
		{
			for (int i = 0; i < 9; i++)
				v[i] = v[i] * val;
			return *this;
		}

		Matrix3& operator /= (const Type& val)
		{
			for (int i = 0; i < 9; i++)
				v[i] /= val;
			return *this;
		}

		Matrix3& operator *= (const Matrix3& refMat)
		{
			v[0] = v[0] * refMat.v[0] + v[3] * refMat.v[1] + v[6] * refMat.v[2];
			v[1] = v[1] * refMat.v[0] + v[4] * refMat.v[1] + v[7] * refMat.v[2];
			v[2] = v[2] * refMat.v[0] + v[5] * refMat.v[1] + v[8] * refMat.v[2];

			v[3] = v[0] * refMat.v[3] + v[3] * refMat.v[4] + v[6] * refMat.v[5];
			v[4] = v[1] * refMat.v[3] + v[4] * refMat.v[4] + v[7] * refMat.v[5];
			v[5] = v[2] * refMat.v[3] + v[5] * refMat.v[4] + v[8] * refMat.v[5];
			
			v[6] = v[0] * refMat.v[6] + v[3] * refMat.v[7] + v[6] * refMat.v[8];
			v[7] = v[1] * refMat.v[6] + v[4] * refMat.v[7] + v[7] * refMat.v[8];
			v[8] = v[2] * refMat.v[6] + v[5] * refMat.v[7] + v[8] * refMat.v[8];

			return *this;
		}


		template<class Type> friend Matrix3<Type> operator+ (const Matrix3<Type>& r1, const Matrix3<Type>& r2);
		template<class Type> friend Matrix3<Type> operator- (const Matrix3<Type>& r1, const Matrix3<Type>& r2);

		template<class Type> friend Vector3<Type> operator* (const Matrix3<Type>& lhs, const Vector3<Type>& rhs);
		template<class Type> friend Matrix3<Type> operator* (const Matrix3<Type>& r1, const Type& val);
		template<class Type> friend Matrix3<Type> operator* (const Matrix3<Type>& r1, const Matrix3<Type>& r2);	

		template<class Type> friend Matrix3<Type> operator/ (const Matrix3<Type>& r1, const Type& val);

		template<class Type> friend std::ostream& operator<<(std::ostream& os, const Matrix3<Type>& refMat);


	public:
		Type v[9];
	};

	template<class Type> 
	Matrix3<Type> operator+ (const Matrix3<Type>& r1, const Matrix3<Type>& r2)
	{
		Type m[9];
		for( int i = 0 ; i < 9 ; ++i )
			m[i] = r1.v[i] + r2.v[i];
		return Matrix3<Type>(m);
	}

	template<class Type>
	Matrix3<Type> operator- (const Matrix3<Type>& r1, const Matrix3<Type>& r2)
	{
		Type m[9];
		for( int i = 0 ; i < 9 ; ++i )
			m[i] = r1.v[i] - r2.v[i];
		return Matrix3<Type>(m);
	}

	template<class Type> 
	Vector3<Type> operator* (const Matrix3<Type>& lhs, const Vector3<Type>& rhs)
	{
		return Vector3<Type>(
			lhs.v[0] * rhs.v[0] + lhs.v[3] * rhs.v[1] + lhs.v[6] * rhs.v[2],
			lhs.v[1] * rhs.v[0] + lhs.v[4] * rhs.v[1] + lhs.v[7] * rhs.v[2],
			lhs.v[2] * rhs.v[0] + lhs.v[5] * rhs.v[1] + lhs.v[8] * rhs.v[2]);
	}

	template<class Type>
	Matrix3<Type> operator* (const Matrix3<Type>& r1, const Type& val)
	{
		Type m[9];
		for( int i = 0 ; i < 9 ; ++i )
			m[i] = r1.v[i] * val;
		return Matrix3<Type>(m);
	}

	template<class Type>
	Matrix3<Type> operator* (const Matrix3<Type>& r1, const Matrix3<Type>& r2)
	{
		Type m[9];
		m[0] = r1.v[0] * r2.v[0] + r1.v[3] * r2.v[1] + r1.v[6] * r2.v[2];
		m[1] = r1.v[1] * r2.v[0] + r1.v[4] * r2.v[1] + r1.v[7] * r2.v[2];
		m[2] = r1.v[2] * r2.v[0] + r1.v[5] * r2.v[1] + r1.v[8] * r2.v[2];

		m[3] = r1.v[0] * r2.v[3] + r1.v[3] * r2.v[4] + r1.v[6] * r2.v[5];
		m[4] = r1.v[1] * r2.v[3] + r1.v[4] * r2.v[4] + r1.v[7] * r2.v[5];
		m[5] = r1.v[2] * r2.v[3] + r1.v[5] * r2.v[4] + r1.v[8] * r2.v[5];

		m[6] = r1.v[0] * r2.v[6] + r1.v[3] * r2.v[7] + r1.v[6] * r2.v[8];
		m[7] = r1.v[1] * r2.v[6] + r1.v[4] * r2.v[7] + r1.v[7] * r2.v[8];
		m[8] = r1.v[2] * r2.v[6] + r1.v[5] * r2.v[7] + r1.v[8] * r2.v[8];
		return Matrix3<Type>(m);
	}

	template<class Type>
	Matrix3<Type> operator/ (const Matrix3<Type>& r1, const Type& val)
	{
		assert(val != (Type)0);
		Type m[9];
		for( int i = 0 ; i < 9 ; ++i )
			m[i] = r1.v[i] / val;
		return Matrix3<Type>(m);
	}

	template<class Type>
	std::ostream& operator<<(std::ostream& os, const Matrix3<Type>& refMat)
	{
		os << refMat.v[0] << "  " << refMat.v[3] << "  " << refMat.v[6] << std::endl;
		os << refMat.v[1] << "  " << refMat.v[4] << "  " << refMat.v[7] << std::endl;
		os << refMat.v[2] << "  " << refMat.v[5] << "  " << refMat.v[8] <<std::endl;
		return os;
	}
	// Column-Major Matrix for OpenGL
	//	v[0]	v[4]	v[8]	v[12]
	//	v[1]	v[5]	v[9]	v[13]
	//	v[2]	v[6]	v[10]	v[14]
	//	v[3]	v[7]	v[11]	v[15]

	template<class Type>
	class Matrix4
	{
	public:
		Matrix4()
		{
			v[0] = (Type)1.0f;	v[1] = (Type)0.0f;	v[2] = (Type)0.0f;	v[3] = (Type)0.0f;  // Column 0
			v[4] = (Type)0.0f;	v[5] = (Type)1.0f;	v[6] = (Type)0.0f;	v[7] = (Type)0.0f;	// Column 1	
			v[8] = (Type)0.0f;	v[9] = (Type)0.0f;	v[10] = (Type)1.0f;	v[11] = (Type)0.0f;	// Column 2
			v[12] = (Type)0.0f;	v[13] = (Type)0.0f;	v[14] = (Type)0.0f;	v[15] = (Type)1.0f;	// Column 3
		}

		explicit Matrix4(const Type& val)
		{
			memset(v, 0, sizeof(Type)* 16);
			v[0] = v[5] = v[10] = val;
			v[15] = (Type)1;
		}

		Matrix4(const Vector4<Type>& v1, const Vector4<Type>& v2, const Vector4<Type>& v3, const Vector4<Type>& v4)
		{
			v[0] = v1.x();	v[4] = v2.x();	v[8] = v3.x();	v[12] = v4.x();
			v[1] = v1.y();	v[5] = v2.y();	v[9] = v3.y();	v[13] = v4.y();
			v[2] = v1.z();	v[6] = v2.z();	v[10] = v3.z();	v[14] = v4.z();
			v[3] = v1.w();	v[7] = v2.w();	v[11] = v3.w();	v[15] = v4.w();
		}

		explicit Matrix4(const Type& a00, const Type& a10, const Type& a20, const Type& a30,
			const Type& a01, const Type& a11, const Type& a21, const Type& a31,
			const Type& a02, const Type& a12, const Type& a22, const Type& a32,
			const Type& a03, const Type& a13, const Type& a23, const Type& a33)
		{
			v[0] = a00;	v[1] = a10;	v[2] = a20;	v[3] = a30;
			v[4] = a01;	v[5] = a11;	v[6] = a21;	v[7] = a31;
			v[8] = a02; v[9] = a12; v[10] = a22; v[11] = a32;
			v[12] = a03; v[13] = a13; v[14] = a23; v[15] = a33;
		}

		explicit Matrix4(Type* pv)
		{
			for (int i = 0; i < 16; i++)
				v[i] = *(pv + i);
		}

		Matrix4(const Matrix4& refMat4)
		{
			for (int i = 0; i < 16; i++)
				v[i] = refMat4.v[i];
		}

		~Matrix4() {}

		Matrix4& operator = (const Matrix4& refMat)
		{
			for (int i = 0; i < 16; i++)
				v[i] = refMat.v[i];
			return *this;
		}

		Matrix4& operator += (const Matrix4& refMat)
		{
			for (int i = 0; i < 16; i++)
				v[i] += refMat.v[i];
			return *this;
		}

		Matrix4& operator -= (const Matrix4& refMat)
		{
			for (int i = 0; i < 16; i++)
				v[i] -= refMat.v[i];
			return *this;
		}

		Matrix4& operator *= (const Type& val)
		{
			for (int i = 0; i < 16; i++)
				v[i] = v[i] * val;
			return *this;
		}

		Matrix4& operator /= (const Type& val)
		{
			for (int i = 0; i < 16; i++)
				v[i] /= val;
			return *this;
		}

		Matrix4& operator *= (const Matrix4& refMat)
		{
			v[0] = v[0] * refMat.v[0] + v[4] * refMat.v[1] + v[8] * refMat.v[2] + v[12] * refMat.v[3];
			v[1] = v[1] * refMat.v[0] + v[5] * refMat.v[1] + v[9] * refMat.v[2] + v[13] * refMat.v[3];
			v[2] = v[2] * refMat.v[0] + v[6] * refMat.v[1] + v[10] * refMat.v[2] + v[14] * refMat.v[3];
			v[3] = v[3] * refMat.v[0] + v[7] * refMat.v[1] + v[11] * refMat.v[2] + v[15] * refMat.v[3];

			v[4] = v[0] * refMat.v[4] + v[4] * refMat.v[5] + v[8] * refMat.v[6] + v[12] * refMat.v[7];
			v[5] = v[1] * refMat.v[4] + v[5] * refMat.v[5] + v[9] * refMat.v[6] + v[13] * refMat.v[7];
			v[6] = v[2] * refMat.v[4] + v[6] * refMat.v[5] + v[10] * refMat.v[6] + v[14] * refMat.v[7];
			v[7] = v[3] * refMat.v[4] + v[7] * refMat.v[5] + v[11] * refMat.v[6] + v[15] * refMat.v[7];

			v[8] = v[0] * refMat.v[8] + v[4] * refMat.v[9] + v[8] * refMat.v[10] + v[12] * refMat.v[11];
			v[9] = v[1] * refMat.v[8] + v[5] * refMat.v[9] + v[9] * refMat.v[10] + v[13] * refMat.v[11];
			v[10] = v[2] * refMat.v[8] + v[6] * refMat.v[9] + v[10] * refMat.v[10] + v[14] * refMat.v[11];
			v[11] = v[3] * refMat.v[8] + v[7] * refMat.v[9] + v[11] * refMat.v[10] + v[15] * refMat.v[11];

			v[12] = v[0] * refMat.v[12] + v[4] * refMat.v[13] + v[8] * refMat.v[14] + v[12] * refMat.v[15];
			v[13] = v[1] * refMat.v[12] + v[5] * refMat.v[13] + v[9] * refMat.v[14] + v[13] * refMat.v[15];
			v[14] = v[2] * refMat.v[12] + v[6] * refMat.v[13] + v[10] * refMat.v[14] + v[14] * refMat.v[15];
			v[15] = v[3] * refMat.v[12] + v[7] * refMat.v[13] + v[11] * refMat.v[14] + v[15] * refMat.v[15];

			return *this;
		}


		template<class Type> friend Matrix4<Type> operator+ (const Matrix4<Type>& r1, const Matrix4<Type>& r2);
		template<class Type> friend Matrix4<Type> operator- (const Matrix4<Type>& r1, const Matrix4<Type>& r2);

		template<class Type> friend Vector4<Type> operator* (const Matrix4<Type>& lhs, const Vector4<Type>& rhs);
		template<class Type> friend Matrix4<Type> operator* (const Matrix4<Type>& r1, const Type& val);
		template<class Type> friend Matrix4<Type> operator* (const Matrix4<Type>& r1, const Matrix4<Type>& r2);	

		template<class Type> friend Matrix4<Type> operator/ (const Matrix4<Type>& r1, const Type& val);

		template<class Type> friend std::ostream& operator<<(std::ostream& os, const Matrix4<Type>& refMat);



		template<typename Type> friend Matrix4<Type> perspective(const Type& fovy, const Type& ratio, const Type& nearClip, const Type& farClip);
		template<typename Type>friend Matrix4<Type> lookAt(const Vector3<Type>& eye, const Vector3<Type>& center, const Vector3<Type>& up);
		template<class Type> friend Matrix4<Type> translate(const Vector3<Type>& trans);
		template<class Type> friend Matrix4<Type> rotate(const Type& radian, const Vector3<Type>& axis);
		template<class Type> friend Matrix4<Type> translate(Type x,Type y, Type z);
		template<class Type> friend Matrix4<Type> scale(const Type& s);
		template<class Type> friend Matrix4<Type> scale(const Vector3<Type>& n, const Type& k);
		template<class Type> friend Matrix4<Type> viewport(const Type& x, const Type& y, const Type& width, const Type& height);


		void identify(void)
		{
			memset(v, 0, 16 * sizeof(Type));
			v[0] = v[5] = v[10] = v[15] = (Type)1;
		}

	public:
		Type v[16];
	};


	// Scale in any direction by factor k
	template<class Type>
	Matrix4<Type> scale(const Vector3<Type>& n, const Type& k)
	{
		//n.normalize();
		Matrix4<Type> mat((Type)1);
		Type km1 = k - (Type)1.0f;
		mat.v[0] = (Type)1.0f + km1 * n.X() * n.X();
		mat.v[1] = km1 * n.X() * n.Y();
		mat.v[2] = km1 * n.X() * n.Z();

		mat.v[4] = km1 * n.X() * n.Y();
		mat.v[5] = (Type)1.0f + km1 * n.Y() * n.Y();
		mat.v[6] = km1 * n.Y() * n.Z();

		mat.v[8] = km1 * n.X() * n.Z();
		mat.v[9] = km1 * n.Y() * n.Z();
		mat.v[10] = (Type)1.0f + km1 * n.Z() * n.Z();
	}

	template<class Type>
	Matrix4<Type> scale(const Type& s)
	{
		if (s == (Type)0.0f)
			return Matrix4<Type>(1.0);
		return Matrix4<Type>(s);
	}

	template<class Type>
	Matrix4<Type> scale(Type x,Type y,Type z)
	{
		assert( x != 0 && y != 0 && z != 0 );
		Matrix4<Type> mat(x);
		mat.v[5] = y;
		mat.v[10] = z;
		return mat;
	}


	template<class Type>
	Matrix4<Type> rotate(const Type& radian, const Vector3<Type>& n)
	{
		//	v[0]	v[4]	v[8]	v[12]
		//	v[1]	v[5]	v[9]	v[13]
		//	v[2]	v[6]	v[10]	v[14]
		//	v[3]	v[7]	v[11]	v[15]
		if (radian == (Type)0.0f)
			return Matrix4<Type>((Type)1);

		Vector3<Type> axis = normalize(n);

		Matrix4<Type> mat((Type)1);

		Type c = (Type)cos(radian);
		Type s = (Type)sin(radian);
		Type OneMinusC = (Type)1.0f - c;

		mat.v[0] = OneMinusC * axis.x * axis.x + c;
		mat.v[1] = OneMinusC * axis.x * axis.y + axis.z * s;
		mat.v[2] = OneMinusC * axis.x * axis.z - axis.y * s;

		mat.v[4] = OneMinusC * axis.x * axis.y - axis.z * s;
		mat.v[5] = OneMinusC * axis.y * axis.y + c;
		mat.v[6] = OneMinusC * axis.y * axis.z + axis.x * s;

		mat.v[8] = OneMinusC * axis.x * axis.z + axis.y * s;
		mat.v[9] = OneMinusC * axis.y * axis.z - axis.x * s;
		mat.v[10] = OneMinusC * axis.z * axis.z + c;
		return mat;
	}


	template<class Type>
	Matrix4<Type> translate(const Vector3<Type>& trans)
	{
		//	v[0]	v[4]	v[8]	v[12]
		//	v[1]	v[5]	v[9]	v[13]
		//	v[2]	v[6]	v[10]	v[14]
		//	v[3]	v[7]	v[11]	v[15]
		Matrix4<Type> mat((Type)1);

		mat.v[12] = trans.x;
		mat.v[13] = trans.y;
		mat.v[14] = trans.z;

		return mat;
	}

	template<class Type>
	Matrix4<Type> translate(Type x,Type y, Type z)
	{
		Matrix4<Type> mat((Type)1);
		mat.v[12] = x;
		mat.v[13] = y;
		mat.v[14] = z;
		return mat;
	}

	template<class Type>
	Matrix4<Type> operator / (const Matrix4<Type>& r1, const Type& val)
	{
		Type m[16];
		for (int i = 0; i < 16; i++)
			m[i] = r1.v[i] / val;
		return Matrix4<Type>(m);
	}

	template<class Type>
	Matrix4<Type> operator * (const Matrix4<Type>& r1,const Type& val)
	{
		Type m[16];
		for (int i = 0; i < 16; i++)
			m[i] = r1.v[i] * val;
		return Matrix4(m);
	}

	template<class Type>
	Matrix4<Type&> operator - (const Matrix4<Type>& r1, const Matrix4<Type>& r2)
	{
		Type m[16];
		for (int i = 0; i < 16; i++)
			m[i] = r1.v[i] - r2.v[i];
		return Matrix4(m);
	}

	template<typename Type>
	Matrix4<Type> operator + (const Matrix4<Type>& r1,const Matrix4<Type>& r2)
	{
		Type m[16];
		for (int i = 0; i < 16; i++)
			m[i] = r1.v[i] + r2.v[i];
		return Matrix4(m);
	}


	template<class Type> 
	Matrix4<Type> operator* (const Matrix4<Type>& r1, const Matrix4<Type>& r2)
	{
		//	v[0]	v[4]	v[8]	v[12]
		//	v[1]	v[5]	v[9]	v[13]
		//	v[2]	v[6]	v[10]	v[14]
		//	v[3]	v[7]	v[11]	v[15]

		Type m[16];

		m[0] = r1.v[0] * r2.v[0] + r1.v[4] * r2.v[1] + r1.v[8] * r2.v[2] + r1.v[12] * r2.v[3];
		m[1] = r1.v[1] * r2.v[0] + r1.v[5] * r2.v[1] + r1.v[9] * r2.v[2] + r1.v[13] * r2.v[3];
		m[2] = r1.v[2] * r2.v[0] + r1.v[6] * r2.v[1] + r1.v[10] * r2.v[2] + r1.v[14] * r2.v[3];
		m[3] = r1.v[3] * r2.v[0] + r1.v[7] * r2.v[1] + r1.v[11] * r2.v[2] + r1.v[15] * r2.v[3];

		m[4] = r1.v[0] * r2.v[4] + r1.v[4] * r2.v[5] + r1.v[8] * r2.v[6] + r1.v[12] * r2.v[7];
		m[5] = r1.v[1] * r2.v[4] + r1.v[5] * r2.v[5] + r1.v[9] * r2.v[6] + r1.v[13] * r2.v[7];
		m[6] = r1.v[2] * r2.v[4] + r1.v[6] * r2.v[5] + r1.v[10] * r2.v[6] + r1.v[14] * r2.v[7];
		m[7] = r1.v[3] * r2.v[4] + r1.v[7] * r2.v[5] + r1.v[11] * r2.v[6] + r1.v[15] * r2.v[7];

		m[8] = r1.v[0] * r2.v[8] + r1.v[4] * r2.v[9] + r1.v[8] * r2.v[10] + r1.v[12] * r2.v[11];
		m[9] = r1.v[1] * r2.v[8] + r1.v[5] * r2.v[9] + r1.v[9] * r2.v[10] + r1.v[13] * r2.v[11];
		m[10] = r1.v[2] * r2.v[8] + r1.v[6] * r2.v[9] + r1.v[10] * r2.v[10] + r1.v[14] * r2.v[11];
		m[11] = r1.v[3] * r2.v[8] + r1.v[7] * r2.v[9] + r1.v[11] * r2.v[10] + r1.v[15] * r2.v[11];

		m[12] = r1.v[0] * r2.v[12] + r1.v[4] * r2.v[13] + r1.v[8] * r2.v[14] + r1.v[12] * r2.v[15];
		m[13] = r1.v[1] * r2.v[12] + r1.v[5] * r2.v[13] + r1.v[9] * r2.v[14] + r1.v[13] * r2.v[15];
		m[14] = r1.v[2] * r2.v[12] + r1.v[6] * r2.v[13] + r1.v[10] * r2.v[14] + r1.v[14] * r2.v[15];
		m[15] = r1.v[3] * r2.v[12] + r1.v[7] * r2.v[13] + r1.v[11] * r2.v[14] + r1.v[15] * r2.v[15];
		return Matrix4<Type>(m);
	}


	template<class Type>
	Vector4<Type> operator * (const Matrix4<Type>& lhs, const Vector4<Type>& rhs)
	{
		return Vector4<Type>(lhs.v[0] * rhs.v[0] + lhs.v[4] * rhs.v[1] + lhs.v[8] * rhs.v[2] + lhs.v[12] * rhs.v[3],
			lhs.v[1] * rhs.v[0] + lhs.v[5] * rhs.v[1] + lhs.v[9] * rhs.v[2] + lhs.v[13] * rhs.v[3],
			lhs.v[2] * rhs.v[0] + lhs.v[6] * rhs.v[1] + lhs.v[10] * rhs.v[2] + lhs.v[14] * rhs.v[3],
			lhs.v[3] * rhs.v[0] + lhs.v[7] * rhs.v[1] + lhs.v[11] * rhs.v[2] + lhs.v[15] * rhs.v[3] );
	}

	template<class Type> 
	std::ostream& operator<<(std::ostream& os, const Matrix4<Type>& refMat)
	{
		os << refMat.v[0] << "  " << refMat.v[4] << "  " << refMat.v[8] << "  " << refMat.v[12] << std::endl;
		os << refMat.v[1] << "  " << refMat.v[5] << "  " << refMat.v[9] << "  " << refMat.v[13] << std::endl;
		os << refMat.v[2] << "  " << refMat.v[6] << "  " << refMat.v[10] << "  " << refMat.v[14] << std::endl;
		os << refMat.v[3] << "  " << refMat.v[7] << "  " << refMat.v[11] << "  " << refMat.v[15] << std::endl;
		return os;
	}




	template<typename Type>
	class Quaternion
	{
	public:
		// w,vx,vy,vz
		Type v[4];

		Quaternion()
		{
			v[0] = (Type)0;
			v[1] = (Type)0;
			v[2] = (Type)1;
			v[3] = (Type)0;
		}

		Quaternion(const Quaternion& rQuat)
		{
			for( int i = 0 ; i < 4 ; ++i )
				v[i] = rQuat.v[i];
		}

		Quaternion(Type radians,const Vector3<Type>& axis)
		{
			Type l = length(axis);
			assert(l > Eps || l < -Eps);
			Type h = radians / 2.0f;
			v[0] = cos(h);
			Type s = sin(h);
			v[1] = axis.x() * s;
			v[2] = axis.y() * s;
			v[3] = axis.z() * s;
		}

		Quaternion(Type radians, Type x, Type y, Type z)
		{
			Type h = radians / 2.0f;
			v[0] = cos(h);
			Type s = sin(h);
			Type root = sqrt(x * x + y * y + z * z);
			assert(root > Eps || root < -Eps);

			v[1] = s * x / root;
			v[2] = s * y / root;
			v[3] = s * z / root;
		}

		Quaternion& operator = (const Quaternion& rQuat)
		{
			for (int i = 0; i < 4; ++i)
				v[i] = rQuat.v[i];
		}

		bool operator == (const Quaternion& rQuat)
		{
			return (v[0] == rQuat.v[0] &&
				v[1] == rQuat.v[1] &&
				v[2] == rQuat.v[2] &&
				v[3] == rQuat.v[3]);
		}

		Matrix3<Type> convertToMatrix(void)
		{
			Type ySquare = v[2] * v[2];
			Type xSquare = v[1] * v[1];
			Type zSquare = v[3] * v[3];

			Type xy = v[1] * v[2];
			Type xz = v[1] * v[3];
			Type yz = v[2] * v[3];
			Type xw = v[1] * v[0];
			Type yw = v[2] * v[0];
			Type zw = v[3] * v[0];

			return Matrix3f(1 - 2 * (ySquare + zSquare), 2 * (xy + zw), 2 * (xz - yw),
				2 * (xy - zw), 1 - 2 * (xSquare + zSquare), 2 * (yz + xw),
				2 * (xz + yw), 2 * (yz - xw), 1 - 2 * (xSquare + ySquare));
		}


		Type getAngle()
		{
			return 2.0 * acos(v[0]);
		}


		template<typename Type> friend Quaternion<Type> operator * (const Quaternion<Type>& r1, const Quaternion<Type>& r2);
		template<typename Type> friend Quaternion<Type> operator / (const Quaternion<Type>& r1, const Quaternion<Type>& r2);
		template<typename Type> friend Quaternion<Type> operator / (const Quaternion<Type>& r1, Type val);
		template<typename Type> friend Vector3<Type> operator * (const Quaternion<Type>& r1, const Vector3<Type>& r2);

	};


	template<typename Type>
	Quaternion<Type> operator * (const Quaternion<Type>& r1, const Quaternion<Type>& r2)
	{
		Vector3<Type> v1(&r1.v[1]), v2(&r2.v[1]);
		return Quaternion(r1.v[0] * r2.v[0] - dot(v1, v2), r1.v[0] * v2 + r2.v[0] * v1 + cross(v1, v2));
	}

	template<typename Type>
	Quaternion<Type> operator / (const Quaternion<Type>& r1, const Quaternion<Type>& r2)
	{
		return r2 * inverse(r1);
	}

	template<typename Type>
	Quaternion<Type> operator / (const Quaternion<Type>& r1, Type val)
	{
		assert(val != 0);
		return Quaternion<Type>(r1.v[0] / val, r1.v[1] / val, r1.v[2] / val, r1.v[3] / val);
	}

	template<typename Type>
	Vector3<Type> operator *(const Quaternion<Type>& r1, const Vector3<Type>& v1)
	{
		return r1.convertToMatrix() * v1;
	}




	// Generate ViewMatrix #1
	template<typename Type>
	Matrix4<Type> lookAt(const Vector3<Type>& eye, const Vector3<Type>& center, const Vector3<Type>& up)
	{
		Vector3<Type> f = normalize(center - eye);		// z
		Vector3<Type> u = normalize(up);				// Temp y
		Vector3<Type> s = normalize(cross(f, u));		// x
		u = normalize(cross(s, f));

		return Matrix4<Type>(s.x, u.x, -f.x, 0.0f,
			s.y, u.y, -f.y, 0.0f,
			s.z, u.z, -f.z, 0.0f,
			-dot(s, eye), -dot(u, eye), dot(f, eye), 1.0f);
	}

	//// Generate ViewMatrix #2
	//// @Param:	pos, face and up are unit vectors and 
	//template<typename Type>
	//Matrix4<Type> viewAt(const Vector3<Type>& pos, const Vector3<Type>& face, const Vector3<Type>& up)
	//{
	//	
	//}


	// Generate Projection Matrix :-)
	// fovy: field of view in Y axis. That means tan(fovy/2) = (height/2) / n
	// ratio: width / height
	// nearClip; near clip plane.
	template<typename Type>
	Matrix4<Type> perspective(const Type& fovy, const Type& ratio, const Type& nearClip, const Type& farClip)
	{
		Type tanHalfFovy = tan(Degree2Radian(fovy / (Type)2.0f));
		Type zRange = farClip - nearClip;
		Matrix4<Type> mat((Type)0);
		mat.v[0] = (Type)1 / (tanHalfFovy * ratio);
		mat.v[5] = (Type)1 / tanHalfFovy;
		mat.v[10] = -(farClip + nearClip) / zRange;
		mat.v[14] = -(Type)2 * farClip * nearClip / zRange;
		mat.v[11] = (Type)-1;
		mat.v[15] = (Type)0;
		return mat;
	}


	template<class Type>
	Quaternion<Type> inverse(const Quaternion<Type>& rQuat)
	{
		Quaternion conj(rQuat.v[0], -rQuat.v[1], -rQuat.v[2], -rQuat.v[3]);
		Type l = rQuat.v[0] * rQuat.v[0] + rQuat.v[1] * rQuat.v[1] + rQuat.v[2] * rQuat.v[2] + rQuat.v[3] * rQuat.v[3];
		l = sqrt(l);
		assert(l > Eps || l < -Eps);
		return conj / l;
	}

	template<class Type>
	Matrix4<Type> viewport(const Type& x, const Type& y, const Type& width, const Type& height)
	{
		Matrix4<Type> mat((Type)1);
		Type halfW = width / (Type)2;
		Type halfH = height / (Type)2;

		mat.v[0] = halfW;
		mat.v[5] = -halfH;
		mat.v[10] = (Type)0.5;
		mat.v[12] = x + halfW;
		mat.v[13] = y + halfH;
		mat.v[14] = (Type)0.5;

		return mat;
	}

	template<class Type>
	Matrix3<Type> inverse(const Matrix3<Type>& ref)
	{
		Type a0 = ref.v[4] * ref.v[8] - ref.v[5] * ref.v[7];
		Type a1 = ref.v[3] * ref.v[8] - ref.v[5] * ref.v[6];
		Type a2 = ref.v[3] * ref.v[7] - ref.v[4] * ref.v[6];

		Type a3 = ref.v[1] * ref.v[8] - ref.v[2] * ref.v[7];
		Type a4 = ref.v[0] * ref.v[8] - ref.v[2] * ref.v[6];
		Type a5 = ref.v[0] * ref.v[7] - ref.v[1] * ref.v[6];

		Type a6 = ref.v[1] * ref.v[5] - ref.v[2] * ref.v[4];
		Type a7 = ref.v[0] * ref.v[5] - ref.v[2] * ref.v[3];
		Type a8 = ref.v[0] * ref.v[4] - ref.v[1] * ref.v[3];

		Type Det = ref.v[0] * a0 - ref.v[3] * a3 + ref.v[6] * a6;

		assert(Det > (Type)Eps || Det < (Type)Eps);

		Matrix3<Type> fuck(
			a0, -a3, a6,
			-a1, a4, -a7,
			a2, -a5, a8);
		return fuck / Det;
	}


	template<class Type>
	Matrix4<Type> inverse(const Matrix4<Type>& ref)
	{
		Type Coef01 = ref.v[10] * ref.v[15] - ref.v[11] * ref.v[14];
		Type Coef02 = ref.v[6] * ref.v[15] - ref.v[7] * ref.v[14];
		Type Coef03 = ref.v[6] * ref.v[11] - ref.v[7] * ref.v[10];
		Type Coef04 = ref.v[2] * ref.v[15] - ref.v[3] * ref.v[14];
		Type Coef05 = ref.v[2] * ref.v[11] - ref.v[3] * ref.v[10];
		Type Coef06 = ref.v[2] * ref.v[7] - ref.v[3] * ref.v[6];

		Type Coef07 = ref.v[8] * ref.v[13] - ref.v[9] * ref.v[12];
		Type Coef08 = ref.v[4] * ref.v[13] - ref.v[5] * ref.v[12];
		Type Coef09 = ref.v[4] * ref.v[9] - ref.v[5] * ref.v[8];
		Type Coef10 = ref.v[0] * ref.v[13] - ref.v[1] * ref.v[12];
		Type Coef11 = ref.v[0] * ref.v[9] - ref.v[1] * ref.v[8];
		Type Coef12 = ref.v[0] * ref.v[5] - ref.v[1] * ref.v[4];

		Type a0 = ref.v[5] * Coef01 - ref.v[9] * Coef02 + ref.v[13] * Coef03;
		Type a4 = ref.v[1] * Coef01 - ref.v[9] * Coef04 + ref.v[13] * Coef05;
		Type a8 = ref.v[1] * Coef02 - ref.v[5] * Coef04 + ref.v[13] * Coef06;
		Type a12 = ref.v[1] * Coef03 - ref.v[5] * Coef05 + ref.v[9] * Coef06;

		Type a1 = ref.v[4] * Coef01 - ref.v[8] * Coef02 + ref.v[12] * Coef03;
		Type a5 = ref.v[0] * Coef01 - ref.v[8] * Coef04 + ref.v[12] * Coef05;
		Type a9 = ref.v[0] * Coef02 - ref.v[4] * Coef04 + ref.v[12] * Coef06;
		Type a13 = ref.v[0] * Coef03 - ref.v[4] * Coef05 + ref.v[8] * Coef06;

		Type a2 = ref.v[7] * Coef07 - ref.v[11] * Coef08 + ref.v[15] * Coef09;
		Type a6 = ref.v[3] * Coef07 - ref.v[11] * Coef10 + ref.v[15] * Coef11;
		Type a10 = ref.v[3] * Coef08 - ref.v[7] * Coef10 + ref.v[15] * Coef12;
		Type a14 = ref.v[3] * Coef09 - ref.v[7] * Coef11 + ref.v[11] * Coef12;

		Type a3 = ref.v[6] * Coef07 - ref.v[10] * Coef08 + ref.v[14] * Coef09;
		Type a7 = ref.v[2] * Coef07 - ref.v[10] * Coef10 + ref.v[14] * Coef11;
		Type a11 = ref.v[2] * Coef08 - ref.v[6] * Coef10 + ref.v[14] * Coef12;
		Type a15 = ref.v[2] * Coef09 - ref.v[6] * Coef11 + ref.v[10] * Coef12;

		Type Det = ref.v[0] * a0 - ref.v[4] * a4 + ref.v[8] * a8 - ref.v[12] * a12;

		assert(Det > Eps || Det < -Eps);

		Matrix4<Type> adj(
			a0, -a4, a8, -a12,
			-a1, a5, -a9, a13,
			a2, -a6, a10, -a14,
			-a3, a7, -a11, a15);
		return adj / Det;
	}




	typedef Vector2<int> ivec2;
	typedef Vector2<float> vec2;
	typedef Vector2<double> dvec2;
	typedef Vector3<float>	vec3;
	typedef Vector3<double> dvec3;
	typedef Matrix3<float> mat3;
	typedef Matrix3<double> dmat3;
	typedef Matrix4<float> mat4;
	typedef Matrix4<double> dmat4;
	typedef Vector4<float> vec4;
	typedef Vector4<int>	ivec4;
	typedef Vector4<double> dvec4;


	// Get The Angle Of Two Vector3, Return Range [0,Pi]
	template<typename Type>
	inline double GetRadianBetween(const Vector3<Type>& v1,const Vector3<Type>& v2)
	{
		Type product = length(v1) * length(v2);
		assert(!IsZero(product));
		double c = dot(v1,v2) / product;

		if( c > 1.0f )
			return 0.0f;
		else if( c < -1.0f )
			return ivPI;
		else return acos(c);
	}

	template<typename Type>
	inline Type GetPreciseAngle( const Vector3<Type>& v,const Vector3<Type>& x, const Vector3<Type>& y )
	{
		double res = 0.0;
		if( dot(v,x) > 0.0 )
			res = GetRadianBetween(v,y);
		else
			res = -GetRadianBetween(v,y);
		assert(!(res!=res));
		return res;
	}

	template<typename Type>
	inline iv::dvec3 Projection( const Vector3<Type>& v,const Vector3<Type>& x,const Vector3<Type>& y )
	{
		return x * dot(v,x) + y * dot(v,y);
	}

	template<typename Type>
	Type Degree2Radian(Type degrees)
	{
		return (Type)(ivTWOPI * degrees / 360.0);
	}

	template<typename Type>
	Type Radian2Degree(Type radians)
	{
		return (Type)(radians * 360.0 / ivTWOPI);
	}

	template<typename C>
	C sil_min(C x1,C x2)
	{
		return x1 < x2 ? x1 : x2;
	}

	template<typename Type>
	Type sil_max(Type x1,Type x2)
	{
		return x1 > x2 ? x1 : x2;
	}

	/*Vector3f Reflect(const Vector3f& i,const Vector3f& n)
	{
		return n * dot(i,n) * (-2.0f) + i; 
	}*/
}


#endif