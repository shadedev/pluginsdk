#pragma once
SXMODULE_SXCORE

namespace sx {
	#if SXAPI_COCOA
		class HUnlock {
		public:
			explicit HUnlock (Handle h) : h(h) { }
			HUnlock (const HUnlock&) = delete;
			HUnlock& operator= (const HUnlock&) = delete;
			~HUnlock () { if (h) ::HUnlock(h); }
		private:
			const Handle h;
		};
		class DisposeHandle {
		public:
			explicit DisposeHandle (Handle h) : h(h) { }
			DisposeHandle (const DisposeHandle&) = delete;
			DisposeHandle& operator= (const DisposeHandle&) = delete;
			~DisposeHandle () { if (h) ::DisposeHandle(h); }
		private:
			const Handle h;
		};
		class FSCloseIterator {
		public:
			explicit FSCloseIterator (FSIterator iterator) : iterator(iterator) { }
			FSCloseIterator (const FSCloseIterator&) = delete;
			FSCloseIterator& operator= (const FSCloseIterator&) = delete;
			~FSCloseIterator () { ::FSCloseIterator(iterator); }
		private:
			const FSIterator iterator;
		};
	#endif
	#if SXAPI_COCOA || SXAPI_COCOA_TOUCH
		template<typename T> class cfref {
		public:
			cfref (T t = 0) : t(t) { }
			cfref (const cfref&) = delete;
			cfref& operator= (const cfref&) = delete;
			~cfref () { if (t) ::CFRelease(t); }
			T operator() () const { return t; }
			T operator() (T u) { if (t) ::CFRelease(t); t = u; return t; }
			T operator= (T u) { if (t) ::CFRelease(t); t = u; return t; }
			operator T () const { return t; }
		private:
			T t;
		};
		template<> class cfref<CGImageRef> {
		public:
			cfref (CGImageRef t = 0) : t(t) { }
			cfref (const cfref&) = delete;
			cfref& operator= (const cfref&) = delete;
			~cfref () { if (t) ::CGImageRelease(t); }
			CGImageRef operator() () const { return t; }
			CGImageRef operator() (CGImageRef u) { if (t) ::CGImageRelease(t); t = u; return t; }
			CGImageRef operator= (CGImageRef u) { if (t) ::CGImageRelease(t); t = u; return t; }
			operator CGImageRef () const { return t; }
		private:
			CGImageRef t;
		};
		template<> class cfref<CGContextRef> {
		public:
			cfref (CGContextRef t = 0) : t(t) { }
			cfref (const cfref&) = delete;
			cfref& operator= (const cfref&) = delete;
			~cfref () { if (t) ::CGContextRelease(t); }
			CGContextRef operator() () const { return t; }
			CGContextRef operator() (CGContextRef u) { if (t) ::CGContextRelease(t); t = u; return t; }
			CGContextRef operator= (CGContextRef u) { if (t) ::CGContextRelease(t); t = u; return t; }
			operator CGContextRef () const { return t; }
		private:
			CGContextRef t;
		};
	#endif
}

#if SXAPI_COCOA || SXAPI_COCOA_TOUCH
	#if __LP64__
	#else
		inline std::ostream& operator<< (std::ostream &o, const ::CGPoint &p) {
			o << p.x << " " << p.y;
			return o;
		}
		inline std::ostream& operator<< (std::ostream &o, const ::CGRect &r) {
			o << r.origin.x << " " << r.origin.y << " " << r.size.width << " " << r.size.height;
			return o;
		}
	#endif
#endif
