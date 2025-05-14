#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

/**
 * @brief ���̳��Ժ�, �����������������Ĺ��������, �����޷����п�������͸�ֵ
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