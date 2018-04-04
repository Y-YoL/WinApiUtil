#include "stdafx.h"
#include "CppUnitTest.h"
#include "DragQueryFile.h"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		
	using WinApiUtil::DragQueryRange;

	template<class, class = void>
	struct check_iterator_traits : std::false_type
	{
	};

	template<class T>
	struct check_iterator_traits<T, std::void_t<
		typename std::iterator_traits<T>::value_type
		>> : std::true_type
	{
	};

	TEST_CLASS(DragQueryRangeTest)
	{
	public:
		TEST_METHOD(TestDragQueryRangeConstructible)
		{
			Assert::IsTrue(std::is_default_constructible<DragQueryRange>::value);
			Assert::IsTrue(std::is_constructible<DragQueryRange, HDROP>::value);
			Assert::IsTrue(std::is_nothrow_move_constructible<DragQueryRange>::value);
		}

		TEST_METHOD(TestDragQueryRangeNonAssignable)
		{
			Assert::IsFalse(std::is_move_assignable<DragQueryRange>::value);
		}

		TEST_METHOD(TestDragQueryRangeNonCopyable)
		{
			Assert::IsFalse(std::is_copy_constructible<DragQueryRange>::value);
			Assert::IsFalse(std::is_copy_assignable<DragQueryRange>::value);
		}

		TEST_METHOD(TestIteratorTraits)
		{
			Assert::IsTrue(check_iterator_traits<DragQueryRange>::value);
		}

		TEST_METHOD(TestIteratorConstructible)
		{
			using iterator = DragQueryRange::iterator;
			Assert::IsTrue(std::is_nothrow_default_constructible<iterator>::value);
			Assert::IsTrue(std::is_nothrow_move_constructible<iterator>::value);
			Assert::IsTrue(std::is_copy_constructible<iterator>::value);
		}

		TEST_METHOD(TestIteratorAssignable)
		{
			using iterator = DragQueryRange::iterator;
			Assert::IsTrue(std::is_nothrow_assignable<iterator, iterator>::value);
			Assert::IsTrue(std::is_nothrow_move_assignable<iterator>::value);
			Assert::IsTrue(std::is_copy_assignable<iterator>::value);
		}
	};
}