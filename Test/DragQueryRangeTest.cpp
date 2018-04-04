#include "stdafx.h"
#include "CppUnitTest.h"
#include "DragQueryFile.h"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		
	using WinApiUtil::DragQueryRange;

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
			Assert::IsTrue(std::is_same<std::iterator_traits<DragQueryRange>::iterator_category, std::random_access_iterator_tag>::value);
			Assert::IsTrue(std::is_const<std::remove_reference<std::iterator_traits<DragQueryRange>::reference>::type>::value);
			Assert::IsTrue(std::is_const<std::remove_pointer<std::iterator_traits<DragQueryRange>::pointer>::type>::value);
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

		TEST_METHOD(TestIterator)
		{
			using iterator = DragQueryRange::iterator;
			iterator it;
			Assert::AreEqual(std::distance(it, it), 0);

			iterator it2 = it;
			std::advance(it2, 5);
			std::advance(it2, -2);
			Assert::AreEqual(std::distance(it, it2), 5 - 2);

		}
	};
}