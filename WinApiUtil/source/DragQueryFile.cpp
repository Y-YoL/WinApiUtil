
#include "DragQueryFile.h"
#include <utility>
#include <Windows.h>

namespace WinApiUtil
{
	DragQueryRange::DragQueryRange(HDROP hDrop, bool autoRelase)
		: mhDrop(hDrop)
		, mCount(::DragQueryFileW(hDrop, 0xFFFFFF, nullptr, 0))
		, mAutoRelease(autoRelase)
	{
	}

	DragQueryRange::DragQueryRange() noexcept
		: mhDrop()
		, mCount(0)
		, mAutoRelease(false)
	{
	}

	DragQueryRange::DragQueryRange(DragQueryRange&& x) noexcept
		: mhDrop(x.mhDrop)
		, mCount(x.mCount)
		, mAutoRelease(x.mAutoRelease)
	{
		x.mAutoRelease = false;
	}

	DragQueryRange::~DragQueryRange()
	{
		if (mAutoRelease) {
			::DragFinish(mhDrop);
		}
	}

	auto DragQueryRange::begin() -> iterator
	{
		return iterator(mhDrop, 0);
	}

	auto DragQueryRange::end() -> iterator
	{
		return iterator(mhDrop, mCount);
	}

#pragma region iterator
	DragQueryRange::Iterator::Iterator(HDROP hDrop, UINT index)
		: mhDrop(hDrop)
		, mIndex(index)
	{
	}

	auto DragQueryRange::Iterator::operator==(const Iterator& x) const noexcept -> bool
	{
		return (mhDrop == x.mhDrop) && (mIndex == x.mIndex);
	}

	auto DragQueryRange::Iterator::operator!=(const Iterator& x) const noexcept -> bool
	{
		return std::rel_ops::operator!=(*this, x);
	}

	auto DragQueryRange::Iterator::operator-(const Iterator& x) const noexcept -> difference_type
	{
		return mIndex - x.mIndex;
	}

	auto DragQueryRange::Iterator::operator*() -> reference
	{
		if (mBuffer.empty()) {
			if (const auto size = ::DragQueryFileW(mhDrop, mIndex, nullptr, 0)) {
				const auto bufferSize = size + 1;
				mBuffer.resize(bufferSize);
				::DragQueryFileW(mhDrop, mIndex, &mBuffer[0], bufferSize);
			}
		}

		return mBuffer;
	}

	auto DragQueryRange::Iterator::operator++() noexcept -> Iterator&
	{
		++mIndex;
		mBuffer.clear();
		return *this;
	}

	auto DragQueryRange::Iterator::operator+=(difference_type offset) noexcept -> Iterator&
	{
		mIndex += offset;
		mBuffer.clear();
		return *this;
	}
#pragma endregion
}
