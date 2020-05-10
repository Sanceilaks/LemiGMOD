#pragma once
//#include "imgui/imgui.h"

class CColor
{
	public:
		// constructors
		CColor()
		{
			*((int*)this) = 0;
		}
		CColor(int _r, int _g, int _b)
		{
			SetColor(_r, _g, _b);
		}
		CColor(int _r, int _g, int _b, int _a)
		{
			SetColor(_r, _g, _b, _a);
		}
		CColor(float* col_arr)
		{
			if (sizeof(col_arr) > 3)
				SetColor(col_arr[0], col_arr[1], col_arr[2], col_arr[3]);
			else
				SetColor(col_arr[0], col_arr[1], col_arr[2]);
		}

		// set the color
		// r - red component (0-255)
		// g - green component (0-255)
		// b - blue component (0-255)
		// a - alpha component, controls transparency (0 - transparent, 255 - opaque);
		void SetColor(int _r, int _g, int _b, int _a = 255)
		{
			_color[0] = (unsigned char)_r;
			_color[1] = (unsigned char)_g;
			_color[2] = (unsigned char)_b;
			_color[3] = (unsigned char)_a;
		}

		void GetColor(int& _r, int& _g, int& _b, int& _a) const
		{
			_r = _color[0];
			_g = _color[1];
			_b = _color[2];
			_a = _color[3];
		}
		void SetRawColor(int color32)
		{
			*((int*)this) = color32;
		}

		//ImU32 GetU32()
		//{
		//	return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
		//		+ (_color[0] & 0xff);
		//	//return (ImU32)(((_color[3] & 0xff) << 24) + ((_color[0] & 0xff) << 16) + ((_color[1] & 0xff) << 8) + (_color[2] & 0xff));
		//}

		int GetRawColor() const
		{
			return *((int*)this);
		}

		inline int r() const { return _color[0]; }
		inline int g() const { return _color[1]; }
		inline int b() const { return _color[2]; }
		inline int a() const { return _color[3]; }


		unsigned char& operator[](int index)
		{
			return _color[index];
		}

		const unsigned char& operator[](int index) const
		{
			return _color[index];
		}

		bool operator == (const CColor& rhs) const
		{
			return (*((int*)this) == *((int*)&rhs));
		}

		bool operator != (const CColor& rhs) const
		{
			return !(operator==(rhs));
		}

		CColor& operator=(const CColor& rhs)
		{
			SetRawColor(rhs.GetRawColor());
			return *this;
		}

	public:
		unsigned char _color[4];
};