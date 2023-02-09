#ifndef _RECT_H
#define _RECT_H

#include "types.h"
#include "Vector2.h"

template <typename T>
struct Rect {
	Vector2<T> p1; // _00 /* topLeft */
	Vector2<T> p2; // _08 /* bottomRight */

	inline Rect() { }

	inline Rect(Vector2<T> a, Vector2<T> b)
	{
		p1 = a;
		p2 = b;
	}

	inline Rect(T a, T b, T c, T d)
	{
		p1.x = a;
		p1.y = b;
		p2.x = c;
		p2.y = d;
	}

	static inline Rect rectBySize(Vector2<T>& start, Vector2<T>& size) { return Rect(start, start + size); }

	inline void reset()
	{
		p1.x = 0.0f;
		p1.y = 0.0f;

		p2.x = 0.0f;
		p2.y = 0.0f;
	}
};

typedef Rect<int> Recti;
typedef Rect<f32> Rectf;

#endif
