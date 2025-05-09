#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
public:

	template <typename... Args>
	static T& GetInstance(Args&&... args) {
		static T instance(std::forward<Args>(args)...);
		return instance;
	}

	~Singleton() = default;

protected:

	template <typename... Args>
	explicit Singleton(Args&&... args) { }

private:

	Singleton(const Singleton<T>&) = delete;
	Singleton& operator = (const Singleton<T>&) = delete;
};

#endif // SINGLETON_H
