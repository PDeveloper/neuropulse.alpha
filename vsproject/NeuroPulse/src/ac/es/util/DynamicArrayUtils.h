#ifndef __AC_ES_UTIL_DYNAMICARRAYUTILS_H__
#define __AC_ES_UTIL_DYNAMICARRAYUTILS_H__

namespace ac
{
	namespace es
	{
		namespace util
		{
			template <class T>
			void AssignVectorIndexWithAutoResize(T& vector, typename T::size_type index, typename T::value_type value)
			{
				// if we need to resize
				if(vector.size() <= index)
				{
					// then we shall resize!
					vector.resize(index + 1);
				}
				
				// assign the requested element
				vector[index] = value;
			}
			
			template <class T>
			void EnsureCapacity(T& vector, typename T::size_type index)
			{
				// if we need to resize
				if(vector.size() <= index)
				{
					// then we shall resize!
					vector.resize(index + 1);
				}
			}
			
			template <class T>
			typename T::value_type GetFromIndexWithAutoResize(T& vector, typename T::size_type index)
			{
				EnsureCapacity(vector, index);
				return vector[index];
			}
			
			template <class T>
			bool GetFromIndexWithAutoResizeBitset(T& bitset, typename T::size_type index)
			{
				EnsureCapacity(bitset, index);
				return bitset[index];
			}
			
			template <class T>
			void AssignBitsetIndexWithAutoResize(T& bitset, typename T::size_type index, bool value)
			{
				// if we need to resize
				EnsureCapacity(bitset, index);
				// assign the requested element
				bitset[index] = value;
			}
		}
	}
}

#endif // __AC_ES_UTIL_DYNAMICARRAYUTILS_H__