#ifndef MATH_ANIM_TIMELINE_H
#define MATH_ANIM_TIMELINE_H
#include "animation/Animation.h"

namespace MathAnim
{
	struct AnimationManagerData;

	struct TimelinePayload
	{
		AnimObjectTypeV1 objectType;
		AnimTypeV1 animType;
		bool isAnimObject;
	};

	struct TimelineData
	{
		uint8* audioSourceFile;
		size_t audioSourceFileLength;
		int32 firstFrame;
		int32 currentFrame;
		float zoomLevel;
	};

	namespace Timeline
	{
		TimelineData initInstance();
		void init(AnimationManagerData* am);

		void update(TimelineData& data, AnimationManagerData* am);

		void freeInstance(TimelineData& data);
		void free(AnimationManagerData* am);

		RawMemory serialize(const TimelineData& data);
		TimelineData deserialize(RawMemory& memory);
	}
}

#endif 