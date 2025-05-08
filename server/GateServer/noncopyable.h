#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

/**
 * @brief 被继承以后, 派生类对象可以正常的构造和析构, 但是无法进行拷贝构造和赋值
 */
class noncopyable
{
public:
	noncopyable(const noncopyable&) = delete;
	noncopyable& operator== (const noncopyable&) = delete;

protected:
	noncopyable() = default;
	~noncopyable() = default;
};

#endif // _NONCOPYABLE_H_