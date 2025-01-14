#ifndef MATH_ANIM_RENDERER_H
#define MATH_ANIM_RENDERER_H
#include "core.h"

namespace MathAnim
{
	struct Camera;
	struct Shader;
	struct Framebuffer;
	struct Texture;
	struct Font;
	struct SizedFont;
	struct AnimationManagerData;
	struct Path2DContext;

	enum class CapType
	{
		Flat,
		Arrow
	};

	struct RenderableTexture
	{
		const Texture* texture;
		Vec2 start;
		Vec2 size;
		Vec2 texCoordStart;
		Vec2 texCoordSize;
	};

	enum ShaderType : uint8
	{
		ScreenShader,
		RgbToYuvShader,
	};

	namespace Renderer
	{
		void init();
		void free();
		void endFrame();
		Framebuffer prepareFramebuffer(int outputWidth, int outputHeight);

		// ----------- Render calls ----------- 
		void bindAndUpdateViewportForFramebuffer(Framebuffer& framebuffer);
		void clearFramebuffer(Framebuffer& framebuffer, const Vec4& clearColor);
		void renderToFramebuffer(Framebuffer& framebuffer, const char* debugName);
		void renderToFramebuffer(Framebuffer& framebuffer, AnimationManagerData* am, const char* debugName);
		void renderStencilOutlineToFramebuffer(Framebuffer& framebuffer, const std::vector<AnimObjId>& activeObjects);

		void renderFramebuffer(const Framebuffer& framebuffer);
		void renderTextureToFramebuffer(const Texture& texture, const Framebuffer& framebuffer);
		void renderTextureToYuvFramebuffer(const Texture& texture, const Framebuffer& yFramebuffer, const Framebuffer& uvFramebuffer);
		void clearDrawCalls();

		// ----------- Styles ----------- 
		// TODO: Should this be push/pop calls, or more like nvgStroke calls with implicit pops?
		void pushStrokeWidth(float strokeWidth);
		void pushColor(const glm::u8vec4& color);
		void pushColor(const glm::vec4& color);
		void pushColor(const Vec4& color);
		void pushLineEnding(CapType lineEnding);
		void pushFont(const SizedFont* sizedFont);
		void pushCamera2D(const Camera* camera);
		void pushCamera3D(const Camera* camera);
		Vec4 getColor();

		void popStrokeWidth(int numToPop = 1);
		void popColor(int numToPop = 1);
		void popLineEnding(int numToPop = 1);
		void popFont(int numToPop = 1);
		void popCamera2D(int numToPop = 1);
		void popCamera3D(int numToPop = 1);

		// ----------- 2D stuff ----------- 
		// TODO: Switch to using this when drawing completed objects to potentially
		// batch draw calls together and improve performance
		void drawSquare(const Vec2& start, const Vec2& size);
		void drawFilledQuad(const Vec2& start, const Vec2& size, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawTexturedQuad(const Texture& texture, const Vec2& size, const Vec2& uvMin, const Vec2& uvMax, const Vec4& color, AnimObjId objId, const glm::mat4& transform = glm::identity<glm::mat4>());
		void drawFilledTri(const Vec2& p0, const Vec2& p1, const Vec2& p2, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawMultiColoredTri(const Vec2& p0, const Vec4& color0, const Vec2& p1, const Vec4& color1, const Vec2& p2, const Vec4& color2, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawLine(const Vec2& start, const Vec2& end);
		void drawString(const std::string& string, const Vec2& start, uint32 objId);
		void drawFilledCircle(const Vec2& position, float radius, int numSegments);

		// ----------- 2D Line stuff ----------- 
		Path2DContext* beginPath(const Vec2& start, const glm::mat4& transform = glm::identity<glm::mat4>());
		void free(Path2DContext* path);
		bool endPath(Path2DContext* path, bool closePath = true, AnimObjId objId = NULL_ANIM_OBJECT);
		void renderOutline(Path2DContext* path, float startT, float endT, bool closePath = true, AnimObjId objId = NULL_ANIM_OBJECT);

		void lineTo(Path2DContext* path, const Vec2& point);
		void quadTo(Path2DContext* path, const Vec2& p1, const Vec2& p2);
		void cubicTo(Path2DContext* path, const Vec2& p1, const Vec2& p2, const Vec2& p3);

		void setTransform(Path2DContext* path, const glm::mat4& transform);

		// ----------- 3D stuff ----------- 
		
		// 3D Lines
		void drawLine3D(const Vec3& start, const Vec3& end, float thickness, AnimObjId objId = NULL_ANIM_OBJECT);
		
		// Billboards
		void drawTexturedBillboard3D(const Texture& texture, const Vec3& position, const Vec2& size, const Vec2& uvMin, const Vec2& uvMax, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawBillboard3D(const Vec3& position, const Vec2& size, AnimObjId objId = NULL_ANIM_OBJECT);
		
		// 2D Shapes in 3D Space
		void drawFilledQuad3D(const Vec3& position, const Vec2& size, const Vec3& forward, const Vec3& up, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawTexturedQuad3D(const Texture& texture, const Vec2& size, const Vec2& uvMin, const Vec2& uvMax, AnimObjId objId = NULL_ANIM_OBJECT, const glm::mat4& transform = glm::identity<glm::mat4>());
		void drawFilledTri3D(const Vec3& p0, const Vec3& p1, const Vec3& p2, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawMultiColoredTri3D(const Vec3& p0, const Vec4& color0, const Vec3& p1, const Vec4& color1, const Vec3& p2, const Vec4& color2, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawFilledCircle3D(const Vec3& center, float radius, int numSegments, AnimObjId objId = NULL_ANIM_OBJECT, const glm::mat4& transform = glm::identity<glm::mat4>());
		
		// 3D Shapes
		void drawCube3D(const Vec3& center, const Vec3& size, const Vec3& forward, const Vec3& up, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawCone3D(const Vec3& baseCenter, const Vec3& forward, const Vec3& up, float radius, float length, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawCylinder(const Vec3& startCenter, const Vec3& endCenter, const Vec3& up, float radius, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawDonut(const Vec3& center, float innerRadius, float outerRadius, const Vec3& forward, const Vec3& up, float thetaStart = 0, float thetaEnd = 360, AnimObjId objId = NULL_ANIM_OBJECT);
		void drawSphere(const Vec3& center, float radius, AnimObjId objectId = NULL_ANIM_OBJECT);

		// ----------- Miscellaneous ----------- 
		void clearColor(const Vec4& color);

		// ----------- Metrics ----------- 
		int getTotalNumDrawCalls();
		int getDrawList2DNumDrawCalls();
		int getDrawListFont2DNumDrawCalls();
		int getDrawList3DNumDrawCalls();
		int getDrawList3DLineNumDrawCalls();
		int getDrawList3DBillboardNumDrawCalls();

		int getTotalNumTris();
		int getDrawList2DNumTris();
		int getDrawListFont2DNumTris();
		int getDrawList3DNumTris();
		int getDrawList3DLineNumTris();
		int getDrawList3DBillboardNumTris();
	}
}

#endif
