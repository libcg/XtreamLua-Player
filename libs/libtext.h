/*
 *                  LIBTEXT v0.2
 * libtext.h
 * Cette lib est un add-on de la libGE de dridri85. Elle permet de personnaliser vos textes.
 * libText est une lib de JiiCeii, membre d'XtreamLua.com.
 *
 * Je tiens à Remercier La Communauté D'XtreamLua.com, Ainsi qu'à dridri85 pour sa lib.
 *
 * JiiCeii_l@hotmail.fr
 *
 * Faites moi part de vos idées et avis à :
 *     Jean-Christophe le Floch
 *
 *  Librairie portée sur le XtreamLua Player par FlavR, mais tout le crédit revient à JiiCeii.
 *
 */


#ifndef __LIBTEXT_H__
#define __LIBTEXT_H__

#include "common.h"

#include <math.h>

#define SCREEN_W        480
#define SCREEN_H        272

#define ALPHA_LONG_MARK 10

typedef enum degrade_mode dMode;
enum degrade_mode {
	GRAD_UP, GRAD_DOWN, GRAD_LEFT, GRAD_RIGHT, GRAD_UP_LEFT, GRAD_UP_RIGHT, GRAD_DOWN_LEFT, GRAD_DOWN_RIGHT
};


/***** UnderLinedText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 texte : Texte à afficher.
 colorText : La couleur du Texte
 colorLine : La couleur du soulignement
 
 *****/
float UnderLinedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorLine, int center);


/***** StrikedText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 texte : Texte à afficher.
 colorText : La couleur du Texte
 colorLine : La couleur de la ligne
 
 *****/
float StrikedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorLine, int center);


/***** InversedText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 text : Texte à afficher.
 color : La couleur du Texte
 
 *****/
float InversedText(int x, int y, intraFont *font, const char *text, float fontSize, float angle, g2dColor color, g2dColor shadowColor, int center);


/***** AlphaDegrade
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 text : Texte à afficher.
 colorText : La couleur du Texte
 colorMark : La couleur de la marque
 mode :
 le type de marque (allant de 1 à 8).
 UP
 DOWN
 LEFT
 RIGHT
 UP_LEFT
 UP_RIGHT
 DOWN_LEFT
 DOWN_RIGHT
 
 *****/
float AlphaDegrade(int x, int y, intraFont *font, const char *text, g2dColor colorText, g2dColor colorMark, float size, float angle, int center, dMode side);


/***** ShadowedText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 text : Texte à afficher.
 colorText : La couleur du Texte
 colorShadow : La couleur de l'ombre
 Intensity : l'intensité de l'ombre. (pour un meilleur résultat, mettez entre 1 et 30)
 
 *****/
float ShadowedText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorShadow, int center, char Intensity);


/***** ContouredText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 text : Texte à afficher.
 colorText : La couleur du Texte
 colorContour : la couleur du contour
 
 *****/
float ContouredText(int x, int y, intraFont *font, const char *text, float size, float angle, g2dColor colorText, g2dColor colorContour, int center);


/***** BackgroundColorText
 
 x : position en X du texte.
 y : position en Y du texte.
 font : la police du texte.
 text : Texte à afficher.
 colorText : La couleur du Texte
 colorBackground : la couleur du fond
 
 *****/
float BackgroundColorText(int x, int y, intraFont *font, const char *text, float size, g2dColor colorText, g2dColor colorBackground, int center);

#endif

//EOF
