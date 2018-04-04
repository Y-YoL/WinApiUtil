
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
	DragQueryRange::Iterator::Iterator(HDROP hDrop, std::size_t index)
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

	auto DragQueryRange::Iterator::operator*() -> reference
	{
		if (mBuffer.empty()) {
			if (const auto size = ::DragQueryFileW(mhDrop, mIndex, nullptr, 0)) {
				mBuffer.resize(size + 1);
				::DragQueryFileW(mhDrop, mIndex, &mBuffer[0], mBuffer.size());
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
#pragma endregion
}