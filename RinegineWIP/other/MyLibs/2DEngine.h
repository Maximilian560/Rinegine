#pragma once
#include "json.hpp"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <Windows.h>

using namespace sf;
using namespace std;
using json = nlohmann::json;
Font font;
int lang;

int tempint;
char tempchar;
float tempfloat;
double tempdounle;

float Timer = 0;

View view;

float editx = NULL, edity=NULL;
//int SizeFont = NULL;

int seed;
//class RenWin
//{
//	//RenderWindow window;(sf::VideoMode::getDesktopMode(), "Rinerest Alpha", Style::None);
//	int ww, wh;
//	string title;
//public:
//	RenderWindow window;
//	RenWin(int ww, int wh,string title = NULL)
//	{
//		window.setSize({ww,wh});
//		this->ww = ww;
//		this->wh = wh;
//		this->title = title;
//		if (title[0] != NULL)
//		{
//			window.setTitle(title);
//		}
//	}
//	bool draw(Sprite sp)
//	{
//		window.draw(sp);
//		return true;
//	}
//	bool draw(Vertex* ver, int angles, PrimitiveType type)
//	{
//		window.draw(ver, angles, type);
//		return true;
//	}
//	bool draw(Vertex* ver, int angles,PrimitiveType type, Texture *texture)
//	{
//		window.draw(ver, angles, type, texture);	
//		return true;
//	}
//	bool update()
//	{
//		window.display();
//		return true;
//	}
//	
//};

bool engine()
{
	//RenderWindow 
	RenderWindow window(sf::VideoMode::getDesktopMode(), "Rinerest Alpha", Style::None);
	//RenderWindow window(VideoMode(1366,767), "Rinerest Alpha", Style::None); //ÒÎËÜÊÎ ÄËß ÄÅÁÀÃÀ!!!!



	float ww = window.getSize().x, wh = window.getSize().y;

	float editx = ww / 1366, edity = ww / 768;
	int SizeFont = floor(24.0 * 1.0 * editx);

	Event event;
	Clock clocks;

	

	int fps = 1000;
	return true;
}

int SizeFont = floor(24.0 * 1.0 * editx);

Event event;
Clock clocks;



int fps = 1000;


const string Fimages = "images/";
const string Fentity = "entity/";
const string Fgui = "gui/";
const string Fworld = "world/";
const string Fother = "other/";

class Tile
{
public:

	Image Itile;
	Texture Ttile;
	Sprite Stile;
	Tile(string file)
	{
		//if(!jpg)
		Itile.loadFromFile(Fimages+Fworld+file);
		Ttile.loadFromImage(Itile);
		Stile.setTexture(Ttile);
	}

};

class SimpleSprite
{
public:
	Image ISSprite;
	Texture TSSprite;
	Sprite SSSPrite;
	SimpleSprite(string folder)
	{
		ISSprite.loadFromFile(Fimages+Fgui+folder);
		TSSprite.loadFromImage(ISSprite);
		SSSPrite.setTexture(TSSprite);
	}
	void Resize(float x, float y)
	{
		SSSPrite.setScale(Vector2f(x, y));
	}
	void Replace(float x, float y)
	{
		SSSPrite.setPosition(x, y);
	}
};


class ButtonGui
{
public:
	Image Ibut;
	Texture Tbut;
	Sprite Sbut;
	ButtonGui(string gui)
	{

		Ibut.loadFromFile(Fimages + Fgui + gui + ".png");
		Tbut.loadFromImage(Ibut);
		Sbut.setTexture(Tbut);
	}

	void SetPosition(float xbutton = 0, float ybutton = 0)
	{
		Sbut.setPosition(xbutton, ybutton);
	}

	void SetScale(float x=0, float y=0)
	{
		Sbut.setScale(x, y);
	}


};

class Text_
{
public:
	Text text;
	Text_(sf::String tex="", int Sizefont = SizeFont)
	{
		font.loadFromFile(Fimages + Fother + "Font.ttf");
		Text text2(tex, font, Sizefont);
		text = text2;
		
	}

	void SetPosition(float x, float y)
	{
		text.setPosition(x, y);
	}

	void SetSize(float x, float y)
	{
		text.setScale(x, y);
	}

	void SetStyle(bool bold = false,bool underlined = false)
	{
		if(bold)
			text.setStyle(Text::Bold);
		if(underlined)
			text.setStyle(Text::Underlined);
	}

	void SetCollor(Color col=Color::Black)
	{
		text.setFillColor(col);
	}
	void SetText(String Text)
	{
		text.setString(Text);
	}

};

class Tumbler
{
public:
	Sprite STumbler;
	Sprite SOn;
	Sprite SOff;
	Texture TTumbler;
	Texture TOn;
	Texture TOff;
	Image ITumbler;
	Image IOn;
	Image IOff;
	bool turn = false;
	Tumbler(String tumbler, String on, String off)
	{	
		ITumbler.loadFromFile(Fimages + Fgui + tumbler + ".png");
		TTumbler.loadFromImage(ITumbler);
		STumbler.setTexture(TTumbler);
	
		IOff.loadFromFile(Fimages + Fgui + off + ".png");
		TOff.loadFromImage(IOff);
		SOff.setTexture(TOff);
	
		IOn.loadFromFile(Fimages + Fgui + on + ".png");
		TOn.loadFromImage(IOn);
		SOn.setTexture(TOn);	
	}
	void SetScale(float x, float y)
	{
		STumbler.setScale(x, y);
		SOn.setScale(x, y);
		SOff.setScale(x, y);
	}
	void SetPos(float x, float y)
	{	
		STumbler.setPosition(Vector2f(x,y));
		SOn.setPosition((Vector2f(x, y)));
		SOff.setPosition((Vector2f(x+STumbler.getTextureRect().width-SOff.getTextureRect().width, y)));
	}
	void draw(RenderWindow *window)
	{
		window->draw(STumbler);
		if (turn)window->draw(SOn);
		else window->draw(SOff);
	}
	void on()
	{
		turn = true;
	}
	void off()
	{
		turn = false;
	}
	bool clik()
	{
		float sonx = SOn.getPosition().x;
		float sony = SOn.getPosition().y;

		float soffx = SOff.getPosition().x;
		float soffy = SOff.getPosition().y;
		if (turn)
		{
			
			//for (int i = 0; i < 20; i++)
			////while (SOn.getPosition().x < STumbler.getPosition().x + STumbler.getTextureRect().width - SOff.getTextureRect().width)
			//{
			//	SOn.move(1, 0);
			//	window.draw(SOn);
			//	window.display();
			//}
			SOn.setPosition(sonx, sony);
			turn = false;
			return turn;
		}
		if (!turn)
		{
			
			//for (int i = 0; i < 20; i++)
			////while (SOff.getPosition().x > STumbler.getPosition().x)
			//{
			//	SOff.move(-1, 0);
			//	window.draw(SOff);
			//	window.display();
			//}
			SOff.setPosition(soffx , soffy);
			turn = true;
			return turn;
		}
	}
};



class Object
{
public:
	int frame,rect;
	int ti=0;
	bool anim = false;
	Image Iobject;
	Texture Tobject;
	Sprite Sobject;
	Object(string file,bool Anim,int Rect, int Frame)
	{
		rect = Rect;
		frame = Frame;
		anim = Anim;
		Iobject.loadFromFile(Fimages+file);
		Tobject.loadFromImage(Iobject);
		Sobject.setTexture(Tobject);
		if (anim)
		{
			Sobject.setTextureRect(IntRect(0,0,rect,rect));
		}

	}
	void SetPos(float x, float y)
	{
		Sobject.setPosition(x, y);
	}
	void SetScale(float x, float y)
	{
		Sobject.setScale(x, y);
	}
	bool animacion()
	{
		if (!anim)
			return false;
		ti++;
		if (ti > frame * 20)
			ti = 0;
		Sobject.setTextureRect(IntRect(0 + (floor(ti / 20.0) * rect), 0, rect + (floor(ti / 20.0) * rect), rect));
		
	}

};

bool EXIT(RenderWindow *window)
{
	window->close();
	return true;
}

void error_window(RenderWindow* window,string ec)
{
	RenderWindow errorwindow(sf::VideoMode(350,100), "ERROR_WINDOW", Style::Default);

	bool play = true;
	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	Text text;
	text.setFont(font);
	text.setScale(3,3);
	//text.setColor
	text.setFillColor(Color(255,0,0));
	//string EC = "ERROR " .. to_string(ec);

	text.setString(ec);
	Event event;
	while (play)
	{
		while (errorwindow.pollEvent(event))
		{
			if (event.type == Event::Closed) { EXIT(window); errorwindow.close(); play = false; }
		}
		errorwindow.clear(Color(0,0,0));
		errorwindow.draw(text);
		errorwindow.display();
		


	}
}

// new

struct stobj
{
	Texture tex;
	int size;
	Vertex* obj = NULL;
	float posx = 0;
	float posy = 0;
	float sizex = 0;
	float sizey = 0;
	int angle = 0;
	float scale = 1;
	Color Col1 = Color(255, 255, 255, 255);
	Color Col2 = Color(255, 255, 255, 255);

};

class myobj
{
public:
	stobj st;
	//Texture tex;
	//Vertex* obj = (Vertex*) calloc(5,sizeof(Vertex));
	/*float posx =0, posy = 0;
	float sizex = 0, sizey = 0;
	int angle = 0;
	float scale = 1;*/

	myobj(string path = "")
	{
		//st.obj = (Vertex*)calloc(5,sizeof(Vertex));
		do {
			st.obj = (Vertex*)calloc(6, sizeof(Vertex));
		} while (!st.obj);
		st.size = 6;
		if (path != "")
			st.tex.loadFromFile(path);
		//st.tex.setSmooth(true);
		//posx = tex.getSize().x;
		//posy = tex.getSize().y;
		st.sizex = st.tex.getSize().x;
		st.sizey = st.tex.getSize().y;
		st.obj[0] = Vertex(Vector2f(st.posx, st.posy), st.Col1, Vector2f(st.posx, st.posy));
		st.obj[1] = Vertex(Vector2f(st.posx + st.sizex, st.posy), st.Col1, Vector2f(st.posx + st.sizex, st.posy));
		st.obj[2] = Vertex(Vector2f(st.posx + st.sizex, st.posy + st.sizey), st.Col1, Vector2f(st.posx + st.sizex, st.posy + st.sizey));
		st.obj[3] = Vertex(Vector2f(st.posx + st.sizex, st.posy + st.sizey), st.Col1, Vector2f(st.posx + st.sizex, st.posy + st.sizey));
		st.obj[4] = Vertex(Vector2f(st.posx, st.posy + st.sizey), st.Col1, Vector2f(st.posx, st.posy + st.sizey));
		st.obj[5] = Vertex(Vector2f(st.posx, st.posy), st.Col1, Vector2f(st.posx, st.posy));
	}
	void setPosition(float x, float y)
	{
		st.posx += x;
		st.posy += y;


		st.obj[0].position = Vector2f(st.posx, st.posy);
		st.obj[1].position = Vector2f(st.posx + st.sizex, st.posy);
		st.obj[2].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[3].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[4].position = Vector2f(st.posx, st.posy + st.sizey);
		st.obj[5].position = Vector2f(st.posx, st.posy);

	}
	void setScale(float Scale)
	{
		st.scale = Scale;
		st.sizex *= st.scale;
		st.sizey *= st.scale;

		st.obj[0].position = Vector2f(st.posx, st.posy);
		st.obj[1].position = Vector2f(st.posx + st.sizex, st.posy);
		st.obj[2].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[3].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[4].position = Vector2f(st.posx, st.posy + st.sizey);
		st.obj[5].position = Vector2f(st.posx, st.posy);
	}
	void setSize(float sizex, float sizey)
	{
		//st.scale = Scale;
		st.sizex = sizex;
		st.sizey = sizey;

		st.obj[0].position = Vector2f(st.posx, st.posy);
		st.obj[1].position = Vector2f(st.posx + st.sizex, st.posy);
		st.obj[2].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[3].position = Vector2f(st.posx + st.sizex, st.posy + st.sizey);
		st.obj[4].position = Vector2f(st.posx, st.posy + st.sizey);
		st.obj[5].position = Vector2f(st.posx, st.posy);
	}
	Vector2f getPixelSize()
	{
		return Vector2f(st.sizex, st.sizey);
	}
	void setTexCoords(Vector2f pos, Vector2f size)
	{
		st.obj[0].texCoords = Vector2f(pos.x, pos.y);
		st.obj[0].texCoords = Vector2f(pos.x + size.x, pos.y);
		st.obj[0].texCoords = Vector2f(pos.x + size.x, pos.y + size.y);
		st.obj[0].texCoords = Vector2f(pos.x + size.x, pos.y + size.y);
		st.obj[0].texCoords = Vector2f(pos.x, pos.y + size.y);
		st.obj[0].texCoords = Vector2f(pos.x, pos.y);

	}
	void gradient(char type, Color col1, Color col2) // \ | / - 
	{
		st.Col1 = col1;
		st.Col2 = col2;
		if (type == '|')
		{

			st.obj[0].color = col1;
			st.obj[1].color = col1;
			st.obj[2].color = col2;
			st.obj[3].color = col2;
			st.obj[4].color = col2;
			st.obj[5].color = col1;
		}
		else if (type == '-')
		{
			st.obj[0].color = col1;
			st.obj[1].color = col2;
			st.obj[2].color = col2;
			st.obj[3].color = col2;
			st.obj[4].color = col1;
			st.obj[5].color = col1;
		}
	}
	Texture* getTex()
	{
		return &st.tex;
	}
	Vertex* getObj()
	{
		return st.obj;
	}
	void setColor(Color color)
	{
		st.Col1 = color;
		st.obj[0].color = (st.Col1);
		st.obj[1].color = (st.Col1);
		st.obj[2].color = (st.Col1);
		st.obj[3].color = (st.Col1);
		st.obj[4].color = (st.Col1);
		st.obj[5].color = (st.Col1);
	}
	stobj getForArr(void)
	{
		return st;
	}
	void Free(void)
	{
		free(&st.obj[0]);
		//free(&st);
	}

};

class arrobj
{
public:
	Vertex* objs = NULL, * tempver = NULL;
	stobj* st = NULL, * tempstobj = NULL;

	arrobj(void)
	{
		do
		{
			objs = (Vertex*)calloc(1, sizeof(Vertex));
		} while (objs = NULL);
	}


	int addbefore = 0;
	bool add(myobj adding)
	{
		addbefore++;
		do
		{
			tempver = (Vertex*)realloc(objs, 6 * addbefore * sizeof(Vertex));
		} while (!tempver);

		objs = tempver;//(Vertex*)realloc(objs, 6 * addbefore * sizeof(Vertex));

		do
		{
			tempstobj = (stobj*)realloc(st, addbefore * sizeof(stobj));
		} while (!tempstobj);

		st = tempstobj;


		st[addbefore - 1] = adding.getForArr();
		for (int i = 0; i < 6; i++)
		{
			objs[i + (6 * (addbefore - 1))] = st[addbefore - 1].obj[i];
		}

		return true;
	}
	Texture* getTex()
	{
		return &st[addbefore - 1].tex;
	}
	void Free(void)
	{
		free(&st[0]);
		free(&objs[0]);
	}
};

