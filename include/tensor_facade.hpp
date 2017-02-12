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
		using value_type = typename container_type::value_type;

		using reference = typename container_type::reference;
		using const_reference = typename container_type::const_reference;

		using pointer = typename container_type::pointer;
		using const_pointer = typename container_type::const_pointer;

		using iterator = typename container_type::iterator;
		using const_iterator = typename container_type::const_iterator;

		using reverse_iterator = typename container_type::reverse_iterator;
		using const_reverse_iterator = typename container_type::const_reverse_iterator;

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
		 * Note: It doesn't seem possible to initialize an `std::array` of a type with another
		 * of another type, so the exception specification needs to assert that the other type
		 * is nothrow assignable instead.
		*/
		template<typename OtherType>
		tensor_facade(tensor_facade<OtherType, Dims...> const& other)
				noexcept(std::is_nothrow_assignable<Type, OtherType>::value) {
			(*this) = other;
		}

		/* Constructor that initializes the array as if you were to initialize an array of multiple
		 * dimensions (left to right, top to bottom, front to back, etc...).
		 * Note: It doesn't seem possible to initialize an `std::array` with an `std::initializer_list`;
		 * this means that the exception specification needs to assert that the type is nothrow
		 * assignable instead.
		*/
		template<typename OtherType>
		explicit tensor_facade(std::initializer_list<OtherType> const& list)
				noexcept(std::is_nothrow_assignable<Type, OtherType>::value) {
			(*this) = list;
		}

		/* Copy and move assignment work as you would normally expect.
		*/
		tensor_facade& operator=(tensor_facade const&) = default;
		tensor_facade& operator=(tensor_facade&&) = default;

		/* Templated copy assignment operator
		*/
		template<typename OtherType>
		tensor_facade& operator=(tensor_facade<OtherType, Dims...> const& other)
				noexcept(std::is_nothrow_assignable<Type, OtherType>::value) {
			std::copy(other.array.begin(), other.array.end(), array.begin());
			return (*this);
		}

		template<typename OtherType>
		tensor_facade& operator=(std::initializer_list<OtherType> const& list)
				noexcept(std::is_nothrow_assignable<Type, OtherType>::value) {
			std::copy(list.begin(), list.end(), array.begin());
			return (*this);
		}

		/* Iterators.
		*/
		constexpr iterator begin() noexcept { return array.begin(); }
		constexpr const_iterator begin() const noexcept { return array.begin(); }
		constexpr const_iterator cbegin() const noexcept { 
			return const_cast<tensor_facade_type const&>(*this).begin();
		}

		constexpr iterator end() noexcept { return array.end(); }
		constexpr const_iterator end() const noexcept { return array.end(); }
		constexpr const_iterator cend() const noexcept {
			return const_cast<tensor_facade_type const&>(*this).end();
		}

		/* Reverse iterators.
		*/
		constexpr reverse_iterator rbegin() noexcept { return array.rbegin(); }
		constexpr const_reverse_iterator rbegin() const noexcept { return array.rbegin(); }
		constexpr const_reverse_iterator crbegin() const noexcept { 
			return const_cast<tensor_facade_type const&>(*this).rbegin();
		}

		constexpr reverse_iterator rend() noexcept { return array.rend(); }
		constexpr const_reverse_iterator rend() const noexcept { return array.rend(); }
		constexpr const_reverse_iterator crend() const noexcept {
			return const_cast<tensor_facade_type const&>(*this).rend();
		}

		/* Underlying data access.
		*/
		pointer data() noexcept { return array.data(); }
		const_pointer data() const noexcept { return array.data(); }

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
		Type& operator()(Args... args) noexcept {
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

		template<typename... Args,
			typename std::enable_if<sizeof...(Args) == sizeof...(Dims), int>::type = 0>
		Type const& operator()(Args... args) const noexcept {
			auto index = detail::flatten_indexes<Dims...>(args...);
			return array[index];
		}

		/* Size related member functions
		*/
		using difference_type = typename container_type::difference_type;
		using size_type = typename container_type::size_type;

		constexpr size_type size() const noexcept {
			return detail::multiply<Dims...>::value;
		}

		constexpr size_type max_size() const noexcept {
			return this->size();
		}

		constexpr bool empty() const noexcept {
			return size() == 0;
		}

	};

}