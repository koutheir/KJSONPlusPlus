
#ifndef _JSON_BINARY_VALUE_H_
#define _JSON_BINARY_VALUE_H_

namespace JSON {

class BinaryValue :
	public ValueT<BinaryType, BinaryDataType>
{
	friend class ValueFactory;

public:
	virtual ~BinaryValue() {}

	bool operator == (const BinaryValue& obj) const {return this->Equals(obj);}

	virtual BinaryType& ToBinary()	{return m_Value;}

	virtual StringType& ToString()
	{
		static StringType s;
		Base85::Encoder enc;
		enc.Encode(m_Value, s);
		return s;
	}

	virtual int Serialize(StringType& sf) const
	{
		Base85::Encoder enc;
		int r = enc.Encode(m_Value, sf);
		sf.insert(0, L"\"base85:");
		sf += L'\"';
		return (errno = r);
	}

	virtual int Serialize(StringUTF8Type& sf) const
	{
		Base85::Encoder enc;
		int r = enc.Encode(m_Value, sf);
		sf.insert(0, "\"base85:");
		sf += '\"';
		return (errno = r);
	}
};

}

#endif //_JSON_BINARY_VALUE_H_
