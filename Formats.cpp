#include "Formats.h"
#include "FormatHandler.h"
#include "FormatHandlerA1.h"
#include "FormatHandlerA2.h"
#include "FormatHandlerA4.h"
#include "FormatHandlerA8.h"
#include "FormatHandler565.h"
#include "FormatHandler888.h"
#include "FormatHandler1555.h"
#include "FormatHandler8888.h"
#include "FormatHandlerARGB4444.h"
#include "FormatHandlerDXT.h"
#include "FormatHandlerETC1.h"
#include "FormatHandlerGameboy.h"
#include "FormatHandlerNES.h"
#include "FormatHandlerPVRTC.h"

std::string getNameFromFormat(eFormat format)
{
	switch (format)
	{
		case eFormat::A1BE: return "A1BE";
		case eFormat::A1LE: return "A1LE";
		case eFormat::A2BE: return "A2BE";
		case eFormat::A2LE: return "A2LE";
		case eFormat::A4BE: return "A4BE";
		case eFormat::A4LE: return "A4LE";
		case eFormat::A8: return "A8";
		case eFormat::ARGB8888: return "ARGB8888";
		case eFormat::ABGR8888: return "ABGR8888";
		case eFormat::RGBA8888: return "RGBA8888";
		case eFormat::BGRA8888: return "BGRA8888";
		case eFormat::XRGB8888: return "XRGB8888";
		case eFormat::XBGR8888: return "XBGR8888";
		case eFormat::RGBX8888: return "RGBX8888";
		case eFormat::BGRX8888: return "BGRX8888";
		case eFormat::RGB888: return "RGB888";
		case eFormat::BGR888: return "BGR888";
		case eFormat::RGB565BE: return "RGB565BE";
		case eFormat::RGB565LE: return "RGB565LE";
		case eFormat::BGR565BE: return "BGR565BE";
		case eFormat::BGR565LE: return "BGR565LE";
		case eFormat::ARGB1555BE: return "ARGB1555BE";
		case eFormat::ARGB1555LE: return "ARGB1555LE";
		case eFormat::ABGR1555BE: return "ABGR1555BE";
		case eFormat::ABGR1555LE: return "ABGR1555LE";
		case eFormat::XRGB1555BE: return "XRGB1555BE";
		case eFormat::XRGB1555LE: return "XRGB1555LE";
		case eFormat::XBGR1555BE: return "XBGR1555BE";
		case eFormat::XBGR1555LE: return "XBGR1555LE";
		case eFormat::ARGB4444BE: return "ARGB4444BE";
		case eFormat::ARGB4444LE: return "ARGB4444LE";
		case eFormat::dxt1: return "dxt1";
		case eFormat::dxt5: return "dxt5";
		case eFormat::etc1: return "etc1";
		case eFormat::pvrtc_4bpp_rgb: return "pvrtc-4bpp-rgb";
		case eFormat::gameboy: return "gameboy";
		case eFormat::nes: return "nes";

		case eFormat::INVALID:
			[[fallthrough]];
		case eFormat::COUNT:
			[[fallthrough]];
		default:
			return "invalid";
	}
}

eFormat getFormatFromName(const std::string& name)
{
	// TODO: case-insensitive matching
	for (uint32_t f = 0; f < (uint32_t)eFormat::COUNT; ++f)
	{
		eFormat format = (eFormat)f;
		if (name == getNameFromFormat(format))
		{
			return format;
		}
	}
	return eFormat::INVALID;
}

std::shared_ptr<FormatHandler> createFormatHandler(eFormat format)
{
	switch (format)
	{
		case eFormat::A1BE:         return std::make_shared<FormatHandlerA1BE>();
		case eFormat::A1LE:         return std::make_shared<FormatHandlerA1LE>();
		case eFormat::A2BE:         return std::make_shared<FormatHandlerA2BE>();
		case eFormat::A2LE:         return std::make_shared<FormatHandlerA2LE>();
		case eFormat::A4BE:       return std::make_shared<FormatHandlerA4BE>();
		case eFormat::A4LE:       return std::make_shared<FormatHandlerA4LE>();
		case eFormat::A8:         return std::make_shared<FormatHandlerA8>();

		case eFormat::ARGB8888:   return std::make_shared<FormatHandlerARGB8888>();
		case eFormat::ABGR8888:   return std::make_shared<FormatHandlerABGR8888>();
		case eFormat::RGBA8888:   return std::make_shared<FormatHandlerRGBA8888>();
		case eFormat::BGRA8888:   return std::make_shared<FormatHandlerBGRA8888>();

		case eFormat::XRGB8888:   return std::make_shared<FormatHandlerXRGB8888>();
		case eFormat::XBGR8888:   return std::make_shared<FormatHandlerXBGR8888>();
		case eFormat::RGBX8888:   return std::make_shared<FormatHandlerRGBX8888>();
		case eFormat::BGRX8888:   return std::make_shared<FormatHandlerBGRX8888>();

		case eFormat::RGB888:     return std::make_shared<FormatHandlerRGB888>();
		case eFormat::BGR888:     return std::make_shared<FormatHandlerBGR888>();
		
		case eFormat::RGB565BE:   return std::make_shared<FormatHandlerRGB565BE>();
		case eFormat::RGB565LE:   return std::make_shared<FormatHandlerRGB565LE>();
		case eFormat::BGR565BE:   return std::make_shared<FormatHandlerBGR565BE>();
		case eFormat::BGR565LE:   return std::make_shared<FormatHandlerBGR565LE>();
		
		case eFormat::ARGB1555BE: return std::make_shared<FormatHandlerARGB1555BE>();
		case eFormat::ARGB1555LE: return std::make_shared<FormatHandlerARGB1555LE>();
		case eFormat::ABGR1555BE: return std::make_shared<FormatHandlerABGR1555BE>();
		case eFormat::ABGR1555LE: return std::make_shared<FormatHandlerABGR1555LE>();
		
		case eFormat::XRGB1555BE: return std::make_shared<FormatHandlerXRGB1555BE>();
		case eFormat::XRGB1555LE: return std::make_shared<FormatHandlerXRGB1555LE>();
		case eFormat::XBGR1555BE: return std::make_shared<FormatHandlerXBGR1555BE>();
		case eFormat::XBGR1555LE: return std::make_shared<FormatHandlerXBGR1555LE>();

		case eFormat::ARGB4444BE: return std::make_shared<FormatHandlerARGB4444BE>();
		case eFormat::ARGB4444LE: return std::make_shared<FormatHandlerARGB4444LE>();

		case eFormat::dxt1:       return std::make_shared<FormatHandlerDXT1>();
		case eFormat::dxt5:       return std::make_shared<FormatHandlerDXT5>();

		case eFormat::etc1:       return std::make_shared<FormatHandlerETC1>();

		case eFormat::pvrtc_4bpp_rgb: return std::make_shared<FormatHandlerPVRTC_4bpp_RGB>();

		case eFormat::gameboy:    return std::make_shared<FormatHandlerGameboy>();
		case eFormat::nes:        return std::make_shared<FormatHandlerNES>();


		case eFormat::INVALID:
			[[fallthrough]];
		case eFormat::COUNT:
			[[fallthrough]];
		default:
			printf("Couldn't find a format with type %d\n", (int)format);
			exit(1);
			return nullptr;
	}
};