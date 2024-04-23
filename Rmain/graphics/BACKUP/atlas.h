#pragma once

// Определение структуры для хранения текстур атласа
struct AtlasTexture
{
	RG_Matrix<uint8> texture; // Матрица текстуры
	POINT2D<int>size; // Размер текстуры
	POINT2D<int>pos; // Позиция текстуры в атласе
	int cnt = 4; // Количество каналов в текстуре

	// Перегрузка оператора присваивания для копирования текстур
	void operator=(AtlasTexture& a)
	{
		size = a.size;
		texture = a.texture;
		pos = a.pos;
		cnt = a.cnt;
	}
};

// Массив для хранения текстур атласа
RG_Array<AtlasTexture> RG_AtlasArrayTextures;

// Определение структуры атласа
struct Atlas
{
	RG_Matrix<uint8> textureRaw; // Сырая текстура атласа
	uint texture; // Идентификатор текстуры OpenGL
	uint textureMsaa; // Идентификатор текстуры MSAA
	POINT2D<uint> size; // Размер атласа
}RG_StandartAtlas; // Стандартный атлас

// Флаг состояния текстуры
bool RG_TEXTURE_BOOL = false;

// Включение текстуры
void rgTextureOn()
{
	rgEnableClientState(RG_TEXTURE_COORD_ARRAY);
	rgBindTexture(RG_StandartAtlas.texture);
}

// Выключение текстуры
void rgTextureOff()
{
	rgDisableClientState(RG_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	rgBindTexture(0);
}

// Подготовка атласа: распределение текстур и создание атласа
void RG_PreparationAtlas(RG_Array<AtlasTexture> &texs = RG_AtlasArrayTextures, Atlas &atl = RG_StandartAtlas)
{
	POINT2D<uint>pen = {0,0}; // Текущая позиция курсора
	POINT2D<uint>size = {1024<<4,1024<<4}; // Размер атласа
	cout<<size.x<<endl;
	atl.size = size;
	uint8 cnt = 4; // Количество каналов

	atl.textureRaw.resize(size.x*cnt,size.y); // Изменение размера сырой текстуры атласа

	uint beforex = 0;
	uint maxy = 0;

	// Распределение текстур в атласе
	RG_FOR_CYCLEi(texs.size())
	{
		AtlasTexture &texture = texs[i];
	  
		// Проверка на переполнение строки и переход на новую
		if(pen.x + texture.size.x > size.x*cnt){
			pen.x = 0;
			pen.y += maxy+2;
			maxy = 0;
		}

		// Копирование текстуры в атлас
		RG_FOR_CYCLEy(texture.size.y)
		{
			RG_FOR_CYCLEx(texture.size.x)
			{
				// Расчет позиции и копирование пикселей
				uint tx = pen.x+x*cnt;
				uint ty = pen.y+y;
				
				// Копирование пикселей текстуры в атлас
				for(int k = 0; k < cnt; ++k) {
					atl.textureRaw[ty*size.x*cnt+tx+k] = texture.texture[y * texture.size.x*cnt+ x*cnt+k];
				}

				// Добавление границ для предотвращения артефактов
				// (продублировано для всех сторон текстуры)
			}
		}

		texture.pos.x = pen.x/cnt;
		texture.pos.y = pen.y/cnt;
		
		pen.x+=texture.size.x*cnt+2*cnt;
		maxy = rg_max(maxy,texture.size.y);
	}

	// Создание OpenGL текстуры из сырой текстуры атласа
	glGenTextures(1,&atl.texture);
	glBindTexture(GL_TEXTURE_2D, atl.texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atl.size.x, atl.size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, atl.textureRaw.get_mat());
}

// Загрузка текстуры и добавление в атлас
uint RG_LoadTexture(string &path)
{
	RG_AtlasArrayTextures.append();
	uint8*temp = nullptr;
	if((temp = stbi_load(path.c_str(),&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size.x,&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size.y,&RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].cnt,0))==nullptr)
		throw RG_ERROR_LOAD_TEXTURE;

	RG_Matrix<uint8>& texture = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].texture;
	POINT2D<int>&size = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].size;
	int &cnt = RG_AtlasArrayTextures[RG_AtlasArrayTextures.size()-1].cnt;
	texture.resize(size.x * 4, size.y);

	// Преобразование текстуры в формат RGBA, если необходимо
	if(cnt<4){
		if(cnt==3){
			for(int j = 0; j<size.y;j++){
				for(int i = 0; i<size.x;i++){
					// Конвертация из RGB в RGBA
					for(int k = 0; k < 3; ++k) {
						texture.get((i*4)+k,j) = temp[((j*size.x*3 ) + (i*3)) + k];
					}
					texture.get((i*4)+3,j) = 255; // Установка альфа-канала в максимальное значение
				}
			}
			cnt = 4;
		}else{exit(12873689);}
	}else{
		// Если текстура уже в формате RGBA, копирование без изменений
		for(int j = 0; j<size.y;j++){
			for(int i = 0; i<size.x;i++){
				for(int k = 0; k < 4; ++k) {
					texture.get((i*4)+k,j) = temp[((j*size.x*4 ) + (i*4)) + k];
				}
			}
		}
	}

	return RG_AtlasArrayTextures.size()-1;
}

// Комментарии сгенерированы GPT-4
