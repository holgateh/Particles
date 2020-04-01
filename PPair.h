#pragma once

template <class T>
class PPair
{
	private: 
		T * t1, * t2; 
	public:
		PPair(T * t1, T * t2) { this->t1 = t1; this->t2 = t2;}
		T getFirst();
		T getSecond();
};
