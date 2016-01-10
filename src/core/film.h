#pragma once

#include "core/ink.h"
#include "math/vector.h"

namespace ink
{
	class INK_API Film
	{
		public:
			Film();
			Film(uint32 width, uint32 height);
			~Film();
			
			uint32 width()	{ return w; }
			uint32 height() { return h; }

			void 		resize(uint32 width, uint32 height);
			void		clear();
			Vec3f& 	pixel(uint32 x, uint32 y);
			
			bool		save(const char* filepath) const;

		private:
			Vec3f*	data;
			uint32	w;
			uint32	h;
	};

}	// namespace ink

