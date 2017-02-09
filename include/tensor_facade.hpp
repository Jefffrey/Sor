#pragma once

#include <array>
#include <algorithm>
#include <type_traits>

#include "type_traits.hpp"
#include "detail/tmp.hpp"

namespace sor {

	/* Implementation details.
	*/
	namespace detail {

		template<std::size_t... Dims, typename... Args>
		std::size_t flatten_indexes(Args... args) {

			std::initializer_list<std::size_t> indexes = { static_cast<std::size_t>(args)... };
			std::initializer_list<std::size_t> dimensions = { Dims... };

			std::size_t index = 0;
			auto last_index = indexes.end() - 1;
			for (
					auto i = indexes.begin(), d = dimensions.end() - 1; 
					i < last_index && d >= dimensions.begin(); 
					i++, d--
				) {
				index += *i;
				index *= *d;
			}
			index += *last_index;

			return index;

		}

	}

	/* The tensor class.
	*/
	template<typename Type, std::size_t... Dims>
	struct tensor_facade {

	private:

		using tensor_facade_type = tensor_facade<Type, Dims...>;
		using container_type = std::array<Type, detail::multiply<Dims...>::value>;

		container_type array;

	public:

		/* Type definitions
		*/
		using value_type = Type;
		using reference = Type&;
		using const_reference = Type const&;

		/* Friend related tensor facade classes
		*/
		template<typename OtherType, std::size_t... OtherDims>
		friend struct tensor_facade;

		/* Regular default, copy and move constructors work as you would expect.
		*/
		tensor_facade() = default;
		tensor_facade(tensor_facade const&) = default;
		tensor_facade(tensor_facade&&) = default;

		/* Templated copy constructor
		*/
		template<typename OtherType>
		tensor_facade(tensor_facade<OtherType, Dims...> const& other) {
			(*this) = other;
		}

		/* Constructor that initializes the array as if you were to initialize an array of multiple
		 * dimensions (left to right, top to bottom, front to back, etc...).
		*/
		template<typename OtherType>
		explicit tensor_facade(std::initializer_list<OtherType> const& list) {
			(*this) = list;
		}

		/* Copy and move assignment work as you would normally expect.
		*/
		tensor_facade& operator=(tensor_facade const&) = default;
		tensor_facade& operator=(tensor_facade&&) = default;

		/* Templated copy assignment operator
		*/
		template<typename OtherType>
		tensor_facade& operator=(tensor_facade<OtherType, Dims...> const& other) {
			std::copy(other.array.begin(), other.array.end(), array.begin());
			return (*this);
		}

		template<typename OtherType>
		tensor_facade& operator=(std::initializer_list<OtherType> const& list) {
			std::copy(list.begin(), list.end(), array.begin());
			return (*this);
		}

		/* Iterators 
		*/
		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;

		constexpr iterator begin() { return array.begin(); }
		constexpr const_iterator begin() const { return array.begin(); }
		constexpr const_iterator cbegin() const { 
			return const_cast<tensor_facade_type const&>(*this).begin();
		}

		constexpr iterator end() { return array.end(); }
		constexpr const_iterator end() const { return array.end(); }
		constexpr const_iterator cend() const {
			return const_cast<tensor_facade_type const&>(*this).end();
		}

		/* Underlying data access.
		*/
		Type* data() { return array.data(); }
		Type const* data() const { return array.data(); }

		/* Swap function
		*/
		void swap(tensor_facade& rhs) {
			array.swap(rhs.array);
		}

		/* Element access operator. It access the member based on the given indexes.
		 * Example:
		 * 		sor::tensor<int, 3, 4> matrix({
		 * 			0, 1, 2, 3,
		 * 			4, 5, 6, 7,
		 * 			8, 9, 10, 11
		 * 		});
		 *		std::cout << matrix(2, 2); // = 6
		*/
		template<typename... Args,
			typename std::enable_if<sizeof...(Args) == sizeof...(Dims), int>::type = 0>
		Type& operator()(Args... args) {
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

		template<typename... Args,
			typename std::enable_if<sizeof...(Args) == sizeof...(Dims), int>::type = 0>
		Type const& operator()(Args... args) const {
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

		/* Size related member functions
		*/
		using difference_type = typename container_type::difference_type;
		using size_type = typename container_type::size_type;

		constexpr size_type size() const {
			return detail::multiply<Dims...>::value;
		}

		constexpr size_type max_size() const {
			return this->size();
		}

		constexpr bool empty() const {
			return size() == 0;
		}

	};

}