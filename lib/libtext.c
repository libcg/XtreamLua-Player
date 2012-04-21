#include "libtext.h"

float UnderLinedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorLine, int center)
{	
	intraFontSetStyle(font, size, colorText, 0, 0.0f, center);
	
	float width = intraFontMeasureText(font, text);
	
	g2dBeginLines(G2D_VOID);
		g2dSetColor(colorLine);
	
		switch(center)
		{
			case INTRAFONT_ALIGN_LEFT:
				g2dSetCoordXY(x, y + 2);
				g2dAdd();
				
				g2dSetCoordXY(x+width, y+2);
				g2dAdd();
				break;
				
			case INTRAFONT_ALIGN_CENTER:
				g2dSetCoordXY(x - width / 2, y + 2);
				g2dAdd();
				
				g2dSetCoordXY(x+width/2, y+2);
				g2dAdd();
				break;
				
			case INTRAFONT_ALIGN_RIGHT:
				g2dSetCoordXY(x-width, y + 2);
				g2dAdd();
				
				g2dSetCoordXY(x, y+2);
				g2dAdd();
				break;
				
			default:
				g2dSetCoordXY(x, y + 2);
				g2dAdd();
				
				g2dSetCoordXY(x+width, y+2);
				g2dAdd();
				break;
		}
	
	g2dEnd();
	
	return intraFontPrint(font, x, y, text);
}


float InversedText(int x, int y, intraFont *font, const char *text, float fontSize, float angle, g2dColor color, g2dColor shadowColor, int center)
{
    int i, size = strlen(text);
    char textInverse[size];
	
    for (i = size-1; i >= 0; i--)
        textInverse[size-i-1] = text[i];
	
    textInverse[size] = '\0';
	
	intraFontSetStyle(font, fontSize, color, shadowColor, angle, center);
   
	return intraFontPrint(font, x, y, textInverse);
}


float AlphaDegrade(int x, int y, intraFont *font, const char *text, g2dColor colorText, g2dColor colorMark, float size, float angle, int center, dMode side)
{
    colorMark = G2D_RGBA(G2D_GET_R(colorMark), G2D_GET_G(colorMark), G2D_GET_B(colorMark), 180);
    int i, y_Mark = y, x_Mark = x;
	
    for (i = 0; i < ALPHA_LONG_MARK; i++)    
	{
        switch(side)
        {
            case GRAD_UP: 
				y_Mark--; 
				break;
            case GRAD_DOWN: 
				y_Mark++; 
				break;
            case GRAD_LEFT: 
				x_Mark--; 
				break;
            case GRAD_RIGHT: 
				x_Mark++; 
				break;
            case GRAD_UP_LEFT: 
				x_Mark--; 
				y_Mark--; 
				break;
            case GRAD_UP_RIGHT: 
				x_Mark++; 
				y_Mark--;
				break;
            case GRAD_DOWN_LEFT:
				x_Mark--; 
				y_Mark++; 
				break;
            case GRAD_DOWN_RIGHT: 
				x_Mark++; 
				y_Mark++; 
				break;
            default: 
				break;
				
        }
		
		intraFontSetStyle(font, size, G2D_RGBA(G2D_GET_R(colorMark), G2D_GET_G(colorMark), G2D_GET_B(colorMark), G2D_GET_A(colorMark) - 2*i*ALPHA_LONG_MARK), 0, angle, center);
        intraFontPrint(font, x_Mark, y_Mark, text);
    }
	
	intraFontSetStyle(font, size, colorText, 0, angle, center);
    return intraFontPrint(font, x, y,text);
}


float ShadowedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorShadow, int center, char Intensity)
{
    colorShadow = G2D_RGBA(G2D_GET_R(colorShadow), G2D_GET_G(colorShadow), G2D_GET_B(colorShadow), Intensity);
	
	intraFontSetStyle(font, size, colorShadow, 0, angle, center);
	
	intraFontPrint(font, x+2, y+2, text);
	intraFontPrint(font, x+3, y+3, text);
	intraFontPrint(font, x+1, y+1, text);
	intraFontPrint(font, x+4, y+4, text);
	intraFontPrint(font, x+2, y+2, text);
	
	intraFontSetStyle(font, size, colorText, 0, angle, center);
    return intraFontPrint(font, x, y, text);
}


float ContouredText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorContour, int center)
{
    int i, j;
	
	intraFontSetStyle(font, size, colorContour, 0, angle, center);
	
    for (i = 0; i <= 2; i++)
    {
        for (j = 0; j <= 2; j++)
			intraFontPrint(font, x-i, y-j, text);
    }
	
	intraFontSetStyle(font, size, colorText, 0, angle, center);
    return intraFontPrint(font, x-1, y-1, text);
}

float BackgroundColorText(int x, int y, intraFont *font, const char *text, float size, g2dColor colorText, g2dColor colorBackground, int center)
{
    int width = intraFontMeasureText(font, text);

	g2dBeginRects(NULL);
		g2dSetColor(colorBackground);
		g2dSetCoordMode(G2D_UP_LEFT);
		g2dSetScaleWH(width+4, intraFontTextHeight(font, text) + 3);
	
		switch(center)
		{
			case INTRAFONT_ALIGN_LEFT:
				g2dSetCoordXY(x-2, y-intraFontTextHeight(font, text));
				break;
				
			case INTRAFONT_ALIGN_CENTER:
				g2dSetCoordXY(x - 2 - width/2, y-intraFontTextHeight(font, text));
				break;
				
			case INTRAFONT_ALIGN_RIGHT:
				g2dSetCoordXY(x-width-2, y-intraFontTextHeight(font, text));
				break;
				
			default:
				g2dSetCoordXY(x-2, y-intraFontTextHeight(font, text));
				break;
			}
	
		g2dAdd();
	g2dEnd();
	
	intraFontSetStyle(font, size, colorText, 0, 0.0f, center);
    return intraFontPrint(font, x, y, text);
}


float StrikedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorLine, int center)
{
	int width = intraFontMeasureText(font, text);
	int height = intraFontTextHeight(font, text);
	
	intraFontSetStyle(font, size, colorText, 0, 0.0f, center);
	
	g2dBeginLines(G2D_VOID);
		g2dSetColor(colorLine);
	
		switch(center)
		{
			case INTRAFONT_ALIGN_LEFT:
				g2dSetCoordXY(x, y-height/2);
				g2dAdd();
				
				g2dSetCoordXY(x+width, y-height/2);
				g2dAdd();
				break;
				
			case INTRAFONT_ALIGN_CENTER:
				g2dSetCoordXY(x - width/2, y-height/2);
				g2dAdd();
				
				g2dSetCoordXY(x+width/2, y-height/2);
				g2dAdd();
				break;
				
			case INTRAFONT_ALIGN_RIGHT:
				g2dSetCoordXY(x-width, y-height/2);
				g2dAdd();
				
				g2dSetCoordXY(x, y-height/2);
				g2dAdd();
				break;
				
			default:
				g2dSetCoordXY(x, y-height/2);
				g2dAdd();
				
				g2dSetCoordXY(x+width, y-height/2);
				g2dAdd();
				break;
		}
	
	g2dEnd();
	
	return intraFontPrint(font, x, y, text);
}

void GradientText(int x, int y, intraFont *font, const char *text, g2dColor colorBegin, g2dColor colorEnd, float size, float angle, int center)
{
    int i, textSize = strlen(text);
    int posX = x;
    int posY = y;
	
    int Rc =  (G2D_GET_R(colorEnd) - G2D_GET_R(colorBegin))/(textSize-1);
    int Gc =  (G2D_GET_G(colorEnd) - G2D_GET_G(colorBegin))/(textSize-1);
    int Bc =  (G2D_GET_B(colorEnd) - G2D_GET_B(colorBegin))/(textSize-1);
	
    g2dColor ColorJ = 0;
	char help[2] = {0};
	
	intraFontSetStyle(font, size, ColorJ, 0, angle, center);
	
    for(i = 0; i < textSize; i++)
    {
        ColorJ = G2D_RGBA(i * Rc+G2D_GET_R(colorBegin), i * Gc+G2D_GET_G(colorBegin), i * Bc+G2D_GET_B(colorBegin), 255);
		
        help[0] = text[i];
		
        intraFontPrint(font, posX, posY, help);
		
        posX += intraFontMeasureText(font, help);
    }
}

//EOF 
