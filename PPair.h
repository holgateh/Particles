#pragma once

template <class T>
class PPair
{
	private:
		T* t1;
		T* t2;
	public:
		PPair(T * t1, T * t2)
		{
			this->t1 = t1;
			this->t2 = t2;
		}	

		PPair()
		{

		}

		void setFirst(T* t1)
		{
			this->t1 = t1;

		}

		void setSecond(T* t2)
		{
			this->t2 = t2;
		}

		T * getFirst()
		{
			return this->t1;
		}

		T * getSecond()
		{
			return this->t2;
		}
};
