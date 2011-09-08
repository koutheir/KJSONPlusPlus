
#ifndef _JSON_NULL_VALUE_H_
#define _JSON_NULL_VALUE_H_

namespace JSON {

class NullValue :
	public Value
{
	friend class ValueFactory;

protected:
	NullValue() {}

public:
	virtual ~NullValue() {}

	virtual bool Equals(const Value& /* obj */) const {return true;}	///< All null objects are considered equal.
};

}

#endif //_JSON_NULL_VALUE_H_
