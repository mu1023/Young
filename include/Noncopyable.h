#ifndef _YOUNG_NONCOPYABLE_H_
#define _YOUNG_NONCOPYABLE_H_
namespace Young {
	class Noncopyable {
	protected:
		Noncopyable() {}
		~Noncopyable() {}
	public:
		Noncopyable(Noncopyable&) = delete;
		Noncopyable& operator =(Noncopyable&) = delete;
	};
}
#endif