template<class T> class smartptr
{
  private:
		T *ptr;
	public:
		smartptr(T *pVal) : ptr(pVal) { }
		~smartptr() { delete ptr; }

		T &operator*()
		{
			return *ptr;
		}

		T *operator->()
		{
			return ptr;
		}
};
