/*
 *	XtreamLua Player - Final Version
 *	g2d.h
 *
 *	Copyright:
 *
 *	This work is licensed under the Creative Commons BY-SA 3.0 License.
 *	See http://creativecommons.org/licenses/by-sa/3.0/ or the LICENSE file
 *	for more details.
 */

#ifndef __XLP_G2D__
#define __XLP_G2D__

#include "common.h"


/*
	g2d.Clear([color]) - Clear screen & depth buffer, starts rendering.
 
		%arg color [color] The screen will be cleared with this color, dafault: black.
 
		%ret nothing.
 */

int g2D_clear(lua_State *L);


/*
	g2d.ClearZ([color]) - Clear depth buffer.
 
		%arg color [color] The screen will be cleared with this color, dafault: black.
 
		%ret nothing.
 */

int g2D_clearZ(lua_State *L);


/*
	g2d.BeginRects([texture]) - Begin rectangles rendering.
 
		%arg Image [texture] The texture that will be affected by the rendering, default: a white square, 10x10 pixels.
 
		%ret nothing.
 */

int g2D_beginRects(lua_State *L);


/*
	g2d.beginQuads([texture]) - Begin quads rendering.
 
		%arg Image [texture] The texture that will be affected by the rendering, default: a white square, 10x10 pixels.
 
		%ret nothing.
 */

int g2D_beginQuads(lua_State *L);


/*
	g2d.BeginLines() - Begin lines rendering.
 
		%arg nothing
 
		%ret nothing.
 */

int g2D_beginLines(lua_State *L);


/*
	g2d.BeginPoints() - Begin points rendering.
 
		%arg nothing
 
		%ret nothing.
 */

int g2D_beginPoints(lua_State *L);


/*
	g2d.End() - End object rendering.
 
		%arg nothing.
 
		%ret nothing.
 */

int g2D_end(lua_State *L);


/*
	g2d.Reset() - Reset current transformation and attribution.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_reset(lua_State *L);


/*
	g2d.Flip([vsync]) - Flip the screen.
 
		%arg any [vsync] If an argument is passed (like true, 1, ...), Xtream.waitVblankStart() will be called, default: doesn't call Xtream.waitVblankStart().
 
		%ret nothing
 */ 

int g2D_flip(lua_State *L);


/*
	g2d.Add() - Push the current transformation & attribution to a new object.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_add(lua_State *L);


/*
	g2d.Push() - Save the current transformation to the stack.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_push(lua_State *L);


/*
	g2d.Pop() - Restore the current transformation from the stack.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_pop(lua_State *L);


/*
	g2d.TexFree() - Free an image.
 
		%arg Image texture The texture to free.
 
		%ret nothing
 */ 

int g2D_texFree(lua_State *L);


/*
	g2d.TexLoad(path [,swizzle]) - Load an image, formats allowed: .jpg .jpeg .png.
 
		%arg string path The path of the image to load.
		%arg [swizzle] Swizzle or not the texture ( http://en.wikipedia.org/wiki/Swizzling_(computer_graphics) ), pass g2d.SWIZZLE to swizzle it, default: doesn't swizzle.
 
		%ret Image The loaded image.
 */ 

int g2D_texLoad(lua_State *L);


/*
	g2d.ResetCoord() - Reset the current coordinates.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_resetCoord(lua_State *L);


/*
	g2d.SetCoordMode(mode) - Set coordinate mode, this will determinate where the origin of the texture will be taken, the origin can be set with g2d.SetCoord functions.
 
		%arg gMode mode Either: g2d.UP_LEFT, g2d.UP_RIGHT, g2d.CENTER, g2d.DOWN_LEFT or g2d.DOWN_RIGHT.
 
		%ret nothing
 */ 

int g2D_setCoordMode(lua_State *L);


/*
	g2d.GetCoordXYZ() - Get the current position.
 
		%arg nothing
 
		%ret number 3 values, the current x, y and z positions, e.g: local x,y,z = g2d.GetCoordXYZ()
 */ 

int g2D_getCoordXYZ(lua_State *L);


/*
	g2d.SetCoordXY(x,y) - Set the new position.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
 
		%ret nothing
 */ 

int g2D_setCoordXY(lua_State *L);


/*
	g2d.SetCoordXYZ(x,y,z) - Set the new position, with depth support.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
		%arg number z The depth value.
 
		%ret nothing
 */ 

int g2D_setCoordXYZ(lua_State *L);


/*
	g2d.SetCoordXYRelative(x,y) - Set the new position, relative to the current.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
 
		%ret nothing
 */ 

int g2D_setCoordXYRelative(lua_State *L);


/*
	g2d.SetCoordXYZRelative(x,y,z) - Set the new position, with depth support, relative to the current.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
		%arg number z The depth value.
 
		%ret nothing
 */ 

int g2D_setCoordXYZRelative(lua_State *L);


/*
	g2d.ResetCrop() - Reset the current crop.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_resetCrop(lua_State *L);


/*
	g2d.GetCropXY() - Get the current crop position.
 
		%arg nothing
 
		%ret number 2 values, the current x and y crop positions, e.g: local x,y = g2d.GetCropXY()
 */ 

int g2D_getCropXY(lua_State *L);


/*
	g2d.GetCropWH() - Get the current crop scale.
 
		%arg nothing
 
		%ret number 2 values, the current width and height crop scale, e.g: local w,h = g2d.GetCropWH()
 */ 

int g2D_getCropWH(lua_State *L);


/*
	g2d.SetCropXY(x,y) - Set the new crop position.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
 
		%ret nothing
 */ 

int g2D_setCropXY(lua_State *L);


/*
	g2d.SetCropWH(w,h) - Set the new crop scale.
 
		%arg number w The width value.
		%arg number w The height value.
 
		%ret nothing
 */ 

int g2D_setCropWH(lua_State *L);

/*
	g2d.SetCrop(x,y,w,h) - Call g2d.SetCropXY(x,y) and g2d.SetCroWH(w,h) in one line.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
		%arg number w The width value.
		%arg number h The height value.
 
		%ret nothing
 */ 

int g2D_setCrop(lua_State *L);


/*
	g2d.SetCropXYRelative(x,y) - Set the new crop position, relative to the current.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
 
		%ret nothing
 */ 

int g2D_setCropXYRelative(lua_State *L);


/*
	g2d.SetCropWHRelative(w,h) - Set the new crop scale, relative to the current.
 
		%arg number w The width value.
		%arg number h The height value.
 
		%ret nothing
 */ 

int g2D_setCropWHRelative(lua_State *L);


/*
	g2d.SetCropRelative(x,y,w,h) - Call g2d.SetCropXY(x,y) and g2d.SetCroWH(w,h) in one line, relative to current.
 
		%arg number x The X-Coordinate value.
		%arg number y The Y-Coordinate value.
		%arg number w The width value.
		%arg number h The height value.
 
		%ret nothing
 */ 

int g2D_setCropRelative(lua_State *L);


/*
	g2d.ResetScale() - Reset the current scale.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_resetScale(lua_State *L);


/*
	g2d.GetScaleWH() - Get the current scale.
 
		%arg nothing

		%ret number 2 values, the current width and height scale, e.g: local w,h = g2d.GetScale()
 */ 

int g2D_getScale(lua_State *L);


/*
	g2d.SetScale(w,h) - Set the new scale, factor to the current.
 
		%arg number w The width scale factor.
		%arg number h The height scale factor.
 
		%ret nothing
 */

int g2D_setScale(lua_State *L);


/*
	g2d.SetScaleWH(w,h) - Set the new scale, in pixels.
 
		%arg number w The width in pixels.
		%arg number h The height in pixels.
 
		%ret nothing
 */

int g2D_setScaleWH(lua_State *L);


/*
	g2d.SetScaleRelative(w,h) - Set the new scale, factor to the current, relative to the current.
 
		%arg number w The width scale factor to add.
		%arg number h The height scale factor to add.
 
		%ret nothing
 */

int g2D_setScaleRelative(lua_State *L);


/*
	g2d.SetScaleWHRelative(w,h) - Set the new scale, in pixels, relative to the current.
 
		%arg number w The width in pixels to add.
		%arg number h The height in pixels to add.
 
		%ret nothing
 */

int g2D_setScaleWHRelative(lua_State *L);


/*
	g2d.ResetColor() - Reset the current color.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_resetColor(lua_State *L);


/*
	g2d.SetColor(color) - Set the new color.
 
		%arg color color The new color that will be used to colorize a non-textured object, or to make a mask for a texture.
 
		%ret nothing
 */

int g2D_setColor(lua_State *L);


/*
	g2d.ResetAlpha() - Reset the current alpha.
 
		%arg nothing
 
		%ret nothing
 */ 

int g2D_resetAlpha(lua_State *L);


/*
	g2d.GetAlpha() - Get the current alpha.
 
		%arg nothing

		%ret number The current alpha value, between 0 -> 255.
 */ 

int g2D_getAlpha(lua_State *L);


/*
	g2d.SetAlpha(alpha) - Set the new alpha.
 
		%arg number alpha The new alpha value, between 0 -> 255.
 
		%ret nothing
 */ 

int g2D_setAlpha(lua_State *L);


/*
	g2d.SetAlphaRelative(alpha) - Set the new alpha, relative to the current.
 
		%arg number alpha The alpha value to add, between 0 -> 255.
 
		%ret nothing
 */ 

int g2D_setAlphaRelative(lua_State *L);


/*
	g2d.ResetRotation() - Reset the current rotation.
 
		%arg nothing
 
		%ret nothing
 */

int g2D_resetRotation(lua_State *L);


/*
	g2d.GetRotationRad() - Get the current rotation, in radians.
 
		%arg nothing
 
		%ret number The current rotation angle, in radians.
 */ 

int g2D_getRotationRad(lua_State *L);


/*
	g2d.GetRotation() - Get the current rotation, in degrees.
 
		%arg nothing
 
		%ret number The current rotation angle, in degrees.
 */

int g2D_getRotation(lua_State *L);


/*
	g2d.SetRotationRad(angle) - Set the new rotation, in radians.
 
		%arg number angle The new angle, in radians.
 
		%ret nothing
 */

int g2D_setRotationRad(lua_State *L);


/*
	g2d.SetRotation(angle) - Set the new rotation, in degrees.
 
		%arg number angle The new angle, in degrees.
 
		%ret nothing
 */

int g2D_setRotation(lua_State *L);


/*
	g2d.SetRotationRadRelative(angle) - Set the new rotation, in radians, relative to the current.
 
		%arg number angle The angle to add, in radians.
 
		%ret nothing
 */

int g2D_setRotationRadRelative(lua_State *L);


/*
	g2d.SetRotationRelative(angle) - Set the new rotation, in degrees, relative to the current.
 
		%arg number angle The angle to add, in degrees.
 
		%ret nothing
 */

int g2D_setRotationRelative(lua_State *L);


/*
	g2d.ResetTex() - Reset texture properties.
 
		%arg nothing
 
		%ret nothing
 */

int g2D_resetTex(lua_State *L);


/*
	g2d.SetTexRepeat(use) - Set texture wrap.
 
		%arg boolean use Pass true to wrap the wrap the texture, false to do not use it.
 
		%ret nothing
 */

int g2D_setTexRepeat(lua_State *L);


/*
	g2d.SetTexBlend(use) - Use the alpha blending with the texture.
 
		%arg boolean use Pass true to activate (better look), or false to deactivate (better performance).
 
		%ret nothing
 */

int g2D_setTexBlend(lua_State *L);


/*
	g2d.SetTexLinear(use) - Use the bilinear filter with the texture.
 
		%arg boolean use Pass true to activate (better look), or false to deactivate (better performance).
 
		%ret nothing
 */

int g2D_setTexLinear(lua_State *L);


/*
	g2d.ResetScissor() - Reset the draw zone to the entire screen.
 
		%arg nothing
 
		%ret nothing
 */

int g2D_resetScissor(lua_State *L);


/*
	g2d.SetScissor(x,y,w,h) - Set the draw zone.
 
		%arg number x The new X-Coordinate.
		%arg number y The new Y-Coordinate.
		%arg number w The new width.
		%arg number h The new height.
 
		%ret nothing
 */

int g2D_setScissor(lua_State *L);


/*
	g2d.width(texture) - Get the width of a texture, can be used like this: texture:width().
 
		%arg Image texture The image which you want to get the width.
 
		%ret number The width of the image.
 */

int g2D_getWidth(lua_State *L);


/*
	g2d.height(texture) - Get the height of a texture, can be used like this: texture:height().
 
		%arg Image texture The image which you want to get the height.
 
		%ret number The height of the image.
 */

int g2D_getHeight(lua_State *L);


/*
	g2d.Blit(texture, x, y [,cropx, cropy, cropw, croph, angle]) - Blit an image on screen, need less code than a normal code, but a few properties can be changed, better use use backgrounds, can be used like this: textureBlit(x, y [,cropx, cropy, cropw, croph, angle]).
 
		%arg Image texture The image to blit.
		%arg number x The X-Coordinate of the image to blit.
		%arg number y The Y-Coordinate of the image to blit.
		%arg number cropx The crop X-Coordinate position, default: 0.
		%arg number cropy The crop Y-Coordinate position, default: 0.
		%arg number cropw The crop width, default: texture:width().
		%arg number croph The crop height, default: texture:height().
		%arg number angle The angle of the image, in degrees, default: 0.
 
		%ret nothing
 */

int g2D_blit(lua_State *L);


/*
	g2d.getPixel(x,y) - Get a pixel from screen, can be used like this: texture:getPixel(x,y) to get a pixel from an image.
 
		%arg Image [texture] The image which you want to get a pixel.
		%arg number x The X-Coordinate of the pixel.
		%arg number y The Y-Coordinate of the pixel.
 
		%ret number The color of the asked pixel.
 */

int g2D_getPixel(lua_State *L);


/*
	g2d.setPixel(x,y) - Set a pixel on screen, can be used like this: texture:setPixel(x,y) to set a pixel on an image.
 
		%arg Image [texture] The image which you want to set a pixel.
		%arg number x The X-Coordinate of the pixel.
		%arg number y The Y-Coordinate of the pixel.
 
		%ret nothing
 */

int g2D_setPixel(lua_State *L);


/*
	g2d.isSwizzled(texture) - Check if a texture is swizzled or not, can be used like this: texture:isSwizzled().
 
		%arg Image texture The image which you want to know if it's swizzled or not.
 
		%ret boolean trau if the texture is swizzled, false if it's not.
 */

int g2D_isSwizzled(lua_State *L);


/*
	tostring(texture) - Get the pointer of an image, in a string.
 
		%arg Image texture The image which you want to get the pointer.
 
		%ret string A string on this sample: "gImage: 0xXXXXXXXX".
 */

int g2D_tostring(lua_State *L);



// XLP internal code //

int g2D_init(lua_State *L);

static const luaL_reg g2d_methods[] = { // gLib2D methods
	{"Clear", g2D_clear},
	{"ClearZ", g2D_clearZ},
	
	{"BeginRects", g2D_beginRects},
	{"BeginQuads", g2D_beginQuads},
	{"BeginLines", g2D_beginLines},
	{"BeginPoints", g2D_beginPoints},
	
	{"End", g2D_end},
	{"Reset", g2D_reset},
	{"Flip", g2D_flip},
	{"Add", g2D_add},
	{"Push", g2D_push},
	{"Pop", g2D_pop},
	{"TexFree", g2D_texFree},
	{"TexLoad", g2D_texLoad},
	
	{"ResetCoord", g2D_resetCoord},
	{"SetCoordMode", g2D_setCoordMode},
	{"SetCoordXY", g2D_setCoordXY},
	{"SetCoordXYZ", g2D_setCoordXYZ},
	{"SetCoordXYRelative", g2D_setCoordXYRelative},
	{"SetCoordXYZRelative", g2D_setCoordXYZRelative},
	
	{"ResetCrop", g2D_resetCrop},
	{"SetCropXY", g2D_setCropXY},
	{"SetCropWH", g2D_setCropWH},
	{"SetCrop", g2D_setCrop},
	{"SetCropXYRealative", g2D_setCropXYRelative},
	{"SetCropWHRelative", g2D_setCropWHRelative},
	{"SetCropRelative", g2D_setCropRelative},
	
	{"ResetScale", g2D_resetCrop},
	{"SetScale", g2D_setScale},
	{"SetScaleWH", g2D_setScaleWH},
	{"SetScaleRelative", g2D_setScaleRelative},
	{"SetScaleWHRelative", g2D_setScaleWHRelative},
	
	{"ResetColor", g2D_resetColor},
	{"ResetAlpha", g2D_resetAlpha},
	{"SetColor", g2D_setColor},
	{"SetAlpha", g2D_setAlpha},
	{"SetAlphaRelative", g2D_setAlphaRelative},
	
	{"ResetRotation", g2D_resetRotation},
	{"SetRotationRad", g2D_setRotationRad},
	{"SetRotation", g2D_setRotation},
	{"SetRotationRadRelative", g2D_setRotationRadRelative},
	{"SetRotationRelative", g2D_setRotationRelative},
	
	{"ResetTex", g2D_resetTex},
	{"SetTexRepeat", g2D_setTexRepeat},
	{"SetTexBlend", g2D_setTexBlend},
	{"SetTexLinear", g2D_setTexLinear},
	
	{"ResetScissor", g2D_resetScissor},
	{"SetScissor", g2D_setScissor},
	
	{"GetCoordXYZ", g2D_getCoordXYZ},
	{"GetCropXY", g2D_getCropXY},
	{"GetCropWH", g2D_getCropWH},
	{"GetScale", g2D_getScale},
	{"GetAlpha", g2D_getAlpha},
	{"GetRotationRad", g2D_getRotationRad},
	{"GetRotation", g2D_getRotation},
	
	{"Blit", g2D_blit},
	
	{"width", g2D_getWidth},
	{"height",g2D_getHeight},
	{"getPixel", g2D_getPixel},
	{"setPixel",g2D_setPixel},
	{"isSwizzled", g2D_isSwizzled},
	{0,0}
};

static const luaL_reg g2d_metamethods[] = { // gLib2D metamethods
	{"__gc", g2D_texFree},
	{"__tostring", g2D_tostring},
	{0,0}
};

#endif

//EOF
