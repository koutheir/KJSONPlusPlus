
#ifndef _JSON_VALUE_FACTORY_H_
#define _JSON_VALUE_FACTORY_H_

namespace JSON {

class ValueFactory
{
protected:
	static NullValue	*m_NullSingleton;

public:
	virtual ~ValueFactory() {}

	///Creates a JSON value given its type and a possible initial value.
	/**
	The created object can be used through this interface or directly after casting
	it to the right class.

	\param obj_type The JSON type of the newly created object.
	\param init_data Pointer to the initial value assigned to the object. Can be NULL.
	\return An object of the specified \a obj_type and eventually initialized with
		 \a init_data.

	\remark
	If \a init_data is not NULL and the object initialization fails, then the
	method fails.
	*/
	static Value *Create(DataType obj_type, const void *init_data=NULL);

	static NullValue*		CreateNull();
	static BooleanValue*	CreateBoolean(BooleanType init_data=false);
	static IntegerValue*	CreateInteger(IntegerType init_data);
	static DoubleValue*		CreateDouble(DoubleType init_data=0.0);
	static DateTimeValue*	CreateDateTime(const DateTimeType& init_data);
	static StringValue*		CreateString(const StringType& init_data);
	static ObjectValue*		CreateObject();
	static ArrayValue*		CreateArray();
};

}

#endif //_JSON_VALUE_FACTORY_H_
