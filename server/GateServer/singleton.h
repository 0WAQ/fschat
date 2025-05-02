#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:

	static T& GetInstance() {
		static T instance;
		return instance;
	}

	~Singleton() = default;

protected:

	Singleton() = default;

private:

	Singleton(const Singleton<T>&) = delete;
	Singleton& operator = (const Singleton<T>&) = delete;
};

#endif // SINGLETON_H
