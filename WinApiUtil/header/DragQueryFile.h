#pragma once

#include <cstddef>
#include <iterator>
#include <string>
#include <utility>

#include <Windows.h>

namespace WinApiUtil
{
	/// <summary>
	/// Make DragQueryFile correspond to Range
	/// </summary>
	/// <example>
	/// <code><![CDATA[
	/// for (std::wstring file : DragQueryRange(hDrop)) {
	///   std::cout << "drag file is " << file << std::endl;
	/// }
	/// ]]></code>
	/// </example>
	class DragQueryRange
	{
		class Iterator
		{
			friend class DragQueryRange;
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type = std::wstring;
			using difference_type = signed int;
			using pointer = const value_type*;
			using reference = const value_type&;

			Iterator() = default;

			bool operator==(const Iterator& x) const noexcept;
			bool operator!=(const Iterator& x) const noexcept;

			difference_type operator-(const Iterator& x) const noexcept;

			reference operator*();
			Iterator& operator++() noexcept;
			Iterator& operator+=(difference_type) noexcept;

		private:
			Iterator(HDROP hDrop, UINT index);

		private:
			HDROP mhDrop;
			UINT mIndex;
			std::wstring mBuffer;
		};

	public:
		using iterator_category = Iterator::iterator_category;
		using value_type = Iterator::value_type;
		using difference_type = Iterator::difference_type;
		using pointer = Iterator::pointer;
		using reference = Iterator::reference;
		using iterator = Iterator;

		/// <summary>
		/// Construct DragQueryRange
		/// </summary>
		/// <param name="hDrop">parameters passed from WM_DROPFILES.</param>
		/// <param name="autoRelease">if true, call DragFinish with destructor.</param>
		DragQueryRange(HDROP hDrop, bool autoRelease = true);

		/// <summary>
		/// Construct empty range
		/// </summary>
		DragQueryRange() noexcept;

		/// <summary>
		/// Move from rvalue reference
		/// </summary>
		/// <param name="">rvalue reference</param>
		DragQueryRange(DragQueryRange&&) noexcept;

		/// <summary>
		/// Destruct DragQueryRange
		/// </summary>
		/// <remarks>
		/// if autoRelease is true. call DragFinish
		/// </remarks>
		~DragQueryRange();

		// non copyable
		DragQueryRange(const DragQueryRange&) = delete;
		DragQueryRange& operator=(const DragQueryRange&) = delete;

		// non assignable
		DragQueryRange& operator=(DragQueryRange&&) = delete;

		iterator begin();
		iterator end();

	private:
		const HDROP mhDrop;
		const UINT mCount;
		bool mAutoRelease;
	};
}
