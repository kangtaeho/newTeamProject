#pragma once

//=============================================
// ## 17.09.29 ## CommonMacroFunction ##
//=============================================

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void setColorRect(HDC hdc, RECT rc, int R, int G, int B) {
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(R, G, B));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

#define PI 3.141591

#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

inline float getDegree(int degree) {
	float value = (PI / 180)*degree;

	return value;
}


inline void showIntData(HDC hdc, char* dataInfo, int data, int x, int y) {

	char str[100];
	sprintf(str, dataInfo, data);
	TextOut(hdc, x, y, str, strlen(str));

}

inline void showFloatData(HDC hdc, char* dataInfo, float data, int x, int y) {

	char str[100];
	sprintf(str, dataInfo, data);
	TextOut(hdc, x, y, str, strlen(str));

}