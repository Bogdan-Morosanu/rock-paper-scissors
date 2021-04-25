#ifndef APP_OPTIONAL
#define APP_OPTIONAL

#include <new>
#include <cstdint>

namespace app
{
    template < typename T >
    class Optional {
    public:

	Optional() : mIsValid(false), mValue() { }

	Optional(const T& t) : mIsValid(true), mValue()
	{
	    new (&mValue[0]) T(t);
	}

	Optional(T&& t) : mIsValid(true), mValue()
	{
	    new (&mValue[0]) T(std::move(t));
	}

	~Optional()
	{
	    if (isValid()) {
		value().~T();
	    }
	}

	template < typename U >
	Optional& operator = (U&& other)
	{
	    if (isValid()) {
		value() = std::forward<U>(other);

	    } else {
		new (&mValue[0]) T(std::forward<U>(other));
		mIsValid = true;
	    }

	    return *this;
	}

	Optional& operator = (const Optional& other)
	{
	    mIsValid = other.isValid;

	    if (other.isValid) {
		value() = other.value();
	    }

	    return *this;
	}

	Optional& operator = (Optional&& other)
	{
	    mIsValid = other.isValid;

	    if (other.isValid) {
		value() = std::move(other.value());
	    }
	    
	    return *this;
	}
	
	bool isValid() const { return mIsValid; }

	T &value()
	{
	    return *reinterpret_cast<T*>(&mValue[0]);
	}

	const T &value() const
	{
	    return *reinterpret_cast<const T*>(&mValue[0]);
	}
	
    private:

	bool mIsValid;

	alignas (T) std::array<std::uint8_t, sizeof(T)> mValue;
	
    };
}


#endif
